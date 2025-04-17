#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height, int color, const std::string& lineStyle)
    : Drawable(x, y, color, lineStyle), width(width), height(height) {}

void Rectangle::draw(wxDC& dc) const {
    wxPen pen(Drawable::convertDxfColorToWxColour(color), 1);
    setLineStyle(pen,dc); // Use the new setLineStyle function
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(x, y, width, height);
}