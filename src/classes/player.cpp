#include "player.hpp"
#include "engine.hpp"

void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    SDL_Rect rect = { static_cast<int>(pos[0]), static_cast<int>(pos[1]), static_cast<int>(size[0]), static_cast<int>(size[1]) };
    SDL_RenderFillRect(renderer, &rect);
}

void Player::update(std::vector<SDL_Event> &events, float deltaTime) {
    if (engineParams.keys[SDL_SCANCODE_W]) {
        pos[1] -= speed * deltaTime;
    }
    else if (engineParams.keys[SDL_SCANCODE_S]) {
        pos[1] += speed * deltaTime;
    }
    if (engineParams.keys[SDL_SCANCODE_A]) {
        pos[0] -= speed * deltaTime;
    }
    else if (engineParams.keys[SDL_SCANCODE_D]) {
        pos[0] += speed * deltaTime;
    }
}