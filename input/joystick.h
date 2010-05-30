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

void checkjoystick(void);

int numofjoysticks;
SDL_Joystick *joy[16];

int joystickenabled;
int joystickused;

struct {
  int x;
  int y;
  float axis[2];
  int throttle;
  int numofbuttons;
  int button[32];
  int numofhats;
  int hat[4];
  char name[64];
  } joystick[16];

struct {
  int x;
  int y;
  float axis[2];
  int throttle;
  int numofbuttons;
  int button[32];
  int numofhats;
  int hat[4];
  char name[64];
  } prevjoystick[16];

