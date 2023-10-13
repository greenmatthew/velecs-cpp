#include <Windows.h>
#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>

int SDL_main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow(
        "HarvestHavoc",                  // window title
        SDL_WINDOWPOS_UNDEFINED,         // initial x position
        SDL_WINDOWPOS_UNDEFINED,         // initial y position
        800,                             // width, in pixels
        600,                             // height, in pixels
        SDL_WINDOW_VULKAN                // flags - set to use Vulkan
    );

    if (window == nullptr) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Your game code here
    SDL_Delay(1000);

    // Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}