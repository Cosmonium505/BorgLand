#pragma once

#include <string>
#include <SDL2/SDL.h>

class Object {
    public:
        std::string name;
        float pos[2] = {0, 0};
        float size[2] = {0, 0};
        int color[3] = {255, 255, 255};

        int rotation = 0;

        virtual void render(SDL_Renderer* renderer) {
            // Default render implementation
        }
        virtual void update() {
            // Default update implementation
        }
};