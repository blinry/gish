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

void particlecollisionlevel(int particlenum)
  {
  int count;
  float vec[3],vec2[3],vec3[3];
  float normal[3];
  float intersectpoint[3];
  float friction;
  float scale;
  float scaletemp;

  if (particle[particlenum].timetolive==0)
    return;

  count=0;
  scale=1.0f;

  while (count<10 && lineintersectlevel(intersectpoint,normal,&scaletemp,particle[particlenum].prevposition,particle[particlenum].position))
    {
    scaleaddvectors(particle[particlenum].position,intersectpoint,normal,0.01f);

    scale*=1.0f-scaletemp;
    if (dotproduct(particle[particlenum].velocity,normal)<0.0f)
      {
      copyvector(vec,particle[particlenum].velocity);
      calculatefriction(vec,vec2,normal,particle[particlenum].friction);
  
      scaleaddvectors(particle[particlenum].velocity,particle[particlenum].velocity,vec,-particle[particlenum].elasticity);
      scaleaddvectors(particle[particlenum].velocity,particle[particlenum].velocity,vec2,-1.0f);

      copyvector(particle[particlenum].prevposition,particle[particlenum].position);
      scaleaddvectors(particle[particlenum].position,particle[particlenum].prevposition,particle[particlenum].velocity,scale);
      }
    else
      {
      copyvector(particle[particlenum].prevposition,particle[particlenum].position);
      scaleaddvectors(particle[particlenum].position,particle[particlenum].prevposition,particle[particlenum].velocity,scale);
      }

    count++;
    }
  }

void calculatefriction(float *nforce,float *fforce,float *normal,float cofric)
  {
  float vec[3];
  float veclength;

  copyvector(vec,nforce);
  scalevector(nforce,normal,dotproduct(vec,normal));
  subtractvectors(fforce,vec,nforce);

  veclength=vectorlength(fforce);
  if (veclength>0.00001f)
    {
    normalizevector(vec,fforce);
    if (veclength>cofric*vectorlength(nforce))
      veclength=cofric*vectorlength(nforce);
    scalevector(fforce,vec,veclength);
    }
  else
    zerovector(fforce);
  }

void particlesimulation(void)
  {
  int count,count2;
  int x,y;
  int blocknum;
  float vec[3];
  float scale;

  for (count=0;count<numofparticles;count++)
    {
    //particle[count].velocity[1]-=particle[count].gravity;
    scalevector(particle[count].velocity,particle[count].velocity,particle[count].drag);
    x=particle[count].position[0];
    y=particle[count].position[1];
    blocknum=level.foregrid[y][x];
    if (block[blocknum].density!=0.0f)
      {
      scale=1.0f;

      /*
      scale=particle[count].position[1]-(float)y;
      scale=1.0f-scale;

      if (block[level.foregrid[y+1][x]].density!=0.0f)
        scale=1.0f;
      */
      /*
      if (level.foregrid[y+1][x]>=168 && level.foregrid[y+1][x]<172)
        scale+=1.0f;
      if (level.foregrid[y+2][x]>=168 && level.foregrid[y+2][x]<172)
        scale+=1.0f;
      if (level.foregrid[y+3][x]>=168 && level.foregrid[y+3][x]<172)
        scale+=1.0f;
      */

      scale=scale*0.5f*block[blocknum].density/particle[count].mass;
      if (scale>6.0f)
        scale=6.0f;
      if (level.gametype!=16)
        particle[count].velocity[1]+=particle[count].gravity*scale;
      }
    else
      {
      if (particle[count].texturenum==366)
      if (particle[count].timetolive>5)
        particle[count].timetolive=5;
      }
    if (block[blocknum].drag!=0.0f)
      scalevector(particle[count].velocity,particle[count].velocity,(1.0f-block[blocknum].drag));

    copyvector(particle[count].prevvelocity,particle[count].velocity);
    }

  for (count=0;count<numofparticles;count++)
    {
    copyvector(particle[count].prevposition,particle[count].position);
    addvectors(particle[count].position,particle[count].position,particle[count].velocity);
    }
  /*
  for (count=0;count<numofparticles;count++)
    {
    if (particle[count].levelcollision)
      particlecollisionlevel(count);
    }
  */
  }

void particletimetolive(void)
  {
  int count;

  count=0;
  while (count<numofparticles)
    {
    if (particle[count].timetolive<10000)
      particle[count].timetolive--;
    while (count<numofparticles && particle[count].timetolive<0)
      {
      deleteparticle(count);

      if (particle[count].timetolive<10000)
        particle[count].timetolive--;
      }
    count++;
    }
  }

void createparticle(int type,float *position,float *velocity,float mass,int objectnum,int timetolive)
  {
  float scale;

  if (numofparticles>10000)
    return;

  memset(&particle[numofparticles],0,sizeof(particle[numofparticles]));

  particle[numofparticles].type=type;
  memcpy(particle[numofparticles].position,position,12);
  memcpy(particle[numofparticles].prevposition,position,12);
  if (velocity!=NULL)
    memcpy(particle[numofparticles].velocity,velocity,12);
  else
    memset(particle[numofparticles].velocity,0,12);
  memcpy(particle[numofparticles].prevvelocity,particle[numofparticles].velocity,12);
  if (mass>0.0f)
    particle[numofparticles].mass=mass;
  else
    particle[numofparticles].mass=0.001f;

  particle[numofparticles].numofbonds=0;
  particle[numofparticles].objectnum=objectnum;
  particle[numofparticles].timetolive=timetolive;

  particle[numofparticles].drag=particletype[type].drag;
  particle[numofparticles].gravity=particletype[type].gravity;
  particle[numofparticles].elasticity=particletype[type].elasticity;
  particle[numofparticles].friction=particletype[type].friction;
  particle[numofparticles].levelcollision=particletype[type].levelcollision;
  particle[numofparticles].objectcollision=particletype[type].objectcollision;
  particle[numofparticles].rendertype=particletype[type].rendertype;

  numofparticles++;
  }

void deleteparticle(int particlenum)
  {
  int count,count2;

  if (particlenum>=numofparticles)
    return;

  numofparticles--;

  count=0;
  while (count<numofbonds)
    {
    while (count<numofbonds && (bond[count].part1==particlenum || bond[count].part2==particlenum))
      deletebond(count);
    count++;
    }
  count=0;
  while (count<numofropes)
    {
    while (count<numofropes && (rope[count].part1==particlenum || rope[count].part2==particlenum))
      deleterope(count);
    count++;
    }

  for (count=0;count<physicstemp.numofbonds;count++)
  if (physicstemp.bond[count].type==5)
    {
    if (physicstemp.bond[count].part1==particlenum)
      {
      physicstemp.bond[count].type=-1;
      object[physicstemp.bond[count].objectnum[0]].particlestick[physicstemp.bond[count].part4]=0;
      }
    if (physicstemp.bond[count].part2==particlenum)
      {
      physicstemp.bond[count].type=-1;
      object[physicstemp.bond[count].objectnum[0]].particlestick[physicstemp.bond[count].part4]=0;
      }
    if (physicstemp.bond[count].part3==particlenum)
      {
      physicstemp.bond[count].type=-1;
      object[physicstemp.bond[count].objectnum[0]].particlestick[physicstemp.bond[count].part4]=0;
      }
    }

  if (particlenum==numofparticles)
    return;

  memcpy(&particle[particlenum],&particle[numofparticles],sizeof(particle[0]));

  for (count=0;count<numofobjects;count++)
  for (count2=0;count2<object[count].numofparticles;count2++)
  if (object[count].particle[count2]==numofparticles)
    object[count].particle[count2]=particlenum;

  if (game.godparticle==numofparticles)
    game.godparticle=particlenum;

  for (count=0;count<numofbonds;count++)
    {
    if (bond[count].part1==numofparticles)
      bond[count].part1=particlenum;
    if (bond[count].part2==numofparticles)
      bond[count].part2=particlenum;
    }
  for (count=0;count<numofropes;count++)
    {
    if (rope[count].part1==numofparticles)
      rope[count].part1=particlenum;
    if (rope[count].part2==numofparticles)
      rope[count].part2=particlenum;
    }

  for (count=0;count<physicstemp.numofbonds;count++)
  if (physicstemp.bond[count].type==5)
    {
    if (physicstemp.bond[count].part1==numofparticles)
      physicstemp.bond[count].part1=particlenum;
    if (physicstemp.bond[count].part2==numofparticles)
      physicstemp.bond[count].part2=particlenum;
    if (physicstemp.bond[count].part3==numofparticles)
      physicstemp.bond[count].part3=particlenum;
    }
  }

void applyforceparticle(int particlenum,float force[3])
  {
  scaleaddvectors(particle[particlenum].velocity,particle[particlenum].velocity,force,1.0f/particle[particlenum].mass);
  }

void getforceparticle(int particlenum,float force[3])
  {
  scalevector(force,particle[particlenum].prevvelocity,particle[particlenum].mass);
  }


