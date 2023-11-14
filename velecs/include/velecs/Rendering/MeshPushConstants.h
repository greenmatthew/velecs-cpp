/// @file    MeshPushConstants.h
/// @author  Matthew Green
/// @date    10/29/2023 18:14:22
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace velecs {

/// @class MeshPushConstants
/// @brief Brief description.
///
/// Rest of description.
class MeshPushConstants {
public:
    // Enums

    // Public Fields

    glm::vec4 data;
    glm::mat4 renderMatrix;

    // Constructors and Destructors
    
    /// @brief Default constructor.
    MeshPushConstants() = default;
    
    /// @brief Default deconstructor.
    ~MeshPushConstants() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
