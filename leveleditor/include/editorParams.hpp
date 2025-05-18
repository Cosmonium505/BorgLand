#pragma once

#include <vector>
#include "editorElement.hpp"

class EditorEngineParams {
    public:
        float cameraPos[2] = {0.0f, 0.0f};
        float zoom = 1.0f;
        float gridSize = 50.0f;
        bool showGrid = true;
        bool gridEnabled = true;

        std::vector<EditorElement*> elements;
};

extern EditorEngineParams *editorParams;