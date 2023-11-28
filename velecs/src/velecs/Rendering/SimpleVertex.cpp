/// @file    SimpleVertex.cpp
/// @author  Matthew Green
/// @date    2023-11-26 14:05:00
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/Rendering/SimpleVertex.h"
#include "velecs/Rendering/VertexInputAttributeDescriptor.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

SimpleVertex::SimpleVertex(const glm::vec3 position)
    : position(position) {}

SimpleVertex::SimpleVertex(const float x, const float y, const float z)
    : position(glm::vec3(x, y, z)) {}

// Public Methods

VertexInputAttributeDescriptor SimpleVertex::GetVertexDescription()
{
    VertexInputAttributeDescriptor description;

    //we will have just 1 vertex buffer binding, with a per-vertex rate
    VkVertexInputBindingDescription mainBinding = {};
    mainBinding.binding = 0;
    mainBinding.stride = sizeof(SimpleVertex);
    mainBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    description.bindings.push_back(mainBinding);

    //Position will be stored at Location 0
    VkVertexInputAttributeDescription positionAttribute = {};
    positionAttribute.binding = 0;
    positionAttribute.location = 0;
    positionAttribute.format = VK_FORMAT_R32G32B32_SFLOAT;
    positionAttribute.offset = offsetof(SimpleVertex, position);

    description.attributes.push_back(positionAttribute);
    return description;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
