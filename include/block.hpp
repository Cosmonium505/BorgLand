#pragma once
#include "object.hpp"
#include <SDL2/SDL.h>

class Block : public Object {
    public:
        Block() {
            size[0] = 50;
            size[1] = 50;
            blockType = 0;
            type = ObjectType::BLOCK;
        }
        int blockType = 0;

        virtual void render(SDL_Renderer* renderer) override;
        virtual void update(std::vector<SDL_Event> &events, float deltaTime) override;
};