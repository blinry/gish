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

void setupphysics(void);
void particlecollision(int particlenum);
void objectcollision(int objectnum);
void objectcollisionobject(int objectnum);
void bondsimulation2(void);
int lineintersectline2(float *intersectpoint,float *normal,float *scale,float *startpoint,float *endpoint,float *vertex1,float *vertex2);

struct
  {
  int numofbonds;
  struct
    {
    int part1;
    int part2;
    int part3;
    int part4;
    int type;
    int cycles;
    float elasticity;
    float length;
    float friction;
    float breakpoint;
    float point[3];
    float normal[3];
    float force[2];
    int objectnum[2];
    int blocknum;
    int blockx;
    int blocky;
    float forceapplied[2][3];
    } bond[8192];
  } physicstemp;

int numoflevellines;
struct
  {
  float line[2][3];
  float normal[3];
  float friction;
  int blocknum;
  int blockx;
  int blocky;
  } levelline[1024];
