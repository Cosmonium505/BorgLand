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

void BlockElement::save(std::ofstream& out) {
    out.write(reinterpret_cast<const char*>(&type), sizeof(type));
    out.write(reinterpret_cast<const char*>(&x), sizeof(x));
    out.write(reinterpret_cast<const char*>(&y), sizeof(y));
    out.write(reinterpret_cast<const char*>(&width), sizeof(width));
    out.write(reinterpret_cast<const char*>(&height), sizeof(height));
    out.write(reinterpret_cast<const char*>(&blockType), sizeof(blockType));
}

void BlockElement::load(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&x), sizeof(x));
    in.read(reinterpret_cast<char*>(&y), sizeof(y));
    in.read(reinterpret_cast<char*>(&width), sizeof(width));
    in.read(reinterpret_cast<char*>(&height), sizeof(height));
    in.read(reinterpret_cast<char*>(&blockType), sizeof(blockType));
}