#include <vector>

#include "Math/Consts.h"
#include "Math/Vec2.h"
#include "Engine/vk_engine.h"

#include "Engine/vk_types.h"
#include "Engine/vk_mesh.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Math/Vec3.h"
#include "ECS/Transform.h"
#include "ECS/Entity.h"
#include "ECS/Component.h"

using namespace engine;

struct Rect {
public:
    engine::Vec2 min;
    engine::Vec2 max;

    Rect(const engine::Vec2 min, const engine::Vec2 max)
        : min(min), max(max) {}
    
    Rect(const float left, const float bottom, const float right, const float top)
        : min({left, bottom}), max({right, top}) {}
};

struct Camera : public Component {
private:
    static Camera* mainCamera;
    static VkExtent2D vkExtent;

    Rect extent;
protected:
    Camera(Entity* entity)
        : Component(entity), extent({0.0f, vkExtent.width, 0.0f, vkExtent.height})
    {
        if (!mainCamera)
        {
            mainCamera = this;
        }
    }
public:
    static Camera* GetMainCamera()
    {
        return mainCamera;
    }

    const Rect& GetExtent() const
    {
        return extent;
    }
};

struct Mesh {
public:
    friend class VulkanEngine;

    std::vector<Vertex> vertices;
private:
    MeshRenderer* meshRenderer;

    glm::mat4 GetRenderMatrix()
    {
        Camera* camera = Camera::GetMainCamera();
        Transform camTransform = camera->GetTransform();
        glm::vec3 camPos = camTransform.position;
        glm::vec3 camRot = camTransform.rotation;
        Rect camExtent = camera->GetExtent();

        Transform modelTransform = GetTransform();
        glm::vec3 modelPos = modelTransform.position;
        glm::vec3 modelRot = modelTransform.rotation;
        glm::vec3 modelScale = modelTransform.scale;

        // Create the view matrix
        glm::mat4 view = glm::translate(glm::mat4(1.0f), -camPos);  // Note: typically the camera position is negated
        view = glm::rotate(view, glm::radians(camRot.x), glm::vec3(1, 0, 0));
        view = glm::rotate(view, glm::radians(camRot.y), glm::vec3(0, 1, 0));
        view = glm::rotate(view, glm::radians(camRot.z), glm::vec3(0, 0, 1));

        // Create the projection matrix
        glm::mat4 projection = glm::ortho(camExtent.min.x, camExtent.max.x, camExtent.min.y, camExtent.max.y, -1.0f, 1.0f);  // Adjust these values as needed

        // Create the model matrix
        glm::mat4 model = glm::mat4(1.0f);  // Initialize to identity matrix
        model = glm::translate(model, modelPos);  // Assuming you have a modelPosition variable
        model = glm::rotate(model, glm::radians(modelRot.x), glm::vec3(1, 0, 0));  // Assuming you have a modelRotation variable
        model = glm::rotate(model, glm::radians(modelRot.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(modelRot.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, modelScale);  // Assuming you have a modelScale variable

        // Compute the final matrix
        glm::mat4 meshMatrix = projection * view * model;

        return meshMatrix;
    }
public:
    Transform& GetTransform()
    {
        return meshRenderer->GetTransform();
    }
};

struct Material {
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    VkVertexInputAttributeDescription vertexInputAttributeDescriptor;
};

struct MeshRenderer : public Component {
public:
    Mesh mesh;
    Material material;
};