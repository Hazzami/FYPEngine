cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(FYP2025)

add_definitions(-DSDL_MAIN_HANDLED)

include_directories(
  src
  contrib/cl-windows-x86_64/include
)

link_directories(
  contrib/cl-windows-x86_64/lib
)

add_library(FYPEngine
  src/FYPEngine/Entity.cpp
  src/FYPEngine/Component.cpp
  src/FYPEngine/Core.cpp
  src/FYPEngine/Window.cpp
  src/FYPEngine/Keyboard.cpp
  src/FYPEngine/Mouse.cpp
  src/FYPEngine/StaticObject.cpp
  src/FYPEngine/ObjectController.cpp
  src/FYPEngine/PhysicsObject.cpp
  src/FYPEngine/CollisionBox.cpp
  src/FYPEngine/Background.cpp
  src/FYPEngine/WorldObject.cpp
  src/FYPEngine/ParallaxObject.cpp
  src/FYPEngine/Texture.cpp

  src/FYPEngine/FYPEngine.h
  src/FYPEngine/Entity.h
  src/FYPEngine/Component.h
  src/FYPEngine/Core.h
  src/FYPEngine/Window.h
  src/FYPEngine/Keyboard.h
  src/FYPEngine/Mouse.h
  src/FYPEngine/StaticObject.h
  src/FYPEngine/ObjectController.h
  src/FYPEngine/PhysicsObject.h
  src/FYPEngine/CollisionBox.h
  src/FYPEngine/Background.h
  src/FYPEngine/WorldObject.h
  src/FYPEngine/ParallaxObject.h
  src/FYPEngine/Texture.h
)
target_link_libraries(FYPEngine glew32 SDL2 opengl32 fltk fltk_forms fltk_gl fltk_images fltk_png fltk_jpeg fltk_z comctl32 gdi32 ole32 uuid)

add_executable(UI
  src/UI/main.cpp
)
target_link_libraries(UI FYPEngine)
