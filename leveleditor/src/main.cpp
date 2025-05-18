#include <wx/wx.h>

#include "ui/mainDisplay.hpp"
#include "editorParams.hpp"
#include "blockElement.hpp"
#include <wx/splitter.h>
#include <string>

#include "mainWindow.hpp"

#include "ui/blockSelector.hpp"
#include "ui/toolDisplay.hpp"
#include "saveLevel.hpp"

EditorEngineParams *editorParams = new EditorEngineParams();

wxBEGIN_EVENT_TABLE(EditorMainWindow, wxFrame)
    EVT_MENU(wxID_EXIT, EditorMainWindow::OnExit)
    EVT_MENU(wxID_HIGHEST + 1, EditorMainWindow::OnZoomIn)
    EVT_MENU(wxID_HIGHEST + 2, EditorMainWindow::OnZoomOut)
    EVT_MENU(wxID_HIGHEST + 3, EditorMainWindow::OnResetZoom)
    EVT_MENU(wxID_HIGHEST + 9, EditorMainWindow::ReturnToHome)
    EVT_MENU(wxID_HIGHEST + 4, EditorMainWindow::ToggleGrid)
    
    EVT_MENU(wxID_HIGHEST + 5, GameEditorDisplay::MoveSelLeft)
    EVT_MENU(wxID_HIGHEST + 6, GameEditorDisplay::MoveSelRight)
    EVT_MENU(wxID_HIGHEST + 7, GameEditorDisplay::MoveSelUp)
    EVT_MENU(wxID_HIGHEST + 8, GameEditorDisplay::MoveSelDown)

    EVT_MENU(wxID_SAVE, EditorMainWindow::OnLevelSave)
    EVT_MENU(wxID_OPEN, EditorMainWindow::OnLevelLoad)
    EVT_MENU(wxID_FILE, EditorMainWindow::OnLevelExport)
    EVT_MENU(wxID_NEW, EditorMainWindow::NewLevel)
    EVT_MENU(wxID_UNDO, GameEditorDisplay::OnUndo)
    EVT_MENU(wxID_REDO, GameEditorDisplay::OnRedo)

    EVT_MENU(wxID_SELECTALL, EditorMainWindow::SelectAll)
    EVT_MENU(wxID_SELECT_FONT, EditorMainWindow::SelectType)
    EVT_MENU(wxID_MOVE_FRAME, GameEditorDisplay::MoveToSelected)
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
    menuFile->Append(wxID_NEW, "New\tCtrl-N");
    menuFile->Append(wxID_OPEN, "Open\tCtrl-O");
    menuFile->Append(wxID_FILE, "Export\tCtrl-E");
    menuFile->Append(wxID_SAVE, "Save\tCtrl-S");

    const int ID_ZOOM_IN = wxID_HIGHEST + 1;
    const int ID_ZOOM_OUT = wxID_HIGHEST + 2;
    const int ID_RESET_ZOOM = wxID_HIGHEST + 3;
    const int ID_SHOW_GRID = wxID_HIGHEST + 4;

    const int ID_MOVE_LEFT = wxID_HIGHEST + 5;
    const int ID_MOVE_RIGHT = wxID_HIGHEST + 6;
    const int ID_MOVE_UP = wxID_HIGHEST + 7;
    const int ID_MOVE_DOWN = wxID_HIGHEST + 8;

    const int ID_RETURN_HOME = wxID_HIGHEST + 9;

    wxMenu *menuView = new wxMenu;
    menuView->Append(ID_ZOOM_IN, "Zoom In\tCtrl-=");
    menuView->Append(ID_ZOOM_OUT, "Zoom Out\tCtrl--");
    menuView->Append(ID_RESET_ZOOM, "Reset Zoom\tCtrl-0");
    menuView->AppendSeparator();
    menuView->Append(ID_RETURN_HOME, "Return to Home\tCtrl-Home");
    menuView->AppendSeparator();
    menuView->AppendCheckItem(ID_SHOW_GRID, "Show Grid\tCtrl-G");
    menuView->Check(ID_SHOW_GRID, true);

    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append(ID_MOVE_LEFT, "Move Left");
    menuEdit->Append(ID_MOVE_RIGHT, "Move Right");
    menuEdit->Append(ID_MOVE_UP, "Move Up");
    menuEdit->Append(ID_MOVE_DOWN, "Move Down");
    menuEdit->AppendSeparator();
    menuEdit->Append(wxID_UNDO, "Undo\tCtrl-Z");
    menuEdit->Append(wxID_REDO, "Redo\tCtrl-Shift-Z");

    wxMenu *menuSelect = new wxMenu;
    menuSelect->Append(wxID_SELECTALL, "Select All\tCtrl-A");
    menuSelect->Append(wxID_SELECT_FONT, "Select type\tCtrl-T");
    menuSelect->AppendSeparator();
    menuSelect->Append(wxID_MOVE_FRAME, "Go to Selection\tCtrl-F");
    
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuView, "&View");
    menuBar->Append(menuEdit, "&Edit");
    menuBar->Append(menuSelect, "&Select");

    
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

void EditorMainWindow::OnLevelSave(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, "Save Level", "", "", 
        "Level Files (*.lvl)|*.lvl", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (saveFileDialog.ShowModal() == wxID_OK)
    {
        wxString path = saveFileDialog.GetPath();
        std::string filename = path.ToStdString();
        if (saveLevel(filename) == 0)
        {
            SetStatusText("Level saved successfully.");
        }
        else
        {
            wxMessageBox("Failed to save level.", "Error", wxOK | wxICON_ERROR);
            SetStatusText("Level save failed.");
        }
    }
}

void EditorMainWindow::OnLevelLoad(wxCommandEvent& event)
{
    EditorMainWindow::NewLevel(event);
    wxFileDialog openFileDialog(this, "Open Level", "", "", 
        "Level Files (*.lvl)|*.lvl", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openFileDialog.ShowModal() == wxID_OK)
    {
        wxString path = openFileDialog.GetPath();
        std::string filename = path.ToStdString();
        if (loadLevel(filename) == 0)
        {
            SetStatusText("Level loaded successfully.");
            Refresh();
        }
        else
        {
            wxMessageBox("Failed to load level.", "Error", wxOK | wxICON_ERROR);
            SetStatusText("Level load failed.");
        }
    }
}

void EditorMainWindow::SelectAll(wxCommandEvent& event)
{
    int amountSelected = 0;
    for (auto element : editorParams->elements)
    {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (block)
        {
            block->selected = true;
            amountSelected++;
        }
    }
    if (amountSelected > 0)
    {
        SetStatusText(wxString::Format("%d blocks selected.", amountSelected));
    }
    else
    {
        SetStatusText("No blocks found.");
    }
    Refresh();
}

void EditorMainWindow::SelectType(wxCommandEvent& event)
{
    int amountSelected = 0;
    for (auto element : editorParams->elements)
    {
        BlockElement* block = dynamic_cast<BlockElement*>(element);
        if (block)
        {
            block->selected = (block->blockType == editorParams->currentBlockType);
            if (block->selected)
            {
                amountSelected++;
            }
        }
    }
    Refresh();
    if (amountSelected > 0)
    {
        SetStatusText(wxString::Format("%d blocks of type %d selected.", amountSelected, editorParams->currentBlockType));
    }
    else
    {
        SetStatusText("No blocks of the selected type found.");
    }
}

void EditorMainWindow::OnLevelExport(wxCommandEvent& event)
{
    wxFileDialog exportFileDialog(this, "Export Level", "", "", 
        "Level Files (*.lvlc)|*.lvlc", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (exportFileDialog.ShowModal() == wxID_OK)
    {
        wxString path = exportFileDialog.GetPath();
        std::string filename = path.ToStdString();
        if (exportLevel(filename) == 0)
        {
            SetStatusText("Level exported successfully.");
        }
        else
        {
            wxMessageBox("Failed to export level.", "Error", wxOK | wxICON_ERROR);
            SetStatusText("Level export failed.");
        }
    }
}

void EditorMainWindow::NewLevel(wxCommandEvent& event)
{
    int response = wxMessageBox("Are you sure you want to create a new level? Unsaved changes will be lost.", 
                                 "Confirm New Level", wxYES_NO | wxCANCEL | wxICON_QUESTION);
    if (response == wxNO || response == wxCANCEL)
    {
        return;
    }

    editorParams->elements.clear();
    editorParams->cameraPos[0] = 0.0f;
    editorParams->cameraPos[1] = 0.0f;
    editorParams->zoom = 1.0f;
    Refresh();
}

int main(int argc, char **argv)
{
    return wxEntry(argc, argv);
}


wxIMPLEMENT_APP_NO_MAIN(LevelEditorApp);