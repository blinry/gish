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

void checkmouse(void)
  {
	Uint8 buttons;

	memcpy(&prevmouse,&mouse,sizeof(mouse));
  //buttons=SDL_GetRelativeMouseState(&mouse.xdif,&mouse.ydif); 
  //SDL_PumpEvents();
  buttons=SDL_GetMouseState(&mouse.x,&mouse.y); 
  mouse.x=mouse.x*640/windowinfo.resolutionx;
  mouse.y=mouse.y*480/windowinfo.resolutiony;

  mouse.xdif=mouse.x-prevmouse.x;
  mouse.ydif=mouse.y-prevmouse.y;
	
  if (buttons&SDL_BUTTON(1))
		mouse.lmb=1;
	else
		mouse.lmb=0;
	
  if (buttons&SDL_BUTTON(3))
		mouse.rmb=1;
	else
		mouse.rmb=0;

	if (mouse.lmb==0 && prevmouse.lmb==1)
		mouse.lmbr=1;
	else
		mouse.lmbr=0;
	
	if (mouse.rmb==0 && prevmouse.rmb==1)
		mouse.rmbr=1;
	else
		mouse.rmbr=0;
  }


