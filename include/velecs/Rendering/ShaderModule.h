/// @file    ShaderModule.h
/// @author  Matthew Green
/// @date    10/24/2023 17:47:23
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <vulkan/vulkan_core.h>

#include <memory>
#include <string>

namespace velecs {

/// @class ShaderModule
/// @brief A wrapper class for Vulkan shader modules.
///
/// ShaderModule encapsulates Vulkan shader modules, providing lifecycle management
/// and shader loading functionalities. It manages the creation and destruction of
/// Vulkan shader modules and associated pipeline shader stage create info.
class ShaderModule {
public:
    // Enums

    // Public Fields

    VkDevice device{VK_NULL_HANDLE}; /// @brief Handle to the Vulkan device.
    VkShaderModule shaderModule{VK_NULL_HANDLE}; /// @brief Handle to the Vulkan shader module.
    VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo{}; /// @brief Information for creating a pipeline shader stage.

    // Constructors & Destructors

    ShaderModule() = default;

    /// @brief Destructor that releases the Vulkan shader module resource.
    /// Calls vkDestroyShaderModule to clean up the Vulkan shader module.
    ~ShaderModule();
    
    // Public Methods

    /// @brief Creates a vertex shader from a file.
    /// @param device The Vulkan device.
    /// @param relFilePath Relative file path to the vertex shader SPIR-V file, relative to Path::SHADERS_DIR.
    /// @return A ShaderModule object with the vertex shader loaded.
    /// Throws runtime_error if the shader file can't be opened, the file is not a valid vertex shader, or shader module creation fails.
    static ShaderModule CreateVertShader(const VkDevice device, const std::string& relFilePath);

    /// @brief Creates a fragment shader from a file.
    /// @param device The Vulkan device.
    /// @param relFilePath Relative file path to the fragment shader SPIR-V file, relative to Path::SHADERS_DIR.
    /// @return A ShaderModule object with the fragment shader loaded.
    /// Throws runtime_error if the shader file can't be opened, the file is not a valid fragment shader, or shader module creation fails.
    static ShaderModule CreateFragShader(const VkDevice device, const std::string& relFilePath);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Constructors

    // Private Methods

    /// @brief Loads a shader from a file.
    /// @param device The Vulkan device.
    /// @param relFilePath Relative file path to the shader SPIR-V file, relative to Path::SHADERS_DIR.
    /// @return A VkShaderModule created from the specified file.
    /// Throws runtime_error if the shader file can't be opened or Vulkan shader module creation fails.
    static VkShaderModule LoadShader(const VkDevice device, const std::string& relFilePath);

    /// @brief Loads a vertex shader from a file.
    /// @param device The Vulkan device.
    /// @param filePath Relative file path to the vertex shader SPIR-V file, relative to Path::SHADERS_DIR.
    /// @return A VkShaderModule created from the specified file.
    /// Validates the file extension and throws runtime_error if it's not a valid vertex shader file or shader module creation fails.
    static VkShaderModule LoadVertexShader(const VkDevice device, const std::string& filePath);

    /// @brief Loads a fragment shader from a file.
    /// @param device The Vulkan device.
    /// @param filePath Relative file path to the fragment shader SPIR-V file, relative to Path::SHADERS_DIR.
    /// @return A VkShaderModule created from the specified file.
    /// Validates the file extension and throws runtime_error if it's not a valid fragment shader file or shader module creation fails.
    static VkShaderModule LoadFragmentShader(const VkDevice device, const std::string& filePath);

};

} // namespace velecs
