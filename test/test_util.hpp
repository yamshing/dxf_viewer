#ifndef TEST_UTIL_HPP
#define TEST_UTIL_HPP

#include <wx/bitmap.h>
#include <wx/image.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <errno.h>

// Function to compare two wxBitmap objects by raw pixel data
inline bool CompareBitmaps(const wxBitmap& bmp1, const wxBitmap& bmp2) {
    if (!bmp1.IsOk() || !bmp2.IsOk()) {
        return false; // One or both bitmaps are invalid
    }

    if (bmp1.GetWidth() != bmp2.GetWidth() || bmp1.GetHeight() != bmp2.GetHeight()) {
        return false; // Dimensions do not match
    }

    wxImage img1 = bmp1.ConvertToImage();
    wxImage img2 = bmp2.ConvertToImage();

    if (img1.GetWidth() != img2.GetWidth() || img1.GetHeight() != img2.GetHeight()) {
        return false; // Image dimensions do not match
    }

    // Compare raw pixel data
    unsigned char* data1 = img1.GetData();
    unsigned char* data2 = img2.GetData();
    size_t dataSize = img1.GetWidth() * img1.GetHeight() * 3; // 3 bytes per pixel (RGB)

    for (size_t i = 0; i < dataSize; ++i) {
        if (data1[i] != data2[i]) {
            return false; // Pixel data does not match
        }
    }

    return true; // Pixel data matches
}

// Function to ensure a directory exists
inline void EnsureDirectoryExists(const std::string& dirPath) {
    if (mkdir(dirPath.c_str(), 0777) == 0) {
        // Directory created
    } else if (errno == EEXIST) {
        // Directory already exists
    } else {
        // Failed to create directory
    }
}

#endif // TEST_UTIL_HPP
