cmake_minimum_required(VERSION 2.6)

project(Gish C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/;${CMAKE_MODULE_PATH}")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")

find_package(SDL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Vorbis REQUIRED)
find_package(PNG REQUIRED)


include_directories(
    ${SDL_INCLUDE_DIR}
    ${OPENAL_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${Vorbis_INCLUDE_DIR}
    ${PNG_INCLUDE_DIR}
)

set(GISH_SRCS
    audio/audio.c
    game/ai.c
    game/animation.c
    game/block.c
    game/boss.c
    game/config.c
    game/credits.c
    game/custom.c
    game/damage.c
    game/debug.c
    game/editor.c
    game/game.c
    game/gameaudio.c
    game/gamemenu.c
    game/gameobject.c
    game/gametexture.c
    game/high.c
    game/level.c
    game/lighting.c
    game/logic.c
    game/mainmenu.c
    game/mappack.c
    game/music.c
    game/objedit.c
    game/objfunc.c
    game/options.c
    game/physics.c
    game/player.c
    game/prerender.c
    game/random.c
    game/record.c
    game/render.c
    game/replay.c
    game/ropeedit.c
    game/setup.c
    game/socket.c
    game/sprite.c
    game/vsmode.c
    input/joystick.c
    input/keyboard.c
    input/mouse.c
    math/intersec.c
    math/vector.c
    menu/menu.c
    parser/parser.c
    physics/bond.c
    physics/object.c
    physics/particle.c
    sdl/endian.c
    sdl/event.c
    sdl/file.c
    sdl/video.c
    video/glfunc.c
    video/opengl.c
    video/text.c
    video/texture.c
    main.c
)

set(GISH_H
    audio/audio.h
    game/ai.h
    game/animation.h
    game/block.h
    game/boss.h
    game/config.h
    game/credits.h
    game/custom.h
    game/damage.h
    game/debug.h
    game/editor.h
    game/english.h
    game/game.h
    game/gameaudio.h
    game/gamemenu.h
    game/gameobject.h
    game/gametexture.h
    game/high.h
    game/level.h
    game/lighting.h
    game/logic.h
    game/mainmenu.h
    game/mappack.h
    game/music.h
    game/objedit.h
    game/objfunc.h
    game/options.h
    game/physics.h
    game/player.h
    game/prerender.h
    game/random.h
    game/record.h
    game/render.h
    game/replay.h
    game/ropeedit.h
    game/setup.h
    game/socket.h
    game/sprite.h
    game/vsmode.h
    input/joystick.h
    input/keyboard.h
    input/mouse.h
    math/intersec.h
    math/math.h
    math/vector.h
    menu/menu.h
    parser/parser.h
    physics/bond.h
    physics/object.h
    physics/particle.h
    sdl/endian.h
    sdl/event.h
    sdl/file.h
    sdl/sdl.h
    sdl/video.h
    video/glext.h
    video/glfunc.h
    video/opengl.h
    video/text.h
    video/texture.h
    config.h
)

add_executable(gish ${GISH_SRCS} ${GISH_H})

target_link_libraries(gish
    ${SDL_LIBRARY}
    ${OPENAL_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${Vorbis_LIBRARIES}
    ${PNG_LIBRARIES}
)
