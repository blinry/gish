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

#define TEXT_CENTER 0x10000
#define TEXT_END 0x20000

void drawtext(unsigned char *textstring,int textposx,int textposy,int textsize,float red,float green,float blue,float alpha,...);
void setuptextdisplay(void);
void convertscreenvertex(float vec[3],int resolutionx,int resolutiony);
void drawbackground(int texturenum,int x,int y,int sizex,int sizey,int resolutionx,int resolutiony);
void drawmousecursor(int texturenum,int x,int y,int textsize,float red,float green,float blue,float alpha);

unsigned char textstring2[1024];
unsigned char textstring3[1024];

struct
  {
  int sizex;
  int sizey;
  int texturenum;
  int cursornum;
  } font;
