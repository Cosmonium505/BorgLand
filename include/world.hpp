#pragma once

#include <vector>

#include "object.hpp"

class World {
    public:
        int color[3] = {0, 0, 0};

        std::vector<Object*> objects;

        virtual void render(SDL_Renderer* renderer);
        virtual void update(std::vector<SDL_Event> events, float deltaTime);
};