cmake_minimum_required(VERSION 2.8)
project(muggengine)

set(LIBRARIES
    lua
    GLEW
    enet
    freeimage
    assimp
    GL
    GLU
)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
find_package(Freetype REQUIRED)

set(CMAKE_CXX_FLAGS " -std=c++11")

include_directories(${SDL2_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ./headers ./src)
file(GLOB SOURCES src/*.cpp src/*.c)
file(GLOB HEADERS headers/*.hpp headers/*.h)

add_executable(${PROJECT_NAME} ./src/main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
