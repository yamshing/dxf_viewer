#include "app.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <wx/wx.h>

wxIMPLEMENT_APP_NO_MAIN(App);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_file>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    App* app = nullptr;

    // Check if the file is a DXF file
    if (filePath.size() > 4 && filePath.substr(filePath.size() - 4) == ".dxf") {
        app = new App(filePath, true); // Pass true to indicate DXF input
    } else {
        std::ifstream jsonFile(filePath);
        if (!jsonFile.is_open()) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
            return 1;
        }

        std::stringstream buffer;
        buffer << jsonFile.rdbuf();
        std::string jsonString = buffer.str();
        app = new App(jsonString);
    }

    wxApp::SetInstance(app);
    return wxEntry(argc, argv);
}


