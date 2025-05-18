#pragma once

#include <wx/wx.h>

enum class EditorElementType {
    NONE,
    BLOCK
};

class EditorElement {
    public:
        EditorElementType type = EditorElementType::NONE;
        float x = 0.0f;
        float y = 0.0f;
        float width = 50.0f;
        float height = 50.0f;
        bool selected = false;

        virtual void render(wxPaintDC& dc) {
            
        }

        virtual float getX();
        virtual float getY();
        virtual float getWidth();
        virtual float getHeight();

        EditorElement() {}
        EditorElement(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
};