# How to compile (Linux)

To compile, you need to install at least the following packages:

    libopenal-dev libsdl1.2-dev cmake

Then simply issue

    cmake .
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

# How to play

To play, you need the game's resources, more specifically the following directories:

- animation
- level
- music
- replay (may be empty)
- sound
- texture
- tile01 ... tile07

Under Windows you'll also need the files:

- OpenAL32.dll
- SDL.DLL

Copy them into the directory of your compiled binaries and run `./gish` or `gish.exe`.
