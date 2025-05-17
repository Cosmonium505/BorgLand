#include "block.hpp"
#include "engine.hpp"

void Block::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    SDL_Rect rect = { static_cast<int>(pos[0] - engineParams.currentWorld->worldpos[0]), static_cast<int>(pos[1] - engineParams.currentWorld->worldpos[1]), static_cast<int>(size[0]), static_cast<int>(size[1])};
    SDL_RenderFillRect(renderer, &rect);
}

void Block::update(std::vector<SDL_Event> &events, float deltaTime) {
    // Block update logic here
}