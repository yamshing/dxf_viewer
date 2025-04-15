#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <gtest/gtest.h>
#include "app.h"
#include "frame.h"
#include "page.h"
#include <cstdio>
#include <unistd.h>
#include <nlohmann/json.hpp> // Include for JSON parsing
#include <wx/image.h> // Include for wxImage to compare bitmaps
#include <sys/stat.h> // Include for mkdir
#include <sys/types.h> // Include for mode_t
#include <errno.h> // Include for errno
#include "test_util.hpp" // Include the utility header
#include <fstream> // Include for std::ifstream

void DrawAndSaveBitmap(Page* page, int bitmap_w, int bitmap_h, const std::string& bitmap_name) {
    // Create a wxBitmap and associate it with wxMemoryDC
    wxBitmap bitmap(bitmap_w, bitmap_h); // Create a bitmap with the specified size
    wxMemoryDC memoryDC;
    memoryDC.SelectObject(bitmap); // Associate the bitmap with the memory DC

    // Initialize the bitmap with a white background
    memoryDC.SetBackground(*wxWHITE_BRUSH);
    memoryDC.Clear();

    // Mock a wxDC to test drawing
    page->OnDraw(memoryDC);

    // Save the bitmap to a BMP file
    std::string file_path = "result_image/" + bitmap_name + ".bmp";
    bitmap.SaveFile(file_path, wxBITMAP_TYPE_BMP);

    // Load the expected bitmap
    std::string expected_path = "../test/expect_image/" + bitmap_name + ".bmp";
    wxBitmap expectedBitmap(expected_path, wxBITMAP_TYPE_BMP);
    ASSERT_TRUE(expectedBitmap.IsOk()) << "Failed to load " << expected_path;

    // Compare the output bitmap with the expected bitmap
    ASSERT_TRUE(CompareBitmaps(bitmap, expectedBitmap)) << file_path << " does not match " << expected_path;
}

TEST(AppTest, DrawRectanglesFromJson)
{
    // Ensure the result_image directory exists
    EnsureDirectoryExists("result_image");

    std::string jsonString = R"([
              {
                  "type": "rectangle",
                  "x": 10,
                  "y": 20,
                  "width": 100,
                  "height": 50,
                  "child_arr": [
                      {
                          "type": "rectangle",
                          "x": 30,
                          "y": 40,
                          "width": 50,
                          "height": 25
                      }
                  ]
              }
          ])";

    // Initialize wxWidgets without launching the main loop
    int argc = 0;
    char** argv = nullptr;
    wxApp* pApp = new App(jsonString);
    wxApp::SetInstance(pApp);
    wxEntryStart(argc, argv);

    // Run the app initialization
    ASSERT_TRUE(wxTheApp->CallOnInit());

    // Get the Frame and verify it is initialized
    Frame* frame = dynamic_cast<Frame*>(wxTheApp->GetTopWindow());
    ASSERT_NE(frame, nullptr);

    // Retrieve the wxNotebook using its unique ID
    wxNotebook* notebook = wxDynamicCast(frame->FindWindow(Frame::NOTEBOOK_ID), wxNotebook);
    ASSERT_NE(notebook, nullptr);

    // Verify the first page of the notebook
    Page* page = dynamic_cast<Page*>(notebook->GetPage(0));
    ASSERT_NE(page, nullptr);

    // Call the refactored function
    DrawAndSaveBitmap(page, 200, 200, "default_page_draw_no_json");

    // Clean up wxWidgets
    wxTheApp->OnExit();
    wxEntryCleanup();
}

TEST(AppTest, RunAppWithInputJson)
{
    // Ensure the result_image directory exists
    EnsureDirectoryExists("result_image");

    // Load the JSON file
    std::ifstream jsonFile("../test/input_test.json");
    ASSERT_TRUE(jsonFile.is_open()) << "Failed to open test/input_test.json";

    std::stringstream buffer;
    buffer << jsonFile.rdbuf();
    std::string jsonString = buffer.str();

    // Initialize wxWidgets without launching the main loop
    int argc = 0;
    char** argv = nullptr;
    wxApp* pApp = new App(jsonString);
    wxApp::SetInstance(pApp);
    wxEntryStart(argc, argv);

    // Run the app initialization
    ASSERT_TRUE(wxTheApp->CallOnInit());

    // Get the Frame and verify it is initialized
    Frame* frame = dynamic_cast<Frame*>(wxTheApp->GetTopWindow());
    ASSERT_NE(frame, nullptr);

    // Retrieve the wxNotebook using its unique ID
    wxNotebook* notebook = wxDynamicCast(frame->FindWindow(Frame::NOTEBOOK_ID), wxNotebook);
    ASSERT_NE(notebook, nullptr);

    // Verify the first page of the notebook
    Page* page = dynamic_cast<Page*>(notebook->GetPage(0));
    ASSERT_NE(page, nullptr);

    // Call the refactored function to draw and save the bitmap
    DrawAndSaveBitmap(page, 200, 200, "run_app_with_input_json");

    // Clean up wxWidgets
    wxTheApp->OnExit();
    wxEntryCleanup();
}

TEST(AppTest, DrawLine) {
    // Ensure the result_image directory exists
    EnsureDirectoryExists("result_image");

    // Create a JSON string for a line
    std::string jsonString = R"([
        {
            "type": "line",
            "x1": 10,
            "y1": 20,
            "x2": 100,
            "y2": 200
        }
    ])";

    // Initialize wxWidgets without launching the main loop
    int argc = 0;
    char** argv = nullptr;
    wxApp* pApp = new App(jsonString);
    wxApp::SetInstance(pApp);
    wxEntryStart(argc, argv);

    // Run the app initialization
    ASSERT_TRUE(wxTheApp->CallOnInit());

    // Get the Frame and verify it is initialized
    Frame* frame = dynamic_cast<Frame*>(wxTheApp->GetTopWindow());
    ASSERT_NE(frame, nullptr);

    // Retrieve the wxNotebook using its unique ID
    wxNotebook* notebook = wxDynamicCast(frame->FindWindow(Frame::NOTEBOOK_ID), wxNotebook);
    ASSERT_NE(notebook, nullptr);

    // Verify the first page of the notebook
    Page* page = dynamic_cast<Page*>(notebook->GetPage(0));
    ASSERT_NE(page, nullptr);

    // Call the refactored function to draw and save the bitmap
    DrawAndSaveBitmap(page, 200, 200, "draw_line");

    //wxTheApp->OnRun();

    // Clean up wxWidgets
    wxTheApp->OnExit();
    wxEntryCleanup();
}

TEST(AppTest, OpenDxfAndShowInPage) {
    // Ensure the result_image directory exists
    EnsureDirectoryExists("result_image");

    // Path to the DXF file
    std::string dxfFilePath = "../test/circle.dxf";

    // Initialize wxWidgets without launching the main loop
    int argc = 0;
    char** argv = nullptr;
    wxApp* pApp = new App(dxfFilePath, true); // Pass true to indicate DXF input
    wxApp::SetInstance(pApp);
    wxEntryStart(argc, argv);

    // Run the app initialization
    ASSERT_TRUE(wxTheApp->CallOnInit());

    // Get the Frame and verify it is initialized
    Frame* frame = dynamic_cast<Frame*>(wxTheApp->GetTopWindow());
    ASSERT_NE(frame, nullptr);

    // Retrieve the wxNotebook using its unique ID
    wxNotebook* notebook = wxDynamicCast(frame->FindWindow(Frame::NOTEBOOK_ID), wxNotebook);
    ASSERT_NE(notebook, nullptr);

    // Verify the first page of the notebook
    Page* page = dynamic_cast<Page*>(notebook->GetPage(0));
    ASSERT_NE(page, nullptr);

    // Call the refactored function to draw and save the bitmap
    DrawAndSaveBitmap(page, 200, 200, "open_dxf_and_show_in_page");

    // Clean up wxWidgets
    wxTheApp->OnExit();
    wxEntryCleanup();
}

// Main function for Google Test
int main(int argc, char** argv) {
    // Suppress wxWidgets GUI initialization
    
    ::testing::InitGoogleTest(&argc, argv);

    // Redirect stderr to /dev/null to suppress Gtk-WARNING messages
    int original_stderr = dup(STDERR_FILENO);
    freopen("/dev/null", "w", stderr);

    int result = RUN_ALL_TESTS();

    // Restore stderr
    fflush(stderr);
    dup2(original_stderr, STDERR_FILENO);
    close(original_stderr);

    return result;
}
