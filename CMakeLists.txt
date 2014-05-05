project(muggengine)
cmake_minimum_required(VERSION 2.8)

set(LIBRARIES
    lua
    glfw
    enet
    freeimage
    freetype
    openal
    assimp
    GLEW
    GL
    GLU
)

file(GLOB SOURCES src/*.cpp src/*.c)
file(GLOB HEADERS headers/*.hpp headers/*.h)

add_executable(${PROJECT_NAME} ./src/main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
include_directories(./headers)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
