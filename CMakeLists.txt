project(muggengine)
cmake_minimum_required(VERSION 2.8)

set(LIBRARIES
    lua
    glfw
    enet
    freetype
    freeimage
    assimp
    GLEW
    GL
    GLU
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCES src/*.cpp src/*.c)
file(GLOB HEADERS headers/*.hpp headers/*.h)


add_executable(${PROJECT_NAME} ./src/main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
include_directories(./headers)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
