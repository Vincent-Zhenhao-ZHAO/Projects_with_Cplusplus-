cmake_minimum_required(VERSION 3.10)
project(FlappyBird)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find SFML components
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

# Add executable
add_executable(main main.cpp)

# Link SFML libraries
target_link_libraries(main sfml-graphics sfml-audio)

# Copy font files to build directory
set(FONT_DIRECTORY "${CMAKE_SOURCE_DIR}/fonts")
set(TARGET_FONT_DIRECTORY "${CMAKE_BINARY_DIR}/fonts")

# Create target directory for fonts
file(MAKE_DIRECTORY ${TARGET_FONT_DIRECTORY})

# Copy font files to target directory
file(COPY ${FONT_DIRECTORY} DESTINATION ${CMAKE_BINARY_DIR})


