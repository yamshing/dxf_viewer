#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <wx/dc.h>

class Drawable {
public:
    int x, y, width, height;

    Drawable(int x, int y, int width, int height);

    virtual ~Drawable() = default;

    virtual void draw(wxDC& dc) const = 0; // Update draw method to accept wxDC
};

#endif // DRAWABLE_H