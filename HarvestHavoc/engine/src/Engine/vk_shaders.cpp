/// \file    vk_shaders.cpp
/// \author  Matthew Green
/// \date    10/24/2023 17:49:07
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Engine/vk_shaders.h"

#include "FileManagement/Path.h"
#include "FileManagement/File.h"

#include "Core/GameExceptions.h"

#include <vector>
#include <fstream>

namespace engine::Engine {

// Public Fields

// Constructors and Destructors

// Public Methods

bool ShaderModule::LoadVertexShader(const VkDevice& device, const char* filePath, VkShaderModule* outShaderModule)
{
    const std::string newPath{ Path::Combine(Path::VERT_SHADERS_DIR, std::string{filePath}) };
    if (File::Exists(newPath))
    {
        return LoadShader(device, newPath.c_str(), outShaderModule);
    }
    else
    {
        try
        {
            return LoadShader(device, Path::ResolvePath(std::string{filePath}).c_str(), outShaderModule);
        }
        catch (std::exception ex)
        {
            return false;
        }
    }
    return false;
}

bool ShaderModule::LoadFragmentShader(const VkDevice& device, const char* filePath, VkShaderModule* outShaderModule)
{
    const std::string newPath{ Path::Combine(Path::FRAG_SHADERS_DIR, std::string{filePath}) };
    if (File::Exists(newPath))
    {
        return LoadShader(device, newPath.c_str(), outShaderModule);
    }
    else
    {
        try
        {
            return LoadShader(device, Path::ResolvePath(std::string{filePath}).c_str(), outShaderModule);
        }
        catch (std::exception ex)
        {
            return false;
        }
    }
    return false;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

bool ShaderModule::LoadShader(const VkDevice& device, const char* filePath, VkShaderModule* outShaderModule)
{
    //open the file. With cursor at the end
    std::ifstream file(filePath, std::ios::ate | std::ios::binary);
    if (!file.is_open())
    {
        return false;
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
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
    {
        return false;
    }

    *outShaderModule = shaderModule;
    return true;
}

} // namespace engine::Engine
