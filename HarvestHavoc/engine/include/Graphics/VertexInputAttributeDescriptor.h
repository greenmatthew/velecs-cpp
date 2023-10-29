/// \file    VertexInputAttributeDescriptor.h
/// \author  Matthew Green
/// \date    10/29/2023 18:03:32
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace engine {

/// \class VertexInputAttributeDescriptor
/// \brief Brief description.
///
/// Rest of description.
class VertexInputAttributeDescriptor {
public:
    // Enums

    // Public Fields

    std::vector<VkVertexInputBindingDescription> bindings;
    std::vector<VkVertexInputAttributeDescription> attributes;

    VkPipelineVertexInputStateCreateFlags flags = 0;

    // Constructors and Destructors
    
    /// \brief Default constructor.
    VertexInputAttributeDescriptor() = default;
    
    /// \brief Default deconstructor.
    ~VertexInputAttributeDescriptor() = default;

    // Public Methods

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace engine
