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
/// @brief Represents a basic mesh structure.
///
/// This structure is used to define a simple mesh containing vertices,
/// indices, and a buffer for vertex data. It supports loading from
/// external files and predefined shapes.
struct SimpleMesh {
public:
    // Enums

    // Public Fields
        
    std::vector<SimpleVertex> _vertices; /// @brief Vertex data of the mesh.
    std::vector<uint32_t> _indices; /// @brief Indices for drawing the mesh.
    AllocatedBuffer _vertexBuffer; /// @brief Allocated buffer for vertex data.
    AllocatedBuffer _indexBuffer; /// @brief Allocated buffer for index data.

    // Constructors and Destructors

    /// @brief Default constructor.
    SimpleMesh() = default;

    /// @brief Default deconstructor.
    ~SimpleMesh() = default;

    // Public Methods

    /// @brief Creates and returns a predefined equilateral triangle mesh.
    /// @return A `SimpleMesh` instance representing an equilateral triangle.
    /// This method provides a quick way to generate a standard equilateral triangle mesh for use in rendering.
    static const SimpleMesh& EQUILATERAL_TRIANGLE();

    /// @brief Creates and returns a predefined square mesh.
    /// @return A `SimpleMesh` instance representing a square.
    /// This method provides a quick way to generate a standard square mesh for use in rendering.
    static const SimpleMesh& SQUARE();

    static const SimpleMesh& MONKEY();

    /// @brief Loads a mesh from a file.
    /// @param filePath Path to the mesh file.
    /// @return Loaded SimpleMesh object.
    /// @throw std::runtime_error if loading fails.
    static SimpleMesh Load(std::string filePath);

    /// @brief Tries to load a mesh from a file, returning success status.
    /// @param filePath Path to the mesh file.
    /// @param mesh Pointer to the mesh to load.
    /// @return True if loading succeeds, false otherwise.
    static bool TryLoad(const std::string& filePath, SimpleMesh*& mesh);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace namespace::
