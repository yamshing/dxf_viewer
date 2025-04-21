#include "drawable.h"
#include <wx/colour.h>

Drawable::Drawable(int x, int y, int color, const std::string& lineStyle, double lineWidth)
    : x(x), y(y), color(color), lineStyle(lineStyle), lineWidth(lineWidth) {}

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

void Drawable::setLineStyle(wxPen& pen,wxDC& dc) const {

    if (!lineStylePattern.empty()) {
        pen.SetStyle(wxPENSTYLE_USER_DASH); // Use custom dash pattern

        wxDash* dashes = new wxDash[lineStylePattern.size()];
        for (size_t i = 0; i < lineStylePattern.size(); ++i) {
            dashes[i] = static_cast<int>(lineStylePattern[i]); 
        }
        pen.SetDashes(lineStylePattern.size(), dashes);
        dc.SetPen(pen);
        delete[] dashes; 
    } else {
        //pen.SetStyle(wxPENSTYLE_SOLID); // Default to solid style if no pattern is set
        dc.SetPen(pen);
    }
}

void Drawable::setLineWidthFromEnum(int lWeightEnum) {
    // Convert libdxfrw lineWidth enum to wxWidgets line width in pixels
    switch (lWeightEnum) {
        case 0: lineWidth = 0.0; break;       // 0.00mm
        case 1: lineWidth = 0.5; break;       // 0.05mm
        case 2: lineWidth = 0.9; break;       // 0.09mm
        case 3: lineWidth = 1.3; break;       // 0.13mm
        case 4: lineWidth = 1.5; break;       // 0.15mm
        case 5: lineWidth = 1.8; break;       // 0.18mm
        case 6: lineWidth = 2.0; break;       // 0.20mm
        case 7: lineWidth = 2.5; break;       // 0.25mm
        case 8: lineWidth = 3.0; break;       // 0.30mm
        case 9: lineWidth = 3.5; break;       // 0.35mm
        case 10: lineWidth = 4.0; break;      // 0.40mm
        case 11: lineWidth = 5.0; break;      // 0.50mm
        case 12: lineWidth = 5.3; break;      // 0.53mm
        case 13: lineWidth = 6.0; break;      // 0.60mm
        case 14: lineWidth = 7.0; break;      // 0.70mm
        case 15: lineWidth = 8.0; break;      // 0.80mm
        case 16: lineWidth = 9.0; break;      // 0.90mm
        case 17: lineWidth = 10.0; break;     // 1.00mm
        case 18: lineWidth = 10.6; break;     // 1.06mm
        case 19: lineWidth = 12.0; break;     // 1.20mm
        case 20: lineWidth = 14.0; break;     // 1.40mm
        case 21: lineWidth = 15.8; break;     // 1.58mm
        case 22: lineWidth = 20.0; break;     // 2.00mm
        case 23: lineWidth = 21.1; break;     // 2.11mm
        case 29: lineWidth = 1.0; break;      // By layer (default to 1.0mm)
        case 30: lineWidth = 1.0; break;      // By block (default to 1.0mm)
        case 31: lineWidth = 1.0; break;      // Default (default to 1.0mm)
        default: lineWidth = 1.0; break;      // Fallback to 1.0mm
    }
}