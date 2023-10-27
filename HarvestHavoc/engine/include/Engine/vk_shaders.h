/// \file    vk_shaders.h
/// \author  Matthew Green
/// \date    10/24/2023 17:47:23
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Engine/vk_types.h>

namespace engine {

/// \class ShaderModule
/// \brief Brief description.
///
/// Rest of description.
class ShaderModule {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors
    
    // Public Methods

    /// \brief Loads a vertex shader module from a SPIR-V file.
    ///
    /// \param filePath The path to the SPIR-V file containing the vertex shader code.
    /// \param outShaderModule A pointer to a VkShaderModule structure where the loaded shader module will be stored.
    /// \return Returns true if the vertex shader module was loaded successfully, false otherwise.
    ///
    /// This method reads a SPIR-V file from disk, creates a Vulkan shader module from the contents, 
    /// and stores the shader module in the provided VkShaderModule structure.
    static bool LoadVertexShader(const VkDevice& device, const char* filePath, VkShaderModule* outShaderModule);

    /// \brief Loads a fragment shader module from a SPIR-V file.
    ///
    /// \param filePath The path to the SPIR-V file containing the fragment shader code.
    /// \param outFragShaderModule A pointer to a VkShaderModule structure where the loaded shader module will be stored.
    /// \return Returns true if the fragment shader module was loaded successfully, false otherwise.
    ///
    /// This method reads a SPIR-V file from disk, creates a Vulkan shader module from the contents, 
    /// and stores the shader module in the provided VkShaderModule structure.
    static bool LoadFragmentShader(const VkDevice& device, const char* filePath, VkShaderModule* outShaderModule);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods

    /// \brief Loads a shader module from a SPIR-V file.
    ///
    /// \param filePath The path to the SPIR-V file.
    /// \param outShaderModule A pointer to a VkShaderModule structure where the loaded shader module will be stored.
    /// \return Returns true if the shader module was loaded successfully, false otherwise.
    ///
    /// This method reads a SPIR-V file from disk, creates a Vulkan shader module from the contents, 
    /// and stores the shader module in the provided VkShaderModule structure.
    static bool LoadShader(const VkDevice& device, const char* filePath, VkShaderModule* outShaderModule);

};

} // namespace engine
