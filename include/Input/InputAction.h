#pragma once

#include "Input/Event.h"

#include <stdexcept>

#include <SDL2/SDL.h>

namespace HarvestHavoc
{
    namespace Input
    {
        class InputAction
        {
        public:
            friend class InputActionMap;
            friend class InputActionMapInternal;

        private:
            SDL_Keycode keycode;

            InputAction(SDL_Keycode keycode);

        public:
            static InputAction Create(SDL_Keycode keycode);
            
            Event<> OnPressed;
            Event<> OnHeld;
            Event<> OnReleased;
        };
    }
}