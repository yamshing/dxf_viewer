#ifndef FRAME_H
#define FRAME_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/notebook.h"
#include "node.h"
#include <memory>

class Frame : public wxFrame
{
public:
    static const int NOTEBOOK_ID = wxID_HIGHEST + 1; // Declare NOTEBOOK_ID as a public constant

    Frame(wxWindow *parent, const wxWindowID id, const wxString& title,
          const wxPoint& pos, const wxSize& size,
          std::shared_ptr<Node> rootNode = nullptr);

    void OnAbout(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    std::string getJsonString() const; // Getter method for m_jsonString


private:
    wxNotebook *m_notebook;
    std::shared_ptr<Node> m_rootNode; // Instance variable to store the root Node

    wxDECLARE_EVENT_TABLE();
};

#endif // FRAME_H