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

void setupperspectiveviewport(int viewportx,int viewporty,int viewportwidth,int viewportheight,float nearplane,float farplane);
void setuporthoviewport(int viewportx,int viewporty,int viewportwidth,int viewportheight,float width,float height,float length);
void setupviewpoint(float *position,float orientation[3][3]);
void setupobjectrender(float *position,float orientation[3][3]);
void screenshot(void);
void setupglext(void);

int screenshotbuffer[1280*960];
