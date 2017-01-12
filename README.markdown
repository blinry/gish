# How to compile (Linux)

Make sure CMake and the development libraries for SDL, OpenAL and Vorbis are installed. In Debian-based systems, you need to install the following packages:

    sudo apt-get install libsdl1.2-dev libopenal-dev libvorbis-dev

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

# How to compile (Mac OS X)

Open the Xcode project in the main directory.
'Get info' on the Gish executable and change its working directory to "Project Directory"
If the build fails, check the dependencies. The Xcode project currently does not use the ./externals directory:
- Frameworks: Cocoa, SDL, OpenAL, Ogg, Vorbis
    Ogg and Vorbis Frameworks built from from http://xiph.org/downloads/ and installed in /Library/Frameworks/.
- libpng; macports is an option. Change appropriate search paths:
    Change (Gish target -> get info -> "Header Search Paths") to point to libpng headers. (e.g. /opt/local/include/libpng14/)
    Using recursive header search of /opt/local/include may slow things down or present conflicts, not recommended.

Note: If you own the original assets, you can use them simply by changing the working directory mentioned above to /Applications/Gish.app/Contents/Resources
An note of caution, this will use the original apps user file as well.

# How to play

Simply run `./gish` or `gish.exe`. There are some assets included (codenamed the *FreeGish* project), making Gish a completely free game! There is also one level available, `freegish.lvl`, you'll find it under "Custom Levels". Try it and replace what you don't like.

If you own the original assets, you may also copy those into this directory. You'll need:

- animation
- level
- music
- sound
- texture
- tile01 ... tile07


# Note: this branch has been merged with SysLord, who added a few fun features, documented in Note-SysLord.markdown
