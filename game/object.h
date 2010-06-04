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

void createbox(float position[3],float sizex,float sizey,float mass,float friction);
void createtarboy(float position[3]);
void createwheel(float position[3],float sizex,float sizey,float mass,float friction,int anchor);
void setupobjecttypes(void);
void createrope(int type,int particlenum,int particlenum2,int objectnum,int objectnum2,int texturenum);
void createanchor(float position[3]);
void createbutton(float position[3],float mass);
void createswitch(float position[3],float mass,int rotate);
void createbeast(int beasttype,float position[3],float sizex,float sizey,float mass,float friction);
void createbobble(int beasttype,float position[3],float sizex,float sizey,float mass,float friction);
void createhead(float position[3],float sizex,float sizey,float mass,float friction);
void createamber(float position[3]);
void creategenerator(float position[3],float mass);
void deleteobject(int objectnum);
void deleterope(int ropenum);
void objecttimetolive(void);
void createcar(float position[3],float sizex,float sizey,float mass,float friction);

int numofobjects;
struct
  {
  int type;
  int texturenum;
  int timetolive;
  int prevhitpoints;
  int hitpoints;
  int damagedelay;
  int animationnum;
  int animationtype;
  int frame;
  float framedelay;
  int direction;
  int link;
  float mass;
  float axis[8];
  int button;
  float data[8];
  int idata[8];
  int soundnum[4];
  float size[2];
  float position[3];
  float prevposition[3];
  int numoforientations;
  float orientation[3][3];
  float angle;
  float velocity[3];
  float prevvelocity[3];
  float radius;
  float friction;
  float frictionapplied;
  int numofparticles;
  int particle[32];
  int particlestick[32];
  float particlestickposition[32][3];
  float particlesticknormal[32][3];
  int numofcdlines;
  int cdline[32][2];
  float texcoord[4][2];
  int lighttype;
  int lighton;
  float lightcolor[3];
  float lightintensity;
  float lightintensitymax;
  int rotate;
  int ai;
  int beasttype;
  } object[512];

struct
  {
  int collide[256];
  int numofpoints;
  struct
    {
    int type;
    float position[3];
    float mass;
    } point[64];
  int numoflinks;
  struct
    {
    int type;
    int part1;
    int part2;
    } link[256];
  } objecttype[128];

int numofropes;
struct
  {
  int type;
  int part1;
  int part2;
  int bondnum;
  int link;
  int texturenum;
  float angle;
  float cycle;
  float cyclelength;
  float cyclecount;
  float range;
  } rope[1024];
