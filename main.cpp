#include "app.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <wx/wx.h>

wxIMPLEMENT_APP_NO_MAIN(App);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_json_file>" << std::endl;
        return 1;
    }

    std::ifstream jsonFile(argv[1]);
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open JSON file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << jsonFile.rdbuf();
    std::string jsonString = buffer.str();

    App* app = new App(jsonString);
    wxApp::SetInstance(app);
    return wxEntry(argc, argv);
}


