#pragma once
#include <wx/wx.h>
#include <vector>

class GameEditorDisplay : public wxPanel {
public:
    GameEditorDisplay(wxWindow* parent);
    ~GameEditorDisplay();

    bool dragging = false;
    wxPoint dragStartPos;
    wxPoint dragInitPos;

    void render(wxPaintDC& dc);
    void OnPaint(wxPaintEvent& event) {
        wxPaintDC dc(this);
        render(dc);
    }
    
    void OnDrag(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnScroll(wxMouseEvent& event);

    void MoveSelLeft(wxCommandEvent& event);
    void MoveSelRight(wxCommandEvent& event);
    void MoveSelUp(wxCommandEvent& event);
    void MoveSelDown(wxCommandEvent& event);

    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);

    void OnKeyPress(wxKeyEvent& event);


    void update();
};