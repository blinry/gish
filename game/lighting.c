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

void setuplightingtextures(void)
  {
  int count,count2;
  int texturenum;
  int red,green,blue,alpha;
  float vec[3];

  texturenum=330;
  texture[texturenum].sizex=128;
  texture[texturenum].sizey=128;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_RGBA;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=GL_CLAMP_TO_EDGE;
  texture[texturenum].wrapt=GL_CLAMP_TO_EDGE;
  texture[texturenum].magfilter=GL_LINEAR;
  texture[texturenum].minfilter=GL_LINEAR;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  for (count=0;count<128;count++)
  for (count2=0;count2<128;count2++)
    {
    vec[0]=((float)count2-63.5f)/64.0f;
    vec[1]=((float)count-63.5f)/64.0f;
    vec[2]=sqrt(1.0f-(vec[0]*vec[0]+vec[1]*vec[1]));

    if (vec[2]<0.0f)
      zerovector(vec);

    red=128.0f+vec[0]*127.0f;
    green=128.0f+vec[1]*127.0f;
    blue=128.0f+vec[2]*127.0f;
    alpha=255;
#ifndef THINKSTUPID
    texture[texturenum].rgba[0][count*128+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
#endif
#ifdef THINKSTUPID
    texture[texturenum].rgba[0][count*128+count2]=(red<<24)+(green<<16)+(blue<<8)+alpha;
#endif
    }

  setuptexture(texturenum);

  texturenum=331;
  texture[texturenum].sizex=128;
  texture[texturenum].sizey=128;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_ALPHA;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=GL_CLAMP_TO_EDGE;
  texture[texturenum].wrapt=GL_CLAMP_TO_EDGE;
  texture[texturenum].magfilter=GL_LINEAR;
  texture[texturenum].minfilter=GL_LINEAR;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  setuptexture(texturenum);

  texturenum=332;
  texture[texturenum].sizex=128;
  texture[texturenum].sizey=128;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_RGBA;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=GL_CLAMP_TO_EDGE;
  texture[texturenum].wrapt=GL_CLAMP_TO_EDGE;
  texture[texturenum].magfilter=GL_LINEAR;
  texture[texturenum].minfilter=GL_LINEAR;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  for (count=0;count<128;count++)
  for (count2=0;count2<128;count2++)
    {
    vec[0]=((float)count2-63.5f)/64.0f;
    vec[1]=((float)count-63.5f)/64.0f;
    vec[2]=1.0f-sqrt(vec[0]*vec[0]+vec[1]*vec[1]);

    if (vec[2]<0.0f)
      zerovector(vec);

    red=vec[2]*255.0f;
    green=vec[2]*255.0f;
    blue=vec[2]*255.0f;
    alpha=255;
    //red&=(~31);
    //green&=(~31);
    //blue&=(~31);
#ifndef THINKSTUPID
    texture[texturenum].rgba[0][count*128+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
#endif
#ifdef THINKSTUPID
    texture[texturenum].rgba[0][count*128+count2]=(red<<24)+(green<<16)+(blue<<8)+alpha;
#endif
    }

  setuptexture(texturenum);

  texturenum=333;
  texture[texturenum].sizex=128;
  texture[texturenum].sizey=128;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_RGB;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=GL_CLAMP_TO_EDGE;
  texture[texturenum].wrapt=GL_CLAMP_TO_EDGE;
  texture[texturenum].magfilter=GL_NEAREST;
  texture[texturenum].minfilter=GL_NEAREST;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  setuptexture(texturenum);

  texturenum=334;
  texture[texturenum].sizex=256;
  texture[texturenum].sizey=256;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_RGB;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=GL_CLAMP_TO_EDGE;
  texture[texturenum].wrapt=GL_CLAMP_TO_EDGE;
  texture[texturenum].magfilter=GL_NEAREST;
  texture[texturenum].minfilter=GL_NEAREST;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  setuptexture(texturenum);

  texturenum=335;
  texture[texturenum].sizex=1;
  texture[texturenum].sizey=1;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_RGB;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=GL_CLAMP_TO_EDGE;
  texture[texturenum].wrapt=GL_CLAMP_TO_EDGE;
  texture[texturenum].magfilter=GL_NEAREST;
  texture[texturenum].minfilter=GL_NEAREST;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  setuptexture(texturenum);
  }

void setupframelighting(void)
  {
  int count,count2;
  float vec[3];

  frame.numoflights=0;
  for (count=0;count<numofobjects;count++)
  if (frame.numoflights<8)
  if (object[count].lighton)
    {
    if (object[count].lighttype>=1 && object[count].lighttype<=3)
      {
      subtractvectors(vec,view.position,object[count].position);
      vec[2]=0.0f;
      if (vectorlength(vec)<view.zoom+2.0f+object[count].lightintensity*0.5f)
        {
        copyvector(frame.light[frame.numoflights].position,object[count].position);
        /*
        if (object[count].lighttype==3)
          {
          frame.light[frame.numoflights].position[0]+=((float)(rand()&255)/512.0f-0.25f);
          frame.light[frame.numoflights].position[1]+=((float)(rand()&255)/512.0f-0.25f);
          }
        */
        copyvector(frame.light[frame.numoflights].color,object[count].lightcolor);
        frame.light[frame.numoflights].intensity=object[count].lightintensity;
        frame.numoflights++;
        }
      }
    }

  //if (keyboard[SCAN_L])
  //  frame.numoflights=0;
  }

void rendershadows(void)
  {
  int count,count2,count3;
  int lightcount;
  int lightrange;
  int blocknum;
  float vec[3],vec2[3],vec3[3];
  float normal[3];
  float scale;

  glDisable(GL_TEXTURE_2D);
  glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
  glEnable(GL_STENCIL_TEST);

  for (lightcount=0;lightcount<frame.numoflights;lightcount++)
    {
    lightrange=frame.light[lightcount].intensity*0.5f;

    glStencilMask((1<<lightcount));
    glStencilOp(GL_KEEP,GL_REPLACE,GL_REPLACE);
    glStencilFunc(GL_ALWAYS,(1<<lightcount),(1<<lightcount));

    for (count=view.position[1]-(view.zoomy+lightrange);count<=view.position[1]+(view.zoomy+lightrange);count++)
    if (count>=0 && count<256)
    for (count2=view.position[0]-(view.zoomx+lightrange);count2<=view.position[0]+(view.zoomx+lightrange);count2++)
    if (count2>=0 && count2<256)
      {
      blocknum=level.grid[count][count2];
      if (level.gridmod[count][count2]!=0)
        blocknum=0;
  
      if (blocknum!=0)
        {
        for (count3=0;count3<block[blocknum].numoflines;count3++)
        if (((level.gridflags[count][count2]>>count3)&1)==0)
          {
          normal[0]=-(block[blocknum].line[count3][3]-block[blocknum].line[count3][1]);
          normal[1]=(block[blocknum].line[count3][2]-block[blocknum].line[count3][0]);
          normal[2]=0.0f;
          normalizevector(normal,normal);

          vec[0]=(float)count2+block[blocknum].line[count3][0];
          vec[1]=(float)count+block[blocknum].line[count3][1];
          vec[2]=0.0f;
          subtractvectors(vec2,frame.light[lightcount].position,vec);
          if (dotproduct(vec2,normal)<0.0f)
            {
            vec[0]=(float)count2+block[blocknum].line[count3][2];
            vec[1]=(float)count+block[blocknum].line[count3][3];
            vec[2]=0.0f;
            subtractvectors(vec3,frame.light[lightcount].position,vec);

            normalizevector(vec2,vec2);
            normalizevector(vec3,vec3);

            glBegin(GL_QUADS);

            vec[0]=(float)count2+block[blocknum].line[count3][0];
            vec[1]=(float)count+block[blocknum].line[count3][1];
            vec[2]=0.0f;
            glVertex3fv(vec);
        
            vec[0]=(float)count2+block[blocknum].line[count3][2];
            vec[1]=(float)count+block[blocknum].line[count3][3];
            vec[2]=0.0f;
            glVertex3fv(vec);

            vec[0]=(float)count2+block[blocknum].line[count3][2];
            vec[1]=(float)count+block[blocknum].line[count3][3];
            vec[2]=0.0f;
            scaleaddvectors(vec,vec,vec3,-frame.light[lightcount].intensity*0.55f);
            glVertex3fv(vec);

            vec[0]=(float)count2+block[blocknum].line[count3][0];
            vec[1]=(float)count+block[blocknum].line[count3][1];
            vec[2]=0.0f;
            scaleaddvectors(vec,vec,vec2,-frame.light[lightcount].intensity*0.55f);
            glVertex3fv(vec);
    
            glEnd();
            }
          }
        }
      }

    for (count=0;count<numofobjects;count++)
    if (object[count].timetolive>=50)
      {
      if (object[count].type==2)
        {
        for (count2=0;count2<4;count2++)
          {
          normal[0]=-(particle[object[count].particle[((count2+1)&3)]].position[1]-particle[object[count].particle[count2]].position[1]);
          normal[1]=(particle[object[count].particle[((count2+1)&3)]].position[0]-particle[object[count].particle[count2]].position[0]);
          normal[2]=0.0f;
          normalizevector(normal,normal);

          subtractvectors(vec2,frame.light[lightcount].position,particle[object[count].particle[count2]].position);
          if (dotproduct(vec2,normal)<0.0f)
            {
            subtractvectors(vec3,frame.light[lightcount].position,particle[object[count].particle[((count2+1)&3)]].position);

            normalizevector(vec2,vec2);
            normalizevector(vec3,vec3);

            glBegin(GL_QUADS);

            scaleaddvectors(vec,particle[object[count].particle[count2]].position,vec2,-0.0f);
            glVertex3fv(vec);

            scaleaddvectors(vec,particle[object[count].particle[((count2+1)&3)]].position,vec3,-0.0f);
            glVertex3fv(vec);

            scaleaddvectors(vec,particle[object[count].particle[((count2+1)&3)]].position,vec3,-frame.light[lightcount].intensity*0.55f);
            glVertex3fv(vec);

            scaleaddvectors(vec,particle[object[count].particle[count2]].position,vec2,-frame.light[lightcount].intensity*0.55f);
            glVertex3fv(vec);

            glEnd();
            }
          }
        }
      }
    }

  glDisable(GL_STENCIL_TEST);
  glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_FALSE);
  glEnable(GL_TEXTURE_2D);
  }

void renderobjectspecular(int objectnum)
  {
  int count,count2;
  int lightcount;
  float vec[3],vec2[3],vec3[3];
  float normal[3];
  float windowsize;
  float scale;
  char tempcolor[4];

  if (windowinfo.bitsperpixel!=32)
    return;
  if (!glext.texture_env_dot3)
    return;

  for (lightcount=0;lightcount<frame.numoflights;lightcount++)
    {
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE_ARB);
    glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB_ARB,GL_DOT3_RGBA_ARB);
    glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE0_RGB_ARB,GL_TEXTURE);
    glTexEnvi(GL_TEXTURE_ENV,GL_SOURCE1_RGB_ARB,GL_PRIMARY_COLOR_ARB);

    //glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_TRUE);

    glEnable(GL_ALPHA_TEST);

    glEnable(GL_STENCIL_TEST);
    glStencilMask((1<<lightcount));
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
    glStencilFunc(GL_NOTEQUAL,(1<<lightcount),(1<<lightcount));

    glBlendFunc(GL_ONE,GL_ONE);

    glBindTexture(GL_TEXTURE_2D,texture[330].glname);

    glActiveTextureARB(GL_TEXTURE1_ARB);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture[335].glname);

    glAlphaFunc(GL_GREATER,1.0f-1.0f/32.0f);

    subtractvectors(vec,frame.light[lightcount].position,objectrender[objectnum].vertex[32]);
    scale=frame.light[lightcount].intensity/(vec[0]*vec[0]+vec[1]*vec[1]);

    if (scale>1.0f)
      scale=1.0f;
    scalevector(vec,frame.light[lightcount].color,scale);

    tempcolor[0]=vec[0]*255.0f;
    tempcolor[1]=vec[1]*255.0f;
    tempcolor[2]=vec[2]*255.0f;
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,1,1,GL_RGBA,GL_UNSIGNED_BYTE,tempcolor);

    for (count=0;count<32;count++)
      {
      glBegin(GL_TRIANGLES);

      subtractvectors(vec,frame.light[lightcount].position,objectrender[objectnum].vertex[count]);
      normalizevector(vec,vec);
      addvectors(vec,vec,zaxis);
      normalizevector(vec,vec);
      vec[0]=0.5f+vec[0]*0.5f;
      vec[1]=0.5f+vec[1]*0.5f;
      vec[2]=0.5f+vec[2]*0.5f;
      glColor3fv(vec);

      vec2[0]=objectrender[objectnum].vertex[((count+0)&31)][1]-objectrender[objectnum].vertex[((count+1)&31)][1];
      vec2[1]=objectrender[objectnum].vertex[((count+1)&31)][0]-objectrender[objectnum].vertex[((count+0)&31)][0];
      vec2[2]=0.0f;
      vec[0]=objectrender[objectnum].vertex[((count-1)&31)][1]-objectrender[objectnum].vertex[((count+0)&31)][1];
      vec[1]=objectrender[objectnum].vertex[((count+0)&31)][0]-objectrender[objectnum].vertex[((count-1)&31)][0];
      vec[2]=0.0f;
      normalizevector(vec2,vec2);
      normalizevector(vec,vec);
      addvectors(vec2,vec2,vec);
      normalizevector(vec2,vec2);
      glTexCoord2f(0.5f+vec2[0]*0.5f,0.5f+vec2[1]*0.5f);
      glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,0.0f);
      glVertex3fv(objectrender[objectnum].vertex[count]);

      subtractvectors(vec,frame.light[lightcount].position,objectrender[objectnum].vertex[((count+1)&31)]);
      normalizevector(vec,vec);
      addvectors(vec,vec,zaxis);
      normalizevector(vec,vec);
      vec[0]=0.5f+vec[0]*0.5f;
      vec[1]=0.5f+vec[1]*0.5f;
      vec[2]=0.5f+vec[2]*0.5f;
      glColor3fv(vec);

      vec2[0]=objectrender[objectnum].vertex[((count+1)&31)][1]-objectrender[objectnum].vertex[((count+2)&31)][1];
      vec2[1]=objectrender[objectnum].vertex[((count+2)&31)][0]-objectrender[objectnum].vertex[((count+1)&31)][0];
      vec2[2]=0.0f;
      vec[0]=objectrender[objectnum].vertex[((count+0)&31)][1]-objectrender[objectnum].vertex[((count+1)&31)][1];
      vec[1]=objectrender[objectnum].vertex[((count+1)&31)][0]-objectrender[objectnum].vertex[((count+0)&31)][0];
      vec[2]=0.0f;
      normalizevector(vec2,vec2);
      normalizevector(vec,vec);
      addvectors(vec2,vec2,vec);
      normalizevector(vec2,vec2);
      glTexCoord2f(0.5f+vec2[0]*0.5f,0.5f+vec2[1]*0.5f);
      glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,0.0f);
      glVertex3fv(objectrender[objectnum].vertex[((count+1)&31)]);

      subtractvectors(vec,frame.light[lightcount].position,objectrender[objectnum].vertex[32]);
      normalizevector(vec,vec);
      addvectors(vec,vec,zaxis);
      normalizevector(vec,vec);
      vec[0]=0.5f+vec[0]*0.5f;
      vec[1]=0.5f+vec[1]*0.5f;
      vec[2]=0.5f+vec[2]*0.5f;
      glColor3fv(vec);

      glTexCoord2f(0.5f,0.5f);
      glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,0.0f);
      glVertex3fv(objectrender[objectnum].vertex[32]);
  
      glEnd();
      }
    /*
    glAlphaFunc(GL_GREATER,1.0f-1.0f/32.0f-1.0f/32.0f);

    subtractvectors(vec,frame.light[lightcount].position,objectrender[objectnum].vertex[32]);
    scale=frame.light[lightcount].intensity/(vec[0]*vec[0]+vec[1]*vec[1]);
    if (scale>1.0f)
      scale=1.0f;
    scalevector(vec,frame.light[lightcount].color,scale);

    tempcolor[0]=vec[0]*192.0f;
    tempcolor[1]=vec[1]*192.0f;
    tempcolor[2]=vec[2]*192.0f;
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,1,1,GL_RGBA,GL_UNSIGNED_BYTE,tempcolor);

    for (count=0;count<32;count++)
      {
      glBegin(GL_TRIANGLES);

      subtractvectors(vec,frame.light[lightcount].position,objectrender[objectnum].vertex[count]);
      normalizevector(vec,vec);
      addvectors(vec,vec,zaxis);
      normalizevector(vec,vec);
      vec[0]=0.5f+vec[0]*0.5f;
      vec[1]=0.5f+vec[1]*0.5f;
      vec[2]=0.5f+vec[2]*0.5f;
      glColor3fv(vec);

      vec2[0]=objectrender[objectnum].vertex[((count+0)&31)][1]-objectrender[objectnum].vertex[((count+1)&31)][1];
      vec2[1]=objectrender[objectnum].vertex[((count+1)&31)][0]-objectrender[objectnum].vertex[((count+0)&31)][0];
      vec2[2]=0.0f;
      vec[0]=objectrender[objectnum].vertex[((count-1)&31)][1]-objectrender[objectnum].vertex[((count+0)&31)][1];
      vec[1]=objectrender[objectnum].vertex[((count+0)&31)][0]-objectrender[objectnum].vertex[((count-1)&31)][0];
      vec[2]=0.0f;
      normalizevector(vec2,vec2);
      normalizevector(vec,vec);
      addvectors(vec2,vec2,vec);
      normalizevector(vec2,vec2);
      glTexCoord2f(0.5f+vec2[0]*0.5f,0.5f+vec2[1]*0.5f);
      glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,0.0f);
      glVertex3fv(objectrender[objectnum].vertex[count]);

      subtractvectors(vec,frame.light[lightcount].position,objectrender[objectnum].vertex[((count+1)&31)]);
      normalizevector(vec,vec);
      addvectors(vec,vec,zaxis);
      normalizevector(vec,vec);
      vec[0]=0.5f+vec[0]*0.5f;
      vec[1]=0.5f+vec[1]*0.5f;
      vec[2]=0.5f+vec[2]*0.5f;
      glColor3fv(vec);

      vec2[0]=objectrender[objectnum].vertex[((count+1)&31)][1]-objectrender[objectnum].vertex[((count+2)&31)][1];
      vec2[1]=objectrender[objectnum].vertex[((count+2)&31)][0]-objectrender[objectnum].vertex[((count+1)&31)][0];
      vec2[2]=0.0f;
      vec[0]=objectrender[objectnum].vertex[((count+0)&31)][1]-objectrender[objectnum].vertex[((count+1)&31)][1];
      vec[1]=objectrender[objectnum].vertex[((count+1)&31)][0]-objectrender[objectnum].vertex[((count+0)&31)][0];
      vec[2]=0.0f;
      normalizevector(vec2,vec2);
      normalizevector(vec,vec);
      addvectors(vec2,vec2,vec);
      normalizevector(vec2,vec2);
      glTexCoord2f(0.5f+vec2[0]*0.5f,0.5f+vec2[1]*0.5f);
      glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,0.0f);
      glVertex3fv(objectrender[objectnum].vertex[((count+1)&31)]);

      subtractvectors(vec,frame.light[lightcount].position,objectrender[objectnum].vertex[32]);
      normalizevector(vec,vec);
      addvectors(vec,vec,zaxis);
      normalizevector(vec,vec);
      vec[0]=0.5f+vec[0]*0.5f;
      vec[1]=0.5f+vec[1]*0.5f;
      vec[2]=0.5f+vec[2]*0.5f;
      glColor3fv(vec);

      glTexCoord2f(0.5f,0.5f);
      glMultiTexCoord2fARB(GL_TEXTURE1_ARB,0.0f,0.0f);
      glVertex3fv(objectrender[objectnum].vertex[32]);
  
      glEnd();
      }
    */

    glDisable(GL_TEXTURE_2D);
    glActiveTextureARB(GL_TEXTURE0_ARB);

    glDisable(GL_ALPHA_TEST);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   
    glDisable(GL_STENCIL_TEST);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }
  }

