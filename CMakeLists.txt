cmake_minimum_required(VERSION 2.8)
project(muggengine)

set(LIBRARIES
    lua
    glfw
    enet
    freeimage
    assimp
    GLEW
    GL
    GLU
)
find_package(Freetype REQUIRED)

set(CMAKE_CXX_FLAGS " -std=c++11")

include_directories(${FREETYPE_INCLUDE_DIRS} ./headers ./src)
file(GLOB SOURCES src/*.cpp src/*.c)
file(GLOB HEADERS headers/*.hpp headers/*.h)

add_executable(${PROJECT_NAME} ./src/main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
