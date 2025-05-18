#pragma once

#include "editorElement.hpp"
#include <wx/wx.h>

class BlockElement : public EditorElement {
    public:
        BlockElement(float x, float y, float width, float height) : EditorElement(x, y, width, height) {
            type = EditorElementType::BLOCK;
        }
        
        int blockType = 0;

        virtual void render(wxPaintDC& dc) override;
        virtual void save(std::ofstream& out) override;
        virtual void load(std::ifstream& in) override;
};