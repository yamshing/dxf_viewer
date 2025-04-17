#include "line.h"

Line::Line(int x1, int y1, int x2, int y2, int color, const std::string& lineStyle)
    : Drawable(x1, y1, color, lineStyle), x1(x1), y1(y1), x2(x2), y2(y2) {}

void Line::draw(wxDC& dc) const {
    wxPen pen(Drawable::convertDxfColorToWxColour(color), 1);
    setLineStyle(pen,dc); // Use the new setLineStyle function
    
    dc.DrawLine(x1, y1, x2, y2);
}
