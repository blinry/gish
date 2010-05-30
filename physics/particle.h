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

#define PHYSICSCYCLE 50.0f

void particlecollisionlevel(int particlenum);
void calculatefriction(float *nforce,float *fforce,float *normal,float cofric);
void particlesimulation(void);
void particletimetolive(void);
void createparticle(int type,float *position,float *velocity,float mass,int objectnum,int timetolive);
void deleteparticle(int particlenum);
void applyforceparticle(int particlenum,float force[3]);
void getforceparticle(int particlenum,float force[3]);

int numofparticles;
struct
  {
  float position[3];
  float prevposition[3];
  float velocity[3];
  float prevvelocity[3];
  int type;
  float mass;
  float drag;
  float gravity;
  float elasticity;
  float friction;
  int numofbonds;
  int objectnum;
  int objectid;
  int timetolive;
  int levelcollision;
  int objectcollision;
  int rendertype;
  float rendersize;
  int texturenum;
  } particle[16384];

struct 
  {
  float drag;
  float gravity;
  float elasticity;
  float friction;
  int levelcollision;
  int objectcollision;
  int rendertype;
  } particletype[16384];
