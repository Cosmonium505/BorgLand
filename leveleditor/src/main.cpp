#include <wx/wx.h>

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
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    
private:
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(EditorMainWindow, wxFrame)
    EVT_MENU(wxID_EXIT, EditorMainWindow::OnExit)
    EVT_MENU(wxID_OPEN, EditorMainWindow::OnOpen)
    EVT_MENU(wxID_SAVE, EditorMainWindow::OnSave)
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
    menuFile->Append(wxID_EXIT, "Exit\tAlt-F4", "Quit this program");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_OPEN, "Open\tCtrl-O", "Open a file");
    menuFile->Append(wxID_SAVE, "Save\tCtrl-S", "Save the current file");
    
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    
    SetMenuBar(menuBar);

    CreateStatusBar(2);
    SetStatusText("Welcome to BorgLand Level Editor");
    
    wxPanel* panel = new wxPanel(this);
}

void EditorMainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

wxIMPLEMENT_APP(LevelEditorApp);