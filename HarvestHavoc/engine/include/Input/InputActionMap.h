/// \file    InputActionMap.h
/// \author  Matthew Green
/// \date    10/16/2023 19:08:09
/// 
/// \section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "Core/IEnableDisable.h"

#include <memory>
#include <unordered_map>
#include <functional>

#include <SDL2/SDL.h>

namespace engine::Input {

class InputAction;

/// \class InputActionMap
/// \brief Manages the mappings of SDL keycodes to input actions and handles triggering of actions based on input events.
/// 
/// The InputActionMap class serves as a registry and manager for input actions in the application. 
/// It creates bindings between SDL keycodes and InputAction instances, and provides methods to handle 
/// the triggering of actions based on input events. The class is designed to be extended by subclasses 
/// for specific input handling behaviors, with abstract methods for initialization and action map switching.
/// It implements the IEnableDisable and IInputAccessor interfaces to provide enabling/disabling logic and 
/// input handling, respectively. The class maintains lists of held and recently released key binds to efficiently 
/// handle continuous input and state transitions.
class InputActionMap : public IEnableDisable {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// \brief Default constructor.
    InputActionMap();

    /// \brief Virtual destructor to allow for subclassing and also makes class abstract.
    virtual ~InputActionMap() = 0;

    // Public Methods

    /// \brief Initializes the InputActionMap.
    virtual void Init() = 0;

    /// \brief Creates an InputAction binding for the specified key.
    ///
    /// \param[in] keycode The SDL keycode for the key.
    /// \return A shared pointer to the newly created InputAction.
    std::shared_ptr<InputAction> CreateBinding(const SDL_Keycode keycode);

    /// \brief Tries to invoke the OnPressed event for the specified key.
    ///
    /// \param[in] keycode The SDL keycode for the key.
    /// \return true if the event was successfully invoked; false otherwise.
    bool TryOnPressed(const SDL_Keycode keycode);

    /// \brief Attempts to invoke the OnHeld event for all held key binds.
    ///
    /// \return true if any OnHeld event was successfully invoked; false otherwise.
    bool TryOnHeld();

    /// \brief Attempts to invoke the OnReleased event for the specified key.
    ///
    /// \param[in] keycode The SDL keycode for the key.
    /// \return true if the OnReleased event was successfully invoked; false otherwise.
    bool TryOnReleased(const SDL_Keycode keycode);

    /// \brief Attempts to set the state of all recently released key binds to idle.
    void TrySettingToIdle();

    /// \brief Adds the specified InputAction to the list of held key binds.
    ///
    /// \param[in] inputActionPtr A shared pointer to the InputAction to add.
    void AddToHeldKeyBinds(std::shared_ptr<InputAction> inputActionPtr);

    /// \brief Removes the specified InputAction from the list of held key binds.
    ///
    /// \param[in] inputActionPtr A shared pointer to the InputAction to remove.
    void RemoveFromHeldKeyBinds(std::shared_ptr<InputAction> inputActionPtr);

    /// \brief Adds the specified InputAction to the list of recently released key binds.
    ///
    /// \param[in] inputActionPtr A shared pointer to the InputAction to add.
    void AddToReleasedKeyBinds(std::shared_ptr<InputAction> inputActionPtr);

    /// \brief Removes the specified InputAction from the list of recently released key binds.
    ///
    /// \param[in] inputActionPtr A shared pointer to the InputAction to remove.
    void RemoveFromReleasedKeyBinds(std::shared_ptr<InputAction> inputActionPtr);

    /// \brief Invoked when the InputActionMap is enabled.
    void OnEnable() override;

    /// \brief Invoked when the InputActionMap is disabled.
    void OnDisable() override;

    /// \brief A pure virtual method to be implemented by subclasses, defining behavior when switching action maps.
    virtual void Switch() = 0;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    /// \brief The map of key bindings to InputActions.
    std::unordered_map<SDL_Keycode, std::shared_ptr<InputAction>> keyBinds;

    /// \brief A list of key binds currently being held.
    std::vector<std::shared_ptr<InputAction>> heldKeyBinds;

    /// \brief A list of key binds that were recently released.
    std::vector<std::shared_ptr<InputAction>> releasedKeyBinds;

    bool isEnabled = true;

    // Private Methods

    /// \brief Iterates through all key binds, applying the specified callback function.
    ///
    /// \param[in] callback The function to apply to each key bind.
    void ForEachKeyBind(std::function<void(const SDL_Keycode keycode, std::shared_ptr<InputAction>)> callback);

    /// \brief Iterates through all held key binds, applying the specified callback function.
    ///
    /// \param[in] callback The function to apply to each held key bind.
    void ForEachHeldKeyBind(std::function<void(std::shared_ptr<InputAction>)> callback);

    /// \brief Iterates through all recently released key binds, applying the specified callback function.
    ///
    /// \param[in] callback The function to apply to each recently released key bind.
    void ForEachReleasedKeyBind(std::function<void(std::shared_ptr<InputAction>)> callback);

    /// \brief Attempts to find a key bind associated with the specified SDL keycode.
    ///
    /// \param[in] keycode The SDL keycode for which to find a key bind.
    /// \return A shared pointer to the found InputAction, or nullptr if no key bind was found.
    std::shared_ptr<InputAction> TryFindKeyBind(const SDL_Keycode keycode) const;
};

} // namespace engine::Input
