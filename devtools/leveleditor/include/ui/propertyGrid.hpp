#pragma once

#include <wx/wx.h>
#include <wx/grid.h>


class PropertyGrid : public wxGridTableBase, public wxPanel {
    public:
        PropertyGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style = wxWANTS_CHARS);
        ~PropertyGrid();

        virtual int GetNumberRows();
        virtual int GetNumberCols();
        virtual wxString GetValue(int row, int col);
        virtual void SetValue(int row, int col, const wxString& value);
};