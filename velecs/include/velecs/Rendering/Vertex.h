/// @file    Vertex.h
/// @author  Matthew Green
/// @date    10/29/2023 17:59:45
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Graphics/Color32.h"
#include "velecs/Rendering/VertexInputAttributeDescriptor.h"

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace velecs {

/// @struct Vertex
/// @brief Brief description.
///
/// Rest of description.
struct Vertex {
public:
    // Enums

    // Public Fields

    glm::vec3 position;
    glm::vec3 normal;
    Color32 color{Color32::MAGENTA};

    // Constructors and Destructors
    
    /// @brief Default constructor.
    Vertex() = default;
    
    /// @brief Default deconstructor.
    ~Vertex() = default;

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
