#include "ui/blockSelector.hpp"
#include "editorParams.hpp"

BlockSelector::BlockSelector(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxListBox(parent, id, pos, size, 0, nullptr, style | wxLB_SINGLE) {
    for (const auto& schema : editorParams->blockSchemas) {
        Append(wxString(schema.name));
    }

    
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