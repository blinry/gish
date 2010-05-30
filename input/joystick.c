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

void checkjoystick(void)
  {
  int count,count2;

  if (!config.joystick)
    return;

  for (count=0;count<numofjoysticks;count++)
    memcpy(&prevjoystick[count],&joystick[count],sizeof(joystick[0]));

  SDL_JoystickUpdate();
  for (count=0;count<numofjoysticks;count++)
    if (joy[count])
      {
      joystick[count].x=SDL_JoystickGetAxis(joy[count],0);
      joystick[count].y=SDL_JoystickGetAxis(joy[count],1);
      for (count2=0;count2<joystick[count].numofbuttons;count2++)
        joystick[count].button[count2]=SDL_JoystickGetButton(joy[count],count2);

      joystick[count].axis[0]=0.0f;
      joystick[count].axis[1]=0.0f;
      if (joystick[count].x<-10000)
        joystick[count].axis[0]=-1.0f;
      if (joystick[count].x>10000)
        joystick[count].axis[0]=1.0f;
      if (joystick[count].y<-10000)
        joystick[count].axis[1]=1.0f;
      if (joystick[count].y>10000)
        joystick[count].axis[1]=-1.0f;

      if (joystick[count].numofhats>0)
        {
        joystick[count].hat[0]=SDL_JoystickGetHat(joy[count],0);
        if (joystick[count].hat[0]==SDL_HAT_UP || joystick[count].hat[0]==SDL_HAT_RIGHTUP || joystick[count].hat[0]==SDL_HAT_LEFTUP)
          joystick[count].axis[1]=1.0f;
        if (joystick[count].hat[0]==SDL_HAT_DOWN || joystick[count].hat[0]==SDL_HAT_RIGHTDOWN || joystick[count].hat[0]==SDL_HAT_LEFTDOWN)
          joystick[count].axis[1]=-1.0f;
        if (joystick[count].hat[0]==SDL_HAT_LEFT || joystick[count].hat[0]==SDL_HAT_LEFTUP || joystick[count].hat[0]==SDL_HAT_LEFTDOWN)
          joystick[count].axis[0]=-1.0f;
        if (joystick[count].hat[0]==SDL_HAT_RIGHT || joystick[count].hat[0]==SDL_HAT_RIGHTUP || joystick[count].hat[0]==SDL_HAT_RIGHTDOWN)
          joystick[count].axis[0]=1.0f;
        }
      }
  }
