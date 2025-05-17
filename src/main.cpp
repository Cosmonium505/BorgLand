#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>

#include "object.hpp"
#include "world.hpp"
#include "player.hpp"

#include "engine.hpp"

#undef main

EngineParams engineParams;
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Hello SDL2",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return 1;
    }

    // Engine setup
    engineParams.screenWidth = 1280;
    engineParams.screenHeight = 720;
    engineParams.title = "Borgland";
    engineParams.engineTime = 0;
    
    // World Setup

    World world;
    engineParams.currentWorld = &world;
    Player player;
    player.name = "Player";

    world.objects.push_back(&player);


    // End world setup

    SDL_Event event;
    bool running = true;

    std::vector<SDL_Event> events;
    std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0f;
    while (running) {
        deltaTime = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - lastTime).count();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else {
                events.push_back(event);
            }

            int size = 0;
            SDL_GetKeyboardState(&size);
            const Uint8* state = SDL_GetKeyboardState(&size);
            engineParams.keys.clear();
            for (int i = 0; i < size; ++i) {
                engineParams.keys.push_back((Uint8*)state[i]);
            }
        }
        engineParams.engineTime++;
        world.update(std::vector<SDL_Event>(events), deltaTime);
        world.render(renderer);
        events.clear();

        if (engineParams.showFPS) {
            SDL_SetWindowTitle(window, (engineParams.title + " - FPS: " + std::to_string(1.0f / deltaTime)).c_str());
        }
        else {
            SDL_SetWindowTitle(window, engineParams.title.c_str());
        }

        SDL_SetWindowSize(window, engineParams.screenWidth, engineParams.screenHeight);

        lastTime = std::chrono::high_resolution_clock::now();
        if (engineParams.frameLimitEnabled) {
            SDL_Delay(1000 / engineParams.fpsLimiter);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}