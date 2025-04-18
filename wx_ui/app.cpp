#include "app.h"
#include "frame.h"
#include "node.h"
#include <memory>

App::App() : m_jsonString(""), m_rootNode(nullptr) {
    // Default constructor implementation
}

App::App(const std::string& input, bool isDxf)
    : m_jsonString(""), m_rootNode(nullptr) {
    try {
        if (isDxf) {
            m_rootNode = Node::fromDxf(input); // Parse the DXF file
        } 
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
        wxLogError("Failed to parse input: %s", e.what());
    }
}

bool App::OnInit()
{
    if (!m_rootNode) {
        wxLogError("Failed to initialize application due to invalid input.");
        return false; // Return false if parsing fails
    }

    // Create the main frame window with m_rootNode as an optional parameter
    Frame *frame = new Frame(NULL, -1, "Dxf Viewer",
                                wxDefaultPosition, wxSize(500, 400), m_rootNode);

    frame->Show(true);

    return true;
}



