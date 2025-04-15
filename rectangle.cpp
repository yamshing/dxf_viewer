#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height)
    : Drawable(x, y, width, height) {
    }

void Rectangle::draw(wxDC& dc) const {
    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(x, y, width, height);
}