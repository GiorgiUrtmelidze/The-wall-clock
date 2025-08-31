cmake_minimum_required(VERSION 3.30)
project(Clock)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Clock main.cpp
        Time.cpp
        Time.h)

target_link_libraries(Clock sfml-graphics sfml-window sfml-system)
