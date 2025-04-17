#include "line.h"

Line::Line(int x1, int y1, int x2, int y2, int color)
    : Drawable(x1, y1, color), x1(x1), y1(y1), x2(x2), y2(y2) {}

void Line::draw(wxDC& dc) const {
    std::cout << "color: " << color << std::endl;
    dc.SetPen(wxPen(Drawable::convertDxfColorToWxColour(color), 1));
    dc.DrawLine(x1, y1, x2, y2);
}
