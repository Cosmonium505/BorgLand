#pragma once
#include <string>

class EngineParams {
    public:
        int screenWidth = 800;
        int screenHeight = 600;
        std::string title = "Borgland";

        int engineTime = 0;
        int fpsLimiter = 60;
        bool frameLimitEnabled = true;
};

extern EngineParams engineParams;