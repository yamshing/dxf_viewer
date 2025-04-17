#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <wx/dc.h>
#include <wx/colour.h>
#include <string>

class Drawable {
public:
    int x, y;
    int color; // Added color information
    std::string lineStyle; // Added lineStyle property

    Drawable(int x, int y, int color, const std::string& lineStyle = "CONTINUOUS"); // Updated constructor

    virtual ~Drawable() = default;

    virtual void draw(wxDC& dc) const = 0;

    static wxColour convertDxfColorToWxColour(int dxfColor); // Declare the function as static

    // Getter for lineStyle
    const std::string& getLineStyle() const { return lineStyle; }
    // Setter for lineStyle
    void setLineStyle(const std::string& style) { lineStyle = style; }

    void setLineStyle(wxPen& pen) const; // Added setLineStyle function declaration
};

#endif // DRAWABLE_H