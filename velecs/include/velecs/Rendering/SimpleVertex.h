/// @file    SimpleVertex.h
/// @author  Matthew Green
/// @date    2023-11-26 14:04:01
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Graphics/Color32.h"
#include "velecs/Rendering/VertexInputAttributeDescriptor.h"

#include <glm/vec3.hpp>

namespace velecs {

/// @struct Vertex
/// @brief Brief description.
///
/// Rest of description.
struct SimpleVertex {
public:
    // Enums

    // Public Fields

    glm::vec3 position;

    // Constructors and Destructors
    
    /// @brief Default constructor.
    SimpleVertex() = default;

    SimpleVertex(const glm::vec3 position);

    SimpleVertex(const float x, const float y, const float z);
    
    /// @brief Default deconstructor.
    ~SimpleVertex() = default;

    // Public Methods

    static VertexInputAttributeDescriptor GetVertexDescription();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
