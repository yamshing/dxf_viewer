#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <wx/dc.h>
#include <wx/colour.h>
#include <string>
#include <vector>

class Drawable {
public:
    int x, y;
    int color; // Added color information
    std::string lineStyle; // Added lineStyle property
    std::vector<double> lineStylePattern; // Added lineStylePattern to store dash patterns

    Drawable(int x, int y, int color, const std::string& lineStyle = "CONTINUOUS"); // Updated constructor

    virtual ~Drawable() = default;

    virtual void draw(wxDC& dc) const = 0;

    static wxColour convertDxfColorToWxColour(int dxfColor); // Declare the function as static

    // Getter for lineStyle
    const std::string& getLineStyle() const { return lineStyle; }
    // Setter for lineStyle
    void setLineStyle(const std::string& style) { lineStyle = style; }

    void setLineStyle(wxPen& pen, wxDC& dc) const; // Updated to use lineStylePattern

    // Setter for lineStylePattern
    void setLineStylePattern(const std::vector<double>& pattern) { lineStylePattern = pattern; }
    // Getter for lineStylePattern
    const std::vector<double>& getLineStylePattern() const { return lineStylePattern; }
};

#endif // DRAWABLE_H