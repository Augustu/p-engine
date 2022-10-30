cmake_minimum_required(VERSION 3.10)

project(P-Engine)

set(CMAKE_AUTOMOC ON)

include_directories(include)

find_package(PkgConfig REQUIRED)
find_package (glog 0.6.0 REQUIRED)

# pkg_check_modules(glew REQUIRED IMPORTED_TARGET glew)
# pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)
pkg_check_modules(libglog REQUIRED IMPORTED_TARGET libglog)

# add_library(pengine
#     src/pengine/model/model.cpp
#     src/pengine/model/manager.cpp
#     src/pengine/model/cube.cpp
#     src/pengine/world/world.cpp
#     src/pengine/world/control/keyboard.cpp
#     src/pengine/world/control/mouse.cpp
#     src/pengine/glsl/glsl.cpp
#     src/pengine/element/masspoint.cpp
#     src/pengine/element/masspoint.cpp

#     src/pengine/world/object/object.cpp
#     # src/pengine/world/object/particle.cpp
#     src/pengine/force/gravity/point.cpp
#     )

# add_executable(particle
#     src/demo/particle/main.cpp
#     )
# target_link_libraries(particle pengine glew32 glfw3 assimp soil2 opengl32 libglog)

# add_executable(particles
#     src/demo/particles/main.cpp
#     )
# target_link_libraries(particles pengine glew32 glfw3 assimp soil2 opengl32 libglog)

set(Qt6_DIR "/d/msys64/mingw64/lib/cmake/Qt6")

# set(CMAKE_TOOLCHAIN_FILE "/d/msys64/mingw64/qt6-static/lib/cmake/Qt6/qt.toolchain.cmake")

find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL)
qt_standard_project_setup()

# add_library(pengine
#     # src/pengine/model/model.cpp
#     # src/pengine/model/manager.cpp
#     # src/pengine/model/cube.cpp
#     # src/pengine/world/world.cpp
#     # src/pengine/world/control/keyboard.cpp
#     # src/pengine/world/control/mouse.cpp
#     # src/pengine/glsl/glsl.cpp
#     # src/pengine/element/masspoint.cpp
#     # src/pengine/element/masspoint.cpp

#     # src/pengine/world/object/object.cpp
#     # include\pengine\force\gravity\point.h
#     # src/pengine/world/object/particle.cpp

#     src/pengine/element/masspoint.cpp
#     src/pengine/force/gravity/point.cpp
#     )

# ref https://doc.qt.io/qt-6/cmake-get-started.html

add_library(pengine
    # src/pengine/model/model.cpp
    # src/pengine/model/manager.cpp
    # src/pengine/model/cube.cpp
    # src/pengine/world/world.cpp
    # src/pengine/world/control/keyboard.cpp
    # src/pengine/world/control/mouse.cpp
    # src/pengine/glsl/glsl.cpp
    # src/pengine/element/masspoint.cpp
    # src/pengine/element/masspoint.cpp

    # src/pengine/world/object/object.cpp
    # include\pengine\force\gravity\point.h
    # src/pengine/world/object/particle.cpp

    src/pengine/element/masspoint.cpp
    src/pengine/force/gravity/point.cpp

    src/pengine/model/model.cpp

    src/pengine/world/object/object.cpp

    include/pengine/world/qtworld.h
    src/pengine/world/qtworld.cpp

    src/pengine/model/manager.cpp
    )

target_link_libraries(pengine PRIVATE soil2 opengl32 Qt6::Core Qt::Gui Qt::OpenGL)

qt_add_executable(qtparticles
    src/demo/qtparticles/main.cpp
)

set_target_properties(qtparticles PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qtparticles PUBLIC pengine glfw3 assimp libglog
    Qt::Core
    Qt::Gui
    Qt::OpenGL
)

# add_executable(model
#     src/demo/model/main.cpp
#     )
# target_link_libraries(model pengine glew32 glfw3 assimp soil2 opengl32 libglog)

# add_executable(multi
#     src/demo/multi/main.cpp
#     )
# target_link_libraries(multi pengine glew32 glfw3 assimp soil2 opengl32 glog::glog)

# add_executable(sphere
#     src/demo/sphere/main.cpp
#     )
# target_link_libraries(sphere pengine glew32 glfw3 assimp soil2 opengl32 libglog)
