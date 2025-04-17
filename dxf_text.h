#ifndef DXF_TEXT_H
#define DXF_TEXT_H

#include "drawable.h"
#include <string>
#include <wx/dc.h>

class DxfText : public Drawable {
public:
    DxfText(const std::string& content, double x, double y, double height, int color);

    void draw(wxDC& dc) const override;

private:
    std::string content;
    double x, y;
    double height;
    int color;
};

#endif // DXF_TEXT_H