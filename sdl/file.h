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

int comparestrings(const void *arg1,const void *arg2);
int checkfilespec(char *filespec,char *filename);
void listfiles(char *filespec,char filelist[1024][32],int directories);
size_t (*fread2)(void *,size_t,size_t,FILE *);
size_t (*fwrite2)(const void *,size_t,size_t,FILE *);
size_t freadswap(void *ptr,size_t psize,size_t pnum,FILE *pfp);
size_t fwriteswap(const void *ptr,size_t psize,size_t pnum,FILE *pfp);
