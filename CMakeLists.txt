cmake_minimum_required(VERSION 3.6)
project(JumpOrDie)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG)
endif()


#find_package(GLM REQUIRED)
find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(JumpOrDie ${SOURCE_FILES}
        3rdParty/src/gl3w/gl3w.c
        3rdParty/src/lodepng/lodepng.cpp
        src/Car.cpp
        src/GameScene.cpp
        src/Main.cpp
        src/Player.cpp
        src/TraficSign.cpp
        src/Tree.cpp
        src/Engine/Application.cpp
        src/Engine/Graphics/Texture.cpp
        src/Engine/Input/Keyboard.cpp
        src/Engine/Input/Mouse.cpp
        src/Engine/Managers/ResourceManager.cpp
        src/Engine/Managers/SceneManager.cpp
        src/Engine/Managers/ShaderManager.cpp
        src/Engine/Models/Cube.cpp
        src/Engine/Models/CubeColor.cpp
        src/Engine/Models/CubeTexture.cpp
        src/Engine/Models/Floor.cpp
        src/Engine/Models/FloorColor.cpp
        src/Engine/Models/FloorTexture.cpp
        src/Engine/Models/GameObject.cpp
        src/Engine/Models/Model.cpp
        src/Engine/Models/Triangle.cpp
        src/Engine/Scenes/Camera.cpp
        src/Engine/Scenes/Scene.cpp
        src/Engine/Utils/FileReader.cpp
        src/Engine/Utils/Message.cpp
        src/Engine/Utils/Timer.cpp
        )

target_include_directories(JumpOrDie PUBLIC
        #${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        3rdParty/include)

target_link_libraries(JumpOrDie
        ${OPENGL_LIBRARY}
        ${GLFW_LIBRARY}
        ${CMAKE_DL_LIBS})