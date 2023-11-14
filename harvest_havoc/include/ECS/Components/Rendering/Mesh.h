/// @file    Mesh.h
/// @author  Matthew Green
/// @date    10/31/2023 12:45:23
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <velecs/Rendering/Vertex.h>

#include <velecs/Memory/AllocatedBuffer.h>

#include <vector>

namespace hh {

/// @struct Material
/// @brief Brief description.
///
/// Rest of description.
struct Mesh {
    std::vector<velecs::Vertex> _vertices;
    velecs::AllocatedBuffer _vertexBuffer;
};

} // namespace hh
