cmake_minimum_required(VERSION 2.6)

project(Gish C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/;${CMAKE_MODULE_PATH}")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")

find_package(SDL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Vorbis REQUIRED)

add_definitions(-static -static-libgcc)

include_directories(
  ${SDL_INCLUDE_DIR} 
  ${OPENAL_INCLUDE_DIR} 
  ${OPENGL_INCLUDE_DIR}
  ${Vorbis_INCLUDE_DIR}
)

add_executable(gish main.c)

target_link_libraries(gish 
  ${SDL_LIBRARY}
  ${OPENAL_LIBRARY}
  ${OPENGL_LIBRARIES}
  ${Vorbis_LIBRARIES}
)
