/// \file    File.h
/// \author  Matthew Green
/// \date    10/23/2023 22:41:05
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <fstream>
#include <optional>

namespace HarvestHavocEngine {

/// \class File
/// \brief Brief description.
///
/// Rest of description.
class File {
public:
    // Enums

    enum class Type
    {
        UNKNOWN = 0,

        SHADER = 100,
        VERT_SHADER = 101,
        FRAG_SHADER = 101,
    };

    // Public Fields

    // Public Methods

    /// \brief Checks whether a given path points to a file.
    /// \param[in] filePath The path to check.
    /// \return True if a file exists at the specified path, false otherwise.
    /// \note This method will return false if the path points to a directory, not a file.
    static bool Exists(const std::string& filePath);

    /// \brief Checks if the given file path has an extension.
    /// 
    /// This function utilizes GetExtension to determine whether or not
    /// the specified file path has an extension.
    /// 
    /// \param[in] filePath The file path to check.
    /// \return true if the file path has an extension, false otherwise.
    static bool HasExtension(const std::string& filePath);

    /// \brief Retrieves the extension of the current file.
    /// \return The extension of the file as a string.
    static std::string GetExtension(const std::string& filePath);

    /// \brief Retrieves the secondary extension of a given file path.
    /// 
    /// This method is useful for files with nested extensions. 
    /// For example, if the file path is "triangle.vert.frag", 
    /// this method will return ".vert".
    ///
    /// \param[in] filePath The file path from which to extract the secondary extension.
    /// \return The secondary extension of the file as a string.
    static std::string GetSecondaryExtension(const std::string& filePath);

    /// \brief Retrieves the name of the file from the given path.
    /// \param[in] filePath The path of the file.
    /// \param[in] includeExtension Flag to include the extension in the file name.
    /// \return The name of the file as a string.
    static std::string GetFileName(const std::string& filePath, const bool includeExtension);

    static std::ifstream OpenForRead(const std::string& filePath, std::optional<std::ios_base::openmode> mode = std::nullopt);
    static std::ofstream OpenForWrite(const std::string& filePath, std::optional<std::ios_base::openmode> mode = std::nullopt);
    static std::fstream OpenForReadWrite(const std::string& filePath, std::optional<std::ios_base::openmode> mode = std::nullopt);

    static Type DetermineFileType(const std::string& filePath);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace HarvestHavocEngine
