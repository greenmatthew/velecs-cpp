#include "Input/InputAction.h"
#include "Input/InputActionMap.h"

namespace HarvestHavoc
{
    namespace Input
    {
        InputAction::InputAction(SDL_Keycode keycode) : keycode(keycode) {}

        InputAction InputAction::Create(SDL_Keycode keycode)
        {
            auto inputAction = InputActionMap::TryCreateBinding(keycode);
            if (inputAction.has_value())
            {
                return inputAction.value();
            }
            else
            {
                throw std::runtime_error("[InputAction] Binding creation failed: a binding for key " + std::to_string(keycode) + " already exists.");
            }
        }
    }
}