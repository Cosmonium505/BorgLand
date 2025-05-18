#include "editorElement.hpp"
#include <wx/wx.h>

#include "editorParams.hpp"

float EditorElement::getHeight() {
    return height * editorParams->zoom;
}

float EditorElement::getWidth() {
    return width * editorParams->zoom;
}

float EditorElement::getX() {
    return (x + editorParams->cameraPos[0]) * editorParams->zoom;
}

float EditorElement::getY() {
    return (y + editorParams->cameraPos[1]) * editorParams->zoom;
}

void EditorElement::save(std::ofstream& out) {
    out.write(reinterpret_cast<const char*>(&type), sizeof(type));
    out.write(reinterpret_cast<const char*>(&x), sizeof(x));
    out.write(reinterpret_cast<const char*>(&y), sizeof(y));
    out.write(reinterpret_cast<const char*>(&width), sizeof(width));
    out.write(reinterpret_cast<const char*>(&height), sizeof(height));
    out.write(reinterpret_cast<const char*>(&selected), sizeof(selected));
}

void EditorElement::load(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&type), sizeof(type));
    in.read(reinterpret_cast<char*>(&x), sizeof(x));
    in.read(reinterpret_cast<char*>(&y), sizeof(y));
    in.read(reinterpret_cast<char*>(&width), sizeof(width));
    in.read(reinterpret_cast<char*>(&height), sizeof(height));
    in.read(reinterpret_cast<char*>(&selected), sizeof(selected));
}