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

void saveblock(int blocknum);
void loadblock(int blocknum);
void setupblockflags(int blocknum);
void setupblockalpha(int blocknum);

struct
  {
  int numoflines;
  float line[64][8];
  float friction;
  float breakpoint;
  int middamage;
  int foredamage;
  float density;
  float drag;
  int animation;
  int animationspeed;
  int flags;
  } block[1024];

int numofpolygontemps;
struct
  {
  int numofverts;
  float vertex[16][2];
  int ivertex[16][2];
  } polygontemp[16];
