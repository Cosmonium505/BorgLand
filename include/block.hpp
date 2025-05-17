#pragma once
#include "object.hpp"

class Block : public Object {
    public:
        Block() {
            size[0] = 50;
            size[1] = 50;
            type = ObjectType::BLOCK;
        }

        virtual void render(SDL_Renderer* renderer) override;
        virtual void update(std::vector<SDL_Event> &events, float deltaTime) override;
};