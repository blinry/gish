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

void renderlevelback(void)
  {
  int count,count2;
  int lightcount;
  int blocknum;
  int lightrange;
  float vec[3];
  float texcoord[2];

  updateogg();

  for (count=view.position[1]-view.zoomy;count<=view.position[1]+view.zoomy;count++)
  if (count>=0 && count<256)
  for (count2=view.position[0]-view.zoomx;count2<=view.position[0]+view.zoomx;count2++)
  if (count2>=0 && count2<256)
    {
    blocknum=level.backgrid[count][count2];

    if (block[blocknum].animation!=0)
    if (block[blocknum].animationspeed!=0)
      blocknum+=(game.framenum/block[blocknum].animationspeed)%block[blocknum].animation;

    if (!game.godmode)
    if (!editor.active || !editor.showgrid)
    if (level.grid[count][count2]!=0 && level.gridmod[count][count2]==0)
    if (!texture[level.grid[count][count2]].isalpha)
      blocknum=0;

    if (!game.godmode)
    if (!editor.active || !editor.showgrid)
    if (level.foregrid[count][count2]!=0)
    if (!texture[level.foregrid[count][count2]].isalpha)
      blocknum=0;

    if (blocknum!=0)
      {
      glBindTexture(GL_TEXTURE_2D,texture[blocknum].glname);
  
      glBegin(GL_QUADS);
  
      glColor3fv(level.ambient[0]);
  
      vec[0]=(float)count2;
      vec[1]=(float)count+1.0f;
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2+1.0f;
      vec[1]=(float)count+1.0f;
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2+1.0f;
      vec[1]=(float)count;
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2;
      vec[1]=(float)count;
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      glEnd();
      }
    }

  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  glEnable(GL_STENCIL_TEST);

  glActiveTextureARB(GL_TEXTURE1_ARB);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[332].glname);
  glDisable(GL_TEXTURE_2D);
  glActiveTextureARB(GL_TEXTURE0_ARB);

  for (lightcount=0;lightcount<frame.numoflights;lightcount++)
    {
    glStencilMask((1<<lightcount));
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
    glStencilFunc(GL_NOTEQUAL,(1<<lightcount),(1<<lightcount));

    for (count=view.position[1]-view.zoomy;count<=view.position[1]+view.zoomy;count++)
    if (count>=0 && count<256)
    for (count2=view.position[0]-view.zoomx;count2<=view.position[0]+view.zoomx;count2++)
    if (count2>=0 && count2<256)
      {
      blocknum=level.backgrid[count][count2];

      if (block[blocknum].animation!=0)
      if (block[blocknum].animationspeed!=0)
        blocknum+=(game.framenum/block[blocknum].animationspeed)%block[blocknum].animation;

      if (!editor.active || !editor.showgrid)
      if (level.grid[count][count2]!=0 && level.gridmod[count][count2]==0)
      if (!texture[level.grid[count][count2]].isalpha)
        blocknum=0;

      if (!editor.active || !editor.showgrid)
      if (level.foregrid[count][count2]!=0)
      if (!texture[level.foregrid[count][count2]].isalpha)
        blocknum=0;

      lightrange=frame.light[lightcount].intensity*0.5f;
      if ((count2-frame.light[lightcount].position[0])>lightrange+1)
        blocknum=0;
      if ((count-frame.light[lightcount].position[1])>lightrange+1)
        blocknum=0;

      if (blocknum!=0)
        {
        glBindTexture(GL_TEXTURE_2D,texture[blocknum].glname);
    
        glActiveTextureARB(GL_TEXTURE1_ARB);
        glEnable(GL_TEXTURE_2D);
    
        glBegin(GL_QUADS);
    
        glColor3fv(frame.light[lightcount].color);
    
        vec[0]=(float)count2;
        vec[1]=(float)count+1.0f;
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0.0f,0.0f);
        setuplighttexcoord(lightcount,vec);
        glVertex3f(vec[0],vec[1],0.0f);
    
        vec[0]=(float)count2+1.0f;
        vec[1]=(float)count+1.0f;
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,1.0f,0.0f);
        setuplighttexcoord(lightcount,vec);
        glVertex3f(vec[0],vec[1],0.0f);
    
        vec[0]=(float)count2+1.0f;
        vec[1]=(float)count;
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,1.0f,1.0f);
        setuplighttexcoord(lightcount,vec);
        glVertex3f(vec[0],vec[1],0.0f);
    
        vec[0]=(float)count2;
        vec[1]=(float)count;
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,0.0f,1.0f);
        setuplighttexcoord(lightcount,vec);
        glVertex3f(vec[0],vec[1],0.0f);
    
        glEnd();
    
        glDisable(GL_TEXTURE_2D);
        glActiveTextureARB(GL_TEXTURE0_ARB);
        }
      }
    }

  glDisable(GL_STENCIL_TEST);

  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  }

void renderlevel(void)
  {
  int count,count2,count3;
  int lightcount;
  int blocknum;
  int lightrange;
  float vec[3],vec2[3],vec3[3];
  float normal[3];
  float scale;

  updateogg();

  for (count=view.position[1]-view.zoomy;count<=view.position[1]+view.zoomy;count++)
  if (count>=0 && count<256)
  for (count2=view.position[0]-view.zoomx;count2<=view.position[0]+view.zoomx;count2++)
  if (count2>=0 && count2<256)
    {
    blocknum=level.grid[count][count2];

    if (block[blocknum].animation!=0)
    if (block[blocknum].animationspeed!=0)
      blocknum+=(game.framenum/block[blocknum].animationspeed)%block[blocknum].animation;

    if (level.gridmod[count][count2]==1)
      blocknum=0;

    if (blocknum>=240 && blocknum<248)
    if (level.gridmod[count][count2]==2)
      blocknum+=8;

    if (!editor.active || !editor.showgrid)
    if (level.foregrid[count][count2]!=0)
    if (!texture[level.foregrid[count][count2]].isalpha)
      blocknum=0;

    if (blocknum!=0)
      {
      glBindTexture(GL_TEXTURE_2D,texture[blocknum].glname);

      glBegin(GL_QUADS);

      glColor3fv(level.ambient[1]);

      vec[0]=(float)count2;
      vec[1]=(float)count+1.0f;
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2+1.0f;
      vec[1]=(float)count+1.0f;
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2+1.0f;
      vec[1]=(float)count;
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2;
      vec[1]=(float)count;
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      glEnd();
      /*
      if (block[blocknum].friction<0.1f)
        {
        glDisable(GL_TEXTURE_2D);

        for (count3=0;count3<block[blocknum].numoflines;count3++)
        if (((level.gridflags[count][count2]>>count3)&1)==0)
          {
          normal[0]=-(block[blocknum].line[count3][3]-block[blocknum].line[count3][1]);
          normal[1]=(block[blocknum].line[count3][2]-block[blocknum].line[count3][0]);
          normal[2]=0.0f;
          normalizevector(normal,normal);

          glBegin(GL_QUADS);

          glColor4f(0.25f,0.25f,0.25f,1.0f);

          vec[0]=(float)count2+block[blocknum].line[count3][0];
          vec[1]=(float)count+block[blocknum].line[count3][1];
          vec[2]=0.0f;
          glVertex3fv(vec);

          vec[0]=(float)count2+block[blocknum].line[count3][2];
          vec[1]=(float)count+block[blocknum].line[count3][3];
          vec[2]=0.0f;
          glVertex3fv(vec);

          glColor4f(0.25f,0.25f,0.25f,0.0f);

          vec[0]=(float)count2+block[blocknum].line[count3][2]-normal[0]*0.125f*0.5f;
          vec[1]=(float)count+block[blocknum].line[count3][3]-normal[1]*0.125f*0.5f;
          vec[2]=0.0f;
          glVertex3fv(vec);
  
          vec[0]=(float)count2+block[blocknum].line[count3][0]-normal[0]*0.125f*0.5f;
          vec[1]=(float)count+block[blocknum].line[count3][1]-normal[1]*0.125f*0.5f;
          vec[2]=0.0f;
          glVertex3fv(vec);

          glEnd();
          }

        glEnable(GL_TEXTURE_2D);
        }
      */
      }
    }

  glBlendFunc(GL_ONE,GL_ONE);

  glEnable(GL_STENCIL_TEST);

  for (lightcount=0;lightcount<frame.numoflights;lightcount++)
    {
    glStencilMask((1<<lightcount));
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
    glStencilFunc(GL_NOTEQUAL,(1<<lightcount),(1<<lightcount));

    for (count=view.position[1]-view.zoomy;count<=view.position[1]+view.zoomy;count++)
    if (count>=0 && count<256)
    for (count2=view.position[0]-view.zoomx;count2<=view.position[0]+view.zoomx;count2++)
    if (count2>=0 && count2<256)
      {
      blocknum=level.grid[count][count2];

      if (block[blocknum].animation!=0)
      if (block[blocknum].animationspeed!=0)
        blocknum+=(game.framenum/block[blocknum].animationspeed)%block[blocknum].animation;

      if (level.gridmod[count][count2]==1)
        blocknum=0;

      if (blocknum>=240 && blocknum<248)
      if (level.gridmod[count][count2]==2)
        blocknum+=8;

      if (!editor.active || !editor.showgrid)
      if (level.foregrid[count][count2]!=0)
      if (!texture[level.foregrid[count][count2]].isalpha)
        blocknum=0;

      lightrange=frame.light[lightcount].intensity*0.5f;

      if ((count2-frame.light[lightcount].position[0])>lightrange+1)
        blocknum=0;
      if ((count-frame.light[lightcount].position[1])>lightrange+1)
        blocknum=0;

      if (blocknum!=0)
        {
        glBindTexture(GL_TEXTURE_2D,texture[blocknum].glname);
  
        for (count3=0;count3<block[blocknum].numoflines;count3++)
        if (((level.gridflags[count][count2]>>count3)&1)==0)
          {
          normal[0]=-(block[blocknum].line[count3][3]-block[blocknum].line[count3][1]);
          normal[1]=(block[blocknum].line[count3][2]-block[blocknum].line[count3][0]);
          normal[2]=0.0f;
          normalizevector(normal,normal);
  
          glBegin(GL_QUADS);
  
          vec[0]=(float)count2+block[blocknum].line[count3][0];
          vec[1]=(float)count+block[blocknum].line[count3][1];
          vec[2]=0.0f;
          subtractvectors(vec2,frame.light[lightcount].position,vec);
          normalizevector(vec3,vec2);
          scale=frame.light[lightcount].intensity*dotproduct(vec3,normal)/(vec2[0]*vec2[0]+vec2[1]*vec2[1]);
          scalevector(vec2,frame.light[lightcount].color,scale);
          glColor3fv(vec2);
          glTexCoord2f(block[blocknum].line[count3][0],1.0f-block[blocknum].line[count3][1]);
          glVertex3f(vec[0],vec[1],0.0f);
      
          vec[0]=(float)count2+block[blocknum].line[count3][2];
          vec[1]=(float)count+block[blocknum].line[count3][3];
          vec[2]=0.0f;
          subtractvectors(vec2,frame.light[lightcount].position,vec);
          normalizevector(vec3,vec2);
          scale=frame.light[lightcount].intensity*dotproduct(vec3,normal)/(vec2[0]*vec2[0]+vec2[1]*vec2[1]);
          scalevector(vec2,frame.light[lightcount].color,scale);
          glColor3fv(vec2);
          glTexCoord2f(block[blocknum].line[count3][2],1.0f-block[blocknum].line[count3][3]);
          glVertex3f(vec[0],vec[1],0.0f);
  
          vec[0]=(float)count2+block[blocknum].line[count3][2]-normal[0]*0.125f;
          vec[1]=(float)count+block[blocknum].line[count3][3]-normal[1]*0.125f;
          glColor3f(0.0f,0.0f,0.0f);
          glTexCoord2f((block[blocknum].line[count3][2]-normal[0]*0.125f),1.0f-(block[blocknum].line[count3][3]-normal[1]*0.125f));
          glVertex3f(vec[0],vec[1],0.0f);
  
          vec[0]=(float)count2+block[blocknum].line[count3][0]-normal[0]*0.125f;
          vec[1]=(float)count+block[blocknum].line[count3][1]-normal[1]*0.125f;
          glColor3f(0.0f,0.0f,0.0f);
          glTexCoord2f((block[blocknum].line[count3][0]-normal[0]*0.125f),1.0f-(block[blocknum].line[count3][1]-normal[1]*0.125f));
          glVertex3f(vec[0],vec[1],0.0f);
  
          glEnd();
          }
        }
      }
    }

  glDisable(GL_STENCIL_TEST);

  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  }

void renderlevelfore(void)
  {
  int count,count2;
  int blocknum;
  float vec[3];

  updateogg();

  for (count=view.position[1]-view.zoomy;count<=view.position[1]+view.zoomy;count++)
  if (count>=0 && count<256)
  for (count2=view.position[0]-view.zoomx;count2<=view.position[0]+view.zoomx;count2++)
  if (count2>=0 && count2<256)
    {
    blocknum=level.foregrid[count][count2];

    if (block[blocknum].animation!=0)
    if (block[blocknum].animationspeed!=0)
      blocknum+=(game.framenum/block[blocknum].animationspeed)%block[blocknum].animation;

    if (blocknum!=0)
      {
      glBindTexture(GL_TEXTURE_2D,texture[blocknum].glname);

      glBegin(GL_QUADS);

      glColor3fv(level.ambient[2]);

      vec[0]=(float)count2;
      vec[1]=(float)count+1.0f;
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2+1.0f;
      vec[1]=(float)count+1.0f;
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2+1.0f;
      vec[1]=(float)count;
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      vec[0]=(float)count2;
      vec[1]=(float)count;
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(vec[0],vec[1],0.0f);
  
      glEnd();
      }
    }
  }

void renderbonds(void)
  {
  int count;
  float vec[3];

  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);

  glColor4f(0.0f,1.0f,0.0f,1.0f);

  for (count=0;count<numofbonds;count++)
    {
    vec[0]=particle[bond[count].part1].position[0];
    vec[1]=particle[bond[count].part1].position[1];
    vec[2]=particle[bond[count].part1].position[2];
    glVertex3fv(vec);

    vec[0]=particle[bond[count].part2].position[0];
    vec[1]=particle[bond[count].part2].position[1];
    vec[2]=particle[bond[count].part2].position[2];
    glVertex3fv(vec);
    }

  glColor4f(1.0f,1.0f,0.0f,1.0f);

  for (count=0;count<physicstemp.numofbonds;count++)
    {
    if (physicstemp.bond[count].type==0)
      {
      glVertex3fv(particle[physicstemp.bond[count].part1].position);
      glVertex3fv(physicstemp.bond[count].point);
      }
    if (physicstemp.bond[count].type==1)
      {
      glVertex3fv(particle[physicstemp.bond[count].part1].position);
      glVertex3fv(physicstemp.bond[count].point);
      }
    if (physicstemp.bond[count].type==5)
      {
      scalevector(vec,particle[physicstemp.bond[count].part1].position,physicstemp.bond[count].force[0]);
      scaleaddvectors(vec,vec,particle[physicstemp.bond[count].part2].position,physicstemp.bond[count].force[1]);

      glVertex3fv(vec);
      glVertex3fv(particle[physicstemp.bond[count].part3].position);
      }
    }

  glEnd();

  glEnable(GL_TEXTURE_2D);
  }

void renderobjectinvisible(int objectnum)
  {
  int count,count2;
  float vec[3],vec2[3];
  float windowsize;

  windowsize=2.0f*640.0f/800.0f;

  vec[0]=object[objectrender[objectnum].objectnum].position[0]-view.position[0];
  vec[1]=object[objectrender[objectnum].objectnum].position[1]-view.position[1];
  vec[0]/=10.0f;
  vec[1]/=10.0f;
  count2=(windowinfo.resolutionx>>1)+vec[0]*(windowinfo.resolutionx>>1);
  count=(windowinfo.resolutiony>>1)+vec[1]*(windowinfo.resolutionx>>1);
  count2-=64;
  count-=64;
  if (count2<0)
    count2=0;
  if (count<0)
    count=0;
  if (count2>windowinfo.resolutionx-128)
    count2=windowinfo.resolutionx-128;
  if (count>windowinfo.resolutiony-128)
    count=windowinfo.resolutiony-128;

  glBindTexture(GL_TEXTURE_2D,texture[331].glname);
  glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,count2,count,128,128,0);

  glBlendFunc(GL_ONE,GL_ZERO);

  //glDisable(GL_ALPHA_TEST);

  glBindTexture(GL_TEXTURE_2D,texture[331].glname);

  glBegin(GL_TRIANGLES);

  glColor3f(0.75f,0.75f,0.75f);

  for (count2=0;count2<32;count2++)
    {
    subtractvectors(vec2,objectrender[objectnum].vertex[count2],object[objectrender[objectnum].objectnum].position);
    normalizevector(vec2,vec2);
    glTexCoord2f(0.5f+vec2[0]*0.3f,0.5f+vec2[1]*0.3f);
    glVertex3fv(objectrender[objectnum].vertex[count2]);

    subtractvectors(vec2,objectrender[objectnum].vertex[((count2+1)&31)],object[objectrender[objectnum].objectnum].position);
    normalizevector(vec2,vec2);
    glTexCoord2f(0.5f+vec2[0]*0.3f,0.5f+vec2[1]*0.3f);
    glVertex3fv(objectrender[objectnum].vertex[((count2+1)&31)]);

    glTexCoord2f(0.5f,0.5f);
    glVertex3fv(objectrender[objectnum].vertex[32]);
    }

  glEnd();

  /*
  for (count=0;count<16;count++)
    {
    glBegin(GL_TRIANGLES);

    glColor3f(0.5f,0.5f,0.5f);

    subtractvectors(vec2,particle[object[objectnum].particle[count]].position,object[objectnum].position);
    normalizevector(vec2,vec2);
    glTexCoord2f(0.5f+vec2[0]*0.3f,0.5f+vec2[1]*0.3f);
    glVertex3fv(particle[object[objectnum].particle[count]].position);

    subtractvectors(vec2,particle[object[objectnum].particle[((count+1)&15)]].position,object[objectnum].position);
    normalizevector(vec2,vec2);
    glTexCoord2f(0.5f+vec2[0]*0.3f,0.5f+vec2[1]*0.3f);
    glVertex3fv(particle[object[objectnum].particle[((count+1)&15)]].position);

    glTexCoord2f(0.5f,0.5f);
    glVertex3fv(object[objectnum].position);

    glEnd();
    }
  */
  //glEnable(GL_ALPHA_TEST);

  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  }

void setuplighttexcoord(int lightcount,float position[3])
  {
  float texcoord[2];

  texcoord[0]=(position[0]-frame.light[lightcount].position[0])/frame.light[lightcount].intensity+0.5f;
  texcoord[1]=(position[1]-frame.light[lightcount].position[1])/frame.light[lightcount].intensity+0.5f;

  glMultiTexCoord2fARB(GL_TEXTURE1_ARB,texcoord[0],texcoord[1]);
  }

float calclight(int lightcount,float position[3],float normal[3])
  {
  float vec[3],vec2[3];
  float scale;

  subtractvectors(vec,frame.light[lightcount].position,position);
  normalizevector(vec2,vec);
  scale=frame.light[lightcount].intensity*dotproduct(vec2,normal)/(vec[0]*vec[0]+vec[1]*vec[1]);

  return(scale);
  }

void renderparticles(void)
  {
  int count;
  float vec[3];
  float alpha;

  for (count=0;count<numofparticles;count++)
  if (particle[count].type==5)
  if (particle[count].texturenum!=366)
    {
    alpha=1.0f;
    if (particle[count].timetolive<50)
      alpha=(float)particle[count].timetolive/50.0f;

    glBindTexture(GL_TEXTURE_2D,texture[particle[count].texturenum].glname);

    glBegin(GL_QUADS);

    glColor4f(1.0f,1.0f,1.0f,alpha);

    glTexCoord2f(0.0f,0.0f);
    vec[0]=particle[count].position[0]-particle[count].rendersize*0.5f;
    vec[1]=particle[count].position[1]+particle[count].rendersize*0.5f;
    glVertex3f(vec[0],vec[1],0.0f);

    glTexCoord2f(1.0f,0.0f);
    vec[0]=particle[count].position[0]+particle[count].rendersize*0.5f;
    vec[1]=particle[count].position[1]+particle[count].rendersize*0.5f;
    glVertex3f(vec[0],vec[1],0.0f);

    glTexCoord2f(1.0f,1.0f);
    vec[0]=particle[count].position[0]+particle[count].rendersize*0.5f;
    vec[1]=particle[count].position[1]-particle[count].rendersize*0.5f;
    glVertex3f(vec[0],vec[1],0.0f);

    glTexCoord2f(0.0f,1.0f);
    vec[0]=particle[count].position[0]-particle[count].rendersize*0.5f;
    vec[1]=particle[count].position[1]-particle[count].rendersize*0.5f;
    glVertex3f(vec[0],vec[1],0.0f);

    glEnd();
    }
  }

void renderparticles2(void)
  {
  int count;
  float vec[3];
  float alpha;

  for (count=0;count<numofparticles;count++)
  if (particle[count].type==5)
  if (particle[count].texturenum==366)
    {
    alpha=1.0f;
    if (particle[count].timetolive<50)
      alpha=(float)particle[count].timetolive/50.0f;

    glBindTexture(GL_TEXTURE_2D,texture[particle[count].texturenum].glname);

    glBegin(GL_QUADS);

    glColor4f(1.0f,1.0f,1.0f,alpha);

    glTexCoord2f(0.0f,0.0f);
    vec[0]=particle[count].position[0]-particle[count].rendersize*0.5f;
    vec[1]=particle[count].position[1]+particle[count].rendersize*0.5f;
    glVertex3f(vec[0],vec[1],0.0f);

    glTexCoord2f(1.0f,0.0f);
    vec[0]=particle[count].position[0]+particle[count].rendersize*0.5f;
    vec[1]=particle[count].position[1]+particle[count].rendersize*0.5f;
    glVertex3f(vec[0],vec[1],0.0f);

    glTexCoord2f(1.0f,1.0f);
    vec[0]=particle[count].position[0]+particle[count].rendersize*0.5f;
    vec[1]=particle[count].position[1]-particle[count].rendersize*0.5f;
    glVertex3f(vec[0],vec[1],0.0f);

    glTexCoord2f(0.0f,1.0f);
    vec[0]=particle[count].position[0]-particle[count].rendersize*0.5f;
    vec[1]=particle[count].position[1]-particle[count].rendersize*0.5f;
    glVertex3f(vec[0],vec[1],0.0f);

    glEnd();
    }
  }

void renderobjects(void)
  {
  int count,count2;
  int lightcount;
  float vec[3],vec2[3];
  float normal[3];
  float color[4];
  float size;

  updateogg();

  for (count=0;count<numofobjectrenders;count++)
    {
    if (objectrender[count].type==1)
      {
      if (game.godmode && game.oldschool==0)
        renderobjectinvisible(count);
      else
        {
        glDisable(GL_TEXTURE_2D);
  
        glBegin(GL_TRIANGLES);
  
        glColor4f(0.0f,0.0f,0.0f,1.0f);
        if (objectrender[count].objectnum==1)
          glColor4f(0.5f,0.5f,0.5f,1.0f);
        if (objectrender[count].objectnum==2)
          glColor4f(0.355f,0.31f,0.15f,1.0f);
        if (objectrender[count].objectnum==3)
          glColor4f(0.453f,0.3f,0.28f,1.0f);
  
        if (object[objectrender[count].objectnum].hitpoints<object[objectrender[count].objectnum].prevhitpoints)
          glColor4f(0.25f,0.0f,0.0f,1.0f);
  
        for (count2=0;count2<32;count2++)
          {
          glVertex3fv(objectrender[count].vertex[count2]);
          glVertex3fv(objectrender[count].vertex[((count2+1)&31)]);
          glVertex3fv(objectrender[count].vertex[32]);
          }
  
        glEnd();

        glEnable(GL_TEXTURE_2D);
        }

      renderobjectspecular(count);

      size=0.75f;

      glBindTexture(GL_TEXTURE_2D,texture[objectrender[count].texturenum].glname);

      glBegin(GL_QUADS);
    
      glColor4f(1.0f,1.0f,1.0f,1.0f);
    
      vec[0]=objectrender[count].vertex[32][0]+size*cos(objectrender[count].angle+pi/4.0f);
      vec[1]=objectrender[count].vertex[32][1]+size*sin(objectrender[count].angle+pi/4.0f);
      vec[2]=0.0f;
      if (object[objectrender[count].objectnum].direction==0)
        glTexCoord2f(0.0f,0.0f);
      else
        glTexCoord2f(1.0f,0.0f);
      glVertex3fv(vec);
    
      vec[0]=objectrender[count].vertex[32][0]+size*cos(objectrender[count].angle+3.0f*pi/4.0f);
      vec[1]=objectrender[count].vertex[32][1]+size*sin(objectrender[count].angle+3.0f*pi/4.0f);
      vec[2]=0.0f;
      if (object[objectrender[count].objectnum].direction==0)
        glTexCoord2f(1.0f,0.0f);
      else
        glTexCoord2f(0.0f,0.0f);
      glVertex3fv(vec);
    
      vec[0]=objectrender[count].vertex[32][0]+size*cos(objectrender[count].angle+5.0f*pi/4.0f);
      vec[1]=objectrender[count].vertex[32][1]+size*sin(objectrender[count].angle+5.0f*pi/4.0f);
      vec[2]=0.0f;
      if (object[objectrender[count].objectnum].direction==0)
        glTexCoord2f(1.0f,1.0f);
      else
        glTexCoord2f(0.0f,1.0f);   
      glVertex3fv(vec);
    
      vec[0]=objectrender[count].vertex[32][0]+size*cos(objectrender[count].angle+7.0f*pi/4.0f);
      vec[1]=objectrender[count].vertex[32][1]+size*sin(objectrender[count].angle+7.0f*pi/4.0f);
      vec[2]=0.0f;
      if (object[objectrender[count].objectnum].direction==0)
        glTexCoord2f(0.0f,1.0f);
      else
        glTexCoord2f(1.0f,1.0f);
      glVertex3fv(vec);
    
      glEnd();

      if (!object[objectrender[count].objectnum].idata[0])
        {
        if (game.oldschool==0)
          glEnable(GL_LINE_SMOOTH);

        glDisable(GL_TEXTURE_2D);
  
        for (count2=0;count2<32;count2++)
          {
          glBegin(GL_LINES);
  
          if (objectrender[count].objectnum==0)
            glColor4f(0.5f,0.5f,0.5f,0.5f);
          else
            glColor4f(0.25f,0.25f,0.25f,0.5f);
  
          glVertex3fv(objectrender[count].vertex[count2]);
          glVertex3fv(objectrender[count].vertex[((count2+1)&31)]);
  
          glEnd();
          }
        if ((object[objectrender[count].objectnum].button&4)==4)
        for (count2=0;count2<32;count2++)
          {
          glBegin(GL_LINES);
  
          if (objectrender[count].objectnum==0)
            glColor4f(0.5f,0.5f,0.5f,0.5f);
          else
            glColor4f(0.25f,0.25f,0.25f,0.5f);
  
          normal[0]=objectrender[count].vertex[count2][1]-objectrender[count].vertex[((count2+1)&31)][1];
          normal[1]=objectrender[count].vertex[((count2+1)&31)][0]-objectrender[count].vertex[count2][0];
          normal[2]=0.0f;
  
          copyvector(vec,objectrender[count].vertex[count2]);
          scaleaddvectors(vec,vec,normal,0.1f);
          glVertex3fv(vec);
  
          normal[0]=objectrender[count].vertex[((count2+1)&31)][1]-objectrender[count].vertex[((count2+2)&31)][1];
          normal[1]=objectrender[count].vertex[((count2+2)&31)][0]-objectrender[count].vertex[((count2+1)&31)][0];
          normal[2]=0.0f;
  
          copyvector(vec,objectrender[count].vertex[((count2+1)&31)]);
          scaleaddvectors(vec,vec,normal,0.1f);
          glVertex3fv(vec);
  
          glEnd();
          }
        if ((object[objectrender[count].objectnum].button&1)==1)
        for (count2=0;count2<32;count2++)
          {
          glBegin(GL_LINES);
  
          if (objectrender[count].objectnum==0)
            {
            color[0]=0.5f;
            color[1]=0.5f;
            color[2]=0.5f;
            }
          else
            {
            color[0]=0.25f;
            color[1]=0.25f;
            color[2]=0.25f;
            }
  
          normal[0]=objectrender[count].vertex[count2][1]-objectrender[count].vertex[((count2+1)&31)][1];
          normal[1]=objectrender[count].vertex[((count2+1)&31)][0]-objectrender[count].vertex[count2][0];
          normal[2]=0.0f;
          scalevector(normal,normal,0.8f);
  
          copyvector(vec,objectrender[count].vertex[count2]);
          color[3]=1.0f;
          glColor4fv(color);
          glVertex3fv(vec);
          addvectors(vec,vec,normal);
          color[3]=0.0f;
          glColor4fv(color);
          glVertex3fv(vec);

          scalevector(vec,objectrender[count].vertex[count2],0.5f);
          scaleaddvectors(vec,vec,objectrender[count].vertex[((count2+1)&31)],0.5f);
          color[3]=1.0f;
          glColor4fv(color);
          glVertex3fv(vec);
          addvectors(vec,vec,normal);
          color[3]=0.0f;
          glColor4fv(color);
          glVertex3fv(vec);

          glEnd();
          }
  
        glEnable(GL_TEXTURE_2D);

        glDisable(GL_LINE_SMOOTH);
        }
      }
    else
      {
      glBindTexture(GL_TEXTURE_2D,texture[objectrender[count].texturenum].glname);

      glBegin(GL_TRIANGLES);

      glColor4f(level.ambient[1][0],level.ambient[1][1],level.ambient[1][2],objectrender[count].alpha);

      if (objectrender[count].type==8)
      if (object[objectrender[count].objectnum].lighttype==1)
        glColor3fv(object[objectrender[count].objectnum].lightcolor);

      for (count2=0;count2<objectrender[count].numoftris;count2++)
        {
        glTexCoord2fv(objectrender[count].texcoord[objectrender[count].tri[count2][0]]);
        glVertex3fv(objectrender[count].vertex[objectrender[count].tri[count2][0]]);
        glTexCoord2fv(objectrender[count].texcoord[objectrender[count].tri[count2][1]]);
        glVertex3fv(objectrender[count].vertex[objectrender[count].tri[count2][1]]);
        glTexCoord2fv(objectrender[count].texcoord[objectrender[count].tri[count2][2]]);
        glVertex3fv(objectrender[count].vertex[objectrender[count].tri[count2][2]]);
        }

      glEnd();

      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glEnable(GL_STENCIL_TEST);

      for (lightcount=0;lightcount<frame.numoflights;lightcount++)
      if (((objectrender[count].lightflags>>lightcount)&1)==1)
        {
        glStencilMask((1<<lightcount));
        glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
        glStencilFunc(GL_NOTEQUAL,(1<<lightcount),(1<<lightcount));

        glActiveTextureARB(GL_TEXTURE1_ARB);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texture[332].glname);

        if (objectrender[count].type!=2 && objectrender[count].type!=10)
          {
          glBegin(GL_TRIANGLES);
  
          glColor4f(level.ambient[1][0],level.ambient[1][1],level.ambient[1][2],objectrender[count].alpha);
  
          for (count2=0;count2<objectrender[count].numoftris;count2++)
            {
            glTexCoord2fv(objectrender[count].texcoord[objectrender[count].tri[count2][0]]);
            setuplighttexcoord(lightcount,objectrender[count].vertex[objectrender[count].tri[count2][0]]);
            glVertex3fv(objectrender[count].vertex[objectrender[count].tri[count2][0]]);
  
            glTexCoord2fv(objectrender[count].texcoord[objectrender[count].tri[count2][1]]);
            setuplighttexcoord(lightcount,objectrender[count].vertex[objectrender[count].tri[count2][1]]);
            glVertex3fv(objectrender[count].vertex[objectrender[count].tri[count2][1]]);
  
            glTexCoord2fv(objectrender[count].texcoord[objectrender[count].tri[count2][2]]);
            setuplighttexcoord(lightcount,objectrender[count].vertex[objectrender[count].tri[count2][2]]);
            glVertex3fv(objectrender[count].vertex[objectrender[count].tri[count2][2]]);
            }
  
          glEnd();
          }
        else
          {
          glBegin(GL_QUADS);

          for (count2=0;count2<objectrender[count].numofedges;count2++)
            {
            subtractvectors(vec2,frame.light[lightcount].position,objectrender[count].edgevertex[count2][0]);
            scalevector(vec,frame.light[lightcount].color,dotproduct(vec2,objectrender[count].edgenormal[count2]));
            glColor4f(vec[0],vec[1],vec[2],objectrender[count].alpha);

            glTexCoord2fv(objectrender[count].edgetexcoord[count2][0]);
            setuplighttexcoord(lightcount,objectrender[count].edgevertex[count2][0]);
            glVertex3fv(objectrender[count].edgevertex[count2][0]);

            subtractvectors(vec2,frame.light[lightcount].position,objectrender[count].edgevertex[count2][1]);
            scalevector(vec,frame.light[lightcount].color,dotproduct(vec2,objectrender[count].edgenormal[count2]));
            glColor4f(vec[0],vec[1],vec[2],objectrender[count].alpha);

            glTexCoord2fv(objectrender[count].edgetexcoord[count2][1]);
            setuplighttexcoord(lightcount,objectrender[count].edgevertex[count2][1]);
            glVertex3fv(objectrender[count].edgevertex[count2][1]);

            zerovector(vec);
            glColor4f(vec[0],vec[1],vec[2],objectrender[count].alpha);

            glTexCoord2fv(objectrender[count].edgetexcoord[count2][2]);
            setuplighttexcoord(lightcount,objectrender[count].edgevertex[count2][2]);
            glVertex3fv(objectrender[count].edgevertex[count2][2]);

            zerovector(vec);
            glColor4f(vec[0],vec[1],vec[2],objectrender[count].alpha);

            glTexCoord2fv(objectrender[count].edgetexcoord[count2][3]);
            setuplighttexcoord(lightcount,objectrender[count].edgevertex[count2][3]);
            glVertex3fv(objectrender[count].edgevertex[count2][3]);
            }

          glEnd();
          }

        glDisable(GL_TEXTURE_2D);
        glActiveTextureARB(GL_TEXTURE0_ARB);
        }

      glDisable(GL_STENCIL_TEST);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

      if (game.oldschool==2)
      if (objectrender[count].type==32)
        {
        glDisable(GL_TEXTURE_2D);

        glBegin(GL_LINES);

        glColor4f(0.0f,0.0f,0.0f,1.0f);

        glVertex3fv(particle[rope[objectrender[count].objectnum].part1].position);
        glVertex3fv(particle[rope[objectrender[count].objectnum].part2].position);

        glEnd();

        glEnable(GL_TEXTURE_2D);
        }
      }
    }
  }

void rendersprites(void)
  {
  int count;
  int x,y;
  float vec[3];

  for (count=0;count<numofsprites;count++)
    {
    subtractvectors(vec,sprite[count].position,view.position);
    vec[0]/=view.zoom;
    vec[1]/=view.zoom;
    vec[0]*=(float)(640>>1);
    vec[0]+=(float)(640>>1);
    vec[1]*=(float)(640>>1);
    vec[1]=(float)(480>>1)-vec[1];
    x=vec[0];
    y=vec[1];

    drawtext(sprite[count].text,(x|TEXT_CENTER),(y|TEXT_CENTER),sprite[count].size,sprite[count].red,sprite[count].green,sprite[count].blue,sprite[count].alpha);
    }
  }

