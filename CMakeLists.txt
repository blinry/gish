cmake_minimum_required(VERSION 2.6)

project(Gish C)

link_libraries(SDL GL openal vorbisfile)

add_executable(gish main.c)
