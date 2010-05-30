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

void editlevelobjects(void)
  {
  int count,count2;
  int x,y;
  int simtimer;
  int simcount;
  float vec[3],vec2[3];

  simtimer=SDL_GetTicks();

  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glStencilMask(~0);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_FALSE);
    glStencilMask(0);

    setuptextdisplay();
    glColor3fv(level.ambient[3]);
    if (level.background[0]!=0)
      displaybackground(660);

    numofmenuitems=0;
    createmenuitem("",0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    if (editor.objectnum!=-1)
      {
      createmenuitem("Mass   ",(640|TEXT_END),0,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_FLOATINPUT,&level.object[editor.objectnum].mass);
      setmenuitem(MO_HOTKEY,SCAN_M);
      createmenuitem("Friction",(640|TEXT_END),32,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_FLOATINPUT,&level.object[editor.objectnum].friction);
      setmenuitem(MO_HOTKEY,SCAN_F);
      createmenuitem("LType",(640|TEXT_END),64,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_INTINPUT,&level.object[editor.objectnum].lighttype);
      createmenuitem("Red  ",(640|TEXT_END),96,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_FLOATINPUT,&level.object[editor.objectnum].lightcolor[0]);
      createmenuitem("Green",(640|TEXT_END),128,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_FLOATINPUT,&level.object[editor.objectnum].lightcolor[1]);
      createmenuitem("Blue ",(640|TEXT_END),160,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_FLOATINPUT,&level.object[editor.objectnum].lightcolor[2]);
      createmenuitem("Inten",(640|TEXT_END),192,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_FLOATINPUT,&level.object[editor.objectnum].lightintensity);
      }

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkmenuitems();

    view.zoom=10.0f;
    if (keyboard[SCAN_EQUALS])
      view.zoom=20.0f;
    if (keyboard[SCAN_MINUS])
      view.zoom=5.0f;

    view.zoomx=view.zoom+0.5f;
    view.zoomy=view.zoom*0.75f+0.5f;

    setuporthoviewport(0,0,640,480,view.zoom,view.zoom*0.75f,20.0f);
    setupviewpoint(view.position,view.orientation);

    setupframelighting();

    rendershadows();

    renderlevelback();
    renderlevel();
    //renderlevelfore();

    renderlevelfore();
    renderlevelobjects();

    if (keyboard[SCAN_L])
      renderlevellines();

    setuptextdisplay();

    drawtext(TXT_OBJECTSET":/i",0,352,16,1.0f,1.0f,1.0f,1.0f,editor.objecttype);
    drawtext(TXT_OBJECTNUM":/i",0,368,16,1.0f,1.0f,1.0f,1.0f,editor.objectnum);
    if (editor.objectnum!=-1)
      drawtext(TXT_OBJECTYPE":/i",0,384,16,1.0f,1.0f,1.0f,1.0f,level.object[editor.objectnum].type);
    drawtext(TXT_OBJECTS":/i",0,400,16,1.0f,1.0f,1.0f,1.0f,level.numofobjects);
    drawtext(TXT_ROPES":/i",0,416,16,1.0f,1.0f,1.0f,1.0f,level.numofropes);
    if (editor.objectnum!=-1)
      {
      drawtext(TXT_LINK":/i",0,432,16,1.0f,1.0f,1.0f,1.0f,level.object[editor.objectnum].link);
      }

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (mouse.x<512 || mouse.y>224)
      {
      x=view.position[0]+(float)(mouse.x-320)/32.0f;
      y=view.position[1]+(float)(240-mouse.y)/32.0f;
      if (!keyboard[SCAN_K])
        {
        if (mouse.lmb && !prevmouse.lmb)
          {
          if (!keyboard[SCAN_H])
            {
            vec[0]=(float)x+0.5f;
            vec[1]=(float)y+0.5f;
            vec[2]=0.0f;
            }
          else
            {
            vec[0]=(float)x;
            vec[1]=(float)y;
            vec[2]=0.0f;
            }

    
          memset(&level.object[level.numofobjects],0,sizeof(level.object[level.numofobjects]));
          level.object[level.numofobjects].type=editor.objecttype;
          level.object[level.numofobjects].link=-1;
          copyvector(level.object[level.numofobjects].position,vec);
          if (editor.objectnum==-1 || level.object[level.numofobjects].type!=level.object[editor.objectnum].type)
            {
            level.object[level.numofobjects].texturenum=0;
            level.object[level.numofobjects].size[0]=1.0f;
            level.object[level.numofobjects].size[1]=1.0f;
            level.object[level.numofobjects].mass=1.0f;
            level.object[level.numofobjects].friction=0.8f;
            level.object[level.numofobjects].lightcolor[0]=1.0f;
            level.object[level.numofobjects].lightcolor[1]=1.0f;
            level.object[level.numofobjects].lightcolor[2]=1.0f;
            level.object[level.numofobjects].lightintensity=16.0f;
            }
          else
            {
            level.object[level.numofobjects].texturenum=level.object[editor.objectnum].texturenum;
            level.object[level.numofobjects].size[0]=level.object[editor.objectnum].size[0];
            level.object[level.numofobjects].size[1]=level.object[editor.objectnum].size[1];
            level.object[level.numofobjects].mass=level.object[editor.objectnum].mass;
            level.object[level.numofobjects].friction=level.object[editor.objectnum].friction;
            level.object[level.numofobjects].lighttype=level.object[editor.objectnum].lighttype;
            level.object[level.numofobjects].lightcolor[0]=level.object[editor.objectnum].lightcolor[0];
            level.object[level.numofobjects].lightcolor[1]=level.object[editor.objectnum].lightcolor[1];
            level.object[level.numofobjects].lightcolor[2]=level.object[editor.objectnum].lightcolor[2];
            level.object[level.numofobjects].lightintensity=level.object[editor.objectnum].lightintensity;
            }

          editor.objectnum=level.numofobjects;
          level.numofobjects++;
          }
        }
      if (keyboard[SCAN_K])
        {
        vec[0]=view.position[0]+(float)(mouse.x-320)/32.0f;
        vec[1]=view.position[1]+(float)(240-mouse.y)/32.0f;
        vec[2]=0.0f;

        if (mouse.lmb && !prevmouse.lmb)
          {
          if (editor.objectnum!=-1)
          for (count=0;count<level.numofobjects;count++)
            {
            subtractvectors(vec2,vec,level.object[count].position);
            if (vectorlength(vec2)<0.5f)
              level.object[editor.objectnum].link=count;
            }
          }
        if (mouse.rmb && !prevmouse.rmb)
          level.object[editor.objectnum].link=-1;
        }
      if (mouse.rmb && !prevmouse.rmb)
        {
        vec[0]=view.position[0]+(float)(mouse.x-320)/32.0f;
        vec[1]=view.position[1]+(float)(240-mouse.y)/32.0f;
        vec[2]=0.0f;
  
        editor.objectnum=-1;
  
        for (count=0;count<level.numofobjects;count++)
          {
          subtractvectors(vec2,vec,level.object[count].position);
          if (vectorlength(vec2)<0.5f)
            editor.objectnum=count;
          }
        }
      }
    if (!menuinputkeyboard)
      {
      if (editor.objectnum!=-1)
        {
        vec[0]=1.0f;
        if (level.object[editor.objectnum].type==6 || level.object[editor.objectnum].type==7 || level.object[editor.objectnum].type==17)
          vec[0]=0.2f;

        if (keyboard[SCAN_HOME] && !prevkeyboard[SCAN_HOME])
        if (level.numofobjects>1)
          {
          count2=0;
          if (keyboard[SCAN_SHIFT])
            count2=2;
          memcpy(&level.object[255],&level.object[count2],sizeof(level.object[0]));
          memcpy(&level.object[count2],&level.object[editor.objectnum],sizeof(level.object[0]));
          memcpy(&level.object[editor.objectnum],&level.object[255],sizeof(level.object[0]));

          for (count=0;count<level.numofobjects;count++)
            {
            if (level.object[count].link==count2)
              level.object[count].link=editor.objectnum;
            else if (level.object[count].link==editor.objectnum)
              level.object[count].link=count2;
            }

          for (count=0;count<level.numofropes;count++)
            {
            if (level.rope[count].obj1==count2)
              level.rope[count].obj1=editor.objectnum;
            else if (level.rope[count].obj1==editor.objectnum)
              level.rope[count].obj1=count2;
            if (level.rope[count].obj2==count2)
              level.rope[count].obj2=editor.objectnum;
            else if (level.rope[count].obj2==editor.objectnum)
              level.rope[count].obj2=count2;
            }
          editor.objectnum=count2;
          }
        if (keyboard[SCAN_END] && !prevkeyboard[SCAN_END])
        if (level.numofobjects>2)
          {
          count2=1;
          if (keyboard[SCAN_SHIFT])
            count2=3;
          memcpy(&level.object[255],&level.object[count2],sizeof(level.object[0]));
          memcpy(&level.object[count2],&level.object[editor.objectnum],sizeof(level.object[0]));
          memcpy(&level.object[editor.objectnum],&level.object[255],sizeof(level.object[0]));

          for (count=0;count<level.numofobjects;count++)
            {
            if (level.object[count].link==count2)
              level.object[count].link=editor.objectnum;
            else if (level.object[count].link==editor.objectnum)
              level.object[count].link=count2;
            }

          for (count=0;count<level.numofropes;count++)
            {
            if (level.rope[count].obj1==count2)
              level.rope[count].obj1=editor.objectnum;
            else if (level.rope[count].obj1==editor.objectnum)
              level.rope[count].obj1=count2;
            if (level.rope[count].obj2==count2)
              level.rope[count].obj2=editor.objectnum;
            else if (level.rope[count].obj2==editor.objectnum)
              level.rope[count].obj2=count2;
            }
          editor.objectnum=count2;
          }
        if (keyboard[SCAN_LEFT] && !prevkeyboard[SCAN_LEFT])
        if (level.object[editor.objectnum].size[0]>vec[0])
          level.object[editor.objectnum].size[0]-=vec[0];
    
        if (keyboard[SCAN_RIGHT] && !prevkeyboard[SCAN_RIGHT])
        if (level.object[editor.objectnum].size[0]<16.0f)
          level.object[editor.objectnum].size[0]+=vec[0];
  
        if (keyboard[SCAN_DOWN] && !prevkeyboard[SCAN_DOWN])
        if (level.object[editor.objectnum].size[1]>vec[0])
          level.object[editor.objectnum].size[1]-=vec[0];
    
        if (keyboard[SCAN_UP] && !prevkeyboard[SCAN_UP])
        if (level.object[editor.objectnum].size[1]<16.0f)
          level.object[editor.objectnum].size[1]+=vec[0];

        if (keyboard[SCAN_LFT_BRACKET] && !prevkeyboard[SCAN_LFT_BRACKET])
          {
          if (!keyboard[SCAN_SHIFT])
            level.object[editor.objectnum].texturenum--;
          else
            level.object[editor.objectnum].texturenum-=10;
          if (level.object[editor.objectnum].texturenum<0)
            level.object[editor.objectnum].texturenum=0;
          }
        if (keyboard[SCAN_RGT_BRACKET] && !prevkeyboard[SCAN_RGT_BRACKET])
          {
          if (!keyboard[SCAN_SHIFT])
            level.object[editor.objectnum].texturenum++;
          else
            level.object[editor.objectnum].texturenum+=10;
          if (level.object[editor.objectnum].texturenum>255)
            level.object[editor.objectnum].texturenum=255;
          }
        }
  
      if (keyboard[SCAN_Q] && !prevkeyboard[SCAN_Q])
        {
        if (!keyboard[SCAN_SHIFT])
          editor.objecttype++;
        else
          editor.objecttype+=10;
        if (editor.objecttype>255)
          editor.objecttype=255;
        }
      if (keyboard[SCAN_Z] && !prevkeyboard[SCAN_Z])
        {
        if (!keyboard[SCAN_SHIFT])
          editor.objecttype--;
        else
          editor.objecttype-=10;
        if (editor.objecttype<0)
          editor.objecttype=0;
        }
      if (keyboard[SCAN_DELETE] && !prevkeyboard[SCAN_DELETE])
        deletelevelobject(editor.objectnum);
      if (keyboard[SCAN_F5] && !prevkeyboard[SCAN_F5])
        {
        setuplevel();
        setupgame();
        }
      }

    simcount=0;
    while (SDL_GetTicks()-simtimer>20 && simcount<5)
      {
      simcount++;
      count=SDL_GetTicks()-simtimer-20;
      simtimer=SDL_GetTicks()-count;

      if (!menuinputkeyboard)
        {
        if (keyboard[SCAN_W])
          view.position[1]+=0.2f;
        if (keyboard[SCAN_S])
          view.position[1]-=0.2f;
        if (keyboard[SCAN_A])
          view.position[0]-=0.2f;
        if (keyboard[SCAN_D])
          view.position[0]+=0.2f;
        }
      }
    }

  resetmenuitems();
  }

void renderlevelobjects(void)
  {
  int count,count2;
  int objectnum;
  float vec[3];
  float angle;

  for (count=0;count<level.numofobjects;count++)
    {
    if (level.object[count].type==1)
      {
      glDisable(GL_TEXTURE_2D);

      for (count2=0;count2<16;count2++)
        {
        glBegin(GL_TRIANGLES);

        glColor4f(0.0f,0.0f,0.0f,1.0f);

        angle=(float)count2*pi/8.0f;
        vec[0]=level.object[count].position[0]+cos(angle)*0.9f;
        vec[1]=level.object[count].position[1]-sin(angle)*0.9f;
        vec[2]=0.0f;
        glVertex3fv(vec);

        angle=(float)(count2+1)*pi/8.0f;
        vec[0]=level.object[count].position[0]+cos(angle)*0.9f;
        vec[1]=level.object[count].position[1]-sin(angle)*0.9f;
        vec[2]=0.0f;
        glVertex3fv(vec);

        glVertex3fv(level.object[count].position);

        glEnd();
        }

      glEnable(GL_TEXTURE_2D);
      }
    if (level.object[count].type>=2 && level.object[count].type<=5)
      {
      glBindTexture(GL_TEXTURE_2D,texture[level.object[count].texturenum+256].glname);
  
      glBegin(GL_QUADS);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glTexCoord2f(0.0f,0.0f);
      glVertex3f(level.object[count].position[0]-level.object[count].size[0]*0.5f,level.object[count].position[1]+level.object[count].size[1]*0.5f,0.0f);

      glTexCoord2f(1.0f,0.0f);
      glVertex3f(level.object[count].position[0]+level.object[count].size[0]*0.5f,level.object[count].position[1]+level.object[count].size[1]*0.5f,0.0f);

      glTexCoord2f(1.0f,1.0f);
      glVertex3f(level.object[count].position[0]+level.object[count].size[0]*0.5f,level.object[count].position[1]-level.object[count].size[1]*0.5f,0.0f);

      glTexCoord2f(0.0f,1.0f);
      glVertex3f(level.object[count].position[0]-level.object[count].size[0]*0.5f,level.object[count].position[1]-level.object[count].size[1]*0.5f,0.0f);

      glEnd();
      }
    if (level.object[count].type==6 || level.object[count].type==7 || level.object[count].type==17)
      {
      glBindTexture(GL_TEXTURE_2D,texture[level.object[count].texturenum+256].glname);

      for (count2=0;count2<16;count2++)
        {
        glBegin(GL_TRIANGLES);

        glColor4f(1.0f,1.0f,1.0f,1.0f);

        angle=(float)count2*pi/8.0f;
        vec[0]=level.object[count].position[0]+cos(angle)*level.object[count].size[0]*0.5f;
        vec[1]=level.object[count].position[1]-sin(angle)*level.object[count].size[1]*0.5f;
        vec[2]=0.0f;
        glTexCoord2f(0.5f+cos(angle)*0.5f,0.5f+sin(angle)*0.5f);
        glVertex3fv(vec);

        angle=(float)(count2+1)*pi/8.0f;
        vec[0]=level.object[count].position[0]+cos(angle)*level.object[count].size[0]*0.5f;
        vec[1]=level.object[count].position[1]-sin(angle)*level.object[count].size[1]*0.5f;
        vec[2]=0.0f;
        glTexCoord2f(0.5f+cos(angle)*0.5f,0.5f+sin(angle)*0.5f);
        glVertex3fv(vec);

        glTexCoord2f(0.5f,0.5f);
        glVertex3fv(level.object[count].position);

        glEnd();
        }
      }
    if (level.object[count].type==8)
      {
      glBindTexture(GL_TEXTURE_2D,texture[level.object[count].texturenum+256].glname);
  
      glBegin(GL_QUADS);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glTexCoord2f(0.0f,0.0f);
      glVertex3f(level.object[count].position[0]-0.25f,level.object[count].position[1]+0.25f,0.0f);

      glTexCoord2f(1.0f,0.0f);
      glVertex3f(level.object[count].position[0]+0.25f,level.object[count].position[1]+0.25f,0.0f);

      glTexCoord2f(1.0f,1.0f);
      glVertex3f(level.object[count].position[0]+0.25f,level.object[count].position[1]-0.25f,0.0f);

      glTexCoord2f(0.0f,1.0f);
      glVertex3f(level.object[count].position[0]-0.25f,level.object[count].position[1]-0.25f,0.0f);

      glEnd();
      }
    if (level.object[count].type==9 || level.object[count].type==10)
      {
      glBindTexture(GL_TEXTURE_2D,texture[level.object[count].texturenum+256].glname);
  
      glBegin(GL_QUADS);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glTexCoord2f(0.0f,0.0f);
      glVertex3f(level.object[count].position[0]-0.5f,level.object[count].position[1]+0.5f,0.0f);

      glTexCoord2f(1.0f,0.0f);
      glVertex3f(level.object[count].position[0]+0.5f,level.object[count].position[1]+0.5f,0.0f);

      glTexCoord2f(1.0f,1.0f);
      glVertex3f(level.object[count].position[0]+0.5f,level.object[count].position[1],0.0f);

      glTexCoord2f(0.0f,1.0f);
      glVertex3f(level.object[count].position[0]-0.5f,level.object[count].position[1],0.0f);

      glEnd();
      }
    if (level.object[count].type>=20 && level.object[count].type<40)
      {
      glBindTexture(GL_TEXTURE_2D,texture[animation[level.object[count].type-20].stand[0]].glname);
  
      glBegin(GL_QUADS);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glTexCoord2f(0.0f,0.0f);
      glVertex3f(level.object[count].position[0]-level.object[count].size[0]*0.5f,level.object[count].position[1]+level.object[count].size[1]*0.5f,0.0f);

      glTexCoord2f(1.0f,0.0f);
      glVertex3f(level.object[count].position[0]+level.object[count].size[0]*0.5f,level.object[count].position[1]+level.object[count].size[1]*0.5f,0.0f);

      glTexCoord2f(1.0f,1.0f);
      glVertex3f(level.object[count].position[0]+level.object[count].size[0]*0.5f,level.object[count].position[1]-level.object[count].size[1]*0.5f,0.0f);

      glTexCoord2f(0.0f,1.0f);
      glVertex3f(level.object[count].position[0]-level.object[count].size[0]*0.5f,level.object[count].position[1]-level.object[count].size[1]*0.5f,0.0f);

      glEnd();
      }
    if (level.object[count].type==11)
      {
      glBindTexture(GL_TEXTURE_2D,texture[level.object[count].texturenum+256].glname);
  
      glBegin(GL_QUADS);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glTexCoord2f(0.0f,0.0f);
      glVertex3f(level.object[count].position[0]-0.125f,level.object[count].position[1]+0.5f,0.0f);
                                                   
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(level.object[count].position[0]+0.125f,level.object[count].position[1]+0.5f,0.0f);

      glTexCoord2f(1.0f,1.0f);
      glVertex3f(level.object[count].position[0]+0.25f,level.object[count].position[1]-0.5f,0.0f);

      glTexCoord2f(0.0f,1.0f);
      glVertex3f(level.object[count].position[0]-0.25f,level.object[count].position[1]-0.5f,0.0f);

      glEnd();
      }
    if (level.object[count].type==12)
      {
      glBindTexture(GL_TEXTURE_2D,texture[level.object[count].texturenum+256].glname);
  
      glBegin(GL_QUADS);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glTexCoord2f(0.0f,0.0f);
      glVertex3f(level.object[count].position[0]-0.5f,level.object[count].position[1]+0.25f,0.0f);
                                                   
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(level.object[count].position[0]+0.5f,level.object[count].position[1]+0.125f,0.0f);

      glTexCoord2f(1.0f,1.0f);
      glVertex3f(level.object[count].position[0]+0.5f,level.object[count].position[1]-0.125f,0.0f);

      glTexCoord2f(0.0f,1.0f);
      glVertex3f(level.object[count].position[0]-0.5f,level.object[count].position[1]-0.25f,0.0f);

      glEnd();
      }
    if (level.object[count].type==13)
      {
      glBindTexture(GL_TEXTURE_2D,texture[level.object[count].texturenum+256].glname);
  
      glBegin(GL_QUADS);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glTexCoord2f(0.0f,0.0f);
      glVertex3f(level.object[count].position[0]-0.25f,level.object[count].position[1]+0.5f,0.0f);
                                                   
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(level.object[count].position[0]+0.25f,level.object[count].position[1]+0.5f,0.0f);

      glTexCoord2f(1.0f,1.0f);
      glVertex3f(level.object[count].position[0]+0.125f,level.object[count].position[1]-0.5f,0.0f);

      glTexCoord2f(0.0f,1.0f);
      glVertex3f(level.object[count].position[0]-0.125f,level.object[count].position[1]-0.5f,0.0f);

      glEnd();
      }
    if (level.object[count].type==14)
      {
      glBindTexture(GL_TEXTURE_2D,texture[level.object[count].texturenum+256].glname);
  
      glBegin(GL_QUADS);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glTexCoord2f(0.0f,0.0f);
      glVertex3f(level.object[count].position[0]-0.5f,level.object[count].position[1]+0.125f,0.0f);
                                                   
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(level.object[count].position[0]+0.5f,level.object[count].position[1]+0.25f,0.0f);

      glTexCoord2f(1.0f,1.0f);
      glVertex3f(level.object[count].position[0]+0.5f,level.object[count].position[1]-0.25f,0.0f);

      glTexCoord2f(0.0f,1.0f);
      glVertex3f(level.object[count].position[0]-0.5f,level.object[count].position[1]-0.125f,0.0f);

      glEnd();
      }
    if (level.object[count].type==15 || level.object[count].type==16 || level.object[count].type==18)
      {
      glDisable(GL_TEXTURE_2D);
  
      glBegin(GL_LINES);

      glColor4f(1.0f,1.0f,1.0f,1.0f);

      glVertex3f(level.object[count].position[0]-level.object[count].size[0]*0.5f,level.object[count].position[1]+level.object[count].size[1]*0.5f,0.0f);
      glVertex3f(level.object[count].position[0]+level.object[count].size[0]*0.5f,level.object[count].position[1]+level.object[count].size[1]*0.5f,0.0f);

      glVertex3f(level.object[count].position[0]+level.object[count].size[0]*0.5f,level.object[count].position[1]+level.object[count].size[1]*0.5f,0.0f);
      glVertex3f(level.object[count].position[0]+level.object[count].size[0]*0.5f,level.object[count].position[1]-level.object[count].size[1]*0.5f,0.0f);

      glVertex3f(level.object[count].position[0]+level.object[count].size[0]*0.5f,level.object[count].position[1]-level.object[count].size[1]*0.5f,0.0f);
      glVertex3f(level.object[count].position[0]-level.object[count].size[0]*0.5f,level.object[count].position[1]-level.object[count].size[1]*0.5f,0.0f);

      glVertex3f(level.object[count].position[0]-level.object[count].size[0]*0.5f,level.object[count].position[1]-level.object[count].size[1]*0.5f,0.0f);
      glVertex3f(level.object[count].position[0]-level.object[count].size[0]*0.5f,level.object[count].position[1]+level.object[count].size[1]*0.5f,0.0f);

      glEnd();

      glEnable(GL_TEXTURE_2D);
      }
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);

    glColor4f(0.5f,0.5f,0.5f,1.0f);
    if (count==editor.objectnum)
      glColor4f(0.0f,1.0f,0.0f,1.0f);
    else if (editor.objectnum!=-1)
      {
      if (count==level.object[editor.objectnum].link)
        glColor4f(1.0f,0.0f,0.0f,1.0f);
      }

    vec[0]=level.object[count].position[0]-0.5f;
    vec[1]=level.object[count].position[1]+0.5f;
    vec[2]=0.0f;
    glVertex3fv(vec);

    vec[0]=level.object[count].position[0]+0.5f;
    vec[1]=level.object[count].position[1]-0.5f;
    vec[2]=0.0f;
    glVertex3fv(vec);

    vec[0]=level.object[count].position[0]+0.5f;
    vec[1]=level.object[count].position[1]+0.5f;
    vec[2]=0.0f;
    glVertex3fv(vec);

    vec[0]=level.object[count].position[0]-0.5f;
    vec[1]=level.object[count].position[1]-0.5f;
    vec[2]=0.0f;
    glVertex3fv(vec);

    glEnd();
    glEnable(GL_TEXTURE_2D);
    }

  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);

  for (count=0;count<level.numofropes;count++)
  if (level.rope[count].obj1!=-1 && level.rope[count].obj2!=-1)
    {
    if (level.rope[count].type==1)
      glColor4f(0.75f,0.75f,0.0f,1.0f);
    if (level.rope[count].type==2)
      glColor4f(1.0f,1.0f,0.0f,1.0f);
    if (level.rope[count].type==3)
      glColor4f(0.5f,0.5f,0.5f,1.0f);
    if (level.rope[count].type==4)
      glColor4f(0.75f,0.75f,0.75f,1.0f);
    if (level.rope[count].type>=5 && level.rope[count].type<10)
      glColor4f(0.75f,0.0f,0.75f,1.0f);
    if (level.rope[count].type==10)
      glColor4f(0.0f,0.75f,0.75f,1.0f);

    objectnum=level.rope[count].obj1;
    copyvector(vec,level.object[objectnum].position);
    if (level.object[objectnum].type>=2 && level.object[objectnum].type<=5)
      {
      if (level.rope[count].obj1part==0)
        {
        vec[0]-=level.object[objectnum].size[0]*0.5f;
        vec[1]+=level.object[objectnum].size[1]*0.5f;
        }
      if (level.rope[count].obj1part==1)
        {
        vec[0]+=level.object[objectnum].size[0]*0.5f;
        vec[1]+=level.object[objectnum].size[1]*0.5f;
        }
      if (level.rope[count].obj1part==2)
        {
        vec[0]+=level.object[objectnum].size[0]*0.5f;
        vec[1]-=level.object[objectnum].size[1]*0.5f;
        }
      if (level.rope[count].obj1part==3)
        {
        vec[0]-=level.object[objectnum].size[0]*0.5f;
        vec[1]-=level.object[objectnum].size[1]*0.5f;
        }
      }
    if (level.object[objectnum].type>=6 && level.object[objectnum].type<=7)
      {
      if (level.rope[count].obj1part==0)
        vec[0]+=level.object[objectnum].size[0]*0.5f;
      if (level.rope[count].obj1part==4)
        vec[1]-=level.object[objectnum].size[1]*0.5f;
      if (level.rope[count].obj1part==8)
        vec[0]-=level.object[objectnum].size[0]*0.5f;
      if (level.rope[count].obj1part==12)
        vec[1]+=level.object[objectnum].size[1]*0.5f;
      }
    glVertex3fv(vec);

    objectnum=level.rope[count].obj2;
    copyvector(vec,level.object[objectnum].position);
    if (level.object[objectnum].type>=2 && level.object[objectnum].type<=5)
      {
      if (level.rope[count].obj2part==0)
        {
        vec[0]-=level.object[objectnum].size[0]*0.5f;
        vec[1]+=level.object[objectnum].size[1]*0.5f;
        }
      if (level.rope[count].obj2part==1)
        {
        vec[0]+=level.object[objectnum].size[0]*0.5f;
        vec[1]+=level.object[objectnum].size[1]*0.5f;
        }
      if (level.rope[count].obj2part==2)
        {
        vec[0]+=level.object[objectnum].size[0]*0.5f;
        vec[1]-=level.object[objectnum].size[1]*0.5f;
        }
      if (level.rope[count].obj2part==3)
        {
        vec[0]-=level.object[objectnum].size[0]*0.5f;
        vec[1]-=level.object[objectnum].size[1]*0.5f;
        }
      }
    if (level.object[objectnum].type>=6 && level.object[objectnum].type<=7)
      {
      if (level.rope[count].obj2part==0)
        vec[0]+=level.object[objectnum].size[0]*0.5f;
      if (level.rope[count].obj2part==4)
        vec[1]-=level.object[objectnum].size[1]*0.5f;
      if (level.rope[count].obj2part==8)
        vec[0]-=level.object[objectnum].size[0]*0.5f;
      if (level.rope[count].obj2part==12)
        vec[1]+=level.object[objectnum].size[1]*0.5f;
      }
    glVertex3fv(vec);
    }

  glEnd();

  glEnable(GL_TEXTURE_2D);
  }

void deletelevelobject(int objectnum)
  {
  int count;

  if (objectnum<0)
    return;
  if (objectnum>=level.numofobjects)
    return;

  if (editor.objectnum==objectnum)
    editor.objectnum=-1;

  for (count=0;count<level.numofropes;count++)
    {
    while (count<level.numofropes && (level.rope[count].obj1==objectnum || level.rope[count].obj2==objectnum))
      deletelevelrope(count);
    }
  for (count=0;count<level.numofobjects;count++)
    if (level.object[count].link==objectnum)
      level.object[count].link=-1;

  level.numofobjects--;

  if (objectnum==level.numofobjects)
    return;

  memcpy(&level.object[objectnum],&level.object[level.numofobjects],sizeof(level.object[objectnum]));

  if (editor.objectnum==level.numofobjects)
    editor.objectnum=objectnum;

  for (count=0;count<level.numofropes;count++)
    {
    if (level.rope[count].obj1==level.numofobjects)
      level.rope[count].obj1=objectnum;
    if (level.rope[count].obj2==level.numofobjects)
      level.rope[count].obj2=objectnum;
    }
  for (count=0;count<level.numofobjects;count++)
    if (level.object[count].link==level.numofobjects)
      level.object[count].link=objectnum;
  }

void deletelevelrope(int ropenum)
  {
  if (ropenum<0)
    return;
  if (ropenum>=level.numofropes)
    return;

  level.numofropes--;

  if (ropenum==level.numofropes)
    return;

  memcpy(&level.rope[ropenum],&level.rope[level.numofropes],sizeof(level.rope[ropenum]));
  }
