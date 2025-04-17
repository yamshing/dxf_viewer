#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height, int color, const std::string& lineStyle)
    : Drawable(x, y, color, lineStyle), width(width), height(height) {}

void Rectangle::draw(wxDC& dc) const {
    wxPen pen(Drawable::convertDxfColorToWxColour(color), 1);
    pen.SetStyle(wxPENSTYLE_SOLID); // Default to solid style

    if (lineStyle == "DASHED") {
        pen.SetStyle(wxPENSTYLE_SHORT_DASH);
    } else if (lineStyle == "DOTTED") {
        pen.SetStyle(wxPENSTYLE_DOT);
    } else if (lineStyle == "DASHDOT") {
        pen.SetStyle(wxPENSTYLE_DOT_DASH);
    }

    dc.SetPen(pen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(x, y, width, height);
}