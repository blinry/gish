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

void checkbigendian(void)
  {
  unsigned int x;
  char *c;

  x=0x12345678;
  c=(char *)&x;
  if (*c==0x12)
    bigendian=1;
  else
    bigendian=0;

  if (bigendian)
    {
    fread2=freadswap;
    fwrite2=fwriteswap;
    }
  else
    {
    fread2=fread;
    fwrite2=fwrite;
    }
  }
