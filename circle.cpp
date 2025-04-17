#include "circle.h"
#include <iostream>

Circle::Circle(int x, int y, int radius, int color, const std::string& lineStyle)
    : Drawable(x, y, color, lineStyle), radius(radius) {}

void Circle::draw(wxDC& dc) const {
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
    dc.DrawCircle(x, y, radius);
}