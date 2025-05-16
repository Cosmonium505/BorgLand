#include "player.hpp"
#include "engine.hpp"

void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    SDL_Rect rect = { static_cast<int>(pos[0]), static_cast<int>(pos[1]), static_cast<int>(size[0]), static_cast<int>(size[1]) };
    SDL_RenderFillRect(renderer, &rect);
}

void Player::update(std::vector<SDL_Event> &events, float deltaTime) {
    if (pos[0] > engineParams.screenWidth - size[0]) {
        pos[0] = 0;
    }
    if (pos[1] > engineParams.screenHeight - size[1]) {
        pos[1] = 0;
    }
    pos[0] += 80.0f * deltaTime;
    pos[1] += 80.0f * deltaTime;
}