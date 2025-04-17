#include "circle.h"
#include <iostream>

Circle::Circle(int x, int y, int radius, int color)
    : Drawable(x, y, color), radius(radius) {}

void Circle::draw(wxDC& dc) const {
    dc.SetPen(wxPen(Drawable::convertDxfColorToWxColour(color), 1));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawCircle(x, y, radius);
}