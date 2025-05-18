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
    return x * editorParams->zoom + editorParams->cameraPos[0];
}

float EditorElement::getY() {
    return y * editorParams->zoom + editorParams->cameraPos[1];
}

