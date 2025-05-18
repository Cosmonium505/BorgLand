#include "blockElement.hpp"
#include <wx/wx.h>

#include "editorParams.hpp"

void BlockElement::render(wxPaintDC& dc) {
    if (selected) {
        dc.SetBrush(wxBrush(wxColor(200, 200, 200)));
        dc.SetPen(wxPen(wxColor(255, 128, 0), 2));
    } else {
        dc.SetBrush(wxBrush(wxColor(200, 200, 200)));
        dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
    }

    dc.DrawRectangle(getX(), getY(), getWidth(), getHeight());
}
