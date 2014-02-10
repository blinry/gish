cmake_minimum_required(VERSION 2.6)

project(FreeGish C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-extras/;${CMAKE_MODULE_PATH}")

option(INSTALL_FHS "Install into Linux FHS" OFF)

#don't pollute source dir
if(NOT ${INSTALL_FHS})
    set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")
endif(NOT ${INSTALL_FHS})

# Uncomment this to hardcode the data path. On the command line, you
# would actually give -DDATAPATH='"/usr/share/games/gish"' or similar
# but CMake does the extra quoting for us.
#add_definitions(-DDATAPATH="/usr/share/games/gish")

find_package(SDL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Vorbis REQUIRED)
find_package(PNG REQUIRED)
find_library(M_LIBRARIES m)

include_directories(
    ${SDL_INCLUDE_DIR}
    ${OPENAL_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${Vorbis_INCLUDE_DIR}
    ${PNG_INCLUDE_DIR}
)

if(NOT BIN_DIR)
    if(UNIX)
	SET(BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
    endif(UNIX)
endif(NOT BIN_DIR)

if(NOT DATA_DIR)
    if(UNIX)
	SET(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/freegish")
    endif(UNIX)
endif(NOT DATA_DIR)

if(${INSTALL_FHS})
    ADD_DEFINITIONS(-DDATAPATH="${DATA_DIR}")
endif(${INSTALL_FHS})

add_subdirectory(src)

install(FILES gish.bmp DESTINATION ${DATA_DIR})

set(DDIRS animation level sound texture)

foreach(DIR_NAME ${DDIRS})
    install(DIRECTORY ${DIR_NAME}
	DESTINATION ${DATA_DIR}
	PATTERN .gitignore EXCLUDE
	PATTERN *.txt EXCLUDE
	PATTERN backup EXCLUDE
	)
endforeach(DIR_NAME ${DDIRS})
