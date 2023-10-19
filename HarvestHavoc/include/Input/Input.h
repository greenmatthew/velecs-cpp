/// \file    Input.h
/// \author  Matthew Green
/// \date    10/16/2023 18:30:13
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Core/IEnableDisable.h"
#include "Input/InputAction.h"
#include "Input/InputActionMap.h"
#include "Input/PlayerInputActionMap.h"
#include "Input/MenuInputActionMap.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

#include <SDL2/SDL.h>

namespace HarvestHavoc::Input {

class PlayerInputActionMap;
class MenuInputActionMap;

/// \class Input
/// \brief Manages input actions and input action maps.
/// 
/// The Input class serves as a central hub for managing input actions and input action maps.
/// It provides functionality for creating, switching, and handling different input action maps
/// to facilitate various input handling scenarios such as player input or menu navigation.
class Input : public IEnableDisable {
public:
    // Enums

    // Public Fields

    std::shared_ptr<PlayerInputActionMap> Player;  /// \brief Input action map for player controls
    std::shared_ptr<MenuInputActionMap> Menu;      /// \brief Input action map for menu navigation

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

    // Public Methods

    /// \brief Gets the singleton instance of the Input class.
    /// 
    /// \return Reference to the singleton instance of the Input class.
    static Input& GetInstance() {
        static Input instance;  // Created on first use, destroyed at program end
        return instance;
    }

    /// \brief Initializes the Input instance.
    void Init();

    /// \brief Creates a new input action map of type T.
    /// 
    /// \tparam T The type of the input action map to create.
    /// \return A shared pointer to the newly created input action map.
    template<typename T>
    std::shared_ptr<T> CreateMap()
    {
        static_assert(std::is_base_of<InputActionMap, T>::value, "[Input] T must be a subclass of InputActionMap.");
        auto inputActionMapPtr = std::make_shared<T>();
        inputActionMapPtr->Init();
        maps.push_back(inputActionMapPtr);
        return inputActionMapPtr;
    }

    /// \brief Attempts to trigger the 'Pressed' state on all active input maps.
    /// 
    /// \param[in] keycode The SDL keycode representing the key that was pressed.
    /// \return true if at least one input action map successfully processed the key press, false otherwise.
    bool TryOnPressed(const SDL_Keycode keycode);

    /// \brief Attempts to trigger the 'Held' state on all active input maps.
    /// 
    /// \return true if at least one input action map successfully processed the key hold, false otherwise.
    bool TryOnHeld();

    /// \brief Attempts to trigger the 'Released' state on all active input maps.
    /// 
    /// \param[in] keycode The SDL keycode representing the key that was released.
    /// \return true if at least one input action map successfully processed the key release, false otherwise.
    bool TryOnReleased(const SDL_Keycode keycode);

    /// \brief Attempts to set all active input maps to the 'Idle' state.
    void TrySettingToIdle();

    /// \brief Switches to the specified input action map.
    /// 
    /// \param[in] inputActionMapPtr A shared pointer to the input action map to switch to.
    void SwitchTo(std::shared_ptr<InputActionMap> inputActionMapPtr);

    /// \brief Handles enable/disable requests for all input action maps and key bindings.
    void HandleIEnableDisableRequests();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    std::vector<std::shared_ptr<InputActionMap>> maps = std::vector<std::shared_ptr<InputActionMap>>(); /// \brief List of input action maps
    std::unordered_map<SDL_Keycode, std::vector<std::shared_ptr<InputAction>>> keyBinds = std::unordered_map<SDL_Keycode, std::vector<std::shared_ptr<InputAction>>>(); /// \brief Map of key bindings to input actions
    
    // Constructors and Deconstructor

    /// \brief Default constructor.
    Input() = default;
    
    /// \brief Default destructor.
    ~Input() = default;

    // Private Methods

    /// \brief Iterates through all input action maps, applying the specified callback function.
    /// 
    /// \param[in] callback The function to apply to each input action map.
    void ForEachMap(std::function<void(std::shared_ptr<InputActionMap>)> callback);

    /// \brief Iterates through all key bindings, applying the specified callback function.
    /// 
    /// \param[in] callback The function to apply to each key binding.
    void ForEachKeyBinding(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback);

    /// \brief Handles enable/disable requests for the specified object.
    /// 
    /// \param[in] object The object whose enable/disable requests should be handled.
    void HandleIEnableDisableRequests(std::shared_ptr<IEnableDisable> object);
};

} // namespace HarvestHavoc::Input
