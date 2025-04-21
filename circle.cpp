#include "circle.h"
#include <iostream>

Circle::Circle(int x, int y, int radius, int color, const std::string& lineStyle)
    : Drawable(x, y, color, lineStyle), radius(radius) {}

void Circle::draw(wxDC& dc) const {
    wxPen pen(Drawable::convertDxfColorToWxColour(color), static_cast<int>(lineWidth)); // Set pen width using lineWidth
    setLineStyle(pen, dc); // Use the new setLineStyle function
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen(pen); // Apply the pen to the device context
    dc.DrawCircle(x, y, radius);
}