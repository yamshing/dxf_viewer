#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height, int color)
    : Drawable(x, y, color), width(width), height(height) {}

void Rectangle::draw(wxDC& dc) const {
    dc.SetPen(wxPen(Drawable::convertDxfColorToWxColour(color), 1));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(x, y, width, height);
}