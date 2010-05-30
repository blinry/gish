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

void setuprenderobjects(void)
  {
  int count,count2;
  float vec[3],vec2[3];
  float intersectpoint[3];
  float normal[3];
  float angle;
  float scale;
  float w;

  numofobjectrenders=0;

  for (count=0;count<numofobjects;count++)
  if (object[count].texturenum!=0)
    {
    if (object[count].type==8)
      {
      subtractvectors(vec,view.position,object[count].position);
      if (fabs(vec[0])-object[count].radius<view.zoom)
      if (fabs(vec[1])-object[count].radius<view.zoom)
        {
        objectrender[numofobjectrenders].type=8;
        objectrender[numofobjectrenders].depth=-1.0f;
        if (object[count].texturenum==58)
          objectrender[numofobjectrenders].texturenum=256+object[count].texturenum+1+(game.framenum/7)%5;
        else
          objectrender[numofobjectrenders].texturenum=256+object[count].texturenum;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=0;
        objectrender[numofobjectrenders].alpha=1.0f;

        scale=0.35f;

        objectrender[numofobjectrenders].numofverts=4;
        for (count2=0;count2<4;count2++)
          {
          if (count2==0 || count2==3)
            vec[0]=object[count].position[0]-scale;
          else
            vec[0]=object[count].position[0]+scale;
          if (count2<2)
            vec[1]=object[count].position[1]+scale*2.0f;
          else
            vec[1]=object[count].position[1];
          vec[2]=0.0f;

          copyvector(objectrender[numofobjectrenders].vertex[count2],vec);
          if (count2==0 || count2==3)
            objectrender[numofobjectrenders].texcoord[count2][0]=0.0f;
          else
            objectrender[numofobjectrenders].texcoord[count2][0]=1.0f;
          if (count2<2)
            objectrender[numofobjectrenders].texcoord[count2][1]=0.0f;
          else
            objectrender[numofobjectrenders].texcoord[count2][1]=1.0f;
          }
        objectrender[numofobjectrenders].numoftris=2;
        objectrender[numofobjectrenders].tri[0][0]=0;
        objectrender[numofobjectrenders].tri[0][1]=1;
        objectrender[numofobjectrenders].tri[0][2]=2;
        objectrender[numofobjectrenders].tri[1][0]=0;
        objectrender[numofobjectrenders].tri[1][1]=2;
        objectrender[numofobjectrenders].tri[1][2]=3;

        numofobjectrenders++;

        objectrender[numofobjectrenders].type=8;
        objectrender[numofobjectrenders].depth=-1.0f;
        objectrender[numofobjectrenders].texturenum=256+object[count].texturenum;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=0;
        objectrender[numofobjectrenders].alpha=1.0f;

        objectrender[numofobjectrenders].numofverts=4;
        for (count2=0;count2<4;count2++)
          {
          if (count2==0 || count2==3)
            vec[0]=object[count].position[0]-scale;
          else
            vec[0]=object[count].position[0]+scale;
          if (count2<2)
            vec[1]=object[count].position[1];
          else
            vec[1]=object[count].position[1]-scale*2.0f;
          vec[2]=0.0f;

          copyvector(objectrender[numofobjectrenders].vertex[count2],vec);
          if (count2==0 || count2==3)
            objectrender[numofobjectrenders].texcoord[count2][0]=0.0f;
          else
            objectrender[numofobjectrenders].texcoord[count2][0]=1.0f;
          if (count2<2)
            objectrender[numofobjectrenders].texcoord[count2][1]=0.0f;
          else
            objectrender[numofobjectrenders].texcoord[count2][1]=1.0f;
          }
        objectrender[numofobjectrenders].numoftris=2;
        objectrender[numofobjectrenders].tri[0][0]=0;
        objectrender[numofobjectrenders].tri[0][1]=1;
        objectrender[numofobjectrenders].tri[0][2]=2;
        objectrender[numofobjectrenders].tri[1][0]=0;
        objectrender[numofobjectrenders].tri[1][1]=2;
        objectrender[numofobjectrenders].tri[1][2]=3;

        numofobjectrenders++;
        }
      }
    }

  for (count=0;count<numofobjects;count++)
  if (object[count].texturenum!=0)
    {
    if (object[count].type==10)
      {
      subtractvectors(vec,view.position,object[count].position);
      if (fabs(vec[0])-object[count].radius<view.zoom)
      if (fabs(vec[1])-object[count].radius<view.zoom)
        {
        objectrender[numofobjectrenders].type=2;
        objectrender[numofobjectrenders].depth=2.0f;
        objectrender[numofobjectrenders].texturenum=object[count].texturenum+256;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=setuprenderobjectlight(count);
        objectrender[numofobjectrenders].alpha=1.0f;

        objectrender[numofobjectrenders].numofverts=4;
        for (count2=0;count2<4;count2++)
          {
          copyvector(objectrender[numofobjectrenders].vertex[count2],particle[object[count].particle[count2]].position);
          objectrender[numofobjectrenders].texcoord[count2][0]=object[count].texcoord[count2][0];
          objectrender[numofobjectrenders].texcoord[count2][1]=object[count].texcoord[count2][1];
          }
        objectrender[numofobjectrenders].numoftris=2;
        objectrender[numofobjectrenders].tri[0][0]=0;
        objectrender[numofobjectrenders].tri[0][1]=1;
        objectrender[numofobjectrenders].tri[0][2]=2;
        objectrender[numofobjectrenders].tri[1][0]=0;
        objectrender[numofobjectrenders].tri[1][1]=2;
        objectrender[numofobjectrenders].tri[1][2]=3;

        objectrender[numofobjectrenders].numofedges=4;
        for (count2=0;count2<4;count2++)
          {
          normal[0]=-(particle[object[count].particle[((count2+1)&3)]].position[1]-particle[object[count].particle[count2]].position[1]);
          normal[1]=(particle[object[count].particle[((count2+1)&3)]].position[0]-particle[object[count].particle[count2]].position[0]);
          normal[2]=0.0f;
          normalizevector(normal,normal);
          if (object[count].rotate==3)
            negvector(normal,normal);
          copyvector(objectrender[numofobjectrenders].edgenormal[count2],normal);

          copyvector(objectrender[numofobjectrenders].edgevertex[count2][0],particle[object[count].particle[count2]].position);
          copyvector(objectrender[numofobjectrenders].edgevertex[count2][1],particle[object[count].particle[((count2+1)&3)]].position);
          copyvector(vec,particle[object[count].particle[((count2+1)&3)]].position);
          vec[0]-=normal[0]*0.125f;
          vec[1]-=normal[1]*0.125f;
          copyvector(objectrender[numofobjectrenders].edgevertex[count2][2],vec);
          copyvector(vec,particle[object[count].particle[count2]].position);
          vec[0]-=normal[0]*0.125f;
          vec[1]-=normal[1]*0.125f;
          copyvector(objectrender[numofobjectrenders].edgevertex[count2][3],vec);

          if (count2==0)
            {
            normal[0]=0.0f;
            normal[1]=0.125f;
            }
          if (count2==1)
            {
            normal[0]=-0.125f;
            normal[1]=0.0f;
            }
          if (count2==2)
            {
            normal[0]=0.0f;
            normal[1]=-0.125f;
            }
          if (count2==3)
            {
            normal[0]=0.125f;
            normal[1]=0.0f;
            }

          objectrender[numofobjectrenders].edgetexcoord[count2][0][0]=object[count].texcoord[count2][0];
          objectrender[numofobjectrenders].edgetexcoord[count2][0][1]=object[count].texcoord[count2][1];
          objectrender[numofobjectrenders].edgetexcoord[count2][1][0]=object[count].texcoord[((count2+1)&3)][0];
          objectrender[numofobjectrenders].edgetexcoord[count2][1][1]=object[count].texcoord[((count2+1)&3)][1];
          objectrender[numofobjectrenders].edgetexcoord[count2][2][0]=object[count].texcoord[((count2+1)&3)][0]+normal[0];
          objectrender[numofobjectrenders].edgetexcoord[count2][2][1]=object[count].texcoord[((count2+1)&3)][1]+normal[1];
          objectrender[numofobjectrenders].edgetexcoord[count2][3][0]=object[count].texcoord[count2][0]+normal[0];
          objectrender[numofobjectrenders].edgetexcoord[count2][3][1]=object[count].texcoord[count2][1]+normal[1];
          }

        numofobjectrenders++;
        }
      }
    }

  for (count=0;count<numofobjects;count++)
  if (object[count].texturenum!=0)
    {
    if (object[count].type==1)
      {
      subtractvectors(vec,view.position,object[count].position);
      if (fabs(vec[0])-object[count].radius<view.zoom)
      if (fabs(vec[1])-object[count].radius<view.zoom)
        {
        objectrender[numofobjectrenders].type=1;
        objectrender[numofobjectrenders].depth=0.0f;
        objectrender[numofobjectrenders].angle=object[count].angle;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=setuprenderobjectlight(count);
        objectrender[numofobjectrenders].alpha=1.0f;
        if (count==0)
          objectrender[numofobjectrenders].texturenum=370+object[count].frame;
        else if (count==1)
          objectrender[numofobjectrenders].texturenum=390+object[count].frame;
        else if (count==2)
          objectrender[numofobjectrenders].texturenum=410+object[count].frame;
        else
          objectrender[numofobjectrenders].texturenum=430+object[count].frame;

        objectrender[numofobjectrenders].numofverts=33;

        for (count2=0;count2<16;count2++)
          {
          if (!object[count].particlestick[count2])
            copyvector(objectrender[numofobjectrenders].vertex[count2*2+0],particle[object[count].particle[count2]].position);
          else
            copyvector(objectrender[numofobjectrenders].vertex[count2*2+0],object[count].particlestickposition[count2]);
          }
        for (count2=0;count2<16;count2++)
          {
          addvectors(vec,objectrender[numofobjectrenders].vertex[count2*2+0],objectrender[numofobjectrenders].vertex[((count2+1)&15)*2+0]);
          addvectors(vec2,objectrender[numofobjectrenders].vertex[((count2-1)&15)*2+0],objectrender[numofobjectrenders].vertex[((count2+2)&15)*2+0]);

          w=1.0f/16.0f;

          scalevector(vec,vec,0.5f+w);
          scalevector(vec2,vec2,w);
          subtractvectors(vec,vec,vec2);

          copyvector(objectrender[numofobjectrenders].vertex[count2*2+1],vec);
          }

        /*
        for (count2=0;count2<16;count2++)
          {
          if (!object[count].particlestick[count2])
            copyvector(objectrender[numofobjectrenders].vertex[count2*2+0],particle[object[count].particle[count2]].position);
          else
            copyvector(objectrender[numofobjectrenders].vertex[count2*2+0],object[count].particlestickposition[count2]);

          w=1.0f/16.0f;

          //addvectors(vec,particle[object[count].particle[((count2+0)&15)]].position,particle[object[count].particle[((count2+1)&15)]].position);
          //addvectors(vec2,particle[object[count].particle[((count2-1)&15)]].position,particle[object[count].particle[((count2+2)&15)]].position);
          if (!object[count].particlestick[((count2+0)&15)])
            copyvector(vec,particle[object[count].particle[((count2+0)&15)]].position);
          else
            copyvector(vec,object[count].particlestickposition[((count2+0)&15)]);
          if (!object[count].particlestick[((count2+1)&15)])
            addvectors(vec,vec,particle[object[count].particle[((count2+1)&15)]].position);
          else
            addvectors(vec,vec,object[count].particlestickposition[((count2+1)&15)]);

          if (!object[count].particlestick[((count2-1)&15)])
            copyvector(vec2,particle[object[count].particle[((count2-1)&15)]].position);
          else
            copyvector(vec2,object[count].particlestickposition[((count2-1)&15)]);
          if (!object[count].particlestick[((count2+2)&15)])
            addvectors(vec2,vec2,particle[object[count].particle[((count2+2)&15)]].position);
          else
            addvectors(vec2,vec2,object[count].particlestickposition[((count2+2)&15)]);

          scalevector(vec,vec,0.5f+w);
          scalevector(vec2,vec2,w);
          subtractvectors(vec,vec,vec2);

          copyvector(objectrender[numofobjectrenders].vertex[count2*2+1],vec);
          }
        */

        for (count2=0;count2<32;count2++)
          {
          vec[0]=objectrender[numofobjectrenders].vertex[((count2-1)&31)][1]-objectrender[numofobjectrenders].vertex[((count2+0)&31)][1];
          vec[1]=objectrender[numofobjectrenders].vertex[((count2+0)&31)][0]-objectrender[numofobjectrenders].vertex[((count2-1)&31)][0];
          vec[2]=0.0f;
          vec2[0]=objectrender[numofobjectrenders].vertex[((count2+0)&31)][1]-objectrender[numofobjectrenders].vertex[((count2+1)&31)][1];
          vec2[1]=objectrender[numofobjectrenders].vertex[((count2+1)&31)][0]-objectrender[numofobjectrenders].vertex[((count2+0)&31)][0];
          vec2[2]=0.0f;

          addvectors(vec,vec,vec2);
          normalizevector(vec,vec);

          objectrender[numofobjectrenders].texcoord[count2][0]=0.5f+vec[0]*0.5f;
          objectrender[numofobjectrenders].texcoord[count2][1]=0.5f+vec[1]*0.5f;
          }
        count2=32;
        copyvector(objectrender[numofobjectrenders].vertex[count2],object[count].position);
        objectrender[numofobjectrenders].texcoord[count2][0]=0.5f;
        objectrender[numofobjectrenders].texcoord[count2][1]=0.5f;

        numofobjectrenders++;
        }
      }
    }

  for (count=0;count<numofobjects;count++)
  if (object[count].texturenum!=0)
    {
    if (object[count].type==2 || object[count].type==20)
      {
      subtractvectors(vec,view.position,object[count].position);
      if (fabs(vec[0])-object[count].radius<view.zoom)
      if (fabs(vec[1])-object[count].radius<view.zoom)
        {
        objectrender[numofobjectrenders].type=2;
        objectrender[numofobjectrenders].depth=2.0f;
        objectrender[numofobjectrenders].texturenum=object[count].texturenum+256;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=setuprenderobjectlight(count);
        objectrender[numofobjectrenders].alpha=1.0f;
        if (object[count].timetolive<50)
          objectrender[numofobjectrenders].alpha=(float)object[count].timetolive/50.0f;

        objectrender[numofobjectrenders].numofverts=4;
        for (count2=0;count2<4;count2++)
          {
          copyvector(objectrender[numofobjectrenders].vertex[count2],particle[object[count].particle[count2]].position);
          objectrender[numofobjectrenders].texcoord[count2][0]=object[count].texcoord[count2][0];
          objectrender[numofobjectrenders].texcoord[count2][1]=object[count].texcoord[count2][1];
          }
        objectrender[numofobjectrenders].numoftris=2;
        objectrender[numofobjectrenders].tri[0][0]=0;
        objectrender[numofobjectrenders].tri[0][1]=1;
        objectrender[numofobjectrenders].tri[0][2]=2;
        objectrender[numofobjectrenders].tri[1][0]=0;
        objectrender[numofobjectrenders].tri[1][1]=2;
        objectrender[numofobjectrenders].tri[1][2]=3;

        objectrender[numofobjectrenders].numofedges=4;
        for (count2=0;count2<4;count2++)
          {
          normal[0]=-(particle[object[count].particle[((count2+1)&3)]].position[1]-particle[object[count].particle[count2]].position[1]);
          normal[1]=(particle[object[count].particle[((count2+1)&3)]].position[0]-particle[object[count].particle[count2]].position[0]);
          normal[2]=0.0f;
          normalizevector(normal,normal);
          copyvector(objectrender[numofobjectrenders].edgenormal[count2],normal);

          copyvector(objectrender[numofobjectrenders].edgevertex[count2][0],particle[object[count].particle[count2]].position);
          copyvector(objectrender[numofobjectrenders].edgevertex[count2][1],particle[object[count].particle[((count2+1)&3)]].position);
          copyvector(vec,particle[object[count].particle[((count2+1)&3)]].position);
          vec[0]-=normal[0]*0.125f;
          vec[1]-=normal[1]*0.125f;
          copyvector(objectrender[numofobjectrenders].edgevertex[count2][2],vec);
          copyvector(vec,particle[object[count].particle[count2]].position);
          vec[0]-=normal[0]*0.125f;
          vec[1]-=normal[1]*0.125f;
          copyvector(objectrender[numofobjectrenders].edgevertex[count2][3],vec);

          if (count2==0)
            {
            normal[0]=0.0f;
            normal[1]=0.125f;
            }
          if (count2==1)
            {
            normal[0]=-0.125f;
            normal[1]=0.0f;
            }
          if (count2==2)
            {
            normal[0]=0.0f;
            normal[1]=-0.125f;
            }
          if (count2==3)
            {
            normal[0]=0.125f;
            normal[1]=0.0f;
            }

          objectrender[numofobjectrenders].edgetexcoord[count2][0][0]=object[count].texcoord[count2][0];
          objectrender[numofobjectrenders].edgetexcoord[count2][0][1]=object[count].texcoord[count2][1];
          objectrender[numofobjectrenders].edgetexcoord[count2][1][0]=object[count].texcoord[((count2+1)&3)][0];
          objectrender[numofobjectrenders].edgetexcoord[count2][1][1]=object[count].texcoord[((count2+1)&3)][1];
          objectrender[numofobjectrenders].edgetexcoord[count2][2][0]=object[count].texcoord[((count2+1)&3)][0]+normal[0];
          objectrender[numofobjectrenders].edgetexcoord[count2][2][1]=object[count].texcoord[((count2+1)&3)][1]+normal[1];
          objectrender[numofobjectrenders].edgetexcoord[count2][3][0]=object[count].texcoord[count2][0]+normal[0];
          objectrender[numofobjectrenders].edgetexcoord[count2][3][1]=object[count].texcoord[count2][1]+normal[1];
          }

        numofobjectrenders++;
        }
      }
    }

  for (count=0;count<numofobjects;count++)
  if (object[count].texturenum!=0)
    {
    if (object[count].type==3)
      {
      subtractvectors(vec,view.position,object[count].position);
      if (fabs(vec[0])-object[count].radius<view.zoom)
      if (fabs(vec[1])-object[count].radius<view.zoom)
        {
        objectrender[numofobjectrenders].type=3;
        objectrender[numofobjectrenders].depth=1.0f;
        objectrender[numofobjectrenders].texturenum=object[count].texturenum+256;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=setuprenderobjectlight(count);
        objectrender[numofobjectrenders].alpha=1.0f;
        if (object[count].timetolive<50)
          objectrender[numofobjectrenders].alpha=(float)object[count].timetolive/50.0f;
  
        objectrender[numofobjectrenders].numofverts=17;
        for (count2=0;count2<16;count2++)
          {
          copyvector(objectrender[numofobjectrenders].vertex[count2],particle[object[count].particle[count2]].position);
          angle=(float)count2*pi/8.0f;
          objectrender[numofobjectrenders].texcoord[count2][0]=0.5f+cos(angle)*0.5f;
          objectrender[numofobjectrenders].texcoord[count2][1]=0.5f+sin(angle)*0.5f;
          }
        count2=16;
        copyvector(objectrender[numofobjectrenders].vertex[count2],object[count].position);
        objectrender[numofobjectrenders].texcoord[count2][0]=0.5f;
        objectrender[numofobjectrenders].texcoord[count2][1]=0.5f;

        objectrender[numofobjectrenders].numoftris=16;
        for (count2=0;count2<16;count2++)
          {
          objectrender[numofobjectrenders].tri[count2][0]=count2;
          objectrender[numofobjectrenders].tri[count2][1]=((count2+1)&15);
          objectrender[numofobjectrenders].tri[count2][2]=16;
          }

        numofobjectrenders++;
        }
      }
    }

  for (count=0;count<numofobjects;count++)
  if (object[count].texturenum!=0)
    {
    if (object[count].type==4)
      {
      subtractvectors(vec,view.position,object[count].position);
      if (fabs(vec[0])-object[count].radius<view.zoom)
      if (fabs(vec[1])-object[count].radius<view.zoom)
        {
        objectrender[numofobjectrenders].type=4;
        objectrender[numofobjectrenders].depth=1.0f;
        objectrender[numofobjectrenders].texturenum=object[count].texturenum;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=setuprenderobjectlight(count);
        objectrender[numofobjectrenders].alpha=1.0f;

        objectrender[numofobjectrenders].numofverts=4;
        for (count2=0;count2<4;count2++)
          {
          subtractvectors(vec,particle[object[count].particle[count2]].position,object[count].position);
          if (object[count].beasttype==12)
            {
            if (count2==0)
              {
              subtractvectors(vec,particle[object[count].particle[0]].position,particle[object[count].particle[3]].position);
              addvectors(vec,particle[object[count].particle[0]].position,vec);
              subtractvectors(vec,vec,object[count].position);
              }
            if (count2==1)
              {
              subtractvectors(vec,particle[object[count].particle[1]].position,particle[object[count].particle[2]].position);
              addvectors(vec,particle[object[count].particle[1]].position,vec);
              subtractvectors(vec,vec,object[count].position);
              }
            }
          scaleaddvectors(objectrender[numofobjectrenders].vertex[count2],object[count].position,vec,2.0f);
          if ((object[count].direction==0 && (count2==0 || count2==3)) || (object[count].direction==1 && (count2==1 || count2==2)))
            objectrender[numofobjectrenders].texcoord[count2][0]=0.0f;
          else
            objectrender[numofobjectrenders].texcoord[count2][0]=1.0f;
          if (count2<2)
            objectrender[numofobjectrenders].texcoord[count2][1]=0.0f;
          else
            objectrender[numofobjectrenders].texcoord[count2][1]=1.0f;
          }
        objectrender[numofobjectrenders].numoftris=2;
        objectrender[numofobjectrenders].tri[0][0]=0;
        objectrender[numofobjectrenders].tri[0][1]=1;
        objectrender[numofobjectrenders].tri[0][2]=2;
        objectrender[numofobjectrenders].tri[1][0]=0;
        objectrender[numofobjectrenders].tri[1][1]=2;
        objectrender[numofobjectrenders].tri[1][2]=3;

        numofobjectrenders++;
        }
      }
    }


  for (count=0;count<numofbosses;count++)
  if (boss[count].texturenum!=0)
    {
    subtractvectors(vec,view.position,boss[count].position);
    if (fabs(vec[0])-4.0f<view.zoom)
    if (fabs(vec[1])-4.0f<view.zoom)
      {
      objectrender[numofobjectrenders].type=4;
      objectrender[numofobjectrenders].depth=1.0f;
      objectrender[numofobjectrenders].texturenum=boss[count].texturenum;
      objectrender[numofobjectrenders].objectnum=count;
      objectrender[numofobjectrenders].lightflags=255;
      objectrender[numofobjectrenders].alpha=1.0f;

      objectrender[numofobjectrenders].numofverts=4;
      for (count2=0;count2<4;count2++)
        {
        copyvector(vec,boss[count].position);

        //subtractvectors(vec2,object[0].position,boss[count].position);
        copyvector(vec2,boss[count].velocity);
        normalizevector(vec2,vec2);
        if (boss[count].direction==1)
          negvector(vec2,vec2);
        normal[0]=-vec2[1];
        normal[1]=vec2[0];
        normal[2]=0.0f;

        if (count2==0 || count2==3)
          scaleaddvectors(vec,vec,vec2,-boss[count].size[0]);
        else
          scaleaddvectors(vec,vec,vec2,boss[count].size[0]);

        if (count2<2)
          scaleaddvectors(vec,vec,normal,boss[count].size[1]);
        else
          scaleaddvectors(vec,vec,normal,-boss[count].size[1]);

        copyvector(objectrender[numofobjectrenders].vertex[count2],vec);

        if ((boss[count].direction==0 && (count2==0 || count2==3)) || (boss[count].direction==1 && (count2==1 || count2==2)))
          objectrender[numofobjectrenders].texcoord[count2][0]=0.0f;
        else
          objectrender[numofobjectrenders].texcoord[count2][0]=1.0f;
        if (count2<2)
          objectrender[numofobjectrenders].texcoord[count2][1]=0.0f;
        else
          objectrender[numofobjectrenders].texcoord[count2][1]=1.0f;
        }
      objectrender[numofobjectrenders].numoftris=2;
      objectrender[numofobjectrenders].tri[0][0]=0;
      objectrender[numofobjectrenders].tri[0][1]=1;
      objectrender[numofobjectrenders].tri[0][2]=2;
      objectrender[numofobjectrenders].tri[1][0]=0;
      objectrender[numofobjectrenders].tri[1][1]=2;
      objectrender[numofobjectrenders].tri[1][2]=3;

      numofobjectrenders++;
      }
    }

  for (count=0;count<numofobjects;count++)
  if (object[count].texturenum!=0)
    {
    if (object[count].type==5 || object[count].type==6)
      {
      subtractvectors(vec,view.position,object[count].position);
      if (fabs(vec[0])-object[count].radius<view.zoom)
      if (fabs(vec[1])-object[count].radius<view.zoom)
        {
        objectrender[numofobjectrenders].type=5;
        objectrender[numofobjectrenders].depth=1.1f;
        objectrender[numofobjectrenders].texturenum=object[count].texturenum;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=setuprenderobjectlight(count);
        objectrender[numofobjectrenders].alpha=1.0f;
        if (object[count].timetolive<50)
          objectrender[numofobjectrenders].alpha=(float)object[count].timetolive/50.0f;

        objectrender[numofobjectrenders].numofverts=9;
        for (count2=0;count2<8;count2++)
          {
          if ((count2&1)==0)
            scale=1.0f;
          else
            scale=1.41f;

          subtractvectors(vec,particle[object[count].particle[count2]].position,object[count].position);
          scaleaddvectors(objectrender[numofobjectrenders].vertex[count2],object[count].position,vec,scale);

          angle=(float)count2*pi/4.0f;
          if (object[count].direction==0)
            objectrender[numofobjectrenders].texcoord[count2][0]=0.5f+cos(angle)*0.5f*scale;
          else
            objectrender[numofobjectrenders].texcoord[count2][0]=0.5f-cos(angle)*0.5f*scale;
          objectrender[numofobjectrenders].texcoord[count2][1]=0.5f+sin(angle)*0.5f*scale;
          }
        count2=8;
        copyvector(objectrender[numofobjectrenders].vertex[count2],object[count].position);
        objectrender[numofobjectrenders].texcoord[count2][0]=0.5f;
        objectrender[numofobjectrenders].texcoord[count2][1]=0.5f;

        objectrender[numofobjectrenders].numoftris=8;
        for (count2=0;count2<8;count2++)
          {
          objectrender[numofobjectrenders].tri[count2][0]=count2;
          objectrender[numofobjectrenders].tri[count2][1]=((count2+1)&7);
          objectrender[numofobjectrenders].tri[count2][2]=8;
          }

        numofobjectrenders++;
        }
      }
    }

  for (count=0;count<numofobjects;count++)
  if (object[count].texturenum!=0)
    {
    if (object[count].type==9)
      {
      subtractvectors(vec,view.position,object[count].position);
      if (fabs(vec[0])-object[count].radius<view.zoom)
      if (fabs(vec[1])-object[count].radius<view.zoom)
        {
        objectrender[numofobjectrenders].type=9;
        objectrender[numofobjectrenders].depth=2.0f;
        objectrender[numofobjectrenders].texturenum=object[count].texturenum+256;
        objectrender[numofobjectrenders].objectnum=count;
        objectrender[numofobjectrenders].lightflags=setuprenderobjectlight(count);
        objectrender[numofobjectrenders].alpha=1.0f;

        objectrender[numofobjectrenders].numofverts=6;
        for (count2=0;count2<6;count2++)
          copyvector(objectrender[numofobjectrenders].vertex[count2],particle[object[count].particle[count2]].position);

        objectrender[numofobjectrenders].texcoord[0][0]=0.0f;
        objectrender[numofobjectrenders].texcoord[0][1]=1.0f;
        objectrender[numofobjectrenders].texcoord[1][0]=0.0f;
        objectrender[numofobjectrenders].texcoord[1][1]=0.0f;
        objectrender[numofobjectrenders].texcoord[2][0]=1.0f;
        objectrender[numofobjectrenders].texcoord[2][1]=0.0f;
        objectrender[numofobjectrenders].texcoord[3][0]=1.0f;
        objectrender[numofobjectrenders].texcoord[3][1]=1.0f;
        objectrender[numofobjectrenders].texcoord[4][0]=1.0f;
        objectrender[numofobjectrenders].texcoord[4][1]=0.0f;
        objectrender[numofobjectrenders].texcoord[5][0]=0.0f;
        objectrender[numofobjectrenders].texcoord[5][1]=0.0f;

        objectrender[numofobjectrenders].numoftris=4;
        objectrender[numofobjectrenders].tri[0][0]=0;
        objectrender[numofobjectrenders].tri[0][1]=1;
        objectrender[numofobjectrenders].tri[0][2]=2;
        objectrender[numofobjectrenders].tri[1][0]=0;
        objectrender[numofobjectrenders].tri[1][1]=2;
        objectrender[numofobjectrenders].tri[1][2]=3;
        objectrender[numofobjectrenders].tri[2][0]=0;
        objectrender[numofobjectrenders].tri[2][1]=3;
        objectrender[numofobjectrenders].tri[2][2]=4;
        objectrender[numofobjectrenders].tri[3][0]=0;
        objectrender[numofobjectrenders].tri[3][1]=4;
        objectrender[numofobjectrenders].tri[3][2]=5;

        numofobjectrenders++;
        }
      }
    }

  for (count=0;count<numofropes;count++)
  if (rope[count].texturenum!=0)
    {
    scale=1.0f;
    if (rope[count].type>=5 && rope[count].type<10)
      scale=bond[rope[count].bondnum].length+1.0f;

    subtractvectors(vec,view.position,particle[rope[count].part1].position);
    if (fabs(vec[0])-scale<view.zoom)
    if (fabs(vec[1])-scale<view.zoom)
      {
      objectrender[numofobjectrenders].type=32;
      objectrender[numofobjectrenders].depth=3.0f+(float)count/1000.0f;
      objectrender[numofobjectrenders].objectnum=count;
      objectrender[numofobjectrenders].texturenum=rope[count].texturenum;
      objectrender[numofobjectrenders].lightflags=setuprenderropelight(count,scale);
      objectrender[numofobjectrenders].alpha=1.0f;

      normal[0]=particle[rope[count].part1].position[1]-particle[rope[count].part2].position[1];
      normal[1]=particle[rope[count].part2].position[0]-particle[rope[count].part1].position[0];
      normal[2]=0.0f;
      normalizevector(normal,normal);
      if (rope[count].type==1 || rope[count].type==3)
        scalevector(normal,normal,0.35f);
      if (rope[count].type==2 || rope[count].type==4)
        scalevector(normal,normal,0.5f);
      if (rope[count].type>=5 && rope[count].type<=10)
        scalevector(normal,normal,0.5f);

      objectrender[numofobjectrenders].numofverts=4;
      count2=0;
      subtractvectors(objectrender[numofobjectrenders].vertex[count2],particle[rope[count].part1].position,normal);
      objectrender[numofobjectrenders].texcoord[count2][0]=0.0f;
      objectrender[numofobjectrenders].texcoord[count2][1]=0.0f;
      count2=1;
      addvectors(objectrender[numofobjectrenders].vertex[count2],particle[rope[count].part1].position,normal);
      objectrender[numofobjectrenders].texcoord[count2][0]=1.0f;
      objectrender[numofobjectrenders].texcoord[count2][1]=0.0f;
      count2=2;
      addvectors(objectrender[numofobjectrenders].vertex[count2],particle[rope[count].part2].position,normal);
      objectrender[numofobjectrenders].texcoord[count2][0]=1.0f;
      objectrender[numofobjectrenders].texcoord[count2][1]=1.0f;
      count2=3;
      subtractvectors(objectrender[numofobjectrenders].vertex[count2],particle[rope[count].part2].position,normal);
      objectrender[numofobjectrenders].texcoord[count2][0]=0.0f;
      objectrender[numofobjectrenders].texcoord[count2][1]=1.0f;

      objectrender[numofobjectrenders].numoftris=2;
      objectrender[numofobjectrenders].tri[0][0]=0;
      objectrender[numofobjectrenders].tri[0][1]=1;
      objectrender[numofobjectrenders].tri[0][2]=2;
      objectrender[numofobjectrenders].tri[1][0]=0;
      objectrender[numofobjectrenders].tri[1][1]=2;
      objectrender[numofobjectrenders].tri[1][2]=3;

      numofobjectrenders++;
      }
    }
  }

int setuprenderobjectlight(int objectnum)
  {
  int lightcount;
  int lightflags;
  float vec[3];

  lightflags=0;

  for (lightcount=0;lightcount<frame.numoflights;lightcount++)
    {
    subtractvectors(vec,frame.light[lightcount].position,object[objectnum].position);
    if (fabs(vec[0])-object[objectnum].radius<frame.light[lightcount].intensity*0.5f)
    if (fabs(vec[1])-object[objectnum].radius<frame.light[lightcount].intensity*0.5f)
      lightflags|=(1<<lightcount);
    }

  return(lightflags);
  }

int setuprenderropelight(int ropenum,float radius)
  {
  int lightcount;
  int lightflags;
  float vec[3];

  lightflags=0;

  for (lightcount=0;lightcount<frame.numoflights;lightcount++)
    {
    subtractvectors(vec,frame.light[lightcount].position,particle[rope[ropenum].part1].position);
    if (fabs(vec[0])-radius<frame.light[lightcount].intensity*0.5f)
    if (fabs(vec[1])-radius<frame.light[lightcount].intensity*0.5f)
      lightflags|=(1<<lightcount);
    }

  return(lightflags);
  }

