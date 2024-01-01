/// @file    ShaderModule.cpp
/// @author  Matthew Green
/// @date    10/24/2023 17:49:07
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/Rendering/ShaderModule.h"
#include "velecs/Engine/vk_initializers.h"

#include "velecs/FileManagement/Path.h"
#include "velecs/FileManagement/File.h"

#include "velecs/Core/GameExceptions.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

namespace velecs {

// Public Fields

// Destructors

ShaderModule::~ShaderModule()
{
    if (shaderModule != VK_NULL_HANDLE)
    {
        vkDestroyShaderModule(device, shaderModule, nullptr);
    }
}

// Public Methods

ShaderModule ShaderModule::CreateVertShader(const VkDevice device, const std::string& filePath)
{
    VkShaderModule shaderModule = LoadShader(device, filePath);
    VkPipelineShaderStageCreateInfo info = vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_VERTEX_BIT, shaderModule);

    return ShaderModule{ device, shaderModule, info };
}

ShaderModule ShaderModule::CreateFragShader(const VkDevice device, const std::string& filePath)
{
    VkShaderModule shaderModule = LoadShader(device, filePath);
    VkPipelineShaderStageCreateInfo info = vkinit::pipeline_shader_stage_create_info(VK_SHADER_STAGE_FRAGMENT_BIT, shaderModule);

    return ShaderModule{ device, shaderModule, info };
}

// Protected Fields

// Protected Methods

// Private Fields

// Constructors

// Private Methods

VkShaderModule ShaderModule::LoadShader(const VkDevice device, const std::string& relFilePath)
{
    const std::string fullFilePath = Path::Combine(Path::SHADERS_DIR, relFilePath);

    //open the file. With cursor at the end
    std::ifstream file(fullFilePath, std::ios::ate | std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Issue opening shader file.");
    }

    //find what the size of the file is by looking up the location of the cursor
    //because the cursor is at the end, it gives the size directly in bytes
    size_t fileSize = (size_t)file.tellg();

    //spirv expects the buffer to be on uint32, so make sure to reserve an int vector big enough for the entire file
    std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));

    //put file cursor at beginning
    file.seekg(0);

    //load the entire file into the buffer
    file.read((char*)buffer.data(), fileSize);

    //now that the file is loaded into the buffer, we can close it
    file.close();

    //create a new shader module, using the buffer we loaded
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pNext = nullptr;

    //codeSize has to be in bytes, so multiply the ints in the buffer by size of int to know the real size of the buffer
    createInfo.codeSize = buffer.size() * sizeof(uint32_t);
    createInfo.pCode = buffer.data();

    //check that the creation goes well.
    VkShaderModule shaderModule;
    VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);
    if (result != VK_SUCCESS)
    {
        std::ostringstream oss;
        oss << "Failed to create shader module; Vulkan error: " << result;
        throw std::runtime_error(oss.str());
    }

    return shaderModule;
}

VkShaderModule ShaderModule::LoadVertexShader(const VkDevice device, const std::string& filePath)
{
    if (File::HasExtension(".vert.spv"))
    {
        throw std::runtime_error("Provided path: " + filePath + " is not a valid vertex shader file name. It requires a '.vert.spv' extension.");
    }
    VkShaderModule shaderModule = LoadShader(device, filePath);
    return shaderModule;
}

VkShaderModule ShaderModule::LoadFragmentShader(const VkDevice device, const std::string& filePath)
{
    if (File::HasExtension(".frag.spv"))
    {
        throw std::runtime_error("Provided path: " + filePath + " is not a valid vertex shader file name. It requires a '.frag.spv' extension.");
    }
    VkShaderModule shaderModule = LoadShader(device, filePath);
    return shaderModule;
}

} // namespace velecs
