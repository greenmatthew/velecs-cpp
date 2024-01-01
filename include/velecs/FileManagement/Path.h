/// @file    Path.h
/// @author  Matthew Green
/// @date    10/23/2023 20:00:36
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <string>

namespace velecs {

/// @class Path
/// @brief A utility class for path operations.
///
/// This class provides static methods to perform various operations on paths, 
/// such as checking the existence of files, directories, or any path.
/// Also has methods for retriving commonly used file and directory paths.
class Path {
public:
    // Enums

    // Public Fields

    // Public Fields

    /// @brief The directory where the game executable resides.
    /// This directory is determined by retrieving the executable path and then obtaining its parent directory.
    /// Example value: "/path/to/game"
    static const std::string GAME_DIR;

    /// @brief The directory where all game assets are stored, typically inside the game directory.
    /// Example value: "${GAME_DIR}/assets"
    static const std::string ASSETS_DIR;

    /// @brief The directory where shader files are stored, typically inside the assets directory.
    /// Example value: "${GAME_DIR}/assets/shaders"
    static const std::string SHADERS_DIR;

    /// @brief The directory where vertex shader files are stored, typically inside the shaders directory.
    /// Example value: "${GAME_DIR}/assets/shaders/vert"
    static const std::string VERT_SHADERS_DIR;

    /// @brief The directory where fragment shader files are stored, typically inside the shaders directory.
    /// Example value: "${GAME_DIR}/assets/shaders/frag"
    static const std::string FRAG_SHADERS_DIR;

    /// @brief The directory where mesh files are stored, typically inside the assets directory.
    /// Example value: "${GAME_DIR}/assets/meshes"
    static const std::string MESHES_DIR;

    // Public Methods

    /// @brief Checks whether a given path exists.
    /// @param[in] path The path to check.
    /// @return True if a file or directory exists at the specified path, false otherwise.
    static bool Exists(const std::string& path);

    /// @brief Retrieves the parent directory path from the given path.
    /// @param[in] path The input path from which to extract the parent directory path.
    /// @return A string representing the parent directory path. If the input is "path/to/file.txt", the output will be "path/to/".
    static std::string GetParentDirPath(const std::string& path);

    /// @brief Retrieves the root directory path from the given path.
    /// @param[in] path The input path from which to extract the root directory path.
    /// @return A string representing the root directory path. If the input is "path/to/file.txt", the output will be "path/".
    static std::string GetRootDirPath(const std::string& path);

    /// @brief Retrieves the last directory name from the given path.
    /// @param[in] path The input path from which to extract the last directory name.
    /// @return A string representing the last directory name. If the input is "path/to/file.txt", the output will be "to".
    static std::string GetLastDir(const std::string& path);


    /// @brief Checks if a given path is an absolute path.
    /// @param[in] path The path to check.
    /// @return Returns true if the path is absolute, false otherwise.
    static bool IsAbsolute(const std::string& path);

    /// @brief Checks if a given path is a relative path.
    /// @param[in] path The path to check.
    /// @return Returns true if the path is relative, false otherwise.
    static bool IsRelative(const std::string& path);


    /// @brief Combines two paths into a single path.
    /// @param[in] path1 The first path.
    /// @param[in] path2 The second path.
    /// @return Returns a new path which is the combination of path1 and path2.
    static std::string Combine(const std::string& path1, const std::string& path2);

    /// @brief Combines multiple paths into a single path.
    /// @param[in] path1 The first path.
    /// @param[in] path2 The second path.
    /// @param[in] paths Additional paths to combine.
    /// @return Returns a new path which is the combination of all provided paths.
    template<typename... Paths>
    static std::string Combine(const std::string& path1, const std::string& path2, Paths... paths);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
