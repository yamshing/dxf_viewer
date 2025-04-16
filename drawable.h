#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <wx/dc.h>

class Drawable {
public:
    int x, y; // Removed width and height

    Drawable(int x, int y);

    virtual ~Drawable() = default;

    virtual void draw(wxDC& dc) const = 0;
};

#endif // DRAWABLE_H