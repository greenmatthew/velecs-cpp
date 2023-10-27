/// \file    Directory.cpp
/// \author  Matthew Green
/// \date    10/23/2023 23:18:32
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "FileManagement/Path.h"
#include "FileManagement/File.h"
#include "FileManagement/Directory.h"

#include <filesystem>

namespace engine {

// Public Fields

// Public Methods

bool Directory::Exists(const std::string& dirPath)
{
    return std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath);
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace engine::
