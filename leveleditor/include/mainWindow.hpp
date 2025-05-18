#pragma once

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
    void ToggleGrid(wxCommandEvent& event);
    void OnZoomIn(wxCommandEvent& event);
    void OnZoomOut(wxCommandEvent& event);
    void OnResetZoom(wxCommandEvent& event);
    void OnUpdate();

    void OnLevelSave(wxCommandEvent& event);
    void OnLevelLoad(wxCommandEvent& event);
    void OnLevelExport(wxCommandEvent& event);

    void ReturnToHome(wxCommandEvent& event) {
        editorParams->cameraPos[0] = 0.0f;
        editorParams->cameraPos[1] = 0.0f;
        editorParams->zoom = 1.0f;
        EditorMainWindow::Refresh();
    }

    void NewLevel(wxCommandEvent& event);
    
private:
    wxDECLARE_EVENT_TABLE();
};