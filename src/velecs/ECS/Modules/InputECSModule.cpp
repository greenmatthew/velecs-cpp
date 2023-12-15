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

#include "velecs/ECS/Modules/RenderingECSModule.h"

#include "velecs/Math/Vec2.h"

#include <backends/imgui_impl_sdl2.h>

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
        .iter([this](flecs::iter& it, Input* inputs)
        {
            for (auto i : it)
            {
                Input& input = inputs[i];

                UpdateInput(it, input);
            }
        }
    );
}

// Public Methods

void InputECSModule::UpdateInput(flecs::iter& it, Input& input)
{
    input.prevKeyFlags = input.currKeyFlags;
    SDL_Event event;
    Vec2 mouseDelta = Vec2::ZERO;
    Vec2 mouseWheel = Vec2::ZERO;
    while (SDL_PollEvent(&event) != 0)
    {
        // Handle imgui input
        ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend

        switch (event.type)
        {
        case SDL_QUIT:
            input.isQuitting = true; // Set the flag to quit
            break;
        case SDL_WINDOWEVENT:
        {
            auto windowEvent = event.window.event;
            if (windowEvent == SDL_WINDOWEVENT_RESIZED ||
                windowEvent == SDL_WINDOWEVENT_MINIMIZED ||
                windowEvent == SDL_WINDOWEVENT_MAXIMIZED)
            {
                flecs::world ecs = it.world();
                flecs::entity moduleEntity = ecs.lookup("velecs::RenderingECSModule");
                if (moduleEntity == flecs::entity::null())
                {
                    std::cout << "Failure" << std::endl;
                }
                else
                {
                    RenderingECSModule* module = moduleEntity.get_mut<RenderingECSModule>();

                    switch(windowEvent)
                    {
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_MAXIMIZED:
                            module->OnWindowResize();
                            break;
                        case SDL_WINDOWEVENT_MINIMIZED:
                            module->OnWindowMinimize();
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
        }
        case SDL_KEYDOWN:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            if (event.key.repeat == 0)
            {
                input.currKeyFlags[keycode] = true;
            }
            break;
        }
        case SDL_KEYUP:
        {
            SDL_Keycode keycode = event.key.keysym.sym;
            input.currKeyFlags[keycode] = false;
            break;
        }
        case SDL_MOUSEMOTION:
            input.mousePos = Vec2(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
            mouseDelta += Vec2(static_cast<float>(event.motion.xrel), static_cast<float>(event.motion.yrel));
            break;
        case SDL_MOUSEWHEEL:
            mouseWheel += Vec2(static_cast<float>(event.wheel.x), static_cast<float>(event.wheel.y));
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
