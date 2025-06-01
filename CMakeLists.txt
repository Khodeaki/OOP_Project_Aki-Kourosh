cmake_minimum_required(VERSION 3.28)
project(untitled20 CXX)

set(CMAKE_CXX_STANDARD 17)

# Add all your source files here.
# Make sure to include the .cpp files for all classes you use (Nodes, Resistor, Capacitor, etc.)
add_executable(untitled20
        main.cpp
        Nodes.cpp
        view.cpp
        Components.cpp
        Element.cpp    # Add this if you have it
        ElementException.cpp
)