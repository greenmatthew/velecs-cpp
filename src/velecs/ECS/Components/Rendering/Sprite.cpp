/// @file    Sprite.cpp
/// @author  Matthew Green
/// @date    2023-12-27 17:34:47
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Components/Rendering/Sprite.h"

namespace velecs {

// Public Fields

// Constructors and Destructors


Sprite::Sprite(Sprite&& other) noexcept
    : _isValid(other._isValid),
      _width(other._width),
      _height(other._height),
      _numChannels(other._numChannels),
      _data(std::move(other._data)) {
    other._isValid = false;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept {
    if (this != &other) {
        _isValid = other._isValid;
        _width = other._width;
        _height = other._height;
        _numChannels = other._numChannels;
        _data = std::move(other._data);

        other._isValid = false;
    }
    return *this;
}

// Public Methods

Sprite Sprite::Load(const std::string& filePath)
{
    Sprite sprite;
    unsigned char* rawData = stbi_load(filePath.c_str(), &sprite._width, &sprite._height, &sprite._numChannels, 4);

    if (rawData)
    {
        sprite._data = std::unique_ptr<unsigned char[], void(*)(void*)>(rawData, stbi_image_free);
        sprite._isValid = true;
    }

    return std::move(sprite);
}


const bool Sprite::isValid() const
{
    return _isValid;
}

const int Sprite::width() const
{
    return _width;
}

const int Sprite::height() const
{
    return _height;
}

const int Sprite::numChannels() const
{
    return _numChannels;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs
