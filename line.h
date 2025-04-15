#ifndef LINE_H
#define LINE_H

#include "drawable.h"
#include <wx/dc.h>

class Line : public Drawable {
public:
    Line(int x1, int y1, int x2, int y2);

    void draw(wxDC& dc) const override;

    int getX1() const { return x1; }
    int getY1() const { return y1; }
    int getX2() const { return x2; }
    int getY2() const { return y2; }

private:
    int x1, y1, x2, y2;
};

#endif // LINE_H
