#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <vector>

enum class ObjectType {
    PLAYER,
    BLOCK,
    UNKNOWN
};

class Object {
    public:
        std::string name;
        float pos[2] = {0, 0};
        float size[2] = {0, 0};
        int color[3] = {255, 255, 255};

        ObjectType type = ObjectType::UNKNOWN;

        int rotation = 0;

        virtual void render(SDL_Renderer* renderer) {
            // Default render implementation
        }
        virtual void update(std::vector<SDL_Event> &events, float deltaTime) {
            // Default update implementation
        }
};