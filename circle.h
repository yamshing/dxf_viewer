#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"

class Circle : public Drawable {
public:
    Circle(int x, int y, int radius);

    void draw(wxDC& dc) const override; // Update to match Drawable's method signature

    int getX() const { return x; }
    int getY() const { return y; }
    int getRadius() const { return radius; }

private:
    int x, y, radius;
};

#endif // CIRCLE_H