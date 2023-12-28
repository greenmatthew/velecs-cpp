/// @file    AllocatedImage.h
/// @author  Matthew Green
/// @date    2023-12-28 12:56:19
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <vulkan/vulkan_core.h>

#include <vma/vk_mem_alloc.h>

namespace velecs {

/// @struct AllocatedImage
/// @brief Brief description.
///
/// Rest of description.
struct AllocatedImage {
public:
    // Enums

    // Public Fields

    VkImage _image{VK_NULL_HANDLE};
    VmaAllocation _allocation{VK_NULL_HANDLE};

    // Constructors and Destructors

    /// @brief Default constructor.
    AllocatedImage() = default;

    /// @brief Default deconstructor.
    ~AllocatedImage() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
