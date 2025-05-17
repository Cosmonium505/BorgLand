#pragma once
#include "object.hpp"

class Block : public Object {
    public:

        virtual void render(SDL_Renderer* renderer) override;
        virtual void update(std::vector<SDL_Event> &events, float deltaTime) override;
};