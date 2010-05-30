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

int lineintersectplane(float *intersectpoint,float *normal,float *scale,float *startpoint,float *endpoint,float *point)
  {
  float vec[3],vec2[3],vec3[3];

  subtractvectors(vec,endpoint,point);
  if (dotproduct(vec,normal)>0.0f)
    return(0);

  subtractvectors(vec,startpoint,point);
  if (dotproduct(vec,normal)<0.0f)
    return(0);

  subtractvectors(vec,point,startpoint);
  *scale=dotproduct(vec,normal);
  subtractvectors(vec2,endpoint,startpoint);
  *scale/=dotproduct(vec2,normal);

  scaleaddvectors(intersectpoint,startpoint,vec2,*scale);

  return(1);
  }

int lineintersecttriangle(float *intersectpoint,float *normal,float *scale,float *startpoint,float *endpoint,float *vertex1,float *vertex2,float *vertex3)
  {
  float vec[3],vec2[3],vec3[3];

  subtractvectors(vec,endpoint,vertex1);
  if (dotproduct(vec,normal)>0.0f)
    return(0);

  subtractvectors(vec,startpoint,vertex1);
  if (dotproduct(vec,normal)<0.0f)
    return(0);

  subtractvectors(vec,vertex1,startpoint);
  *scale=dotproduct(vec,normal);
  subtractvectors(vec2,endpoint,startpoint);
  *scale/=dotproduct(vec2,normal);

  scaleaddvectors(intersectpoint,startpoint,vec2,*scale);

  subtractvectors(vec,vertex2,vertex1);
  subtractvectors(vec2,intersectpoint,vertex1);
  crossproduct(vec3,vec,vec2);
  if (dotproduct(vec3,normal)<0.0f)
    return(0);

  subtractvectors(vec,vertex3,vertex2);
  subtractvectors(vec2,intersectpoint,vertex2);
  crossproduct(vec3,vec,vec2);
  if (dotproduct(vec3,normal)<0.0f)
    return(0);

  subtractvectors(vec,vertex1,vertex3);
  subtractvectors(vec2,intersectpoint,vertex3);
  crossproduct(vec3,vec,vec2);
  if (dotproduct(vec3,normal)<0.0f)
    return(0);

  return(1);
  }

int pointintersectline(float *point,float *vertex1,float *vertex2,float bias)
  {
  float vec[3],vec2[3];
  float normal[3];
  float scale;

  subtractvectors(normal,vertex2,vertex1);
  normalizevector(normal,normal);
  subtractvectors(vec,point,vertex1);
  scale=dotproduct(normal,vec);

  scalevector(vec2,normal,scale);
  subtractvectors(vec,vec,vec2);
  scale=vectorlength(vec);
  if (scale>bias)
    return(0);

  subtractvectors(vec,point,vertex1);
  subtractvectors(vec2,vertex2,vertex1);
  if (dotproduct(vec,vec2)<0.0f)
    return(0);

  subtractvectors(vec,point,vertex2);
  subtractvectors(vec2,vertex1,vertex2);
  if (dotproduct(vec,vec2)<0.0f)
    return(0);

  return(1);
  }

int lineintersectline(float *intersectpoint,float *normal,float *scale,float *startpoint,float *endpoint,float *vertex1,float *vertex2)
  {
  float vec[3],vec2[3];
  float dot1,dot2;

  normal[0]=vertex1[1]-vertex2[1];
  normal[1]=vertex2[0]-vertex1[0];
  normal[2]=0.0f;

  vec[0]=startpoint[0]-vertex1[0];
  vec[1]=startpoint[1]-vertex1[1];
  vec[2]=0.0f;

  vec2[0]=endpoint[0]-vertex1[0];
  vec2[1]=endpoint[1]-vertex1[1];
  vec2[2]=0.0f;

  dot1=dotproduct(normal,vec);
  dot2=dotproduct(normal,vec2);
  if (dot1>0.0f)
  if (dot2>0.0f)
    return(0);

  if (dot1<0.0f)
  if (dot2<0.0f)
    return(0);

  normalizevector(normal,normal);

  if (dot1<0.0f)
    {
    normal[0]=-normal[0];
    normal[1]=-normal[1];
    }

  vec[0]=vertex1[0]-startpoint[0];
  vec[1]=vertex1[1]-startpoint[1];
  vec[2]=0.0f;
  *scale=dotproduct(vec,normal);
  vec[0]=endpoint[0]-startpoint[0];
  vec[1]=endpoint[1]-startpoint[1];
  vec[2]=0.0f;
  *scale/=dotproduct(vec,normal);

  scaleaddvectors(intersectpoint,startpoint,vec,*scale);

  vec[0]=intersectpoint[0]-vertex1[0];
  vec[1]=intersectpoint[1]-vertex1[1];
  vec[2]=0.0f;

  vec2[0]=vertex2[0]-vertex1[0];
  vec2[1]=vertex2[1]-vertex1[1];
  vec2[2]=0.0f;

  if (dotproduct(vec,vec2)<0.0f)
    return(0);

  vec[0]=intersectpoint[0]-vertex2[0];
  vec[1]=intersectpoint[1]-vertex2[1];
  vec[2]=0.0f;

  vec2[0]=vertex1[0]-vertex2[0];
  vec2[1]=vertex1[1]-vertex2[1];
  vec2[2]=0.0f;

  if (dotproduct(vec,vec2)<0.0f)
    return(0);

  return(1);
  }

float intersectdistance(float *point,float *startpoint,float *endpoint,float *normal)
  {
  float scale;
  float vec[3];

  subtractvectors(vec,point,startpoint);
  scale=dotproduct(vec,normal);
  subtractvectors(vec,endpoint,startpoint);
  scale/=dotproduct(vec,normal);

  return(scale);
  }

void generatepolygonnormal(float *normal,float *vertex1,float *vertex2,float *vertex3)
  {
  float vec[3],vec2[3];

  subtractvectors(vec,vertex2,vertex1);
  subtractvectors(vec2,vertex3,vertex1);
  crossproduct(normal,vec,vec2);

  normalizevector(normal,normal);
  }

