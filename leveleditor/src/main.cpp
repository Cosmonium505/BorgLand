#include <wx/wx.h>

#include "ui/mainDisplay.hpp"
#include "editorParams.hpp"
#include "blockElement.hpp"

EditorEngineParams *editorParams = new EditorEngineParams();

class LevelEditorApp : public wxApp
{
public:
    virtual bool OnInit();
};

class EditorMainWindow : public wxFrame
{
public:
    EditorMainWindow(const wxString& title);

    void OnExit(wxCommandEvent& event);
    
private:
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(EditorMainWindow, wxFrame)
    EVT_MENU(wxID_EXIT, EditorMainWindow::OnExit)
    EVT_PAINT(GameEditorDisplay::OnPaint)
wxEND_EVENT_TABLE()

bool LevelEditorApp::OnInit()
{
    EditorMainWindow *frame = new EditorMainWindow("BorgLand Level Editor");
    frame->Show(true);
    return true;
}

EditorMainWindow::EditorMainWindow(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT, "Exit\tAlt-F4");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_OPEN, "Open\tCtrl-O");
    menuFile->Append(wxID_SAVE, "Save\tCtrl-S");
    
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    
    SetMenuBar(menuBar);

    CreateStatusBar(2);
    
    wxPanel* panel = new wxPanel(this);
    
    EditorElement* block = new BlockElement(100, 100, 50, 50);
    editorParams->elements.push_back(block);
    
    GameEditorDisplay* editorDisplay = new GameEditorDisplay(panel);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(editorDisplay, 1, wxEXPAND | wxALL, 5);
    panel->SetSizer(sizer);
    panel->Layout();
    
}

void EditorMainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

int main(int argc, char **argv)
{
    return wxEntry(argc, argv);
}

wxIMPLEMENT_APP_NO_MAIN(LevelEditorApp);