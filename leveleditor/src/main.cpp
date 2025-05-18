#include <wx/wx.h>

#include "ui/mainDisplay.hpp"
#include "editorParams.hpp"
#include "blockElement.hpp"
#include <wx/splitter.h>

#include "ui/blockSelector.hpp"
#include "ui/toolDisplay.hpp"

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
    void ToggleGrid(wxCommandEvent& event);
    void OnZoomIn(wxCommandEvent& event);
    void OnZoomOut(wxCommandEvent& event);
    void OnResetZoom(wxCommandEvent& event);
    
private:
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(EditorMainWindow, wxFrame)
    EVT_MENU(wxID_EXIT, EditorMainWindow::OnExit)
    EVT_MENU(wxID_HIGHEST + 1, EditorMainWindow::OnZoomIn)
    EVT_MENU(wxID_HIGHEST + 2, EditorMainWindow::OnZoomOut)
    EVT_MENU(wxID_HIGHEST + 3, EditorMainWindow::OnResetZoom)
    EVT_MENU(wxID_HIGHEST + 4, EditorMainWindow::ToggleGrid)
    
    EVT_MENU(wxID_HIGHEST + 5, GameEditorDisplay::MoveSelLeft)
    EVT_MENU(wxID_HIGHEST + 6, GameEditorDisplay::MoveSelRight)
    EVT_MENU(wxID_HIGHEST + 7, GameEditorDisplay::MoveSelUp)
    EVT_MENU(wxID_HIGHEST + 8, GameEditorDisplay::MoveSelDown)
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

    const int ID_ZOOM_IN = wxID_HIGHEST + 1;
    const int ID_ZOOM_OUT = wxID_HIGHEST + 2;
    const int ID_RESET_ZOOM = wxID_HIGHEST + 3;
    const int ID_SHOW_GRID = wxID_HIGHEST + 4;

    const int ID_MOVE_LEFT = wxID_HIGHEST + 5;
    const int ID_MOVE_RIGHT = wxID_HIGHEST + 6;
    const int ID_MOVE_UP = wxID_HIGHEST + 7;
    const int ID_MOVE_DOWN = wxID_HIGHEST + 8;

    wxMenu *menuView = new wxMenu;
    menuView->Append(ID_ZOOM_IN, "Zoom In\tCtrl-=");
    menuView->Append(ID_ZOOM_OUT, "Zoom Out\tCtrl--");
    menuView->Append(ID_RESET_ZOOM, "Reset Zoom\tCtrl-0");
    menuView->AppendSeparator();
    menuView->AppendCheckItem(ID_SHOW_GRID, "Show Grid\tCtrl-G");
    menuView->Check(ID_SHOW_GRID, true);

    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append(ID_MOVE_LEFT, "Move Left");
    menuEdit->Append(ID_MOVE_RIGHT, "Move Right");
    menuEdit->Append(ID_MOVE_UP, "Move Up");
    menuEdit->Append(ID_MOVE_DOWN, "Move Down");
    
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuView, "&View");
    menuBar->Append(menuEdit, "&Edit");
    
    SetMenuBar(menuBar);

    CreateStatusBar(2);

    wxPanel* topPanel = new wxPanel(this, wxID_ANY);
    
    ToolSelector* toolSelector = new ToolSelector(topPanel, wxID_ANY, 
                                wxDefaultPosition, wxSize(800, 60), 
                                wxTB_HORIZONTAL | wxTB_FLAT | wxTB_NODIVIDER);
    

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(toolSelector, 1, wxEXPAND);
    topPanel->SetSizer(topSizer);
    
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
    mainSizer->Add(topPanel, 0, wxEXPAND);
    mainSizer->Add(splitter, 1, wxEXPAND);
    SetSizer(mainSizer);
}

void EditorMainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void EditorMainWindow::ToggleGrid(wxCommandEvent& event)
{
    editorParams->showGrid = event.IsChecked();
    Refresh();
}

void EditorMainWindow::OnZoomIn(wxCommandEvent& event)
{
    editorParams->zoom += 0.1f;
    Refresh();
}

void EditorMainWindow::OnZoomOut(wxCommandEvent& event)
{
    editorParams->zoom -= 0.1f;
    Refresh();
}

void EditorMainWindow::OnResetZoom(wxCommandEvent& event)
{
    editorParams->zoom = 1.0f;
    Refresh();
}



int main(int argc, char **argv)
{
    return wxEntry(argc, argv);
}

wxIMPLEMENT_APP_NO_MAIN(LevelEditorApp);