/// @file    SimpleMesh.h
/// @author  Matthew Green
/// @date    2023-11-26 14:08:22
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Rendering/SimpleVertex.h"
#include "velecs/Memory/AllocatedBuffer.h"

#include <vector>

namespace velecs {

/// @struct SimpleMesh
/// @brief Brief description.
///
/// Rest of description.
struct SimpleMesh {
public:
    // Enums

    // Public Fields

    std::vector<SimpleVertex> _vertices;
    AllocatedBuffer _vertexBuffer;

    // Constructors and Destructors

    /// @brief Default constructor.
    SimpleMesh() = default;

    /// @brief Default deconstructor.
    ~SimpleMesh() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace namespace::
