/// \file    Mesh.h
/// \author  Matthew Green
/// \date    10/29/2023 17:55:56
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Graphics/Vertex.h"

#include "Engine/AllocatedBuffer.h"

#include "vector"

namespace engine {

/// \class Mesh
/// \brief Brief description.
///
/// Rest of description.
struct Mesh {
public:
    // Enums

    // Public Fields

    std::vector<Vertex> _vertices;

    AllocatedBuffer _vertexBuffer;

    // Constructors and Destructors
    
    /// \brief Default constructor.
    Mesh() = default;
    
    /// \brief Default deconstructor.
    ~Mesh() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace engine
