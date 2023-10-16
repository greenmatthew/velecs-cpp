#pragma once

#include "Input/InputAction.h"

#include <unordered_map>
#include <optional>

#include <SDL2/SDL.h>

namespace HarvestHavoc
{
    namespace Input
    {
        class InputActionMapInternal
        {
        private:
            static std::unordered_map<SDL_Keycode, InputAction> map;

            static bool isEnabled;

        protected:
            static std::optional<InputAction> TryCreateBinding(SDL_Keycode keycode);

        private:
            static std::optional<InputAction> TryFind(SDL_Keycode keycode);

            static void TryInvokingOnHeld(SDL_Keycode keycode);

        protected:
            static void TryInvokingOnPressed(SDL_Keycode keycode);

            static void TryInvokingOnReleased(SDL_Keycode keycode);

            static void TryInvokingEntireMapOnHeld();
        };

        class InputActionMap : public InputActionMapInternal
        {
        public:
            friend class InputAction;
            friend class VulkanEngine;
        };
    }
}