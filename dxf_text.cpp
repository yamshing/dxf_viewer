#include "dxf_text.h"
#include <wx/dc.h>

DxfText::DxfText(const std::string& content, double x, double y, double height, int color)
    : Drawable(x, y, color), content(content), height(height) {}

void DxfText::draw(wxDC& dc) const {
    dc.SetTextForeground(Drawable::convertDxfColorToWxColour(color));
    dc.SetFont(wxFont(height, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    dc.DrawText(content, x, y);
}