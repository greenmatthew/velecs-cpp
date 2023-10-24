/// \file    Path.cpp
/// \author  Matthew Green
/// \date    10/23/2023 20:00:53
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

#ifdef _WIN32
    // Windows-specific code
#include <windows.h>
#include <codecvt>
#include <locale>

static std::string get_executable_path()
{
    std::vector<wchar_t> buffer(MAX_PATH);
    GetModuleFileName(NULL, buffer.data(), static_cast<DWORD>(buffer.size()));
    std::wstring widePath(buffer.data());

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, widePath.data(), (int)widePath.size(), NULL, 0, NULL, NULL);
    std::string utf8Path(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, widePath.data(), (int)widePath.size(), &utf8Path[0], size_needed, NULL, NULL);

    return utf8Path;
}
#else
#error "Unsupported platform"
#endif

namespace HarvestHavoc {

// Public Fields

const std::string Path::GAME_DIR{Path::GetParentDirPath(get_executable_path())};

const std::string Path::ASSETS_DIR{Path::Combine(GAME_DIR, "assets")};

const std::string Path::SHADERS_DIR{Path::Combine(ASSETS_DIR, "shaders")};
const std::string Path::VERT_SHADERS_DIR{Path::Combine(SHADERS_DIR, "vert")};
const std::string Path::FRAG_SHADERS_DIR{Path::Combine(SHADERS_DIR, "frag")};

// Public Methods

bool Path::Exists(const std::string& path)
{
    return std::filesystem::exists(path);
}

std::string Path::GetParentDirPath(const std::string& path)
{
    std::filesystem::path fsPath(path);
    if (fsPath.has_parent_path())
    {
        return fsPath.parent_path().string();
    }
    else
    {
        throw PathHasNoParentDirectoryException(path);
    }
}

std::string Path::GetRootDirPath(const std::string& path)
{
    std::filesystem::path fsPath(path);
    if (fsPath.has_parent_path())
    {
        return fsPath.root_path().string();
    }
    else
    {
        throw PathHasNoParentDirectoryException(path);
    }
}

std::string Path::GetLastDir(const std::string& path)
{
    std::filesystem::path fsPath(path);
    if (fsPath.has_parent_path())
    {
        if (fsPath.has_filename()) // check if fsPath is a file
        {
            return fsPath.parent_path().filename().string();
        }
        else // assume fsPath is a directory
        {
            return fsPath.filename().string();
        }
    }
    else
    {
        throw PathHasNoParentDirectoryException(path);
    }
}

bool Path::IsAbsolute(const std::string& path)
{
    std::filesystem::path fsPath{path};

    return fsPath.is_absolute();
}

bool Path::IsRelative(const std::string& path)
{
    std::filesystem::path fsPath{path};

    return fsPath.is_relative();
}

std::string Path::Combine(const std::string& path1, const std::string& path2)
{
    if (IsAbsolute(path1) && IsAbsolute(path2))
    {
        throw CombineAbsolutePathsException(path1, path2);
    }

    return (std::filesystem::path{path1} / std::filesystem::path{path2}).string();
}

template<typename... Paths>
std::string Path::Combine(const std::string& path1, const std::string& path2, Paths... paths)
{
    return Combine(Combine(path1, path2), paths...);
}

std::string Path::ResolvePath(const std::string& path)
{
    if (Path::Exists(path))
    {
        return path;
    }

    if (Path::IsRelative(path))
    {
        std::string newPath{Path::Combine(Path::GAME_DIR, path)};
        if (Path::Exists(newPath))
        {
            return newPath;
        }

        throw PathNotFoundException(path);
    }
    else
    {
        throw PathNotFoundException(path);
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace HarvestHavoc
