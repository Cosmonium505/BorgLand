#include "ui/blockSelector.hpp"
#include "editorParams.hpp"

BlockSelector::BlockSelector(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxListBox(parent, id, pos, size, 0, nullptr, style | wxLB_SINGLE) {
    Append("Test block 1");
    Append("Test block 2");
    Append("Test block 3");
    Append("Test block 4");
    Append("Test block 5");
    Append("Test block 6");
    Append("Test block 7");
    Append("Test block 8");
    Append("Test block 9");
    Append("Test block 10");
    Append("Test block 11");
    Append("Test block 12");
    Append("Test block 13");
    Append("Test block 14");
    Append("Test block 15");
    Append("Test block 16");

    
    Bind(wxEVT_LISTBOX, &BlockSelector::OnSelect, this);
    Select(0);
}
BlockSelector::~BlockSelector()
{
    // Destructor
}

void BlockSelector::OnSelect(wxCommandEvent& event)
{
    int selection = GetSelection();
    editorParams->currentBlockType = selection;
}

void BlockSelector::OnDeselect(wxCommandEvent& event)
{
    Select(1);
}