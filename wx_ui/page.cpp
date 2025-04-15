#include "page.h"
#include "wx/notebook.h"
#include <math.h>

wxBEGIN_EVENT_TABLE(Page, wxScrolledWindow)
    EVT_MOUSEWHEEL(Page::OnMouseWheel) // Bind mouse wheel event
    EVT_LEFT_DOWN(Page::OnLeftClick)   // Bind left mouse button click event
wxEND_EVENT_TABLE()

Page::Page(wxNotebook *parent, int index)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL)
{
    SetBackgroundColour(*wxWHITE);
    SetScrollbars(20, 20, 50, 50);
    m_index = index;
    m_zoomFactor = 1.0; // Default zoom factor
    m_rootNode = nullptr; // Initialize root node to nullptr

    // Ensure the panel can capture mouse events
    SetFocus();
}

bool Page::OnSave(wxString filename)
{
    wxSVGFileDC svgDC(filename, 600, 650);
    OnDraw(svgDC);
    return svgDC.IsOk();
}

void Page::OnDraw(wxDC& dc)
{
    dc.SetUserScale(m_zoomFactor, m_zoomFactor);

    if (m_rootNode)
    {
        // Pass a lambda function as the draw callback
        m_rootNode->drawTree([&dc](const Drawable& drawable) {
            drawable.draw(dc);
        });
    }
    else
    {
        // Example: draw a simple line
        dc.SetPen(*wxBLACK_PEN);
        dc.DrawLine(0, 0, 100, 100);
    }
    // Reset scaling to default
    dc.SetUserScale(1.0, 1.0);
}

void Page::OnMouseWheel(wxMouseEvent& event) {
    //std::cout << "Mouse wheel event detected" << std::endl;
    if (event.ControlDown()) { // Check if the Ctrl key is pressed
        int rotation = event.GetWheelRotation();
        //std::cout << "Rotation: " << rotation << std::endl;
        if (rotation > 0) {
            m_zoomFactor *= 1.1; // Zoom in
        } else if (rotation < 0) {
            m_zoomFactor /= 1.1; // Zoom out
        }

        // Refresh the panel to redraw with the new zoom factor
        Refresh();
    } else {
        event.Skip(); // Skip the event if Ctrl is not pressed
    }
}

void Page::OnLeftClick(wxMouseEvent& event) {
    event.Skip(); // Allow further processing of the event if needed
}

void Page::setRootNode(Node* rootNode) {
    m_rootNode = rootNode;
}

Node* Page::getRootNode() const {
    return m_rootNode;
}
