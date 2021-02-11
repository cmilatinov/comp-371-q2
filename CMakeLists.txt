# CMakeList.txt : CMake project for COMP426-Asg1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.17)

project ("COMP371-Project")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(src/Headers)

# Add source to this project's executable.
add_executable ("PA1" "src/Camera.cpp" "src/Line.cpp" "src/Main.cpp" "src/Mesh.cpp" "src/Shader.cpp" "src/Window.cpp")

target_link_libraries("PA1" PRIVATE glfw GLEW::GLEW glm)

# TODO: Add tests and install targets if needed.
