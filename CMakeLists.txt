project(muggengine)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)
aux_source_directory(./src/minilzo MINILZO)

set(LIBRARIES
    lua
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
    assimp
    GLEW
    GL
    GLU
)
add_executable(${PROJECT_NAME} ./src/main.cpp ${SRC_LIST} ${MINILZO})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
