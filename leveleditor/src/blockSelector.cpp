#include "ui/blockSelector.hpp"

BlockSelector::BlockSelector(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxListBox(parent, id, pos, size, 0, nullptr, style | wxLB_SINGLE) {
    Append("Block 1");
    Append("Block 2");
    Append("Block 3");

    
    Bind(wxEVT_LISTBOX, &BlockSelector::OnSelect, this);
}
BlockSelector::~BlockSelector()
{
    // Destructor
}

void BlockSelector::OnSelect(wxCommandEvent& event)
{
    int selection = GetSelection();
    if (selection != wxNOT_FOUND) {
        wxString selectedItem = GetString(selection);
        wxLogMessage("Selected: %s", selectedItem);
    }
}

void BlockSelector::OnDeselect(wxCommandEvent& event)
{
    int selection = GetSelection();
    if (selection != wxNOT_FOUND) {
        wxString selectedItem = GetString(selection);
        wxLogMessage("Deselected: %s", selectedItem);
    }
}