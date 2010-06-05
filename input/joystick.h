#ifndef GISH_INPUT_JOYSTICK_H
#define GISH_INPUT_JOYSTICK_H
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

#include "../sdl/sdl.h"

void checkjoystick(void);

typedef struct {
  int x;
  int y;
  float axis[2];
  int throttle;
  int numofbuttons;
  int button[32];
  int numofhats;
  int hat[4];
  char name[64];
  } _joystick;

typedef struct {
  int x;
  int y;
  float axis[2];
  int throttle;
  int numofbuttons;
  int button[32];
  int numofhats;
  int hat[4];
  char name[64];
  } _prevjoystick;

extern int numofjoysticks;
extern SDL_Joystick *joy[16];

extern int joystickenabled;
extern int joystickused;

extern _joystick joystick[16];
extern _prevjoystick prevjoystick[16];

#endif /* GISH_INPUT_JOYSTICK_H */
