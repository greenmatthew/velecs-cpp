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
#include <Input/InputActionMap.h>

#include <memory>

namespace hh::Input {

/// \class Input
/// \brief Brief description.
///
/// Rest of description.
class Input : public engine::Input::IInput {
public:
    // Enums

    // Public Fields

    static std::shared_ptr<class PlayerInputActionMap> Player;  /// \brief Input action map for player controls
    static std::shared_ptr<class MenuInputActionMap> Menu;      /// \brief Input action map for menu navigation

    // Public Methods

    /// \brief Gets the singleton instance of the Input class.
    /// 
    /// \return Reference to the singleton instance of the Input class.
    static Input& GetInstance() {
        static Input instance;  // Created on first use, destroyed at program end
        return instance;
    }

    void Init() override;

    /// \brief Switches to the specified input action map.
    /// 
    /// \param[in] inputActionMapPtr A shared pointer to the input action map to switch to.
    static void SwitchTo(std::shared_ptr<engine::Input::InputActionMap> inputActionMapPtr);

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

} // namespace hh::Input
