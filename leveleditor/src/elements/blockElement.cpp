#include "blockElement.hpp"
#include <wx/wx.h>

#include "editorParams.hpp"

void BlockElement::render(wxPaintDC& dc) {
    if (selected) {
        dc.SetBrush(wxBrush(wxColor(200, 200, 200)));
    } else {
        dc.SetBrush(wxBrush(wxColor(200, 200, 200)));
    }

    dc.DrawRectangle(getX(), getY(), getWidth(), getHeight());
}
