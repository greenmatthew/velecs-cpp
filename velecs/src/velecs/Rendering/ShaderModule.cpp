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

std::unique_ptr<ShaderModule> ShaderModule::CreateVertexShaderModule(const VkDevice device, const std::string& filePath)
{
    VkShaderModule vertShaderModule;
    if (!LoadVertexShader(device, filePath, &vertShaderModule))
    {
        std::cout << "Error when building or loading the vertex shader module: " << filePath << std::endl;
        return nullptr;
    }
    std::cout << "Successfully built and loaded vertex shader module: " << filePath << std::endl;
    return CreateUniquePtr(device, vertShaderModule);
}

std::unique_ptr<ShaderModule> ShaderModule::CreateFragmentShaderModule(const VkDevice device, const std::string& filePath)
{
    VkShaderModule fragShaderModule;
    if (!LoadFragmentShader(device, filePath, &fragShaderModule))
    {
        std::cout << "Error when building or loading the fragment shader module: " << filePath << std::endl;
        return nullptr;
    }
    std::cout << "Successfully built and loaded fragment shader module: " << filePath << std::endl;
    return CreateUniquePtr(device, fragShaderModule);
}

const VkShaderModule ShaderModule::get() const
{
    return shaderModule;
}

ShaderModule::operator const VkShaderModule() const
{
    return shaderModule;
}

// Protected Fields

// Protected Methods

// Private Fields

// Constructors

ShaderModule::ShaderModule(const VkDevice device, const VkShaderModule shaderModule)
    : device(device), shaderModule(shaderModule) {}

// Private Methods

std::unique_ptr<ShaderModule> ShaderModule::CreateUniquePtr(const VkDevice device, const VkShaderModule shaderModule)
{
    struct UniquePtrWrapper : public ShaderModule
    {
        UniquePtrWrapper(const VkDevice device, const VkShaderModule shaderModule) : ShaderModule(device, shaderModule) {}
    };

    return std::make_unique<UniquePtrWrapper>(device, shaderModule);
}

bool ShaderModule::LoadShader(const VkDevice device, const std::string& filePath, VkShaderModule* outShaderModule)
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

bool ShaderModule::LoadVertexShader(const VkDevice device, const std::string& filePath, VkShaderModule* outShaderModule)
{
    const std::string newPath{ Path::Combine(Path::VERT_SHADERS_DIR(), std::string{filePath})};
    if (File::Exists(newPath))
    {
        return LoadShader(device, newPath, outShaderModule);
    }
    else
    {
        try
        {
            return LoadShader(device, filePath, outShaderModule);
        }
        catch (std::exception ex)
        {
            return false;
        }
    }
    return false;
}

bool ShaderModule::LoadFragmentShader(const VkDevice device, const std::string& filePath, VkShaderModule* outShaderModule)
{
    const std::string newPath{ Path::Combine(Path::FRAG_SHADERS_DIR(), filePath)};
    if (File::Exists(newPath))
    {
        return LoadShader(device, newPath, outShaderModule);
    }
    else
    {
        try
        {
            return LoadShader(device, filePath, outShaderModule);
        }
        catch (std::exception ex)
        {
            return false;
        }
    }
    return false;
}

} // namespace velecs
