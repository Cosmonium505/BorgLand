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
    } else if(pos[0] <= engineParams.currentWorld->worldpos[0]) {
        engineParams.currentWorld->worldpos[0] -= speed * deltaTime;
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

    float prevX = pos[0];
    float prevY = pos[1];
    
    pos[0] += velocity[0] * deltaTime;
    pos[1] += velocity[1] * deltaTime;

    bool onGround = false;
    for (Object* block : engineParams.currentWorld->objects) {
        float blockX = block->pos[0];
        float blockY = block->pos[1];
        float blockWidth = block->size[0];
        float blockHeight = block->size[1];
        
        if (pos[0] < blockX + blockWidth &&
            pos[0] + size[0] > blockX &&
            pos[1] < blockY + blockHeight &&
            pos[1] + size[1] > blockY) {
            
            float overlapX1 = (pos[0] + size[0]) - blockX;
            float overlapX2 = (blockX + blockWidth) - pos[0];
            float overlapY1 = (pos[1] + size[1]) - blockY;
            float overlapY2 = (blockY + blockHeight) - pos[1];
            
            float overlapX = (overlapX1 < overlapX2) ? overlapX1 : overlapX2;
            float overlapY = (overlapY1 < overlapY2) ? overlapY1 : overlapY2;
            
            if (overlapX < overlapY) {
                if (prevX + size[0] <= blockX) {
                    pos[0] = blockX - size[0];
                    velocity[0] = 0;
                } else if (prevX >= blockX + blockWidth) {
                    pos[0] = blockX + blockWidth;
                    velocity[0] = 0;
                }
            } else {
                if (prevY + size[1] <= blockY) {
                    pos[1] = blockY - size[1];
                    velocity[1] = 0;
                    onGround = true;
                } else if (prevY >= blockY + blockHeight) {
                    pos[1] = blockY + blockHeight;
                    velocity[1] = 0;
                }
            }
        }
    }

    /*
    if (pos[1] > engineParams.screenHeight - size[1]) {
        pos[1] = engineParams.screenHeight - size[1];
        onGround = true;
    }
    */
    
    if (onGround) {
        for (SDL_Event& event : events) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_SPACE) {
                    velocity[1] = jumppower;
                }
            }
        }
    }
}