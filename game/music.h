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

void checkmusic(void);
void loadoggs(void);
size_t vorbisread(void *ptr,size_t bytesize,size_t sizetoread,void *datasource);
int vorbisseek(void *datasource,ogg_int64_t offset,int whence);
int vorbisclose(void *datasource);
long vorbistell(void *datasource);

typedef struct OGGMEMORYFILE
  {
  char *data;
  int datasize;
  int dataread;
  };

struct OGGMEMORYFILE oggmemoryfile[16];

ov_callbacks vorbiscallbacks;
