/// @file    Transform.cpp
/// @author  Matthew Green
/// @date    2023-11-16 15:50:08
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Components/Rendering/Transform.h"

#include "velecs/Math/Vec2.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  // For transformation functions

#include "velecs/Math/GLMUtility.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

Transform::Transform(flecs::entity entity, Vec3 position /* = Vec3::ZERO */, Vec3 rotation /* = Vec3::ZERO */, Vec3 scale /* = Vec3::ONE */)
    : entity(entity), position(position), rotation(rotation), scale(scale) {}

// Public Methods

flecs::entity Transform::GetParent() const
{
    if (entity == flecs::entity::null())
    {
        throw std::runtime_error("Transform's entity handle was never set.");
    }

    return entity.parent();
}

bool Transform::TryGetParent(flecs::entity& parentEntity) const
{
    parentEntity = flecs::entity::null();
    try
    {
        parentEntity = GetParent();
    }
    catch (std::exception e)
    {
        return false;
    }
    return true;
}

const Transform* const Transform::GetParentTransform() const
{
    flecs::entity parent = GetParent();
    if (parent == flecs::entity::null())
    {
        throw std::runtime_error("Transform's entity does not have a parent.");
    }
    return parent.get<Transform>();
}

bool Transform::TryGetParentTransform(const Transform*& transform) const
{
    transform = nullptr;

    flecs::entity parent;
    if (!TryGetParent(parent))
    {
        return false;
    }

    transform = parent.get<Transform>();
    if (transform == nullptr)
    {
        return false;
    }

    return true;
}

flecs::entity Transform::GetCameraEntity() const
{
    const MainCamera * const mainCamera = entity.world().get<MainCamera>();
    if (!mainCamera)
    {
        throw std::runtime_error("flecs::world is missing a MainCamera component.");
    }

    flecs::entity cameraEntity = mainCamera->camera;
    if (cameraEntity == flecs::entity::null())
    {
        throw std::runtime_error("MainCamera component was uninitialized while trying to access the camera field.");
    }

    return cameraEntity;
}

const Transform* const Transform::GetCameraTransform() const
{
    flecs::entity cameraEntity = GetCameraEntity();

    const Transform* const transform = cameraEntity.get<Transform>();

    return transform;
}

Transform* const Transform::GetCameraTransform()
{
    flecs::entity cameraEntity = GetCameraEntity();

    Transform* const transform = cameraEntity.get_mut<Transform>();

    return transform;
}

const Vec3 Transform::GetAbsPosition() const
{
    glm::mat4 world = GetWorldMatrix();
    glm::vec4 posV4 = world * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    return Vec3(posV4.x, posV4.y, posV4.z);
}

Vec3 Transform::GetForwardVector() const
{
    // Assuming rotation.x = pitch, rotation.y = yaw, rotation.z = roll
    // For a camera facing along the negative Z-axis by default
    float yaw = glm::radians(rotation.y);
    float pitch = glm::radians(rotation.x);

    Vec3 forward
    {
        sin(yaw) * cos(pitch),
        -sin(pitch), // Negative because Y is down in Vulkan
        -cos(yaw) * cos(pitch)
    };

    return forward.Normalize();
}

glm::mat4 Transform::GetWorldMatrix() const
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale));

    glm::mat4 localTransformation = translationMatrix * rotationMatrix * scaleMatrix;

    const Transform* parentTransform;
    if (TryGetParentTransform(parentTransform))
    {
        return parentTransform->GetWorldMatrix() * localTransformation;
    }
    else
    {
        return localTransformation;
    }
}

glm::mat4 Transform::GetWorldMatrixNoScale() const
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

    glm::mat4 localTransformation = translationMatrix * rotationMatrix;

    const Transform* parentTransform;
    if (TryGetParentTransform(parentTransform))
    {
        return parentTransform->GetWorldMatrixNoScale() * localTransformation;
    }
    else
    {
        return localTransformation;
    }
}

glm::mat4 Transform::GetViewMatrix() const
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 localTransform  = translationMatrix * rotationMatrix;

    const Transform* parentTransform;
    if (TryGetParentTransform(parentTransform))
    {
        return glm::inverse(parentTransform->GetWorldMatrixNoScale() * localTransform);
    }
    else
    {
        return glm::inverse(localTransform);
    } 
}

glm::mat4 Transform::GetRenderMatrix(const Transform* const cameraTransform, const PerspectiveCamera* const perspectiveCamera) const
{
    glm::mat4 projection = perspectiveCamera->GetProjectionMatrix();

    glm::mat4 view = cameraTransform->GetViewMatrix();

    glm::mat4 world = GetWorldMatrix();

    glm::mat4 render = projection * view * world;

    return render;
}

glm::mat4 Transform::GetRenderMatrix(const Transform* const cameraTransform, const OrthoCamera* const orthoCamera) const
{
    // Compute the view matrix
    glm::mat4 view = cameraTransform->GetViewMatrix();

    // Compute the projection matrix
    glm::mat4 projection = orthoCamera->GetProjectionMatrix();

    // Compute the model matrix
    glm::mat4 world = GetWorldMatrix();

    return projection * view * world;
}

const Vec2 Transform::GetScreenPosition(const Transform* const cameraTransform, const PerspectiveCamera* const perspectiveCamera) const
{
    // Local space to world space
    glm::vec4 worldSpacePos = GetWorldMatrixNoScale() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // World space to camera (view) space
    glm::mat4 viewMatrix = cameraTransform->GetViewMatrix();
    glm::vec4 cameraSpacePos = viewMatrix * worldSpacePos;

    // Camera space to clip space
    glm::mat4 projectionMatrix = perspectiveCamera->GetProjectionMatrix();
    glm::vec4 clipSpacePos = projectionMatrix * cameraSpacePos;

    // Perspective division to get NDC
    glm::vec3 ndcSpacePos = glm::vec3(clipSpacePos) / clipSpacePos.w;

    
    Vec2 resolution = entity.world().get<MainCamera>()->extent.max;

    // NDC to screen space
    Vec2 screenPos;
    screenPos.x = (ndcSpacePos.x + 1) * 0.5f * resolution.x;
    screenPos.y = (ndcSpacePos.y + 1) * 0.5f * resolution.y;  // Corrected for Vulkan's NDC

    return screenPos;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
