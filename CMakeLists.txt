cmake_minimum_required(VERSION 3.10)

# Set the project version
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# Pass the version to the project
project(DxfViewer VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)


set(DXFRW_LIB "/usr/local/lib/libdxfrw.a" CACHE FILEPATH "Path to the DXFRW library")
set(DXFRW_INCLUDE_DIR "/usr/local/include/libdxfrw" CACHE PATH "Path to the DXFRW include directory")
set(GTEST_LIB_DIR "/usr/lib" CACHE PATH "Path to GoogleTest library directory")
set(GTEST_INCLUDE_DIR "/usr/include" CACHE PATH "Path to GoogleTest include directory")


find_package(wxWidgets 3.2 COMPONENTS core base REQUIRED )

if(wxWidgets_USE_FILE)
     include(${wxWidgets_USE_FILE})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wx_ui)
include_directories(${wxWidgets_INCLUDE_DIRS})
include_directories(${DXFRW_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIR})

set(WX_FRAME_SRC wx_ui/app.cpp wx_ui/frame.cpp wx_ui/page.cpp)
set(DRAWABLE_SRC node.cpp drawable.cpp rectangle.cpp circle.cpp line.cpp dxf_interface_impl.cpp dxf_text.cpp) # Add dxf_text.cpp

# Define a static library for shared sources
add_library(DrawableLib STATIC ${DRAWABLE_SRC} ${WX_FRAME_SRC})

# Link the shared library to the main project
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE main.cpp)
target_link_libraries(${PROJECT_NAME} DrawableLib ${wxWidgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${DXFRW_LIB})

# Add an option to toggle between AddressSanitizer and Valgrind
#  LSAN_OPTIONS=suppressions=../asan.supp ./AppTest

option(DO_MEM_CHECK "Enable Memory Check" OFF)

if(DO_MEM_CHECK)
    option(USE_ASAN "Enable AddressSanitizer" ON)

    # Set debug flags to disable optimizations
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

    if(USE_ASAN)
        # Enable AddressSanitizer
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
        message(STATUS "AddressSanitizer enabled")
    else()
        # Enable LeakSanitizer for Valgrind
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -g")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=leak")
        message(STATUS "LeakSanitizer enabled for Valgrind")
    endif()

    # Ensure AddressSanitizer runtime is linked first (only for ASAN)
    if(USE_ASAN AND CMAKE_BUILD_TYPE MATCHES Debug)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libasan")
    endif()
endif()

# Include the test directory's CMakeLists.txt
add_subdirectory(test)

