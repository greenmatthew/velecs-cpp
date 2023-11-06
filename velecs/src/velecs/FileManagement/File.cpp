/// \file    File.cpp
/// \author  Matthew Green
/// \date    10/23/2023 22:41:18
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/FileManagement/Path.h"
#include "velecs/FileManagement/File.h"
#include "velecs/FileManagement/Directory.h"

#include "velecs/Core/GameExceptions.h"

#include <filesystem>
#include <unordered_map>
#include <functional>

namespace velecs {

// Public Fields

// Constructors and Destructors

// Public Methods

bool File::Exists(const std::string& filePath)
{
    return std::filesystem::exists(filePath) && !std::filesystem::is_directory(filePath);
}

bool File::HasExtension(const std::string& filePath)
{
    return GetExtension(filePath) != "";
}

std::string File::GetExtension(const std::string& filePath)
{
    return std::filesystem::path(filePath).extension().string();
}

std::string File::GetSecondaryExtension(const std::string& filePath)
{
    return File::GetExtension(File::GetFileName(filePath, false));
}

std::string File::GetFileName(const std::string& filePath, const bool includeExtension)
{
    if (includeExtension)
    {
        return std::filesystem::path(filePath).filename().string();
    }
    else
    {
        return std::filesystem::path(filePath).stem().string();
    }
}

std::ifstream File::OpenForRead(const std::string& filePath, std::optional<std::ios_base::openmode> mode /* = std::nullopt */)
{
    return std::ifstream{filePath, mode.value_or(std::ios::in)};
}

std::ofstream File::OpenForWrite(const std::string& filePath, std::optional<std::ios_base::openmode> mode /* = std::nullopt */)
{
    return std::ofstream{filePath, mode.value_or(std::ios::out)};
}

std::fstream File::OpenForReadWrite(const std::string& filePath, std::optional<std::ios_base::openmode> mode /* = std::nullopt */)
{
    return std::fstream{filePath, mode.value_or(std::ios::in | std::ios::out)};
}

File::Type File::DetermineFileType(const std::string& filePath)
{
    static std::unordered_map<std::string, std::function<Type(const std::string&)>> dispathTable
    {
        {
            ".spv",
            [](const std::string& filePath)
            {
                static std::unordered_map<std::string, Type> shaderDispathTable
                {
                    {".vert", Type::VERT_SHADER},
                    {".frag", Type::FRAG_SHADER},
                };
                const std::string secExt = File::GetSecondaryExtension(filePath);

                auto it = shaderDispathTable.find(secExt);
                if (it != shaderDispathTable.end())
                {
                    return it->second;
                }
                return Type::SHADER;
            }
        }
    };

    const std::string ext = File::GetExtension(filePath);

    auto it = dispathTable.find(ext);
    if (it != dispathTable.end())
    {
        return it->second(filePath);
    }
    return Type::UNKNOWN;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
