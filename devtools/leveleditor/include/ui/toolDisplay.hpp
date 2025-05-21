#pragma once

#include <wx/wx.h>

class ToolSelector : public wxToolBar {
public:
    ToolSelector(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
    ~ToolSelector();

    void OnSelect(wxCommandEvent& event);
    void OnDeselect(wxCommandEvent& event);

    void UpdateToolState();
};
