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

#include <glm/gtc/matrix_transform.hpp>

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

const Vec3 Transform::GetAbsPosition() const
{
    Vec3 absPosition = position;
    const Transform* currentTransform = this;

    while (currentTransform->TryGetParentTransform(currentTransform))
    {
        absPosition -= currentTransform->position; // Accumulate the position
    }

    return absPosition;
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

const Camera* const Transform::GetCamera() const
{
    flecs::entity cameraEntity = GetCameraEntity();

    const Camera* const camera = cameraEntity.get<Camera>();

    return camera;
}

Camera* const Transform::GetCamera()
{
    flecs::entity cameraEntity = GetCameraEntity();

    Camera* const camera = cameraEntity.get_mut<Camera>();

    return camera;
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

glm::mat4 Transform::GetModelMatrix(const bool useScale /* = true*/) const
{
    glm::mat4 model = glm::mat4(1.0f); 

    // Apply scaling
    if (useScale)
    {
        model = glm::scale(model, (glm::vec3)scale);
    }

    // Apply rotation around the x, y, and z axes
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

    glm::mat4 worldTranslation = glm::translate(glm::mat4(1.0f), (glm::vec3)GetAbsPosition());

    return worldTranslation * model;
}

glm::mat4 Transform::GetRenderMatrix(const Transform* const cameraTransform, const PerspectiveCamera* const perspectiveCamera) const
{
    // Compute the view matrix
    glm::mat4 view = cameraTransform->GetModelMatrix(false);

    // Compute the projection matrix
    glm::mat4 projection = perspectiveCamera->GetProjectionMatrix();

    // Compute the model matrix
    glm::mat4 model = GetModelMatrix();

    return projection * view * model;
}

glm::mat4 Transform::GetRenderMatrix(const Transform* const cameraTransform, const OrthoCamera* const orthoCamera) const
{
    // Compute the view matrix
    glm::mat4 view = cameraTransform->GetModelMatrix(false);

    // Compute the projection matrix
    glm::mat4 projection = orthoCamera->GetProjectionMatrix();

    // Compute the model matrix
    glm::mat4 model = GetModelMatrix();

    // Calculate the final mesh matrix
    glm::mat4 meshMatrix = projection * view * model;

    return meshMatrix;
}

const Vec2 Transform::GetScreenPosition(const Transform* const cameraTransform, const PerspectiveCamera* const perspectiveCamera) const
{
    // Get the view matrix from the camera
    glm::mat4 viewMatrix = cameraTransform->GetModelMatrix(false);

    // Get the projection matrix from the camera
    glm::mat4 projectionMatrix = perspectiveCamera->GetProjectionMatrix();

    // Transform the world position to camera space
    glm::vec4 cameraSpacePos = glm::inverse(viewMatrix) * glm::vec4((glm::vec3)this->GetAbsPosition(), 1.0f);

    // Transform the camera space position to clip space
    glm::vec4 clipSpacePos = projectionMatrix * cameraSpacePos;

    // Perform perspective division to get Normalized Device Coordinates (NDC)
    glm::vec3 ndcSpacePos = glm::vec3(clipSpacePos) / clipSpacePos.w;

    // Map from NDC space [-1, 1] to screen space [0, resolution]
    Vec2 screenPos;
    screenPos.x = (ndcSpacePos.x + 1) * 0.5f * perspectiveCamera->GetResolution().x;
    screenPos.y = (1 - ndcSpacePos.y) * 0.5f * perspectiveCamera->GetResolution().y; // Y is inverted

    return screenPos;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
