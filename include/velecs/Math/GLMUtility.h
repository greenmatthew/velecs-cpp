/// @file    GLMUtility.h
/// @author  Matthew Green
/// @date    2023-12-28 18:42:11
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <sstream>
#include <iomanip>

#include <glm/mat4x4.hpp>

namespace velecs {

/// @class GLMUtility
/// @brief Brief description.
///
/// Rest of description.
class GLMUtility {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    // Delete the constructor, deconstructor, copy constructor, and copy assignment operator to prevent accidental instantiations.
    GLMUtility() = delete;
    ~GLMUtility() = default;
    GLMUtility(const GLMUtility&) = delete;
    GLMUtility& operator=(const GLMUtility&) = delete;

    // Public Methods

    // Static method to convert glm::mat4 to a formatted string.
    static std::string ToString(const glm::mat4& mat);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
