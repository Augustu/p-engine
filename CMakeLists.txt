cmake_minimum_required(VERSION 3.10)

project(P-Engine)

include_directories(include)

find_package(PkgConfig REQUIRED)

pkg_check_modules(glew REQUIRED IMPORTED_TARGET glew)
pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)

add_library(pengine
    src/pengine/world/world.cpp
    src/pengine/world/control/keyboard.cpp
    src/pengine/world/control/mouse.cpp
    src/pengine/world/object/object.cpp
    src/pengine/world/object/particle.cpp
    src/pengine/element/masspoint.cpp
    src/pengine/model/model.cpp
    src/pengine/model/cube.cpp

    src/pengine/glsl/glsl.cpp
    )

add_executable(particle
    src/demo/particle/main.cpp
    )
target_link_libraries(particle pengine glew32 glfw3 assimp soil2 opengl32)

add_executable(model
    src/demo/model/main.cpp
    )
target_link_libraries(model pengine glew32 glfw3 assimp soil2 opengl32)
