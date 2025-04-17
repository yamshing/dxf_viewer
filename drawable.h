#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <wx/dc.h>
#include <wx/colour.h>

class Drawable {
public:
    int x, y;
    int color; // Added color information

    Drawable(int x, int y, int color);

    virtual ~Drawable() = default;

    virtual void draw(wxDC& dc) const = 0;

    static wxColour convertDxfColorToWxColour(int dxfColor); // Declare the function as static
};

#endif // DRAWABLE_H