#include "block.hpp"
#include "engine.hpp"

void Block::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    SDL_FRect rect = { pos[0] - engineParams.currentWorld->worldpos[0], pos[1] - engineParams.currentWorld->worldpos[1], size[0], size[1] };
    const SDL_Rect textureAtlasUV = { static_cast<int>(blockType * 24), static_cast<int>(floor(blockType/8)) * 24, 24, 24 };
    SDL_RenderCopyF(renderer, engineParams.blockAtlas, &textureAtlasUV, &rect);
}

void Block::update(std::vector<SDL_Event> &events, float deltaTime) {
    // Block update logic here
}