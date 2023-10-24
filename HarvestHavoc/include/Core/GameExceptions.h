/// \file    GameException.h
/// \author  Matthew Green
/// \date    10/23/2023 23:33:54
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <exception>
#include <string>

namespace HarvestHavoc {

/// \class GameException
/// \brief This class represents a base exception for game-specific errors.
/// 
/// GameException is derived from the standard exception class, 
/// providing a basis for exception handling within the game's context.
/// 
/// \code
/// throw GameException("Specific error message");
class GameException : public std::exception {
public:
    /// \brief Constructs a GameException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit GameException(const std::string& message);

    /// \brief Retrieves the error message associated with this exception.
    /// \returns The message describing the exception.
    virtual char const* what() const noexcept override;
    
    /// \brief Default deconstructor.
    ~GameException() = default;

private:
    std::string msg_; /// \brief The error message.
};

/// \class GameLogicException
/// \brief Represents an exception for game-specific logic errors.
/// 
/// Derived from GameException, this class encapsulates errors related 
/// to game logic that might occur during runtime.
class GameLogicException : public GameException {
public:
    /// \brief Constructs a GameLogicException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit GameLogicException(const std::string& message);
};

/// \class GameRuntimeException
/// \brief Represents an exception for game-specific runtime errors.
/// 
/// Derived from GameException, this class encapsulates errors that 
/// occur during the runtime, which are not covered by other more 
/// specific exception types.
class GameRuntimeException : public GameException {
public:
    /// \brief Constructs a GameRuntimeException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit GameRuntimeException(const std::string& message);
};



/// \class FileSystemException
/// \brief Represents an exception for file system related errors.
/// 
/// Derived from GameRuntimeException, this class encapsulates errors 
/// related to file system operations within the game's context, such 
/// as file not found, directory not readable, etc.
class FileSystemException : public GameRuntimeException {
public:
    /// \brief Constructs a FileSystemException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit FileSystemException(const std::string& message);
};

/// \class PathException
/// \brief Represents an exception related to path operations.
/// 
/// Derived from FileSystemException, this class encapsulates errors 
/// related to path operations within the game's context, such as invalid 
/// path format, nonexistent path, etc.
class PathException : public FileSystemException {
public:
    /// \brief Constructs a PathException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit PathException(const std::string& message);
};

/// \class PathNotFoundException
/// \brief Represents an exception for a path not found error.
/// 
/// Derived from PathException, this class encapsulates the specific error 
/// case where a path was not found within the game's context.
/// 
class PathNotFoundException : public PathException {
public:
    /// \brief Constructs a PathNotFoundException with a specific error message.
    /// \param[in] path The path that could not be found.
    explicit PathNotFoundException(const std::string& path);
};

/// \class PathHasNoParentDirectoryException
/// \brief Represents an exception for a path with no parent directory error.
/// 
/// Derived from PathException, this class encapsulates the specific error 
/// case where a path has no parent directory within the game's context.
class PathHasNoParentDirectoryException : public PathException {
public:
    /// \brief Constructs a PathHasNoParentDirectoryException with a specific error message.
    /// \param[in] path The path that has no parent directory.
    explicit PathHasNoParentDirectoryException(const std::string& path);
};

/// \class CombineAbsolutePathsException
/// \brief Represents an exception when attempting to combine two absolute paths.
///
/// Derived from PathException, this class encapsulates the error scenario
/// where two absolute paths are passed to a function expecting at most one 
/// absolute path, which could lead to unexpected behavior or bugs.
class CombineAbsolutePathsException : public PathException {
public:
    /// \brief Constructs a CombineAbsolutePathsException with a specific error message.
    /// \param[in] path1 The first absolute path.
    /// \param[in] path2 The second absolute path.
    CombineAbsolutePathsException(const std::string& path1, const std::string& path2)
        : PathException("Cannot combine two absolute paths: " + path1 + ", " + path2) {}
};



/// \class FileException
/// \brief Represents an exception related to file operations.
/// 
/// Derived from FileSystemException, this class encapsulates errors 
/// related to file operations within the game's context, such as 
/// file not found, file not readable, etc.
class FileException : public FileSystemException {
public:
    /// \brief Constructs a FileException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit FileException(const std::string& message);
};

/// \class FileNotFoundException
/// \brief Represents an exception for a file not found error.
/// 
/// Derived from FileException, this class encapsulates the specific error 
/// case where a file was not found within the game's context.
class FileNotFoundException : public FileException {
public:
    /// \brief Constructs a FileNotFoundException with a specific error message.
    /// \param[in] filePath The path of the file that could not be found.
    explicit FileNotFoundException(const std::string& filePath);
};

/// \class FileExpectedButDirectoryFoundException
/// \brief Represents an exception where a file was expected, but a directory was found.
/// 
/// Derived from FileException, this class encapsulates the specific error 
/// case where a directory was mistakenly provided when a file was expected.
/// 
class FileExpectedButDirectoryFoundException : public FileException {
public:
    /// \brief Constructs a FileExpectedButDirectoryFoundException with a specific error message.
    /// \param[in] filePath The file path that led to the exception.
    explicit FileExpectedButDirectoryFoundException(const std::string& filePath);
};



/// \class DirectoryException
/// \brief Represents an exception related to directory operations.
/// 
/// Derived from FileSystemException, this class encapsulates errors 
/// related to directory operations within the game's context, such as 
/// directory not found, directory not readable, etc.
class DirectoryException : public FileSystemException {
public:
    /// \brief Constructs a DirectoryException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit DirectoryException(const std::string& message);
};

/// \class DirectoryNotFoundException
/// \brief Represents an exception for a directory not found error.
/// 
/// Derived from DirectoryException, this class encapsulates the specific error 
/// case where a directory was not found within the game's context.
class DirectoryNotFoundException : public DirectoryException {
public:
    /// \brief Constructs a DirectoryNotFoundException with a specific error message.
    /// \param[in] dirPath The directory path that could not be found.
    explicit DirectoryNotFoundException(const std::string& dirPath);
};

} // namespace HarvestHavoc
