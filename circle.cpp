#include "circle.h"
#include <iostream>

Circle::Circle(int x, int y, int radius, int color, const std::string& lineStyle)
    : Drawable(x, y, color, lineStyle), radius(radius) {}

void Circle::draw(wxDC& dc) const {
    wxPen pen(Drawable::convertDxfColorToWxColour(color), 1);
    setLineStyle(pen); // Use the new setLineStyle function
    dc.SetPen(pen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawCircle(x, y, radius);
}