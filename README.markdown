# How to compile (Linux)

To compile, you need to install at least the following packages:

    libopenal-dev libsdl1.2-dev

Then simply issue good ol'

    make

To play, you need the game's resources, more specifically the following directories:

- animation
- level
- music
- replay (may be empty)
- sound
- texture
- tile01 ... tile07

Copy them into this directory and run `./gish`.

# How to compile (Windows with VS2008)

Download and install required libraries:
From http://www.libsdl.org/download-1.2.php:
    SDL-devel-1.2.14-VC8.zip and unzip.

From http://www.libsdl.org/projects/SDL_mixer/:
    SDL_mixer-devel-1.2.11-VC.zip and unzip.

From http://connect.creativelabs.com/openal/Downloads/Forms/AllItems.aspx:
    OpenAL11CoreSDK and install.

From http://xiph.org/downloads/:
    libogg-1.2.0.zip, unzip and compile using libogg-1.2.0\win32\VS2008\libogg_static.vcproj
    libvorbis-1.3.1.zip, unzip and compile using libvorbis-1.3.1\win32\VS2008\libvorbis\libvorbis_static.vcproj and compile using     libvorbis-1.3.1\win32\VS2008\libvorbisfile\libvorbisfile_static.vcproj.

HACK: because gish includes "AL\al.h" I created the directory "C:\Program Files\OpenAL 1.1 SDK\include\AL" and copied all files from "C:\Program Files\OpenAL 1.1 SDK\include".

In Visual Studio add to your include-paths:
    ...\libvorbis-1.3.1\include
    ...\libogg-1.2.0\include
    C:\Program Files\OpenAL 1.1 SDK\include
    ...\SDL-1.2.14_VC8\include
    ...\SDL_mixer-1.2.11\include

In Visual Studio add to your library-paths:
    ...\libvorbis-1.3.1\win32\VS2008\libvorbisfile\Win32\Debug
    ...\libogg-1.2.0\win32\VS2008\Win32\Debug
    ...\libvorbis-1.3.1\win32\VS2008\libvorbis\Win32\Debug
    C:\Program Files\OpenAL 1.1 SDK\libs\Win32
    ...\SDL_mixer-1.2.11\lib
    ...\SDL-1.2.14_VC8\lib

Open gish.sln and compile.