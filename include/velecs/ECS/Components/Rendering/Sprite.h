/// @file    Sprite.h
/// @author  Matthew Green
/// @date    2023-12-27 17:35:19
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <string>
#include <memory>

#include <stb_image.h>

namespace velecs {

/// @struct Sprite
/// @brief Brief description.
///
/// Rest of description.
struct Sprite {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Default constructor.
    Sprite() = default;

    // Move Constructor
    Sprite::Sprite(Sprite&& other) noexcept;

    // Move Assignment Operator
    Sprite& operator=(Sprite&& other) noexcept;

    /// @brief Deconstructor.
    ~Sprite() = default;

    // Public Methods

    static Sprite Load(const std::string& filePath);

    const bool isValid() const;
    const int width() const;
    const int height() const;
    const int numChannels() const;

protected:
    // Protected Fields

    bool _isValid = false;

    int _width = -1;
    int _height = -1;
    int _numChannels = -1;
    std::unique_ptr<unsigned char[], void(*)(void*)> _data = {nullptr, stbi_image_free};

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs
