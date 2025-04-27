cmake_minimum_required(VERSION 3.10)
project(ActivityTracker)

set(CMAKE_CXX_STANDARD 11)
set(wxWidgets_ROOT_DIR "C:/Users/Jonathan/Desktop/wxWidgets_3.0.5")
set(wxWidgets_LIB_DIR  "${wxWidgets_ROOT_DIR}/lib/gcc510TDM_x64_dll")
set(wxWidgets_INCLUDE_DIR "${wxWidgets_ROOT_DIR}/include")
set(wxWidgets_USE_STATIC ON)

find_package(wxWidgets REQUIRED net gl core base xrc adv)
include(${wxWidgets_USE_FILE})

add_executable(ActivityTracker main.cpp
        MainFrame.cpp
        MainFrame.h
        Activity.cpp
        Activity.h
        Register.cpp
        Register.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})