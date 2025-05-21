#pragma once

#include <vector>
#include "editorElement.hpp"

enum EditorTool {
    TOOL_SELECT,
    TOOL_DRAW,
    TOOL_ERASE,
    TOOL_RECTANGLE_SELECT
};

class EditorEngineParams {
    public:
        float cameraPos[2] = {0.0f, 0.0f};
        float zoom = 1.0f;
        float gridSize = 50.0f;
        bool showGrid = true;
        bool gridEnabled = true;
        int currentBlockType = 0;
        EditorTool currentTool = TOOL_SELECT;
        int currentUndoIndex = 0;
        wxPoint rectangleStart;
        wxPoint rectangleEnd;
        bool rectDragging = false;

        wxImage blockAtlas;

        std::vector<EditorElement*> selectedElements;

        std::vector<std::vector<EditorElement*>> undoStack;

        std::vector<EditorElement*> elements;
};

extern EditorEngineParams *editorParams;

void SetUndoWaypoint();
float roundToGrid(float value);