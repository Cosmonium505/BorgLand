#include "ui/mainDisplay.hpp"

#include <wx/wx.h>
#include "utils/tileLoader.hpp"
#include "editorParams.hpp"
#include "editorElement.hpp"
#include "blockElement.hpp"

#include "mainWindow.hpp"

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
    if (editorParams->rectDragging) {
        dc.SetPen(wxPen(wxColor(255, 128, 0), 2));
        dc.SetBrush(wxBrush(wxColor(255, 128, 0, 50)));
        dc.DrawRectangle(editorParams->rectangleStart.x, editorParams->rectangleStart.y,
                        editorParams->rectangleEnd.x - editorParams->rectangleStart.x,
                        editorParams->rectangleEnd.y - editorParams->rectangleStart.y);
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
        if (editorParams->currentTool == EditorTool::TOOL_RECTANGLE_SELECT) {
            editorParams->rectangleStart = event.GetPosition();
            editorParams->rectangleEnd = event.GetPosition();
            editorParams->rectDragging = true;
        }
        dragging = true;
        dragStartPos = event.GetPosition();
        dragInitPos = event.GetPosition();
        CaptureMouse();
    }
    if (editorParams->currentTool != EditorTool::TOOL_SELECT) {
        SetUndoWaypoint();
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
        if (editorParams->rectDragging) {
            editorParams->selectedElements.clear();
            editorParams->rectangleEnd = event.GetPosition();
            editorParams->rectDragging = false;
            wxPoint start = editorParams->rectangleStart;
            wxPoint end = editorParams->rectangleEnd;

            float startX = (start.x + editorParams->cameraPos[0]) / editorParams->zoom;
            float startY = (start.y + editorParams->cameraPos[1]) / editorParams->zoom;
            float endX = (end.x + editorParams->cameraPos[0]) / editorParams->zoom;
            float endY = (end.y + editorParams->cameraPos[1]) / editorParams->zoom;

            if (startX > endX) {
                std::swap(startX, endX);
            }

            if (startY > endY) {
                std::swap(startY, endY);
            }

            for (auto element : editorParams->elements) {
                BlockElement* block = dynamic_cast<BlockElement*>(element);
                if (block && block->x >= startX && block->x <= endX &&
                    block->y >= startY && block->y <= endY) {
                    editorParams->selectedElements.push_back(block);
                }
            }
        }

        bool isShiftDown = wxGetKeyState(WXK_SHIFT);
        float mouseDeltaDist = sqrt(pow(event.GetPosition().x - dragInitPos.x, 2) + pow(event.GetPosition().y - dragInitPos.y, 2));

        if (editorParams->currentTool == EditorTool::TOOL_DRAW && mouseDeltaDist < 5) {
                wxPoint currentPos = event.GetPosition();
                float gridX = roundToGrid(((currentPos.x / editorParams->zoom) - editorParams->cameraPos[0]));
                float gridY = roundToGrid(((currentPos.y / editorParams->zoom) - editorParams->cameraPos[1]));

                BlockElement* gridBlock = new BlockElement(gridX, gridY, editorParams->gridSize, editorParams->gridSize);
                gridBlock->blockType = editorParams->currentBlockType;
                editorParams->elements.push_back((EditorElement*)gridBlock);
        }
        if (editorParams->currentTool == EditorTool::TOOL_SELECT && mouseDeltaDist < 5) {
            wxPoint currentPos = event.GetPosition();
            wxPoint delta = currentPos - dragStartPos;
            float gridX = roundToGrid(((currentPos.x / editorParams->zoom) - editorParams->cameraPos[0]));
            float gridY = roundToGrid(((currentPos.y / editorParams->zoom) - editorParams->cameraPos[1]));

            for (auto element : editorParams->elements) {
                BlockElement* block = dynamic_cast<BlockElement*>(element);
                if (block && block->x == gridX && block->y == gridY) {
                    if (isShiftDown) {
                        auto it = std::find(editorParams->selectedElements.begin(), editorParams->selectedElements.end(), block);
                        if (it != editorParams->selectedElements.end()) {
                            editorParams->selectedElements.erase(it);
                        } else {
                            editorParams->selectedElements.push_back(block);
                        }
                    } else {
                        editorParams->selectedElements.clear();
                        editorParams->selectedElements.push_back(block);
                    }
                    isSelecting = true;
                    break;
                }
            }
            
            if (!isSelecting) {
                editorParams->selectedElements.clear();
            }
        }
    }
    OnUpdate();
    Refresh();
}

void GameEditorDisplay::OnUpdate()
{
    int objectsSelected = editorParams->selectedElements.size();
    EditorMainWindow* mainWindow = dynamic_cast<EditorMainWindow*>(wxTheApp->GetTopWindow());
    if (mainWindow) {
        mainWindow->SetStatusText(wxString::Format("Objects Selected: %d", objectsSelected));
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
    if (editorParams->rectDragging) {
        editorParams->rectangleEnd = event.GetPosition();
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
    SetUndoWaypoint();
    bool shiftDown = wxGetKeyState(WXK_SHIFT);
    std::vector<EditorElement*> newSelectedElements;
    
    for (auto element: editorParams->selectedElements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (shiftDown) {
            BlockElement* newBlock = new BlockElement(block->x - editorParams->gridSize, block->y, 
                                                     block->width, block->height);
            newBlock->blockType = block->blockType;
            newSelectedElements.push_back(newBlock);  
            editorParams->elements.push_back(newBlock);                     
        }
        else {
            block->x -= editorParams->gridSize;
        
        }
    }
    if (shiftDown) {
        editorParams->selectedElements.clear();
        for (auto element : newSelectedElements) {
            BlockElement* block = dynamic_cast<BlockElement*>(element);
            if (block) {
                editorParams->selectedElements.push_back(block);
            }
        }
    }
    Refresh();
}

void GameEditorDisplay::MoveSelRight(wxCommandEvent& event) {
    SetUndoWaypoint();
    bool shiftDown = wxGetKeyState(WXK_SHIFT);
    std::vector<EditorElement*> newSelectedElements;
    
    for (auto element: editorParams->selectedElements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (shiftDown) {
            BlockElement* newBlock = new BlockElement(block->x + editorParams->gridSize, block->y, 
                                                     block->width, block->height);
            newBlock->blockType = block->blockType;
            newSelectedElements.push_back(newBlock);  
            editorParams->elements.push_back(newBlock);                     
        }
        else {
            block->x += editorParams->gridSize;
        
        }
    }
    if (shiftDown) {
        editorParams->selectedElements.clear();
        for (auto element : newSelectedElements) {
            BlockElement* block = dynamic_cast<BlockElement*>(element);
            if (block) {
                editorParams->selectedElements.push_back(block);
            }
        }
    }
    Refresh();
}

void GameEditorDisplay::MoveSelUp(wxCommandEvent& event) {
    SetUndoWaypoint();
    bool shiftDown = wxGetKeyState(WXK_SHIFT);
    std::vector<EditorElement*> newSelectedElements;
    
    for (auto element: editorParams->selectedElements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (shiftDown) {
            BlockElement* newBlock = new BlockElement(block->x, block->y - editorParams->gridSize, 
                                                     block->width, block->height);
            newBlock->blockType = block->blockType;
            newSelectedElements.push_back(newBlock);  
            editorParams->elements.push_back(newBlock);                     
        }
        else {
            block->y -= editorParams->gridSize;
        
        }
    }
    if (shiftDown) {
        editorParams->selectedElements.clear();
        for (auto element : newSelectedElements) {
            BlockElement* block = dynamic_cast<BlockElement*>(element);
            if (block) {
                editorParams->selectedElements.push_back(block);
            }
        }
    }
    Refresh();
}

void SetUndoWaypoint() {
    if (editorParams->currentUndoIndex < editorParams->undoStack.size() - 1 && editorParams->currentUndoIndex > 0) {
        editorParams->undoStack.erase(editorParams->undoStack.begin() + editorParams->currentUndoIndex + 1, 
                                    editorParams->undoStack.end());
    }

    std::vector<EditorElement*> copyElements;
    for (auto element : editorParams->elements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (block) {
            BlockElement* newBlock = new BlockElement(block->x, block->y, block->width, block->height);
            newBlock->blockType = block->blockType;
            copyElements.push_back(newBlock);
        }
    }
    editorParams->undoStack.push_back(copyElements);
    editorParams->currentUndoIndex++;
}

void GameEditorDisplay::MoveSelDown(wxCommandEvent& event) {
    SetUndoWaypoint();
    bool shiftDown = wxGetKeyState(WXK_SHIFT);
    std::vector<EditorElement*> newSelectedElements;
    
    for (auto element: editorParams->selectedElements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (shiftDown) {
            BlockElement* newBlock = new BlockElement(block->x, block->y + editorParams->gridSize, 
                                                     block->width, block->height);
            newBlock->blockType = block->blockType;
            newSelectedElements.push_back(newBlock);  
            editorParams->elements.push_back(newBlock);                     
        }
        else {
            block->y += editorParams->gridSize;
        
        }
    }
    if (shiftDown) {
        editorParams->selectedElements.clear();
        for (auto element : newSelectedElements) {
            BlockElement* block = dynamic_cast<BlockElement*>(element);
            if (block) {
                editorParams->selectedElements.push_back(block);
            }
        }
    }
    Refresh();
}

void GameEditorDisplay::MoveToSelected(wxCommandEvent& event) {
    for (auto element : editorParams->selectedElements) {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        float blockCenterX = block->x + block->width / 2;
        float blockCenterY = block->y + block->height / 2;
        
        editorParams->cameraPos[0] = (-(blockCenterX));
        editorParams->cameraPos[1] = (-(blockCenterY));
        break;
    }
    Refresh();
}

void GameEditorDisplay::OnKeyPress(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_DELETE) {
        SetUndoWaypoint();
        for (EditorElement* element : editorParams->selectedElements) {
            auto it = std::find(editorParams->elements.begin(), editorParams->elements.end(), element);
            if (it != editorParams->elements.end()) {
                editorParams->elements.erase(it);
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
    else {
        event.Skip();
    }
}

void GameEditorDisplay::OnUndo(wxCommandEvent& event) {
    if (editorParams->currentUndoIndex > 0) {
        editorParams->currentUndoIndex--;
        editorParams->elements = editorParams->undoStack[editorParams->currentUndoIndex];
        Refresh();
    }
}

void GameEditorDisplay::OnRedo(wxCommandEvent& event) {
    if (editorParams->currentUndoIndex < editorParams->undoStack.size() - 1) {
        editorParams->currentUndoIndex++;
        editorParams->elements = editorParams->undoStack[editorParams->currentUndoIndex];
        Refresh();
    }
}