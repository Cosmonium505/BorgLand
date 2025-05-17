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

    if (pos[1] > (engineParams.screenHeight - size[1] + engineParams.currentWorld->worldpos[1])) {
        engineParams.currentWorld->worldpos[1] += speed * deltaTime;
    } else if(pos[1] <= engineParams.currentWorld->worldpos[1]) {
        engineParams.currentWorld->worldpos[1] -= speed * deltaTime;
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
    // Calculate movement vector
    float moveX = pos[0] - prevX;
    float moveY = pos[1] - prevY;
    
    for (Object* block : engineParams.currentWorld->objects) {
        if (block->type != ObjectType::BLOCK) {
            continue;
        }
        float blockX = block->pos[0];
        float blockY = block->pos[1];
        float blockWidth = block->size[0];
        float blockHeight = block->size[1];

        float testX = prevX + (moveX > 0 ? 0 : moveX);
        float testY = prevY + (moveY > 0 ? 0 : moveY);
        float testWidth = size[0] + std::abs(moveX);
        float testHeight = size[1] + std::abs(moveY);
        
        if (testX < blockX + blockWidth &&
            testX + testWidth > blockX &&
            testY < blockY + blockHeight &&
            testY + testHeight > blockY) {

            float tNearX = (moveX == 0) ? -INFINITY : (moveX > 0 ? (blockX - (prevX + size[0])) : ((blockX + blockWidth) - prevX)) / moveX;
            float tNearY = (moveY == 0) ? -INFINITY : (moveY > 0 ? (blockY - (prevY + size[1])) : ((blockY + blockHeight) - prevY)) / moveY;
            float tFarX = (moveX == 0) ? INFINITY : (moveX > 0 ? ((blockX + blockWidth) - prevX) : (blockX - (prevX + size[0]))) / moveX;
            float tFarY = (moveY == 0) ? INFINITY : (moveY > 0 ? ((blockY + blockHeight) - prevY) : (blockY - (prevY + size[1]))) / moveY;

            float tHit = std::max(tNearX, tNearY);
            float tExit = std::min(tFarX, tFarY);

            if (tExit >= tHit && tHit >= 0 && tHit <= 1) {
                if (tNearX > tNearY) {
                    velocity[0] = 0;
                    if (moveX > 0) {
                        pos[0] = blockX - size[0];
                    } else {
                        pos[0] = blockX + blockWidth;
                    }
                } else {
                    velocity[1] = 0;
                    if (moveY > 0) {
                        pos[1] = blockY - size[1];
                        onGround = true;
                    } else {
                        pos[1] = blockY + blockHeight;
                    }
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