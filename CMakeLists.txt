cmake_minimum_required(VERSION 2.8)

project(Gish C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/;${CMAKE_MODULE_PATH}")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Vorbis REQUIRED)

# This should really be done like this but instead the developers made a 
# main.c. Oh well.
#aux_source_directory(audio/ gish_audio_srcs)
#aux_source_directory(game/ gish_game_srcs)
#aux_source_directory(input/ gish_input_srcs)
#aux_source_directory(math/ gish_math_srcs)G
#aux_source_directory(menu/ gish_menu_srcs)
#aux_source_directory(parser/ gish_parser_srcs)
#aux_source_directory(physics/ gish_physics_srcs)
#aux_source_directory(sdl/ gish_sdl_srcs)
#aux_source_directory(video/ gish_video_srcs)

# This builds a completely static lib! :D
add_definitions(-static -static-libgcc)

include_directories(
  ${SDL_INCLUDE_DIR} 
  ${SDLMIXER_INCLUDE_DIR} 
  ${OPENAL_INCLUDE_DIR} 
  ${OPENGL_INCLUDE_DIR}
  ${Vorbis_INCLUDE_DIR}
)

add_executable(gish 
    main.c 
# Commented out because [see above]. This would be the proper way.
#    ${gish_audio_srcs} 
#    ${gish_game_srcs}
#    ${gish_input_srcs}
#    ${gish_math_srcs}
#    ${gish_menu_srcs}
#    ${gish_parser_srcs}
#    ${gish_physics_srcs}
#    ${gish_sdl_srcs}
#    ${gish_video_srcs}
)

target_link_libraries(gish 
  ${SDL_LIBRAY} 
  ${SDLMIXER_LIBRARY} 
  ${OPENAL_LIBRARY}
  ${OPENGL_LIBRARIES}
  ${Vorbis_LIBRARIES}
)

# vim:ts=2:sw=2:et
