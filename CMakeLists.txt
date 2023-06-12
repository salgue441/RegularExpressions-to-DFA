cmake_minimum_required(VERSION 3.20)
project(regex-to-dfa-converter)

# C++ Standard Version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost Libraries
find_package(Boost REQUIRED COMPONENTS regex)

# OpenGL and GLEW Libraries
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Include directories
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp

    # Project files
    src/node/node.cpp
    src/graph/graph.cpp
    src/nfa/nfa.cpp
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(regex-to-dfa-converter
    ${Boost_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)