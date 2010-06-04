# How to compile (Linux)

Make sure CMake and the development libraries for SDL, OpenAL and Vorbis are installed. In Debian-based systems, you need to install the following packages:

    cmake libsdl1.2-dev libopenal-dev libvorbis-dev

Then simply issue

    mkdir build && cd build
    cmake ..
    make

# How to compile (Windows with VS2008)

Download and install the required libraries:

- <http://www.libsdl.org/release/SDL-devel-1.2.14-VC8.zip>
- <http://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-devel-1.2.11-VC.zip>
- <http://downloads.xiph.org/releases/ogg/libogg-1.2.0.zip>
    - compile using *win32\VS2008\libogg_static.vcproj*
- <http://downloads.xiph.org/releases/vorbis/libvorbis-1.3.1.zip>
    - compile *win32\VS2008\libvorbis\libvorbis_static.vcproj*
    - compile *win32\VS2008\libvorbisfile\libvorbisfile_static.vcproj*
- <http://connect.creativelabs.com/openal/Downloads/OpenAL11CoreSDK.zip>
    - install
    - create *C:\Program Files\OpenAL 1.1 SDK\include\AL* and copy all files from *C:\Program Files\OpenAL 1.1 SDK\include*

In Visual Studio add to your include-paths:

- *...\libvorbis-1.3.1\include*
- *...\libogg-1.2.0\include*
- *C:\Program Files\OpenAL 1.1 SDK\include*
- *...\SDL-1.2.14_VC8\include*
- *...\SDL_mixer-1.2.11\include*

In Visual Studio add to your library-paths:

- *...\libvorbis-1.3.1\win32\VS2008\libvorbisfile\Win32\Debug*
- *...\libogg-1.2.0\win32\VS2008\Win32\Debug*
- *...\libvorbis-1.3.1\win32\VS2008\libvorbis\Win32\Debug*
- *C:\Program Files\OpenAL 1.1 SDK\libs\Win32*
- *...\SDL_mixer-1.2.11\lib*
- *...\SDL-1.2.14_VC8\lib*

Open *gish.sln* and compile.

You will need the following files to be present:

- OpenAL32.dll
- SDL.DLL

# How to play

Simply run `./gish` or `gish.exe`. There are some assets included (codenamed the *FreeGish* project), making Gish a completely free game! There is also one level available, `freegish.lvl`, you'll find it under "Custom Levels". Try it and replace what you don't like.

If you own the original assets, you may also copy those into this directory. You'll need:

- animation
- level
- music
- sound
- texture
- tile01 ... tile07
