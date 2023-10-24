/// \file    GameException.cpp
/// \author  Matthew Green
/// \date    10/23/2023 23:37:09
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "Core/GameExceptions.h"

namespace HarvestHavoc {

// Public Fields

// Constructors and Destructors

GameException::GameException(const std::string& message) : msg_(message) {}

char const* GameException::what() const noexcept { return msg_.c_str(); }


GameLogicException::GameLogicException(const std::string& message) : GameException(message) {}


GameRuntimeException::GameRuntimeException(const std::string& message) : GameException(message) {}


FileSystemException::FileSystemException(const std::string& message) : GameRuntimeException(message) {}


PathException::PathException(const std::string& message) : FileSystemException(message) {}

PathNotFoundException::PathNotFoundException(const std::string& path)
    : PathException("Path not found: " + path) {}

PathHasNoParentDirectoryException::PathHasNoParentDirectoryException(const std::string& path)
    : PathException("Path has no parent directory: " + path) {}


FileException::FileException(const std::string& message) : FileSystemException(message) {}

FileNotFoundException::FileNotFoundException(const std::string& filePath)
    : FileException("File not found: " + filePath) {}

FileExpectedButDirectoryFoundException::FileExpectedButDirectoryFoundException(const std::string& filePath)
    : FileException("File expected, but directory found: " + filePath) {}



DirectoryException::DirectoryException(const std::string& message) : FileSystemException(message) {}

DirectoryNotFoundException::DirectoryNotFoundException(const std::string& dirPath)
    : DirectoryException("Directory not found: " + dirPath) {}

// Public Methods

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc
