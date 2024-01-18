cmake_minimum_required(VERSION 3.10)

project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/dependencies/include)

# Add the current source directory
include_directories(${CMAKE_SOURCE_DIR})

# Source files
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/main.cpp")# "${CMAKE_SOURCE_DIR}/shader.h")

# Add glad.c if it exists
if(EXISTS "${CMAKE_SOURCE_DIR}/glad.c")
    list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/glad.c")
endif()

# Executable
add_executable(OpenGLApp ${SOURCES})

# Link libraries
set(GLFW_LIB "/Users/milladbahrami/Desktop/bahram23GC3A4/dependencies/library/libglfw.3.3.dylib")

if(NOT GLFW_LIB)
    message(FATAL_ERROR "GLFW library not found")
endif()

target_link_libraries(OpenGLApp
        ${GLFW_LIB}
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
)

# Compiler flags
target_compile_options(OpenGLApp PRIVATE -Wall -g -Wno-deprecated)
