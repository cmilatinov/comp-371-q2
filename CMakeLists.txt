# CMakeList.txt : CMake project for COMP426-Asg1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.17)

project ("COMP371-Project")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the required library packages
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glew REQUIRED)
find_package(glm CONFIG REQUIRED)

# Specify the project's include directory
include_directories(src/Headers)

# Clump source files from src
file(GLOB PA1_SRC "src/*.cpp")

# Add the source code to this project's executable.
add_executable ("PA1" ${PA1_SRC})

# Link the needed libraries along with the executable
target_link_libraries("PA1" PRIVATE glfw GLEW::GLEW glm)

# Delete Resource directory if it already exists to prevent zombie files
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/src/Shaders)

# Copy Resource directory to output binary
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/src/Shaders)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Add tests and install targets if needed.
