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

INLINE float dotproduct(float *vec1,float *vec2);
INLINE void crossproduct(float *result,float *vec1,float *vec2);
INLINE float vectorlength(float *vec1);
INLINE void normalizevector(float *result,float *vec1);
INLINE void copyvector(float *result,float *vec1);
INLINE void negvector(float *result,float *vec);
INLINE void zerovector(float *result);
INLINE void addvectors(float *result,float *vec,float *vec2);
INLINE void subtractvectors(float *result,float *vec,float *vec2);
INLINE void scalevector(float *result,float *vec,float scale);
INLINE void scaleaddvectors(float *result,float *vec,float *vec2,float scale);
INLINE void addvectors2(float *result,float *vec,float *vec2);
INLINE void subtractvectors2(float *result,float *vec,float *vec2);
INLINE void scalevector2(float *result,float *vec,float scale);
INLINE void scaleaddvectors2(float *result,float *vec,float *vec2,float scale);
void resetorientation(float orientation[3][3]);
void rotateorientation(float orientation[3][3],float *rotationvector,float rotationangle);

float xaxis[3]={ 1.0f,0.0f,0.0f };
float yaxis[3]={ 0.0f,1.0f,0.0f };
float zaxis[3]={ 0.0f,0.0f,1.0f };
