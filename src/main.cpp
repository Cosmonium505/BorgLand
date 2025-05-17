#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>

#include "object.hpp"
#include "world.hpp"
#include "player.hpp"
#include "block.hpp"

#include "engine.hpp"
#include "utils/tileLoader.hpp"

#undef main


int testTileMap[20][20] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

EngineParams engineParams;
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Hello SDL2",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
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

    std::vector<Tile> tiles = convertBitmaskToTilemap((int*)testTileMap, 20, 20);
    for (Tile& tile : tiles) {
        if (tile.type == 1) {
            Block* block = new Block();
            block->name = "Block";
            block->pos[0] = tile.x * 50;
            block->pos[1] = tile.y * 50;
            block->size[0] = 50;
            block->size[1] = 50;
            block->color[0] = 200;
            block->color[1] = 200;
            block->color[2] = 200;
            world.objects.push_back(block);
        }
        else if (tile.type == 2) {
            Player* player = new Player();
            player->name = "Player";
            player->pos[0] = tile.x * 50;
            player->pos[1] = tile.y * 50;
            world.objects.push_back(player);
        }

    }


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
            SDL_SetWindowTitle(window, (engineParams.title + " - FPS: " + std::to_string(static_cast<int>(1.0f / deltaTime))).c_str());
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