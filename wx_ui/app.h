#ifndef APP_H
#define APP_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <string>
#include <memory>
#include "node.h"

class App : public wxApp
{
public:
    // Default constructor
    App();

    // Constructor for JSON string or DXF file path
    App(const std::string& input, bool isDxf = false);

    // Override OnInit
    virtual bool OnInit();

private:
    std::string m_jsonString;
    std::shared_ptr<Node> m_rootNode;
};

#endif // APP_H