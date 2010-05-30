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

void createsprite(int points,float position[3])
  {
  sprite[numofsprites].type=1;
  sprite[numofsprites].timetolive=75;

  sprintf(sprite[numofsprites].text,"%u",points);
  copyvector(sprite[numofsprites].position,position);
  sprite[numofsprites].red=1.0f;
  sprite[numofsprites].green=1.0f;
  sprite[numofsprites].blue=1.0f;
  sprite[numofsprites].alpha=1.0f;
  sprite[numofsprites].size=12;
  numofsprites++;
  }

void spritetimetolive(void)
  {
  int count;

  count=0;
  while (count<numofsprites)
    {
    if (sprite[count].timetolive<10000)
      sprite[count].timetolive--;
    while (count<numofsprites && sprite[count].timetolive<0)
      {
      deletesprite(count);

      if (sprite[count].timetolive<10000)
        sprite[count].timetolive--;
      }
    count++;
    }
  }

void deletesprite(int spritenum)
  {
  if (spritenum<0)
    return;
  if (spritenum>=numofsprites)
    return;

  numofsprites--;

  if (spritenum==numofsprites)
    return;

  memcpy(&sprite[spritenum],&sprite[numofsprites],sizeof(sprite[0]));
  }

void spritesimulation(void)
  {
  int count;
  float angle;

  for (count=0;count<numofsprites;count++)
    {
    angle=(float)(sprite[count].timetolive&31)*2.0f*pi/31.0f;
    angle=sin(angle)*0.25f;

    if (sprite[count].timetolive<50)
      sprite[count].alpha=(float)sprite[count].timetolive/50.0f;
    sprite[count].position[1]+=0.01f;

    sprite[count].red=0.75f+angle;
    sprite[count].green=0.75f+angle;
    sprite[count].blue=0.75f+angle;
    }
  }
