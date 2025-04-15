#include "line.h"

Line::Line(int x1, int y1, int x2, int y2)
    : Drawable(x1, y1, x2 - x1, y2 - y1), x1(x1), y1(y1), x2(x2), y2(y2) {}

void Line::draw(wxDC& dc) const {
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawLine(x1, y1, x2, y2);
}
