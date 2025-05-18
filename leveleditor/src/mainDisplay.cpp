#include "ui/mainDisplay.hpp"

#include <wx/wx.h>
#include "utils/tileLoader.hpp"
#include "editorParams.hpp"
#include "editorElement.hpp"


GameEditorDisplay::GameEditorDisplay(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(800, 600))
{


}

GameEditorDisplay::~GameEditorDisplay()
{
    
}

void GameEditorDisplay::render(wxPaintDC& dc)
{
    dc.SetBackground(wxBrush(*wxBLACK));
    dc.Clear();

    for (EditorElement* element : editorParams->elements) {
        element->render(dc);
    }
}


void GameEditorDisplay::update()
{
    
}

