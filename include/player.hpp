#pragma once

#include "object.hpp"

class Player : public Object {
    public:
        Player() {
            size[0] = 30;
            size[1] = 30;
            type = ObjectType::PLAYER;
        }

        int health = 100;
        float size[2] = {50, 50};

        float speed = 1700.0f;
        float jumppower = -500.0f;
        float velocity[2] = {0.0f, 0.0f};
        float friction = 0.90f;

        ObjectType type = ObjectType::PLAYER;

        virtual void render(SDL_Renderer* renderer) override;
        virtual void update(std::vector<SDL_Event> &events, float deltaTime) override;
};