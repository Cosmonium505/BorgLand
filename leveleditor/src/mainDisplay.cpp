#include "ui/mainDisplay.hpp"

#include <wx/wx.h>
#include "utils/tileLoader.hpp"
#include "editorParams.hpp"
#include "editorElement.hpp"
#include "blockElement.hpp"


GameEditorDisplay::GameEditorDisplay(wxWindow* parent)
: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(800, 600))
{
    Bind(wxEVT_PAINT, &GameEditorDisplay::OnPaint, this);
    Bind(wxEVT_MOTION, &GameEditorDisplay::OnDrag, this);
    Bind(wxEVT_LEFT_DOWN, &GameEditorDisplay::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &GameEditorDisplay::OnLeftUp, this);
    Bind(wxEVT_MOUSEWHEEL, &GameEditorDisplay::OnScroll, this);

    Bind(wxEVT_KEY_DOWN, &GameEditorDisplay::OnKeyPress, this);
    
    IsFocusable();
    SetFocus();
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetDoubleBuffered(true);
}

GameEditorDisplay::~GameEditorDisplay()
{
    
}

void GameEditorDisplay::render(wxPaintDC& dc)
{
    dc.SetBackground(wxBrush(*wxBLACK));
    dc.Clear();
    
    
    if (editorParams->showGrid) {
        dc.SetPen(wxPen(wxColor(50, 50, 50), 1));
        float scaledGridSize = editorParams->gridSize * editorParams->zoom;
        
        float startX = -editorParams->cameraPos[0] * editorParams->zoom;
        float startY = -editorParams->cameraPos[1] * editorParams->zoom;
        
        float offsetX = fmod(startX, scaledGridSize);
        float offsetY = fmod(startY, scaledGridSize);
        
        for (float x = -offsetX; x < GetSize().GetWidth(); x += scaledGridSize) {
            dc.DrawLine(x, 0, x, GetSize().GetHeight());
        }
        
        for (float y = -offsetY; y < GetSize().GetHeight(); y += scaledGridSize) {
            dc.DrawLine(0, y, GetSize().GetWidth(), y);
        }
    }

    for (EditorElement* element : editorParams->elements) {
        element->render(dc);
    }
}


float roundToGrid(float value) {
    return floor(value / editorParams->gridSize) * editorParams->gridSize;
}

void GameEditorDisplay::update()
{
    
}

void GameEditorDisplay::OnLeftDown(wxMouseEvent& event)
{
    if (event.LeftIsDown()) {
        dragging = true;
        dragStartPos = event.GetPosition();
        dragInitPos = event.GetPosition();
        CaptureMouse();
    }
    SetFocus();
    Refresh();

}

void GameEditorDisplay::OnLeftUp(wxMouseEvent& event)
{
    if (dragging) {
        dragging = false;
        ReleaseMouse();
        bool isSelecting = false;

        bool isShiftDown = wxGetKeyState(WXK_SHIFT);

        float mouseDeltaDist = sqrt(pow(event.GetPosition().x - dragInitPos.x, 2) + pow(event.GetPosition().y - dragInitPos.y, 2));
        if (editorParams->currentTool == EditorTool::TOOL_SELECT && mouseDeltaDist < 5) {
            wxPoint currentPos = event.GetPosition();
            float gridX = roundToGrid(((currentPos.x / editorParams->zoom) - editorParams->cameraPos[0]));
            float gridY = roundToGrid(((currentPos.y / editorParams->zoom) - editorParams->cameraPos[1]));

            for (auto element : editorParams->elements) {
                BlockElement* block = dynamic_cast<BlockElement*>(element);
                if (block && block->x == gridX && block->y == gridY) {
                    if (isShiftDown) {
                        block->selected = !block->selected;
                    } else {
                        for (auto element : editorParams->elements) {
                            BlockElement* block1 = dynamic_cast<BlockElement*>(element);
                            if (block1) {
                                block1->selected = false;
                            }
                        }
                        block->selected = true;
                    }
                    isSelecting = true;
                    break;
                }
            }
            if (!isSelecting) {
            for (auto element : editorParams->elements) {
                BlockElement* block = dynamic_cast<BlockElement*>(element);
                if (block) {
                    block->selected = false;
                }
            }
        }
        }
        Refresh();
    }
}

void GameEditorDisplay::OnDrag(wxMouseEvent& event)
{
    if (dragging && editorParams->currentTool == EditorTool::TOOL_SELECT) {
        wxPoint currentPos = event.GetPosition();
        wxPoint delta = currentPos - dragStartPos;

        editorParams->cameraPos[0] += delta.x / editorParams->zoom;
        editorParams->cameraPos[1] += delta.y / editorParams->zoom;

        dragStartPos = currentPos;
        Refresh();
    }
    else if (dragging && editorParams->currentTool == EditorTool::TOOL_DRAW) {
        wxPoint currentPos = event.GetPosition();
        wxPoint delta = currentPos - dragStartPos;

        float gridX = roundToGrid(((currentPos.x / editorParams->zoom) - editorParams->cameraPos[0]));
        float gridY = roundToGrid(((currentPos.y / editorParams->zoom) - editorParams->cameraPos[1]));
        
        bool blockExists = false;
        if (editorParams->gridEnabled) {
            for (auto element : editorParams->elements) {
                BlockElement* block = dynamic_cast<BlockElement*>(element);
                if (block && block->x == gridX && block->y == gridY) {
                    blockExists = true;
                    break;
                }
            }
        }

        if (!blockExists) {
            BlockElement* block = new BlockElement(gridX, gridY, editorParams->gridSize, editorParams->gridSize);
            block->blockType = editorParams->currentBlockType;
            block->selected = false;
            editorParams->elements.push_back((EditorElement*)block);
        }

        dragStartPos = currentPos;
        Refresh();
    }
    else if(dragging && editorParams->currentTool == EditorTool::TOOL_ERASE) {
        wxPoint currentPos = event.GetPosition();
        wxPoint delta = currentPos - dragStartPos;

        float gridX = roundToGrid(((currentPos.x / editorParams->zoom) - editorParams->cameraPos[0]));
        float gridY = roundToGrid(((currentPos.y / editorParams->zoom) - editorParams->cameraPos[1]));

        for (auto it = editorParams->elements.begin(); it != editorParams->elements.end(); ) {
            BlockElement* block = dynamic_cast<BlockElement*>(*it);
            if (block && block->x == gridX && block->y == gridY) {
                it = editorParams->elements.erase(it);
            } else {
                ++it;
            }
        }

        dragStartPos = currentPos;
        Refresh();
    }
}

void GameEditorDisplay::OnScroll(wxMouseEvent& event)
{
    float wheelDelta = event.GetWheelRotation() > 0 ? 0.1f : -0.1f;

    float newZoom = editorParams->zoom + wheelDelta;
    editorParams->zoom = std::max(0.1f, std::min(5.0f, newZoom));

    Refresh();
}

void GameEditorDisplay::MoveSelLeft(wxCommandEvent& event) {
    bool shiftDown = wxGetKeyState(WXK_SHIFT);
    
    for (auto element : editorParams->elements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (block && block->selected) {
            if (shiftDown) {
                BlockElement* newBlock = new BlockElement(block->x - editorParams->gridSize, block->y, 
                                                         block->width, block->height);
                newBlock->blockType = block->blockType;

                for (EditorElement* existingElement : editorParams->elements) {
                    existingElement->selected = false;
                }
                newBlock->selected = true;
                editorParams->elements.push_back(newBlock);
            } else {
                block->x -= editorParams->gridSize;
            }
            break;
        }
    }
    Refresh();
}

void GameEditorDisplay::MoveSelRight(wxCommandEvent& event) {
    bool shiftDown = wxGetKeyState(WXK_SHIFT);
    
    for (auto element : editorParams->elements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (block && block->selected) {
            if (shiftDown) {
                BlockElement* newBlock = new BlockElement(block->x + editorParams->gridSize, block->y, 
                                                         block->width, block->height);
                newBlock->blockType = block->blockType;
                for (EditorElement* existingElement : editorParams->elements) {
                    existingElement->selected = false;
                }
                newBlock->selected = true;
                editorParams->elements.push_back(newBlock);
            } else {
                block->x += editorParams->gridSize;
            }
            break;
        }
    }
    Refresh();
}

void GameEditorDisplay::MoveSelUp(wxCommandEvent& event) {
    bool shiftDown = wxGetKeyState(WXK_SHIFT);
    
    for (auto element : editorParams->elements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (block && block->selected) {
            if (shiftDown) {
                BlockElement* newBlock = new BlockElement(block->x, block->y - editorParams->gridSize, 
                                                         block->width, block->height);
                newBlock->blockType = block->blockType;
                for (EditorElement* existingElement : editorParams->elements) {
                    existingElement->selected = false;
                }
                newBlock->selected = true;
                editorParams->elements.push_back(newBlock);
            } else {
                block->y -= editorParams->gridSize;
            }
            break;
        }
    }
    Refresh();
}

void GameEditorDisplay::MoveSelDown(wxCommandEvent& event) {
    bool shiftDown = wxGetKeyState(WXK_SHIFT);
    
    for (auto element : editorParams->elements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (block && block->selected) {
            if (shiftDown) {
                BlockElement* newBlock = new BlockElement(block->x, block->y + editorParams->gridSize, 
                                                         block->width, block->height);
                newBlock->blockType = block->blockType;
                for (EditorElement* existingElement : editorParams->elements) {
                    existingElement->selected = false;
                }
                newBlock->selected = true;
                editorParams->elements.push_back(newBlock);
            } else {
                block->y += editorParams->gridSize;
            }
            break;
        }
    }
    Refresh();
}

void GameEditorDisplay::OnKeyPress(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_DELETE) {
        for (auto it = editorParams->elements.begin(); it != editorParams->elements.end(); ) {
            BlockElement* block = dynamic_cast<BlockElement*>(*it);
            if (block && block->selected) {
                it = editorParams->elements.erase(it);
            } else {
                ++it;
            }
        }
        Refresh();
    }
    else if (event.GetKeyCode() == WXK_UP || event.GetKeyCode() == 'W') {
        wxCommandEvent cmdEvent;
        MoveSelUp(cmdEvent);
    }
    else if (event.GetKeyCode() == WXK_DOWN || event.GetKeyCode() == 'S') {
        wxCommandEvent cmdEvent;
        MoveSelDown(cmdEvent);
    }
    else if (event.GetKeyCode() == WXK_LEFT || event.GetKeyCode() == 'A') {
        wxCommandEvent cmdEvent;
        MoveSelLeft(cmdEvent);
    }
    else if (event.GetKeyCode() == WXK_RIGHT || event.GetKeyCode() == 'D') {
        wxCommandEvent cmdEvent;
        MoveSelRight(cmdEvent);
    }
}