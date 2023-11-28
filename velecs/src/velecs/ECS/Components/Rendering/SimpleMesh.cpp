/// @file    SimpleMesh.cpp
/// @author  Matthew Green
/// @date    2023-11-26 16:41:46
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Components/Rendering/SimpleMesh.h"

#include "velecs/Math/Vec3.h"

#include "velecs/FileManagement/Path.h"
#include "velecs/FileManagement/File.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace velecs {

// Public Fields

// Constructors and Destructors

// Public Methods

const SimpleMesh& SimpleMesh::EQUILATERAL_TRIANGLE()
{
    static const SimpleMesh EQUILATERAL_TRIANGLE{SimpleMesh::Load("equilateral_triangle.obj")};
    return EQUILATERAL_TRIANGLE;
};

const SimpleMesh& SimpleMesh::SQUARE()
{
    static const SimpleMesh SQUARE{SimpleMesh::Load("square.obj")};
    return SQUARE;
}

const SimpleMesh& SimpleMesh::MONKEY()
{
    static const SimpleMesh MONKEY{SimpleMesh::Load("monkey.obj")};
    return MONKEY;
}

SimpleMesh SimpleMesh::Load(std::string filePath)
{
    filePath = Path::Combine(Path::MESHES_DIR(), filePath);

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_ValidateDataStructure);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw std::runtime_error("Failed to load file: " + filePath + "; Error: " + importer.GetErrorString());
    }

    if (scene->mNumMeshes == 0)
    {
        throw std::runtime_error("No meshes found in file: " + filePath);
    }
    if (scene->mNumMeshes > 1)
    {
        throw std::runtime_error("More than one mesh found in file: " + filePath + "; Mesh count: " + std::to_string(scene->mNumMeshes));
    }

    aiMesh* aiMesh = scene->mMeshes[0]; // Assuming one mesh per file

    // Extract vertices
    SimpleMesh mesh;
    size_t numVertices = aiMesh->mNumVertices;
    mesh._vertices.reserve(numVertices);
    for (size_t i = 0; i < numVertices; ++i)
    {
        mesh._vertices.emplace_back
        (
            glm::vec3
            {
                aiMesh->mVertices[i].x,
                aiMesh->mVertices[i].y,
                aiMesh->mVertices[i].z
            }
        );
    }

    for (size_t i = 0; i < aiMesh->mNumFaces; ++i)
    {
        aiFace face = aiMesh->mFaces[i];
        if (face.mNumIndices != 3)
        {
            throw std::runtime_error("Face " + std::to_string(i) + " has invalid number of indices (" + std::to_string(face.mNumIndices) + "), expected 3.");
        }

        for (size_t j = 0; j < face.mNumIndices; ++j)
        {
            mesh._indices.emplace_back(face.mIndices[j]);
        }
    }

    return mesh;
}


bool SimpleMesh::TryLoad(const std::string& filePath, SimpleMesh*& mesh)
{
    try
    {
        *mesh = Load(filePath);
    }
    catch (std::exception e)
    {
        return false;
    }
    return true;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
