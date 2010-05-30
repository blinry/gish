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

void createboss(int type,float position[3])
  {
  memset(&boss[numofbosses],0,sizeof(boss[0]));

  boss[numofbosses].type=type;
  boss[numofbosses].timetolive=10000;
  copyvector(boss[numofbosses].position,position);
  boss[numofbosses].animationnum=14;
  boss[numofbosses].size[0]=3.0f;
  boss[numofbosses].size[1]=3.0f;

  numofbosses++;
  }

void bosssimulation(void)
  {
  int count,count2;
  float vec[3];

  for (count=0;count<numofbosses;count++)
    {
    if (boss[count].timetolive>100)
      {
      subtractvectors(vec,object[0].position,boss[count].position);
      if (boss[count].animationtype!=2)
      if (vectorlength(vec)<3.0f)
        {
        boss[count].animationtype=2;
        boss[count].frame=0;
        boss[count].framedelay=0.0f;
        }
      if (boss[count].animationtype==2)
      if (vectorlength(vec)>=3.0f)
        {
        boss[count].animationtype=1;
        boss[count].frame=0;
        boss[count].framedelay=0.0f;
        }

      if (vectorlength(vec)>2.5f)
        scaleaddvectors(boss[count].velocity,boss[count].velocity,vec,0.003f);
      scalevector(boss[count].velocity,boss[count].velocity,0.75f);
      addvectors(boss[count].position,boss[count].position,boss[count].velocity);

      if (boss[count].animationtype!=2)
        {
        boss[count].framedelay+=0.1f;
        if (boss[count].framedelay>=1.0f)
          {
          boss[count].framedelay=0.0f;
          boss[count].frame++;
          if (boss[count].frame>=animation[boss[count].animationnum].walk[1])
            boss[count].frame=0;
          }
        boss[count].texturenum=animation[boss[count].animationnum].walk[0]+boss[count].frame;
        }
      else
        {
        boss[count].framedelay+=0.15f;
        if (boss[count].framedelay>=1.0f)
          {
          boss[count].framedelay=0.0f;
          boss[count].frame++;
          if (boss[count].frame>=animation[boss[count].animationnum].attack[1])
            boss[count].frame=0;
          }
        boss[count].texturenum=animation[boss[count].animationnum].attack[0]+boss[count].frame;

        if (boss[count].frame==3)
          object[0].hitpoints-=10;
        }

      if (boss[count].velocity[0]>0.0f)
        boss[count].direction=0;
      else
        boss[count].direction=1;
  
      if (frame.numoflights>1)
      if (boss[count].timetolive>150)
        boss[count].timetolive=150;
      }
    if (boss[count].timetolive<45)
      {
      boss[count].animationtype=3;
      boss[count].frame=0;
      boss[count].framedelay=0.0f;
      boss[count].texturenum=animation[boss[count].animationnum].die[0]+8-boss[count].timetolive/5;
      }
    }
  }

void bosstimetolive(void)
  {
  int count;

  count=0;
  while (count<numofbosses)
    {
    if (boss[count].timetolive<10000)
      boss[count].timetolive--;
    while (count<numofbosses && boss[count].timetolive<0)
      {
      deleteboss(count);

      if (boss[count].timetolive<10000)
        boss[count].timetolive--;
      }
    count++;
    }
  }

void deleteboss(int bossnum)
  {
  if (bossnum<0)
    return;
  if (bossnum>=numofbosses)
    return;

  numofbosses--;

  if (bossnum==numofbosses)
    return;

  memcpy(&boss[bossnum],&boss[numofbosses],sizeof(boss[0]));
  }

