/// @file    Material.h
/// @author  Matthew Green
/// @date    10/31/2023 12:45:31
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/Graphics/Color32.h"

#include <vulkan/vulkan_core.h>

namespace velecs {

/// @struct Material
/// @brief Brief description.
///
/// Rest of description.
struct Material {
    Color32 color{Color32::MAGENTA};
    VkPipeline pipeline{VK_NULL_HANDLE};
    VkPipelineLayout pipelineLayout{VK_NULL_HANDLE};
};

} // namespace velecs
