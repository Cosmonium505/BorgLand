#pragma once
#include <wx/wx.h>
#include <vector>

class GameEditorDisplay : public wxPanel {
public:
    GameEditorDisplay(wxWindow* parent);
    ~GameEditorDisplay();

    void render(wxPaintDC& dc);
    void OnPaint(wxPaintEvent& event) {
        wxPaintDC dc(this);
        render(dc);
    }
    void update();
};