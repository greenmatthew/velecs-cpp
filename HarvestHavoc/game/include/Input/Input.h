/// \file    Input.h
/// \author  Matthew Green
/// \date    10/24/2023 20:43:56
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <Input/IInput.h>

namespace HarvestHavoc::Input {

class PlayerInputActionMap;
class MenuInputActionMap;

/// \class Input
/// \brief Brief description.
///
/// Rest of description.
class Input : public HarvestHavocEngine::Input::IInput {
public:
    // Enums

    // Public Fields

    static std::shared_ptr<PlayerInputActionMap> Player;  /// \brief Input action map for player controls
    static std::shared_ptr<MenuInputActionMap> Menu;      /// \brief Input action map for menu navigation

    // Public Methods

    /// \brief Gets the singleton instance of the Input class.
    /// 
    /// \return Reference to the singleton instance of the Input class.
    static Input& GetInstance() {
        static Input instance;  // Created on first use, destroyed at program end
        return instance;
    }

    void Init() override;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Constructors and Destructors

    /// \brief Default constructor.
    Input() = default;
    
    /// \brief Default destructor.
    ~Input() = default;

    // Deleted copy constructor and assignment operator

    /// \brief Deleted copy constructor.
    /// 
    /// Copy constructor is deleted to prevent copying of instances of this class.
    /// 
    /// \param[in] other The instance to copy.
    Input(const Input& other) = delete;

    /// \brief Deleted copy assignment operator.
    /// 
    /// Copy assignment operator is deleted to prevent copying of instances of this class.
    /// 
    /// \param[in] other The instance to assign from.
    /// \return Reference to this instance.
    Input& operator=(const Input& other) = delete;

    // Private Methods
};

} // namespace HarvestHavoc::Input
