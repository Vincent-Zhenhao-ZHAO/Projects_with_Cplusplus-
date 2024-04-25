cmake_minimum_required(VERSION 3.10)
project(FlappyBird)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find SFML components
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

# Add executable
add_executable(main main.cpp)

# Link SFML libraries
target_link_libraries(main sfml-graphics sfml-audio)
