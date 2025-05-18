#include "ui/toolDisplay.hpp"
#include <wx/artprov.h>
#include "editorParams.hpp"

#include "res/selection.xpm"
#include "res/draw.xpm"
#include "res/erase.xpm"
#include "res/rectangle.xpm"

ToolSelector::ToolSelector(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxToolBar(parent, id, pos, size, style) {
        wxBitmap bitmap(selection_xpm);
        AddTool(EditorTool::TOOL_SELECT, "Select", bitmap, "Select Tool", wxITEM_CHECK);

        wxBitmap bitmap_draw(draw_xpm);
        AddTool(EditorTool::TOOL_DRAW, "Draw", bitmap_draw, "Draw Tool", wxITEM_CHECK);

        wxBitmap bitmap_erase(erase_xpm);
        AddTool(EditorTool::TOOL_ERASE, "Erase", bitmap_erase, "Erase Tool", wxITEM_CHECK);

        wxBitmap bitmap_rectangle(rectangle_xpm);
        AddTool(EditorTool::TOOL_RECTANGLE_SELECT, "Rectangle Select", bitmap_rectangle, "Rectangle Select Tool", wxITEM_CHECK);

        Realize();
        Bind(wxEVT_TOOL, &ToolSelector::OnSelect, this);

        // Set initial tool state
        UpdateToolState();
}

ToolSelector::~ToolSelector() {
    // Destructor
}

void ToolSelector::OnSelect(wxCommandEvent& event) {
    editorParams->currentTool = static_cast<EditorTool>(event.GetId());
    UpdateToolState();
}

void ToolSelector::UpdateToolState() {
    ToggleTool(EditorTool::TOOL_SELECT, editorParams->currentTool == EditorTool::TOOL_SELECT);
    ToggleTool(EditorTool::TOOL_DRAW, editorParams->currentTool == EditorTool::TOOL_DRAW);
    ToggleTool(EditorTool::TOOL_ERASE, editorParams->currentTool == EditorTool::TOOL_ERASE);
    ToggleTool(EditorTool::TOOL_RECTANGLE_SELECT, editorParams->currentTool == EditorTool::TOOL_RECTANGLE_SELECT);
}
