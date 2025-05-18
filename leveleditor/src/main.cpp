#include <wx/wx.h>

#include "ui/mainDisplay.hpp"
#include "editorParams.hpp"
#include "blockElement.hpp"
#include <wx/splitter.h>

#include "ui/blockSelector.hpp"

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
    
    wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY, 
                                wxDefaultPosition, wxDefaultSize, 
                                wxSP_BORDER | wxSP_LIVE_UPDATE);
    
    wxPanel* leftPanel = new wxPanel(splitter);
    wxPanel* rightPanel = new wxPanel(splitter);
    BlockSelector* blockSelector = new BlockSelector(rightPanel, GetId(), 
                              wxDefaultPosition, wxSize(200, 600), 
                              wxLB_SINGLE);
    
    
    EditorElement* block = new BlockElement(100, 100, 50, 50);
    editorParams->elements.push_back(block);

    GameEditorDisplay* editorDisplay = new GameEditorDisplay(leftPanel);
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
    rightSizer->Add(blockSelector, 1, wxEXPAND | wxALL, 5);
    rightPanel->SetSizer(rightSizer);

    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
    leftSizer->Add(editorDisplay, 1, wxEXPAND | wxALL, 5);
    leftPanel->SetSizer(leftSizer);
    
    splitter->SplitVertically(leftPanel, rightPanel);
    splitter->SetMinimumPaneSize(100);
    splitter->SetSashPosition(550);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(splitter, 1, wxEXPAND | wxALL, 0);
    SetSizer(mainSizer);
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