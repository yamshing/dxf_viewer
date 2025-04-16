#include "circle.h"
#include <iostream>

Circle::Circle(int x, int y, int radius)
    : Drawable(x, y), x(x), y(y), radius(radius) {}

void Circle::draw(wxDC& dc) const {
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawCircle(x, y, radius);
}