#include "blockElement.hpp"
#include <wx/wx.h>
#include <algorithm>

#include "editorParams.hpp"

void BlockElement::render(wxPaintDC& dc) {
    bool selected = false;

    for (EditorElement* element : editorParams->selectedElements) {
        if (element == this) {
            selected = true;
            break;
        }
    }

    int atlasX = (blockType % 8) * 24;
    int atlasY = floor(blockType / 8) * 24;
    wxImage image = editorParams->blockAtlas.GetSubImage(wxRect(atlasX, atlasY, 24, 24));
    wxImage scaledImage = image.Scale(getWidth(), getHeight(), wxIMAGE_QUALITY_NEAREST);
    wxBitmap bitmap(scaledImage);

    dc.DrawBitmap(bitmap, getX(), getY(), false);

    if (selected) {
        dc.SetPen(wxPen(wxColor(255, 128, 0), 2));
        dc.SetBrush(wxBrush(wxColor(255, 128, 0, 50)));
        dc.DrawRectangle(getX(), getY(), getWidth() , getHeight());
    }

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