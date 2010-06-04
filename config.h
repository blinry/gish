#ifndef GISH_CONFIG_H
#define GISH_CONFIG_H

#ifdef __linux__
 #define LINUX 1
#endif

#ifdef _WIN32
  #define WINDOWS 1
#endif

#ifdef __APPLE__
  #define MAC 1
#endif

#ifdef MAC
  #define __MACOSX__
#endif

#ifdef WINDOWS
  #define INLINE _inline
#else
  #define INLINE inline
#endif

#define pi 3.14159265359

#define GL_GLEXT_PROTOTYPES

#endif /* GISH_CONFIG_H */
