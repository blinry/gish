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

INLINE float dotproduct(float *vec,float *vec2)
  {
  return(vec[0]*vec2[0]+vec[1]*vec2[1]+vec[2]*vec2[2]);
  }

INLINE void crossproduct(float *result,float *vec,float *vec2)
  {
  result[0]=vec2[1]*vec[2]-vec2[2]*vec[1];
  result[1]=vec2[2]*vec[0]-vec2[0]*vec[2];
  result[2]=vec2[0]*vec[1]-vec2[1]*vec[0];
  }

INLINE float vectorlength(float *vec)
  {
  return(sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]));
  }

INLINE void normalizevector(float *result,float *vec)
  {
  float vectorlengthvalue;

  vectorlengthvalue=vectorlength(vec);
  if (vectorlengthvalue!=0.0f)
    {
    vectorlengthvalue=1.0f/vectorlengthvalue;
    result[0]=vec[0]*vectorlengthvalue;
    result[1]=vec[1]*vectorlengthvalue;
    result[2]=vec[2]*vectorlengthvalue;
    }
  else
    {
    result[0]=0.0f;
    result[1]=0.0f;
    result[2]=0.0f;
    }
  }

INLINE void copyvector(float *result,float *vec)
  {
  memcpy(result,vec,12);
  }

INLINE void negvector(float *result,float *vec)
  {
  result[0]=-vec[0];
  result[1]=-vec[1];
  result[2]=-vec[2];
  }

INLINE void zerovector(float *result)
  {
  memset(result,0,12);
  }

INLINE void addvectors(float *result,float *vec,float *vec2)
  {
  result[0]=vec[0]+vec2[0];
  result[1]=vec[1]+vec2[1];
  result[2]=vec[2]+vec2[2];
  }

INLINE void subtractvectors(float *result,float *vec,float *vec2)
  {
  result[0]=vec[0]-vec2[0];
  result[1]=vec[1]-vec2[1];
  result[2]=vec[2]-vec2[2];
  }

INLINE void scalevector(float *result,float *vec,float scale)
  {
  result[0]=vec[0]*scale;
  result[1]=vec[1]*scale;
  result[2]=vec[2]*scale;
  }

INLINE void scaleaddvectors(float *result,float *vec,float *vec2,float scale)
  {
  result[0]=vec[0]+vec2[0]*scale;
  result[1]=vec[1]+vec2[1]*scale;
  result[2]=vec[2]+vec2[2]*scale;
  }

INLINE void addvectors2(float *result,float *vec,float *vec2)
  {
  result[0]=vec[0]+vec2[0];
  result[1]=vec[1]+vec2[1];
  }

INLINE void subtractvectors2(float *result,float *vec,float *vec2)
  {
  result[0]=vec[0]-vec2[0];
  result[1]=vec[1]-vec2[1];
  }

INLINE void scalevector2(float *result,float *vec,float scale)
  {
  result[0]=vec[0]*scale;
  result[1]=vec[1]*scale;
  }

INLINE void scaleaddvectors2(float *result,float *vec,float *vec2,float scale)
  {
  result[0]=vec[0]+vec2[0]*scale;
  result[1]=vec[1]+vec2[1]*scale;
  }

void resetorientation(float orientation[3][3])
  {
  orientation[0][0]=1.0f;
  orientation[0][1]=0.0f;
  orientation[0][2]=0.0f;
  orientation[1][0]=0.0f;
  orientation[1][1]=1.0f;
  orientation[1][2]=0.0f;
  orientation[2][0]=0.0f;
  orientation[2][1]=0.0f;
  orientation[2][2]=1.0f;
  }

void rotateorientation(float orientation[3][3],float *rotationvector,float rotationangle)
  {
  int count;
  float pointtemp[3],cosnormal[3],sinnormal[3];
  float axisnormal[3];
  float vectorlengthvalue,dotproductvalue;

  normalizevector(axisnormal,rotationvector);

  if (fabs(rotationangle)<.003f)
    return;

  for (count=0;count<3;count++)
    {
    copyvector(pointtemp,orientation[count]);

    crossproduct(sinnormal,axisnormal,pointtemp);

    normalizevector(sinnormal,sinnormal);

    crossproduct(cosnormal,sinnormal,axisnormal);

    normalizevector(cosnormal,cosnormal);

    dotproductvalue=dotproduct(axisnormal,pointtemp);
    pointtemp[0]-=axisnormal[0]*dotproductvalue;
    pointtemp[1]-=axisnormal[1]*dotproductvalue;
    pointtemp[2]-=axisnormal[2]*dotproductvalue;
    vectorlengthvalue=vectorlength(pointtemp);

    orientation[count][0]=axisnormal[0]*dotproductvalue+cosnormal[0]*cos(rotationangle)*vectorlengthvalue+sinnormal[0]*sin(rotationangle)*vectorlengthvalue;
    orientation[count][1]=axisnormal[1]*dotproductvalue+cosnormal[1]*cos(rotationangle)*vectorlengthvalue+sinnormal[1]*sin(rotationangle)*vectorlengthvalue;
    orientation[count][2]=axisnormal[2]*dotproductvalue+cosnormal[2]*cos(rotationangle)*vectorlengthvalue+sinnormal[2]*sin(rotationangle)*vectorlengthvalue;

    normalizevector(orientation[count],orientation[count]);
    }
  }
