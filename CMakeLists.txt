cmake_minimum_required(VERSION 3.6)
project(JumpOrDie)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG)
endif()


find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(JumpOrDie ${SOURCE_FILES}
        external/lodepng.cpp
        src/main.cpp
        src/Engine/Managers/ShaderManager.cpp
        src/Engine/Models/Cube.cpp
        src/Engine/Core.cpp
        src/GameScene.cpp
        src/Engine/Models/GameObject.cpp
        src/Engine/Scenes/Scene.cpp
        src/Engine/Utils/Timer.cpp
        src/Engine/Utils/Utils.cpp
        src/Engine/Managers/SceneManager.cpp
        src/Engine/Managers/SceneManager.h
        src/Engine/Models/Model.cpp
        src/Engine/Models/Model.h
        src/Engine/Utils/FileReader.cpp
        src/Engine/Utils/FileReader.h
        src/Engine/Input/Keyboard.cpp
        src/Engine/Input/Keyboard.h
        src/Engine/Input/Mouse.cpp
        src/Engine/Input/Mouse.h
        src/Engine/Managers/ResourceManager.cpp
        src/Engine/Managers/ResourceManager.h
        src/Engine/Graphics/Texture.cpp
        src/Engine/Graphics/Texture.h
        src/Engine/Models/CubeColor.cpp
        src/Engine/Models/CubeColor.h
        src/Engine/Models/CubeTexture.cpp
        src/Engine/Models/CubeTexture.h src/Engine/Models/Floor.cpp src/Engine/Models/Floor.h src/Engine/Scenes/Camera.cpp src/Engine/Scenes/Camera.h src/Engine/Models/FloorTexture.cpp src/Engine/Models/FloorTexture.h src/Engine/Models/FloorColor.cpp src/Engine/Models/FloorColor.h)

target_include_directories(JumpOrDie PUBLIC
        external
        ${GLM_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR})

target_link_libraries(JumpOrDie
        ${SDL2_LIBRARY}
        ${OPENGL_LIBRARY}
        ${GLEW_LIBRARY})