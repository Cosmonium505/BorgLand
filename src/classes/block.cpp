#include "block.hpp"
#include "engine.hpp"
#include "blockProps.hpp"
#include <iostream>

void Block::render(SDL_Renderer* renderer) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    int atlasX = (blockType % 8) * 24;
    int atlasY = floor(blockType / 8) * 24;
    SDL_FRect rect = { pos[0] - engineParams.currentWorld->worldpos[0], pos[1] - engineParams.currentWorld->worldpos[1], size[0], size[1] };
    const SDL_Rect textureAtlasUV = { atlasX, atlasY, 24, 24 };
    SDL_RenderCopyF(renderer, engineParams.blockAtlas, &textureAtlasUV, &rect);
}

void Block::update(std::vector<SDL_Event> &events, float deltaTime) {
    if (special & BLOCK_PROPS_KILL) {
        pos[0] += 1;
    }
}