/*
Copyright (C) 2005, 2010 - Cryptic Sea

This file is part of Gish.

Gish is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "config.h"

#include "sdl/sdl.h"

#include "video/opengl.h"

#include "audio/audio.h"
#include "game/config.h"
#include "game/high.h"
#include "game/mainmenu.h"
#include "game/player.h"
#include "game/options.h"
#include "input/joystick.h"
#include "menu/menu.h"
#include "sdl/endian.h"
#include "sdl/event.h"
#include "sdl/video.h"
#include "video/text.h"
#include "video/texture.h"

#ifdef DATAPATH
#include <unistd.h>
#define DATAPATH_STR3(X) #X
#define DATAPATH_STR2(X) DATAPATH_STR3(X)
#define DATAPATH_STR DATAPATH_STR2(DATAPATH)
#endif

const SDL_VideoInfo *sdlvideoinfo;
SDL_PixelFormat *sdlpixelformat;

Uint8 iconmask[128]={
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x03,0xF0,0x00,
0x00,0x3F,0xFC,0x00,
0x00,0xFF,0xFF,0x00,
0x03,0xFF,0xFF,0x80,
0x07,0xFF,0xFF,0xC0,
0x0F,0xFF,0xFF,0xE0,
0x0F,0xFF,0xFF,0xF0,
0x1F,0xFF,0xFF,0xF8,
0x3F,0xFF,0xFF,0xFC,
0x3F,0xFF,0xFF,0xFC,
0x7F,0xFF,0xFF,0xFE,
0x7F,0xFF,0xFF,0xFE,
0xFF,0xFF,0xFF,0xFE,
0xFF,0xFF,0xFF,0xFE,
0xFF,0xFF,0xFF,0xFE,
0xFF,0xFF,0xFF,0xFE,
0x7F,0xFF,0xFF,0xFE,
0x3F,0xFF,0xFF,0xFE,
0x0F,0xFF,0xFF,0xFE,
0x03,0xFF,0xFF,0xFC,
0x00,0x7F,0xFF,0xF0,
0x00,0x00,0x00,0x00 };

int main (int argc,char *argv[])
  {
  int count;
  int flags;
  const char *temp;

#ifdef DATAPATH
  chdir(DATAPATH_STR);
#endif

  checkbigendian();

  loadconfig();
  loadscores();
  loadplayers();

  flags=SDL_INIT_VIDEO|SDL_INIT_TIMER;
  if (config.joystick)
    flags|=SDL_INIT_JOYSTICK;

  SDL_Init(flags);

  sdlvideoinfo=SDL_GetVideoInfo();
  sdlpixelformat=sdlvideoinfo->vfmt;
  if (sdlpixelformat->BitsPerPixel==16)
    config.bitsperpixel=16;

  for (count=1;count<argc;count++)
    {
    if (strcmp("-nosound",argv[count])==0)
      {
      config.sound=0;
      option.sound=0;
      option.music=0;
      }
    if (strcmp("-sound",argv[count])==0)
      config.sound=1;
    if (strcmp("-nomusic",argv[count])==0)
      option.music=0;
    }

  saveconfig();

  SDL_ShowCursor(SDL_DISABLE);

  listvideomodes();

  SDL_WM_SetCaption("Gish","SDL");
  SDL_WM_SetIcon(SDL_LoadBMP("gish.bmp"),iconmask);

  if (windowinfo.bitsperpixel==16)
    {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,5);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,0);
    }
  if (windowinfo.bitsperpixel==32)
    {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    }
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,windowinfo.depthbits);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,windowinfo.stencilbits);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  if (windowinfo.fullscreen)
    SDL_SetVideoMode(windowinfo.resolutionx,windowinfo.resolutiony,windowinfo.bitsperpixel,SDL_OPENGL|SDL_FULLSCREEN);
  else
    SDL_SetVideoMode(windowinfo.resolutionx,windowinfo.resolutiony,windowinfo.bitsperpixel,SDL_OPENGL);

  loadglextentions();

  for (count=0;count<2048;count++)
    glGenTextures(1,&texture[count].glname);

  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);

  if (config.joystick)
    {
    numofjoysticks=SDL_NumJoysticks();
    for (count=0;count<numofjoysticks;count++)
      {
      joy[count]=SDL_JoystickOpen(count);
      temp=SDL_JoystickName(count);
      strcpy(joystick[count].name,temp);
      joystick[count].numofbuttons=SDL_JoystickNumButtons(joy[count]);
      joystick[count].numofhats=SDL_JoystickNumHats(joy[count]);
      }

    SDL_JoystickEventState(SDL_IGNORE);
    }

  font.texturenum=0;
  font.cursornum=0;
  font.sizex=640;
  font.sizey=480;

  loadtexturetga(1000,"font00.tga",0,GL_CLAMP,GL_CLAMP,GL_LINEAR,GL_LINEAR);
  loadtexturetga(1001,"font01.tga",0,GL_CLAMP,GL_CLAMP,GL_LINEAR,GL_LINEAR);

  loadtexturetga(768,"mouse00.tga",0,GL_CLAMP,GL_CLAMP,GL_LINEAR,GL_LINEAR);
  loadtexturetga(769,"mouse00.tga",0,GL_CLAMP,GL_CLAMP,GL_LINEAR,GL_LINEAR);

  setupmenuitems();

  if (!glext.multitexture)
    {
    notsupportedmenu();

    SDL_WM_IconifyWindow();
    SDL_Quit();
    return(0);
    }
    
  if (config.sound)
    setupaudio();

  mainmenu();

  saveconfig();
  savescores();
  saveplayers();

  if (config.sound)
    shutdownaudio();

  SDL_WM_IconifyWindow();

  SDL_Quit();

  return(0);
  }
