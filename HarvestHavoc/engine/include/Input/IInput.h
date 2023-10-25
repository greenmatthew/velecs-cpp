/// \file    IInput.h
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

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

#include <SDL2/SDL.h>

namespace HarvestHavocEngine::Input {

/// \class IInput
/// \brief Manages input actions and input action maps.
/// 
/// The Input class serves as a central hub for managing input actions and input action maps.
/// It provides functionality for creating, switching, and handling different input action maps
/// to facilitate various input handling scenarios such as player input or menu navigation.
class IInput : public IEnableDisable {
public:
    // Enums

    // Public Fields

    // Constructors and Deconstructor

    /// \brief Default constructor.
    IInput() = default;

    /// \brief Default destructor.
    ~IInput() = default;

    // Public Methods

    /// \brief Initializes the Input instance.
    virtual void Init() = 0;

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

    /// \brief Handles enable/disable requests for all input action maps and key bindings.
    void HandleIEnableDisableRequests();

protected:
    // Protected Fields

    // Protected Methods

    /// \brief Creates a new input action map of type T.
    /// 
    /// \tparam T The type of the input action map to create.
    /// \return A shared pointer to the newly created input action map.
    template<typename T>
    static std::shared_ptr<T> CreateMap()
    {
        static_assert(std::is_base_of<InputActionMap, T>::value, "[Input] T must be a subclass of InputActionMap.");
        auto inputActionMapPtr = std::make_shared<T>();
        inputActionMapPtr->Init();
        maps.push_back(inputActionMapPtr);
        return inputActionMapPtr;
    }

    /// \brief Switches to the specified input action map.
    /// 
    /// \param[in] inputActionMapPtr A shared pointer to the input action map to switch to.
    void InternalSwitchTo(std::shared_ptr<InputActionMap> inputActionMapPtr);

private:
    // Private Fields

    static std::vector<std::shared_ptr<InputActionMap>> maps; /// \brief List of input action maps
    static std::unordered_map<SDL_Keycode, std::vector<std::shared_ptr<InputAction>>> keyBinds; /// \brief Map of key bindings to input actions

    // Private Methods

    /// \brief Iterates through all input action maps, applying the specified callback function.
    /// 
    /// \param[in] callback The function to apply to each input action map.
    static void ForEachMap(std::function<void(std::shared_ptr<InputActionMap>)> callback);

    /// \brief Iterates through all key bindings, applying the specified callback function.
    /// 
    /// \param[in] callback The function to apply to each key binding.
    static void ForEachKeyBinding(std::function<void(const SDL_Keycode, std::shared_ptr<InputAction>)> callback);

    /// \brief Handles enable/disable requests for the specified object.
    /// 
    /// \param[in] object The object whose enable/disable requests should be handled.
    static void HandleIEnableDisableRequests(std::shared_ptr<IEnableDisable> object);
};

} // namespace HarvestHavocEngine::Input
