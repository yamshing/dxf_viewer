#ifndef PAGE_H
#define PAGE_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/scrolwin.h"
#include "wx/dcsvg.h"
#include "wx/notebook.h"
#include "node.h"

enum PageType
{
    Page_Shapes,
    Page_Max
};
static const char* pageNames[] =
{
    "Shapes",
};

wxCOMPILE_TIME_ASSERT( WXSIZEOF(pageNames) == Page_Max, PageNamesMismatch );

static const char* pageDescriptions[] =
{
     "Svg shapes",
     
};

wxCOMPILE_TIME_ASSERT( WXSIZEOF(pageDescriptions) == Page_Max, PageDescriptionsMismatch );


class Page : public wxScrolledWindow
{
public:
    Page(wxNotebook *parent, int index);
    virtual void OnDraw(wxDC& dc) wxOVERRIDE;
    bool OnSave(wxString filename);

    void setRootNode(Node* rootNode); // Setter for root Node
    Node* getRootNode() const;       // Getter for root Node

    static const char* pageNames[];
    static const char* pageDescriptions[];

private:
    void OnMouseWheel(wxMouseEvent& event);
    void OnLeftClick(wxMouseEvent& event);
    int m_index;
    double m_zoomFactor = 1.0; // Default zoom factor

    Node* m_rootNode = nullptr; // Instance variable to store the root Node
    wxDECLARE_EVENT_TABLE();
};

#endif // PAGE_H