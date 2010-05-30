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

void checksystemmessages(void)
  {
  int count;
	SDL_Event event;

  if (windowinfo.minimized)
    SDL_Delay(20);

  while (SDL_PollEvent(&event))
    {
    if (event.type==SDL_ACTIVEEVENT)
      {
      if (event.active.state&SDL_APPACTIVE)
        {
        if (event.active.gain==1)
          {
          if (windowinfo.fullscreen)
            SDL_SetVideoMode(windowinfo.resolutionx,windowinfo.resolutiony,windowinfo.bitsperpixel,SDL_OPENGL|SDL_FULLSCREEN);
          else
            SDL_SetVideoMode(windowinfo.resolutionx,windowinfo.resolutiony,windowinfo.bitsperpixel,SDL_OPENGL);

          for (count=0;count<2048;count++)
            if (texture[count].sizex!=0)
              setuptexture(count);

          windowinfo.minimized=0;
          }
        }
      if (event.active.state&SDL_APPINPUTFOCUS)
        if (event.active.gain==0)
          {
					if(game.exit==0)
	          game.pause=1;	
          windowinfo.minimized=1;
          }
      }
    if (event.type==SDL_QUIT)
      windowinfo.shutdown=1;
    }
  }
