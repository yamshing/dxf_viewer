#include "frame.h"
#include "page.h"
#include "wx/dcsvg.h"

// Define a unique ID for the wxNotebook
const int NOTEBOOK_ID = wxID_HIGHEST + 1;

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_ABOUT, Frame::OnAbout)
    EVT_MENU(wxID_EXIT, Frame::OnQuit)
wxEND_EVENT_TABLE()

Frame::Frame(wxWindow *parent, const wxWindowID id, const wxString& title,
             const wxPoint& pos, const wxSize& size,
             std::shared_ptr<Node> rootNode)
    : wxFrame(parent, id, title, pos, size), m_rootNode(rootNode)
{
    #if wxUSE_STATUSBAR
    CreateStatusBar();
    #endif // wxUSE_STATUSBAR

    wxMenu *file_menu = new wxMenu;
    file_menu->Append(wxID_EXIT);

    wxMenu *help_menu = new wxMenu;
    help_menu->Append(wxID_ABOUT);

    wxMenuBar *menu_bar = new wxMenuBar;
    menu_bar->Append(file_menu, "&File");
    menu_bar->Append(help_menu, "&Help");

    SetMenuBar(menu_bar);

    // Create the wxNotebook with a unique ID
    m_notebook = new wxNotebook(this, NOTEBOOK_ID, wxDefaultPosition, wxDefaultSize, wxBK_TOP);

    for (int i = 0; i < Page_Max; ++i)
    {
        Page* page = new Page(m_notebook, i);
        if (m_rootNode) {
            page->setRootNode(m_rootNode.get()); // Set the root node for each Page instance
        }
        m_notebook->AddPage(page, pageNames[i]);
    }
}

void Frame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void Frame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    (void)wxMessageBox("wxWidgets SVG sample\n"
        "Authors:\n"
        "   Chris Elliott (c) 2002-2009\n"
        "   Prashant Kumar Nirmal (c) 2017\n"
        "Usage: click File|Save to Save the Selected SVG Test",
        "About SVG Test");
}

std::string Frame::getJsonString() const {
    return m_rootNode ? m_rootNode->toJson().dump() : ""; // Convert the root node to JSON string
}


