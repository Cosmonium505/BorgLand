#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <vector>

class EngineParams {
    public:
        int screenWidth = 800;
        int screenHeight = 600;
        std::string title = "Borgland";

        std::vector<Uint8*> keys;
        

        int engineTime = 0;
        int fpsLimiter = 60;
        bool frameLimitEnabled = true;

        bool showFPS = true;
};

extern EngineParams engineParams;