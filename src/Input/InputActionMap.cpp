#include "Input/InputActionMap.h"

namespace HarvestHavoc
{
    namespace Input
    {
        std::unordered_map<SDL_Keycode, InputAction> InputActionMapInternal::map = std::unordered_map<SDL_Keycode, InputAction>();

        bool InputActionMapInternal::isEnabled = true;

        std::optional<InputAction> InputActionMapInternal::TryCreateBinding(SDL_Keycode keycode)
        {
            auto it = map.find(keycode);
            if (it == map.end())
            {
                auto inputAction = InputAction(keycode);
                map.emplace(keycode, inputAction);
                return inputAction;
            }
            else
            {
                return std::nullopt;
            }
        }

        std::optional<InputAction> InputActionMapInternal::TryFind(SDL_Keycode keycode)
        {
            auto it = map.find(keycode);
            if (it != map.end())
            {
                return it->second;
            }
            else
            {
                return std::nullopt;  // or just return {};
            }
        }

        void InputActionMapInternal::TryInvokingOnHeld(SDL_Keycode keycode)
        {
            std::optional<InputAction> inputActionOpt = TryFind(keycode);
            if (inputActionOpt.has_value())
            {
                inputActionOpt->OnHeld.Invoke();
            }
        }

        void InputActionMapInternal::TryInvokingOnPressed(SDL_Keycode keycode)
        {
            std::optional<InputAction> inputActionOpt = TryFind(keycode);
            if (inputActionOpt.has_value())
            {
                inputActionOpt->OnPressed.Invoke();
            }
        }

        void InputActionMapInternal::TryInvokingOnReleased(SDL_Keycode keycode)
        {
            std::optional<InputAction> inputActionOpt = TryFind(keycode);
            if (inputActionOpt.has_value())
            {
                inputActionOpt->OnReleased.Invoke();
            }
        }

        void InputActionMapInternal::TryInvokingEntireMapOnHeld()
        {
            for (const auto& [keycode, inputAction] : map)
            {
                inputAction.OnHeld.Invoke();
            }
        }
    }
}