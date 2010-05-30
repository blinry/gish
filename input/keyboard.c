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

void checkkeyboard(void)
  {
	memcpy(prevkeyboard,keyboard,323);

  memcpy(keyboard,SDL_GetKeyState(NULL),323);

	if (keyboard[SDLK_KP_ENTER])
		keyboard[SDLK_RETURN]=1;
	if (keyboard[SDLK_RCTRL])
		keyboard[SDLK_LCTRL]=1;
	if (keyboard[SDLK_RSHIFT])
		keyboard[SDLK_LSHIFT]=1;

  if (keyboard[SCAN_NUMLEFT])
    keyboard[SCAN_LEFT]=1;
  if (keyboard[SCAN_NUMRIGHT])
    keyboard[SCAN_RIGHT]=1;
  if (keyboard[SCAN_NUMUP])
    keyboard[SCAN_UP]=1;
  if (keyboard[SCAN_NUMDOWN])
    keyboard[SCAN_DOWN]=1;
  }

