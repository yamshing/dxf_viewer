#include "drawable.h"
#include <wx/colour.h>

Drawable::Drawable(int x, int y, int color, const std::string& lineStyle)
    : x(x), y(y), color(color), lineStyle(lineStyle) {}

wxColour Drawable::convertDxfColorToWxColour(int dxfColor) {
    switch (dxfColor) {
        case 1: return wxColour(255, 0, 0);   // Red
        case 2: return wxColour(255, 255, 0); // Yellow
        case 3: return wxColour(0, 255, 0);   // Green
        case 4: return wxColour(0, 255, 255); // Cyan
        case 5: return wxColour(0, 0, 255);   // Blue
        case 6: return wxColour(255, 0, 255); // Magenta
        case 7: return wxColour(0, 0, 0);     // Black
        default: return wxColour(0, 0, 0);    // Default to Black
    }
}

void Drawable::setLineStyle(wxPen& pen) const {
    pen.SetStyle(wxPENSTYLE_SOLID); // Default to solid style

    if (lineStyle == "DASHED") {
        pen.SetStyle(wxPENSTYLE_SHORT_DASH);
    } else if (lineStyle == "DOTTED") {
        pen.SetStyle(wxPENSTYLE_DOT);
    } else if (lineStyle == "DASHDOT") {
        pen.SetStyle(wxPENSTYLE_DOT_DASH);
    }
}