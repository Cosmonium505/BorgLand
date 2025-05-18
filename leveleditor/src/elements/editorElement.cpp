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

