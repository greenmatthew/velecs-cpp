/// \file    File.cpp
/// \author  Matthew Green
/// \date    10/23/2023 22:41:18
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Core/Path.h"
#include "Core/File.h"
#include "Core/Directory.h"
#include "Core/GameExceptions.h"

#include <filesystem>

namespace HarvestHavoc {

// Public Fields

// Constructors and Destructors

// Public Methods

bool File::Exists(const std::string& filePath)
{
    return std::filesystem::exists(filePath) && !std::filesystem::is_directory(filePath);
}

std::string File::GetExtension(const std::string& filePath)
{
    if (File::Exists(filePath))
    {
        return std::filesystem::path(filePath).extension().string();
    }
    else
    {
        if (Directory::Exists(filePath))
        {
            throw FileExpectedButDirectoryFoundException(filePath);
        }
        else
        {
            throw FileNotFoundException(filePath);
        }
    }
}

std::string File::GetFileName(const std::string& filePath, const bool includeExtension)
{
    if (File::Exists(filePath))
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
    else
    {
        if (Directory::Exists(filePath))
        {
            throw FileExpectedButDirectoryFoundException(filePath);
        }
        else
        {
            throw FileNotFoundException(filePath);
        }
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

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc
