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
    src/Graph/graph.cpp
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

# Testing
enable_testing()

# Test sources
set(TEST_SOURCES
    # Test files
    tests/graph.test.cpp
)

# Test executable
add_executable(test_${PROJECT_NAME} ${TEST_SOURCES})

# Link libraries for tests
target_link_libraries(test_${PROJECT_NAME}
    ${Boost_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    gtest
    gtest_main
)

# Add tests
add_test(NAME ${PROJECT_NAME}_test COMMAND test_${PROJECT_NAME})
