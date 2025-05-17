#include "world.hpp"
#include "player.hpp"
#include "engine.hpp"

void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    SDL_Rect rect = { static_cast<int>(pos[0] - engineParams.currentWorld->worldpos[0]), static_cast<int>(pos[1] - engineParams.currentWorld->worldpos[1]), static_cast<int>(size[0]), static_cast<int>(size[1])};
    SDL_RenderFillRect(renderer, &rect);
}

void Player::update(std::vector<SDL_Event> &events, float deltaTime) {
    if (pos[0] > (engineParams.screenWidth - size[0] + engineParams.currentWorld->worldpos[0])) {
        engineParams.currentWorld->worldpos[0] += speed * deltaTime;
    }

    if (engineParams.keys[SDL_SCANCODE_A] || engineParams.keys[SDL_SCANCODE_LEFT]) {
        velocity[0] -= speed * deltaTime;
    }
    else if (engineParams.keys[SDL_SCANCODE_D] || engineParams.keys[SDL_SCANCODE_RIGHT]) {
        velocity[0] += speed * deltaTime;
    }
    velocity[0] *= friction;

    velocity[0] += engineParams.currentWorld->gravity[0] * deltaTime;
    velocity[1] += engineParams.currentWorld->gravity[1] * deltaTime;

    pos[0] += velocity[0] * deltaTime;
    pos[1] += velocity[1] * deltaTime;

    if (pos[1] > engineParams.screenHeight - size[1]) {
        pos[1] = engineParams.screenHeight - size[1];
        for (SDL_Event& event : events) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_SPACE) {
                    velocity[1] = jumppower;
                }
            }
        }
        //velocity[1] *= -0.9f; bounci
    }
}