#ifndef LINE_H
#define LINE_H

#include "drawable.h"
#include <wx/dc.h>
#include <iostream>
#include <string>


class Line : public Drawable {
public:
    Line(int x1, int y1, int x2, int y2, int color, const std::string& lineStyle);

    void draw(wxDC& dc) const override;

    int getX1() const { return x1; }
    int getY1() const { return y1; }
    int getX2() const { return x2; }
    int getY2() const { return y2; }
    int getColor() const { return color; }

private:
    int x1, y1, x2, y2;
    //int color;
};

#endif // LINE_H
