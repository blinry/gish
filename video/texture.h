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

void loadtexturetga(int texturenum,char *filename,int mipmap,int wraps,int wrapt,int magfilter,int minfilter);
void loadtexturetganodir(int texturenum,char *filename,int mipmap,int wraps,int wrapt,int magfilter,int minfilter);
void loadtexturetgapartial(int texturenum,char *filename,int startx,int starty,int sizex,int sizey);
void generatemipmap(int texturenum);
void setuptexture(int texturenum);

char lasttextureloaded[32];

struct
  {
  int sizex;
  int sizey;
  int mipmaplevels;
  int format;
  int wraps;
  int wrapt;
  int magfilter;
  int minfilter;
  int isalpha;
  int alphamap;
  int normalmap;
  int glossmap;
  int glname;
  unsigned int *rgba[16];
  int glnamenormal;
  unsigned int *normal[16];
  int glnamegloss;
  unsigned char *gloss[16];
  } texture[2048];

struct
  {
  unsigned char imagetypecode;
  short int imagewidth;
  short int imageheight;
  unsigned char pixeldepth;
  unsigned int imagedata[1024*1024];
  } tgaheader;
