cmake_minimum_required(VERSION 3.14)
project(ActivityTracker)

set(CMAKE_CXX_STANDARD 14) # required for Google Test
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# wxWidgets
set(wxWidgets_ROOT_DIR "C:/Users/Jonathan/Desktop/wxWidgets_3.0.5")
set(wxWidgets_LIB_DIR  "${wxWidgets_ROOT_DIR}/lib/gcc510TDM_x64_dll")
set(wxWidgets_INCLUDE_DIR "${wxWidgets_ROOT_DIR}/include")
set(wxWidgets_USE_STATIC ON)

find_package(wxWidgets REQUIRED net gl core base xrc adv)
include(${wxWidgets_USE_FILE})

# source files
set(SOURCE_FILES main.cpp
        MainFrame.cpp
        MainFrame.h
        Activity.cpp
        Activity.h
        Register.cpp
        Register.h
        AddActivityDialog.cpp
        AddActivityDialog.h)

# shared library, to reuse in tests
add_library(core ${SOURCE_FILES})

# main .exe file
add_executable(ActivityTracker ${SOURCE_FILES}) # puts together all source files
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES}) # links source files to wxWidgets library

add_subdirectory(test)

