#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "drawable.h"
#include <wx/dc.h>
#include <iostream>

class Rectangle : public Drawable {
public:
    Rectangle(int x, int y, int width, int height, int color);
    ~Rectangle() override = default;
    void draw(wxDC& dc) const override;

    // Getter methods inherited from Drawable
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int x, y, width, height, color;
};

#endif // RECTANGLE_H