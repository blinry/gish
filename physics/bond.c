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

void bondsimulation(void)
  {
  int count,count2;
  int part1,part2;
  float vec[3];
  float bondnormal[3];
  float veclength;
  float force[2];

  for (count=0;count<32;count++)
    {
    for (count2=0;count2<numofparticles;count2++)
      copyvector(particle[count2].prevvelocity,particle[count2].velocity);

    for (count2=0;count2<numofbonds;count2++)
    if ((count&bond[count2].cycles)==0)
      {
      part1=bond[count2].part1;
      part2=bond[count2].part2;
  
      subtractvectors(bondnormal,particle[part2].position,particle[part1].position);
      veclength=vectorlength(bondnormal)-bond[count2].length;
      normalizevector(bondnormal,bondnormal);

      zerovector(vec);
      scaleaddvectors(vec,vec,particle[part2].prevvelocity,1.0f);
      scaleaddvectors(vec,vec,particle[part1].prevvelocity,-1.0f);

      veclength+=dotproduct(vec,bondnormal);
      if (bondtype[bond[count2].type].compression==0.0f)
        if (veclength<0.0f)
          veclength=0.0f;

      veclength*=bond[count2].elasticity;

      veclength/=(particle[part1].mass+particle[part2].mass);

      force[0]=veclength*particle[part2].mass;
      force[1]=veclength*particle[part1].mass;

      scaleaddvectors(particle[part1].velocity,particle[part1].velocity,bondnormal,force[0]);
      scaleaddvectors(particle[part2].velocity,particle[part2].velocity,bondnormal,-force[1]);
      }
    }
  }

void checkbonds(void)
  {
  int count,count2;
  int numofbondstemp;
  int part1,part2;
  float vec[3],vec2[3];
  float veclength;
  float scale;

  for (count=0;count<numofbonds;count++)
  if (bond[count].type==4 || bond[count].type==6 || bond[count].type==16)
  if (bond[count].timetolive!=-1)
    {
    part1=bond[count].part1;
    part2=bond[count].part2;

    subtractvectors(vec,particle[part2].position,particle[part1].position);

    scaleaddvectors(vec,vec,particle[part2].velocity,1.0f);
    scaleaddvectors(vec,vec,particle[part1].velocity,-1.0f);

    veclength=vectorlength(vec);

    if (bondtype[bond[count].type].compression!=0.0f)
    if (veclength<bond[count].length*bond[count].compression)
      {
      bond[count].timetolive=-1;
      /*
      if (bond[count].type==6)
        {
        for (count2=0;count2<numofbonds;count2++)
        if (bond[count2].type==6)
          if (bond[count2].objectnum==bond[count].objectnum)
            bond[count2].timetolive=-1;
        }
      */
      }
    if (veclength>bond[count].length*bond[count].tension)
      {
      bond[count].timetolive=-1;
      /*
      if (bond[count].type==6)
        {
        for (count2=0;count2<numofbonds;count2++)
        if (bond[count2].type==6)
          if (bond[count2].objectnum==bond[count].objectnum)
            bond[count2].timetolive=-1;
        }
      */
      }
    }

  count=0;
  while (count<numofbonds)
    {
    while (count<numofbonds && bond[count].timetolive==-1)
      deletebond(count);
    count++;
    }
  }

void createbond(int part1,int part2,int type,int objectnum)
  {
  int count;
  float vec[3];
  float length;

  if (part1>=numofparticles)
    return;
  if (part2>=numofparticles)
    return;

  for (count=0;count<numofbonds;count++)
    {
    if (bond[count].part1==part1 && bond[count].part2==part2)
      return;
    if (bond[count].part1==part2 && bond[count].part2==part1)
      return;
    }

  subtractvectors(vec,particle[part1].position,particle[part2].position);
  length=vectorlength(vec);
  if (length==0.0f)
    return;

  memset(&bond[numofbonds],0,sizeof(bond[numofbonds]));

  bond[numofbonds].part1=part1;
  bond[numofbonds].part2=part2;
  bond[numofbonds].type=type;
  bond[numofbonds].timetolive=10000;
  bond[numofbonds].length=length;
  bond[numofbonds].maxlength=length;

  bond[numofbonds].elasticity=bondtype[type].elasticity;
  bond[numofbonds].cycles=bondtype[type].cycles;
  bond[numofbonds].compression=bondtype[type].compression;
  bond[numofbonds].tension=bondtype[type].tension;

  bond[numofbonds].objectnum=objectnum;

  numofbonds++;
  }

void deletebond(int bondnum)
  {
  int count;

  if (bondnum<0)
    return;
  if (bondnum>=numofbonds)
    return;

  if (bond[bondnum].type==4)
    deleterope(bond[bondnum].objectnum);

  if (bond[bondnum].type==6)
  if (bond[bondnum].objectnum!=-1)
    if (object[bond[bondnum].objectnum].timetolive>45)
      object[bond[bondnum].objectnum].timetolive=45;

  numofbonds--;

  if (bondnum==numofbonds)
    return;

  memcpy(&bond[bondnum],&bond[numofbonds],sizeof(bond[0]));

  for (count=0;count<numofropes;count++)
  if (rope[count].type>=5 && rope[count].type<9)
  if (rope[count].bondnum==numofbonds)
    rope[count].bondnum=bondnum;
  }

