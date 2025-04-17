#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"

class Circle : public Drawable {
public:
    Circle(int x, int y, int radius, int color, const std::string& lineStyle);

    void draw(wxDC& dc) const override;

    int getX() const { return x; }
    int getY() const { return y; }
    int getRadius() const { return radius; }

private:
    int radius;
};

#endif // CIRCLE_H