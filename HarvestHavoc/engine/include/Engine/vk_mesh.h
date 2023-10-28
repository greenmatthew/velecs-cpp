/// \file    vk_mesh.h
/// \author  Matthew Green
/// \date    10/26/2023 14:18:31
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Engine/vk_types.h"

#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Math/Vec2.h"
#include "Graphics/Color32.h"

namespace engine {

struct VertexInputDescription {

    std::vector<VkVertexInputBindingDescription> bindings;
    std::vector<VkVertexInputAttributeDescription> attributes;

    VkPipelineVertexInputStateCreateFlags flags = 0;
};

struct Vertex {

    glm::vec3 position;
    glm::vec3 normal;
    Color32 color{Color32::MAGENTA};

    static VertexInputDescription GetVertexDescription();
};

struct Mesh {

    std::vector<Vertex> _vertices;

    AllocatedBuffer _vertexBuffer;
};

struct Vertex2D {

    Vec2 position;
    Color32 color;

    static VertexInputDescription GetVertexDescription();
};

struct Mesh2D {

    std::vector<Vertex2D> _vertices;

    AllocatedBuffer _vertexBuffer;
};

} // namespace engine
