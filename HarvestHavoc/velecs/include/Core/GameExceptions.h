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

namespace velecs {

/// \class GameException
/// \brief This class represents a base exception for game-specific errors.
/// 
/// GameException is derived from the standard exception class, 
/// providing a basis for exception handling within the game's context.
/// 
/// \code
/// throw GameException("Specific error message");
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class GameException : public std::exception {
public:
    /// \brief Constructs a GameException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit GameException(const std::string& message)
        : msg_("[" + std::string{typeid(TWhereExceptionOccurred).name()} + "] " + message) {}

    /// \brief Retrieves the error message associated with this exception.
    /// \returns The message describing the exception, prefixed with the name of the type where the exception occurred.
    virtual char const* what() const noexcept override { return msg_.c_str(); }
    
    /// \brief Default destructor.
    ~GameException() = default;

private:
    std::string msg_; ///< The error message, prefixed with the name of the type where the exception occurred.
};

/// \class GameLogicException
/// \brief Represents an exception for game-specific logic errors.
/// 
/// Derived from GameException, this class encapsulates errors related 
/// to game logic that might occur during runtime.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class GameLogicException : public GameException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a GameLogicException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit GameLogicException(const std::string& message) : GameException<TWhereExceptionOccurred>(message) {}
};

/// \class GameRuntimeException
/// \brief Represents an exception for game-specific runtime errors.
/// 
/// Derived from GameException, this class encapsulates errors that 
/// occur during the runtime, which are not covered by other more 
/// specific exception types.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class GameRuntimeException : public GameException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a GameRuntimeException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit GameRuntimeException(const std::string& message) : GameException<TWhereExceptionOccurred>(message) {}
};



/// \class UninitializedInstanceException
/// \brief Represents an exception for uninitialized instances.
///
/// Derived from GameRuntimeException, this class encapsulates errors 
/// that occur when an attempt is made to access an uninitialized instance.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class UninitializedInstanceException : public GameRuntimeException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs an UninitializedInstanceException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit UninitializedInstanceException()
        : GameRuntimeException<TWhereExceptionOccurred>("Instance was not initialized.") {}
};

/// \class ReinitializationException
/// \brief Represents an exception for re-initialization attempts.
///
/// Derived from GameRuntimeException, this class encapsulates errors 
/// that occur when an attempt is made to re-initialize an already initialized instance.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class ReinitializationException : public GameRuntimeException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a ReinitializationException with a specific error message.
    explicit ReinitializationException()
        : GameRuntimeException<TWhereExceptionOccurred>("Attempted to re-initialize an already initialized instance.") {}
};



/// \class FileSystemException
/// \brief Represents an exception for file system related errors.
/// 
/// Derived from GameRuntimeException, this class encapsulates errors 
/// related to file system operations within the game's context, such 
/// as file not found, directory not readable, etc.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class FileSystemException : public GameRuntimeException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a FileSystemException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit FileSystemException(const std::string& message) : GameRuntimeException<TWhereExceptionOccurred>(message) {}
};

/// \class PathException
/// \brief Represents an exception related to path operations.
/// 
/// Derived from FileSystemException, this class encapsulates errors 
/// related to path operations within the game's context, such as invalid 
/// path format, nonexistent path, etc.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class PathException : public FileSystemException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a PathException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit PathException(const std::string& message) : FileSystemException<TWhereExceptionOccurred>(message) {}
};

/// \class PathNotFoundException
/// \brief Represents an exception for a path not found error.
/// 
/// Derived from PathException, this class encapsulates the specific error 
/// case where a path was not found within the game's context.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class PathNotFoundException : public PathException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a PathNotFoundException with a specific error message.
    /// \param[in] path The path that could not be found.

    explicit PathNotFoundException(const std::string& path)
        : PathException<TWhereExceptionOccurred>("Path not found: " + path) {}
};

/// \class PathHasNoParentDirectoryException
/// \brief Represents an exception for a path with no parent directory error.
/// 
/// Derived from PathException, this class encapsulates the specific error 
/// case where a path has no parent directory within the game's context.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class PathHasNoParentDirectoryException : public PathException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a PathHasNoParentDirectoryException with a specific error message.
    /// \param[in] path The path that has no parent directory.
    explicit PathHasNoParentDirectoryException(const std::string& path)
        : PathException<TWhereExceptionOccurred>("Path has no parent directory: " + path) {}
};

/// \class CombineAbsolutePathsException
/// \brief Represents an exception when attempting to combine two absolute paths.
///
/// Derived from PathException, this class encapsulates the error scenario
/// where two absolute paths are passed to a function expecting at most one 
/// absolute path, which could lead to unexpected behavior or bugs.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class CombineAbsolutePathsException : public PathException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a CombineAbsolutePathsException with a specific error message.
    /// \param[in] path1 The first absolute path.
    /// \param[in] path2 The second absolute path.
    CombineAbsolutePathsException(const std::string& path1, const std::string& path2)
        : PathException<TWhereExceptionOccurred>("Cannot combine two absolute paths: " + path1 + ", " + path2) {}
};



/// \class FileException
/// \brief Represents an exception related to file operations.
/// 
/// Derived from FileSystemException, this class encapsulates errors 
/// related to file operations within the game's context, such as 
/// file not found, file not readable, etc.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class FileException : public FileSystemException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a FileException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit FileException(const std::string& message) : FileSystemException<TWhereExceptionOccurred>(message) {}
};

/// \class FileNotFoundException
/// \brief Represents an exception for a file not found error.
/// 
/// Derived from FileException, this class encapsulates the specific error 
/// case where a file was not found within the game's context.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class FileNotFoundException : public FileException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a FileNotFoundException with a specific error message.
    /// \param[in] filePath The path of the file that could not be found.
    explicit FileNotFoundException(const std::string& filePath)
        : FileException<TWhereExceptionOccurred>("File not found: " + filePath) {}
};

/// \class FileExpectedButDirectoryFoundException
/// \brief Represents an exception where a file was expected, but a directory was found.
/// 
/// Derived from FileException, this class encapsulates the specific error 
/// case where a directory was mistakenly provided when a file was expected.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class FileExpectedButDirectoryFoundException : public FileException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a FileExpectedButDirectoryFoundException with a specific error message.
    /// \param[in] filePath The file path that led to the exception.
    explicit FileExpectedButDirectoryFoundException(const std::string& filePath)
        : FileException<TWhereExceptionOccurred>("File expected, but directory found: " + filePath) {}
};



/// \class DirectoryException
/// \brief Represents an exception related to directory operations.
/// 
/// Derived from FileSystemException, this class encapsulates errors 
/// related to directory operations within the game's context, such as 
/// directory not found, directory not readable, etc.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class DirectoryException : public FileSystemException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a DirectoryException with a specific error message.
    /// \param[in] message The message describing the exception.
    explicit DirectoryException(const std::string& message) : FileSystemException<TWhereExceptionOccurred>(message) {}
};

/// \class DirectoryNotFoundException
/// \brief Represents an exception for a directory not found error.
/// 
/// Derived from DirectoryException, this class encapsulates the specific error 
/// case where a directory was not found within the game's context.
/// \tparam TWhereExceptionOccurred The type where the exception occurred. This type's name will be prefixed to the error message.
template <typename TWhereExceptionOccurred>
class DirectoryNotFoundException : public DirectoryException<TWhereExceptionOccurred> {
public:
    /// \brief Constructs a DirectoryNotFoundException with a specific error message.
    /// \param[in] dirPath The directory path that could not be found.
    explicit DirectoryNotFoundException(const std::string& dirPath)
        : DirectoryException<TWhereExceptionOccurred>("Directory not found: " + dirPath) {}
};

} // namespace velecs
