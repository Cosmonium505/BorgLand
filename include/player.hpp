#pragma once

#include "object.hpp"

class Player : public Object {
    public:
        int health = 100;
        float size[2] = {50, 50};

        virtual void render(SDL_Renderer* renderer) override;
        virtual void update(std::vector<SDL_Event> &events, float deltaTime) override;
};