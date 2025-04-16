#include "dxf_text.h"
#include <wx/dc.h>

DxfText::DxfText(const std::string& content, double x, double y, double height)
    : Drawable(x, y), content(content), x(x), y(y), height(height) {}

void DxfText::draw(wxDC& dc) const {
    dc.SetFont(wxFont(height, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dc.DrawText(content, x, y);
}