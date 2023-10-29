/// \file    AllocatedBuffer.h
/// \author  Matthew Green
/// \date    10/29/2023 18:11:46
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <vulkan/vulkan_core.h>

#include <vma/vk_mem_alloc.h>

namespace engine {

/// \class AllocatedBuffer
/// \brief Brief description.
///
/// Rest of description.
struct AllocatedBuffer {
public:
    // Enums

    // Public Fields

    VkBuffer _buffer{nullptr};
    VmaAllocation _allocation{nullptr};

    // Constructors and Destructors
    
    /// \brief Default constructor.
    AllocatedBuffer() = default;
    
    /// \brief Default deconstructor.
    ~AllocatedBuffer() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace engine
