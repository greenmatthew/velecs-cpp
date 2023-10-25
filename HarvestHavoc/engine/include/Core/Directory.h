/// \file    Directory.h
/// \author  Matthew Green
/// \date    10/23/2023 23:18:22
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <string>

namespace HarvestHavocEngine {

/// \class Directory
/// \brief Brief description.
///
/// Rest of description.
class Directory {
public:
    // Enums

    // Public Fields

    // Public Methods

    /// \brief Checks whether a given path points to a directory.
    /// \param[in] dirPath The path to check.
    /// \return True if a directory exists at the specified path, false otherwise.
    static bool Exists(const std::string& dirPath);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace HarvestHavocEngine
