#pragma once

#include <vector>

#include "object.hpp"

class World {
    public:
        int color[3] = {0, 0, 0};
        float gravity[2] = {0.0f, 1000.0f};
        float worldpos[2] = {0.0f, 0.0f};

        std::vector<Object*> objects;

        virtual void render(SDL_Renderer* renderer);
        virtual void update(std::vector<SDL_Event> events, float deltaTime);
};