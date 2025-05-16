#include "world.hpp"
#include "SDL2/SDL.h"

void World::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    SDL_RenderClear(renderer);

    for (Object* obj : objects) {
        obj->render(renderer);
    }
    SDL_RenderPresent(renderer);
}

void World::update() {
    for (Object* obj : objects) {
        obj->update();
    }
}