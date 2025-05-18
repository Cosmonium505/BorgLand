#pragma once

#include <vector>
#include "editorElement.hpp"

enum EditorTool {
    TOOL_SELECT,
    TOOL_DRAW,
    TOOL_ERASE
};

class EditorEngineParams {
    public:
        float cameraPos[2] = {0.0f, 0.0f};
        float zoom = 1.0f;
        float gridSize = 50.0f;
        bool showGrid = true;
        bool gridEnabled = true;
        EditorTool currentTool = TOOL_SELECT;

        std::vector<EditorElement*> elements;
};

extern EditorEngineParams *editorParams;

float roundToGrid(float value);