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

void objectsimulation(void)
  {
  }

int lineintersectobject(float *intersectpoint,float *normal,float *scale,float *startpoint,float *endpoint,int objectnum,int *particlelist)
  {
  int count;
  int particlelisttemp[2];
  float intersectpointtemp[3];
  float normaltemp[3];
  float scaletemp;

  if (fabs(startpoint[0]-object[objectnum].position[0])>10.0f)
    return(0);
  if (fabs(startpoint[1]-object[objectnum].position[1])>10.0f)
    return(0);

  *scale=1.0f;
  for (count=0;count<object[objectnum].numofcdlines;count++)
    {
    particlelisttemp[0]=object[objectnum].cdline[count][0];
    particlelisttemp[1]=object[objectnum].cdline[count][1];

    if (lineintersectline2(intersectpointtemp,normaltemp,&scaletemp,startpoint,endpoint,particle[object[objectnum].particle[particlelisttemp[0]]].position,particle[object[objectnum].particle[particlelisttemp[1]]].position))
      if (scaletemp<*scale)
        {
        *scale=scaletemp;
        particlelist[0]=particlelisttemp[0];
        particlelist[1]=particlelisttemp[1];
        copyvector(normal,normaltemp);
        copyvector(intersectpoint,intersectpointtemp);
        }
    }
  if (*scale<1.0f)
    return(1);

  return(0);
  }

int lineintersectobject2(float *intersectpoint,float *normal,float *scale,float *startpoint,float *endpoint,int objectnum,int *particlelist)
  {
  int count;
  int particlelisttemp[2];
  float intersectpointtemp[3];
  float normaltemp[3];
  float scaletemp;

  if (fabs(startpoint[0]-object[objectnum].position[0])>10.0f)
    return(0);
  if (fabs(startpoint[1]-object[objectnum].position[1])>10.0f)
    return(0);

  *scale=1.0f;
  for (count=0;count<object[objectnum].numofcdlines;count++)
    {
    particlelisttemp[0]=object[objectnum].cdline[count][0];
    particlelisttemp[1]=object[objectnum].cdline[count][1];

    if (lineintersectline3(intersectpointtemp,normaltemp,&scaletemp,startpoint,endpoint,particle[object[objectnum].particle[particlelisttemp[0]]].position,particle[object[objectnum].particle[particlelisttemp[1]]].position))
      if (scaletemp<*scale)
        {
        *scale=scaletemp;
        particlelist[0]=particlelisttemp[0];
        particlelist[1]=particlelisttemp[1];
        copyvector(normal,normaltemp);
        copyvector(intersectpoint,intersectpointtemp);
        }
    }
  if (*scale<1.0f)
    return(1);

  return(0);
  }

int pointintersectobject(float *intersectpoint,float *normal,float *scale,float *point,int objectnum,int objectnum2,int *particlelist)
  {
  int count;
  int particlelisttemp[2];
  float vec[3];
  float intersectpointtemp[3];
  float normaltemp[3];
  float scaletemp;
  float angle;

  *scale=0.0f;
  for (count=0;count<object[objectnum].numofcdlines;count++)
    {
    particlelisttemp[0]=object[objectnum].cdline[count][0];
    particlelisttemp[1]=object[objectnum].cdline[count][1];

    normaltemp[0]=particle[object[objectnum].particle[particlelisttemp[0]]].position[1]-particle[object[objectnum].particle[particlelisttemp[1]]].position[1];
    normaltemp[1]=particle[object[objectnum].particle[particlelisttemp[1]]].position[0]-particle[object[objectnum].particle[particlelisttemp[0]]].position[0];
    normaltemp[2]=0.0f;
    normalizevector(normaltemp,normaltemp);

    scaleaddvectors(vec,point,normaltemp,0.5f);
    if (object[objectnum].type==10)
      scaleaddvectors(vec,point,normaltemp,0.25f);
    if (object[objectnum].type==2 && object[objectnum].size[0]<=0.5f)
      scaleaddvectors(vec,point,normaltemp,0.25f);
    if (object[objectnum2].type==2 && object[objectnum2].size[0]<=0.5f)
      scaleaddvectors(vec,point,normaltemp,0.25f);

    if (lineintersectline2(intersectpointtemp,normaltemp,&scaletemp,vec,point,particle[object[objectnum].particle[particlelisttemp[0]]].position,particle[object[objectnum].particle[particlelisttemp[1]]].position))
      {
      subtractvectors(vec,intersectpointtemp,object[objectnum2].position);
      normalizevector(vec,vec);
      if (object[objectnum2].type==1)
        angle=0.707f;
      else
        angle=0.0f;

      if (object[objectnum].type==2 && object[objectnum].size[0]<=0.5f)
        angle=0.0f;

      if (dotproduct(vec,normaltemp)<angle)
      if (scaletemp>*scale)
        {
        *scale=scaletemp;
        particlelist[0]=particlelisttemp[0];
        particlelist[1]=particlelisttemp[1];
        copyvector(normal,normaltemp);
        copyvector(intersectpoint,intersectpointtemp);
        }
      }
    }

  if (*scale>0.0f)
    return(1);

  return(0);
  }
