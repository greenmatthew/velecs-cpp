/// @file    InputECSModule.cpp
/// @author  Matthew Green
/// @date    2023-11-13 16:03:55
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2023 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/ECS/Modules/InputECSModule.h"

#include "velecs/Math/Vec2.h"

namespace velecs {

// Public Fields

// Constructors and Destructors

InputECSModule::InputECSModule(flecs::world& ecs)
    : IECSModule(ecs)
{
    ecs.component<Input>();

    ecs.set<Input>({});

    ecs.system<Input>()
        .kind(stages->InputUpdate)
        .each(&InputECSModule::UpdateInput);
}

// Public Methods

void InputECSModule::UpdateInput(flecs::entity e, Input& input)
{
    input.prevKeyFlags = input.currKeyFlags;
    SDL_Event event;
    Vec2 mouseDelta = Vec2::ZERO;
    Vec2 mouseWheel = Vec2::ZERO;
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            input.isQuitting = true; // Set the flag to quit
            break;
        case SDL_KEYDOWN:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            if (event.key.repeat == 0)
            {
                input.currKeyFlags[keycode] = true;
                #ifdef DEBUG_INPUT
                std::cout << "Key Pressed: " << SDL_GetKeyName(keycode) << '\n';
                std::cout << "Key GetState(): ";
                switch (input.GetState(keycode))
                {
                case Input::State::Pressed:
                    std::cout << "Pressed";
                    break;
                case Input::State::Held:
                    std::cout << "Held";
                    break;
                case Input::State::Released:
                    std::cout << "Released";
                    break;
                case Input::State::Idle:
                    std::cout << "Idle";
                    break;
                }
                std::cout << '\n';
                std::cout << "input.prevKeyFlags: " << input.prevKeyFlags[keycode] << '\n';
                std::cout << "input.currKeyFlags[keycode]: " << input.currKeyFlags[keycode] << '\n';
                std::cout << '\n' << std::endl;
                #endif
            }
            break;
        }
        case SDL_KEYUP:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            input.currKeyFlags[keycode] = false;
            #ifdef DEBUG_INPUT
            std::cout << "Key Released: " << SDL_GetKeyName(keycode) << '\n';
            std::cout << "Key GetState(): ";
            switch (input.GetState(keycode))
            {
            case Input::State::Pressed:
                std::cout << "Pressed";
                break;
            case Input::State::Held:
                std::cout << "Held";
                break;
            case Input::State::Released:
                std::cout << "Released";
                break;
            case Input::State::Idle:
                std::cout << "Idle";
                break;
            }
            std::cout << '\n';
            std::cout << "input.prevKeyFlags: " << input.prevKeyFlags[keycode] << '\n';
            std::cout << "input.currKeyFlags[keycode]: " << input.currKeyFlags[keycode] << '\n';
            std::cout << '\n' << std::endl;
            #endif
            break;
        }
        case SDL_MOUSEMOTION:
            input.mousePos = Vec2(event.motion.x, event.motion.y);
            mouseDelta += Vec2(event.motion.xrel, event.motion.yrel);
            break;
        case SDL_MOUSEWHEEL:
            mouseWheel += Vec2(event.wheel.x, event.wheel.y);
            break;
        default:
            break;
        }
    }

    input.mouseDelta = mouseDelta;
    input.mouseWheel = mouseWheel;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private ECS/Methods

} // namespace velecs
