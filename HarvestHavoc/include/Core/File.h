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

namespace HarvestHavoc {

/// \class File
/// \brief Brief description.
///
/// Rest of description.
class File {
public:
    // Enums

    // Public Fields

    // Public Methods

    /// \brief Checks whether a given path points to a file.
    /// \param[in] filePath The path to check.
    /// \return True if a file exists at the specified path, false otherwise.
    /// \note This method will return false if the path points to a directory, not a file.
    static bool Exists(const std::string& filePath);

    /// \brief Retrieves the extension of the current file.
    /// \return The extension of the file as a string.
    static std::string GetExtension(const std::string& filePath);

    /// \brief Retrieves the name of the file from the given path.
    /// \param[in] filePath The path of the file.
    /// \param[in] includeExtension Flag to include the extension in the file name.
    /// \return The name of the file as a string.
    static std::string GetFileName(const std::string& filePath, const bool includeExtension);

    static std::ifstream OpenForRead(const std::string& filePath, std::optional<std::ios_base::openmode> mode = std::nullopt);
    static std::ofstream OpenForWrite(const std::string& filePath, std::optional<std::ios_base::openmode> mode = std::nullopt);
    static std::fstream OpenForReadWrite(const std::string& filePath, std::optional<std::ios_base::openmode> mode = std::nullopt);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace HarvestHavoc
