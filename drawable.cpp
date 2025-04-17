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
    pen.SetStyle(wxPENSTYLE_USER_DASH); // Use custom dash pattern

    if (!lineStylePattern.empty()) {
        wxDash* dashes = new wxDash[lineStylePattern.size()];
        for (size_t i = 0; i < lineStylePattern.size(); ++i) {
            dashes[i] = static_cast<int>(lineStylePattern[i] * 10); // Scale pattern to match wxDash units
        }
        pen.SetDashes(lineStylePattern.size(), dashes);
        delete[] dashes;
    } else {
        pen.SetStyle(wxPENSTYLE_SOLID); // Default to solid style if no pattern is set
    }
}