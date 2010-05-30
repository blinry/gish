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

void editlevel(void);
void setblock(int x,int y,int blocknum);
int getblock(int x,int y);
void rendereditblocks(void);
void editblock(void);
void renderlevellines(void);

struct
  {
  int active;
  int mode;
  int showgrid;
  int showlines;
  int blocknum;
  int objecttype;
  int objectnum;
  char filename[32];
  int editstart[2];
  int editarea[2][2];
  int copysize[2];
  int copybuffer[128][128];
  int paste;
  } editor;

