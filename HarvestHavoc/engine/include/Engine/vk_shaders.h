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

#include <memory>
#include <string>

namespace engine {

/// \class ShaderModule
/// \brief A wrapper class for Vulkan shader modules.
///
/// ShaderModule encapsulates Vulkan shader modules, providing lifecycle management
/// and shader loading functionalities.
class ShaderModule {
public:
    // Enums

    // Public Fields

    // Destructors

    /// \brief Destructor that releases the Vulkan shader module resource.
    ~ShaderModule();
    
    // Public Methods

    /// \brief Creates a vertex shader module from a file.
    ///
    /// \param device The Vulkan device.
    /// \param filePath The path to the SPIR-V file. Can be absolute or relative to Path::VERT_SHADERS_DIR.
    /// \return A unique_ptr to the created ShaderModule.
    static std::unique_ptr<ShaderModule> CreateVertexShaderModule(const VkDevice device, const std::string& filePath);

    /// \brief Creates a fragment shader module from a file.
    ///
    /// \param device The Vulkan device.
    /// \param filePath The path to the SPIR-V file. Can be absolute or relative to Path::FRAG_SHADERS_DIR.
    /// \return A unique_ptr to the created ShaderModule.
    static std::unique_ptr<ShaderModule> CreateFragmentShaderModule(const VkDevice device, const std::string& filePath);

    /// \brief Gets the Vulkan shader module handle.
    ///
    /// \return The Vulkan shader module handle.
    const VkShaderModule get() const;

    /// \brief Implicit conversion to VkShaderModule.
    ///
    /// \return The Vulkan shader module handle.
    operator const VkShaderModule() const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    VkDevice device; /// \brief The Vulkan device handle.
    VkShaderModule shaderModule; /// \brief The Vulkan shader module handle.

    // Constructors

    /// \brief Constructor.
    ///
    /// \param device The Vulkan device handle.
    /// \param shaderModule The Vulkan shader module handle.
    ShaderModule(const VkDevice device, const VkShaderModule shaderModule);

    // Private Methods

    /// \brief Creates a unique_ptr to a ShaderModule instance.
    ///
    /// \param device The Vulkan device handle.
    /// \param shaderModule The Vulkan shader module handle.
    /// \return A unique_ptr to a ShaderModule instance.
    ///
    /// This method facilitates the creation of a ShaderModule instance wrapped in a unique_ptr,
    /// utilizing a nested struct to access the private constructor of ShaderModule.
    static std::unique_ptr<ShaderModule> CreateUniquePtr(const VkDevice device, const VkShaderModule shaderModule);

    /// \brief Loads a shader module from a SPIR-V file.
    ///
    /// \param device The Vulkan device handle.
    /// \param filePath The path to the SPIR-V file.
    /// \param outShaderModule A pointer to a VkShaderModule structure where the loaded shader module will be stored.
    /// \return Returns true if the shader module was loaded successfully, false otherwise.
    ///
    /// This method reads a SPIR-V file from disk, creates a Vulkan shader module from the contents, 
    /// and stores the shader module in the provided VkShaderModule structure.
    static bool LoadShader(const VkDevice device, const std::string& filePath, VkShaderModule* outShaderModule);

    /// \brief Loads a vertex shader module from a SPIR-V file.
    ///
    /// \param device The Vulkan device handle.
    /// \param filePath The path to the SPIR-V file containing the vertex shader code. Can be absolute or relative to Path::VERT_SHADERS_DIR.
    /// \param outShaderModule A pointer to a VkShaderModule structure where the loaded shader module will be stored.
    /// \return Returns true if the vertex shader module was loaded successfully, false otherwise.
    ///
    /// This method reads a SPIR-V file from disk, creates a Vulkan shader module from the contents, 
    /// and stores the shader module in the provided VkShaderModule structure.
    static bool LoadVertexShader(const VkDevice device, const std::string& filePath, VkShaderModule* outShaderModule);

    /// \brief Loads a fragment shader module from a SPIR-V file.
    ///
    /// \param device The Vulkan device handle.
    /// \param filePath The path to the SPIR-V file containing the fragment shader code. Can be absolute or relative to Path::FRAG_SHADERS_DIR.
    /// \param outFragShaderModule A pointer to a VkShaderModule structure where the loaded shader module will be stored.
    /// \return Returns true if the fragment shader module was loaded successfully, false otherwise.
    ///
    /// This method reads a SPIR-V file from disk, creates a Vulkan shader module from the contents, 
    /// and stores the shader module in the provided VkShaderModule structure.
    static bool LoadFragmentShader(const VkDevice device, const std::string& filePath, VkShaderModule* outShaderModule);

};

} // namespace engine
