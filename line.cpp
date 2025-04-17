#include "line.h"

Line::Line(int x1, int y1, int x2, int y2, int color, const std::string& lineStyle)
    : Drawable(x1, y1, color, lineStyle), x1(x1), y1(y1), x2(x2), y2(y2) {}

void Line::draw(wxDC& dc) const {
    wxPen pen(Drawable::convertDxfColorToWxColour(color), 1);
    pen.SetStyle(wxPENSTYLE_SOLID); // Default to solid style

    if (lineStyle == "DASHED") {
        pen.SetStyle(wxPENSTYLE_SHORT_DASH);
    } else if (lineStyle == "DOTTED") {
        pen.SetStyle(wxPENSTYLE_DOT);
    } else if (lineStyle == "DASHDOT") {
        pen.SetStyle(wxPENSTYLE_DOT_DASH);
    }

    dc.SetPen(pen);
    dc.DrawLine(x1, y1, x2, y2);
}
