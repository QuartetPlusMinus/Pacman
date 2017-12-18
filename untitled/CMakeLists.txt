cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "/home/murt/Qt/5.10.0/gcc_64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

set(SOURCE_FILES main.cpp mainwindow.h mainwindow.cpp)
add_executable(untitled ${SOURCE_FILES})
target_link_libraries(untitled Qt5::Widgets Qt5::Core)