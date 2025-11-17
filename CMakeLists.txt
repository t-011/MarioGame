cmake_minimum_required(VERSION 4.0)
project(MarioGame)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "C:/Libraries/SFML-3.0.2/lib/cmake")
find_package(SFML 3.0 COMPONENTS Graphics Window System Audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

add_executable(MarioGame main.cpp
        Animation.cpp
        Animation.h
        Player.cpp
        Player.h
        TextureManager.cpp
        TextureManager.h
        Collider.cpp
        Collider.h)
target_link_libraries(MarioGame PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)
target_link_options(MarioGame PRIVATE -static-libstdc++ -static-libgcc)
