#pragma once
#include <wx/wx.h>

class BlockSelector : public wxListBox {
public:
    BlockSelector(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
    ~BlockSelector();

    void OnSelect(wxCommandEvent& event);
    void OnDeselect(wxCommandEvent& event);
};