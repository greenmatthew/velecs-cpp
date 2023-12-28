/// @file    UploadContext.h
/// @author  Matthew Green
/// @date    2023-12-27 21:01:58
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <vulkan/vulkan_core.h>

namespace velecs {

/// @class UploadContext
/// @brief Brief description.
///
/// Rest of description.
class UploadContext {
public:
    // Enums

    // Public Fields

    VkFence _uploadFence{VK_NULL_HANDLE};
	VkCommandPool _commandPool{VK_NULL_HANDLE};
	VkCommandBuffer _commandBuffer{VK_NULL_HANDLE};

    // Constructors and Destructors

    /// @brief Default constructor.
    UploadContext() = default;

    /// @brief Default deconstructor.
    ~UploadContext() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
