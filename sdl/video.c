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

void listvideomodes(void)
  {
  int count;
  SDL_Rect **sdlmode;

  numofsdlvideomodes=0;

  sdlmode=SDL_ListModes(NULL,SDL_OPENGL|SDL_FULLSCREEN);

  if (sdlmode==(SDL_Rect **)-1)
    {
    sdlvideomode[numofsdlvideomodes].resolutionx=640;
    sdlvideomode[numofsdlvideomodes].resolutiony=480;
    sdlvideomode[numofsdlvideomodes].bitsperpixel=32;
    numofsdlvideomodes++;
    sdlvideomode[numofsdlvideomodes].resolutionx=800;
    sdlvideomode[numofsdlvideomodes].resolutiony=600;
    sdlvideomode[numofsdlvideomodes].bitsperpixel=32;
    numofsdlvideomodes++;
    sdlvideomode[numofsdlvideomodes].resolutionx=1024;
    sdlvideomode[numofsdlvideomodes].resolutiony=768;
    sdlvideomode[numofsdlvideomodes].bitsperpixel=32;
    numofsdlvideomodes++;

    return;
    }

  for (count=0;sdlmode[count]!=NULL && count<64;count++)
    {
    //if (SDL_VideoModeOK(sdlmode[count]->w,sdlmode[count]->h,32,SDL_OPENGL|SDL_FULLSCREEN))
      {
      sdlvideomode[numofsdlvideomodes].resolutionx=sdlmode[count]->w;
      sdlvideomode[numofsdlvideomodes].resolutiony=sdlmode[count]->h;
      sdlvideomode[numofsdlvideomodes].bitsperpixel=32;
      numofsdlvideomodes++;
      }
    //if (SDL_VideoModeOK(sdlmode[count]->w,sdlmode[count]->h,16,SDL_OPENGL|SDL_FULLSCREEN))
      {
      sdlvideomode[numofsdlvideomodes].resolutionx=sdlmode[count]->w;
      sdlvideomode[numofsdlvideomodes].resolutiony=sdlmode[count]->h;
      sdlvideomode[numofsdlvideomodes].bitsperpixel=16;
      numofsdlvideomodes++;
      }
    }
  }

