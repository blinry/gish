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

void editlevel(void)
  {
  int count,count2;
  int x,y;
  int simtimer;
  int simcount;
  float vec[3];

  simtimer=SDL_GetTicks();

  resetmenuitems();

  joystickmenu=0;

  editor.active=1;

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
    setmenuitem(MO_HOTKEY,SCAN_F1);
    createmenuitem(TXT_LEVELNAME"     ",(640|TEXT_END),448,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_STRINGINPUT,editor.filename);
    setmenuitem(MO_HOTKEY,SCAN_ENTER);
    createmenuitem(TXT_GAMETYPE,(640|TEXT_END),0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_INTINPUT,&level.gametype);
    createmenuitem(TXT_GAMETIME,(640|TEXT_END),32,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_INTINPUT,&level.time);
    createmenuitem(TXT_RED"  ",(640|TEXT_END),64,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_FLOATINPUT,&level.ambient[editor.mode][0]);
    createmenuitem(TXT_GREEN,(640|TEXT_END),96,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_FLOATINPUT,&level.ambient[editor.mode][1]);
    createmenuitem(TXT_BLUE" ",(640|TEXT_END),128,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_FLOATINPUT,&level.ambient[editor.mode][2]);
    createmenuitem(TXT_BACKGROUND"     ",(640|TEXT_END),416,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_STRINGINPUT,&level.background);

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

    setuprenderobjects();

    scalevector(level.ambient[editor.mode],level.ambient[editor.mode],2.0f);

    if (!editor.showgrid)
      rendershadows();

    if (!editor.showgrid || editor.mode==0)
      renderlevelback();
    if (!editor.showgrid || editor.mode==1)
      renderlevel();
    renderobjects();
    if (!editor.showgrid || editor.mode==2)
      renderlevelfore();

    scalevector(level.ambient[editor.mode],level.ambient[editor.mode],0.5f);

    if (editor.showlines)
      renderlevellines();

    rendereditblocks();

    glDisable(GL_TEXTURE_2D);

    for (count=0;count<8;count++)
      {
      glBegin(GL_LINES);

      if (count==0)
        glColor4f(0.0f,1.0f,0.0f,1.0f);
      if (count==1)
        glColor4f(0.0f,1.0f,1.0f,1.0f);
      if (count==2)
        glColor4f(1.0f,1.0f,0.0f,1.0f);
      if (count==3)
        glColor4f(1.0f,0.0f,1.0f,1.0f);
      if (count==4)
        glColor4f(0.0f,0.5f,0.0f,1.0f);
      if (count==5)
        glColor4f(0.0f,0.5f,0.5f,1.0f);
      if (count==6)
        glColor4f(0.5f,0.5f,0.0f,1.0f);
      if (count==7)
        glColor4f(0.5f,0.0f,0.5f,1.0f);
  
      glVertex3f(level.area[count][0],level.area[count][1],0.0f);
      glVertex3f(level.area[count][2],level.area[count][1],0.0f);

      glVertex3f(level.area[count][2],level.area[count][1],0.0f);
      glVertex3f(level.area[count][2],level.area[count][3],0.0f);

      glVertex3f(level.area[count][2],level.area[count][3],0.0f);
      glVertex3f(level.area[count][0],level.area[count][3],0.0f);

      glVertex3f(level.area[count][0],level.area[count][3],0.0f);
      glVertex3f(level.area[count][0],level.area[count][1],0.0f);

      glEnd();
      }
    glEnable(GL_TEXTURE_2D);

    setuptextdisplay();

    glBindTexture(GL_TEXTURE_2D,texture[editor.blocknum].glname);

    glBegin(GL_QUADS);

    glColor4f(1.0f,1.0f,1.0f,1.0f);

    vec[0]=0.0f;
    vec[1]=416.0f;
    convertscreenvertex(vec,font.sizex,font.sizey);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(vec[0],vec[1],-1.0f);

    vec[0]=64.0f;
    vec[1]=416.0f;
    convertscreenvertex(vec,font.sizex,font.sizey);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(vec[0],vec[1],-1.0f);

    vec[0]=64.0f;
    vec[1]=480.0f;
    convertscreenvertex(vec,font.sizex,font.sizey);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(vec[0],vec[1],-1.0f);

    vec[0]=0.0f;
    vec[1]=480.0f;
    convertscreenvertex(vec,font.sizex,font.sizey);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(vec[0],vec[1],-1.0f);

    glEnd();

    if (editor.mode==0)
      drawtext(TXT_BACKGROUND,0,384,16,1.0f,1.0f,1.0f,1.0f);
    if (editor.mode==1)
      drawtext(TXT_MIDGROUND,0,384,16,1.0f,1.0f,1.0f,1.0f);
    if (editor.mode==2)
      drawtext(TXT_FOREGROUND,0,384,16,1.0f,1.0f,1.0f,1.0f);
    if (editor.mode==3)
      drawtext(TXT_WAYBACKGROUND,0,384,16,1.0f,1.0f,1.0f,1.0f);
    drawtext(TXT_TILESET":/i",0,368,16,1.0f,1.0f,1.0f,1.0f,level.tileset);
    drawtext(TXT_TILE":/i",0,400,16,1.0f,1.0f,1.0f,1.0f,editor.blocknum);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (!menuinputkeyboard)
      {
      if (keyboard[SCAN_L] && !prevkeyboard[SCAN_L])
        editor.showlines^=1;
      if (keyboard[SCAN_K] && !prevkeyboard[SCAN_K])
        editor.showgrid^=1;

      x=view.position[0]+(float)(mouse.x-320)/32.0f;
      y=view.position[1]+(float)(240-mouse.y)/32.0f;
  
      if (!editor.paste)
        {
        if (!keyboard[SCAN_SHIFT])
          {
          if (mouse.lmb)
            setblock(x,y,editor.blocknum);
          if (mouse.rmb && (editor.editstart[0]==0 && editor.editstart[1]==0))
            setblock(x,y,0);
          }
        else
          {
          if (mouse.lmb && !prevmouse.lmb)
            {
            editor.editstart[0]=x;
            editor.editstart[1]=y;
            }
          if (mouse.lmb && (editor.editstart[0]!=0 || editor.editstart[1]!=0))
            {
            if (editor.editstart[0]<x)
              {
              editor.editarea[0][0]=editor.editstart[0];
              editor.editarea[1][0]=x;
              }
            else
              {
              editor.editarea[0][0]=x;
              editor.editarea[1][0]=editor.editstart[0];
              }
            if (editor.editstart[1]<y)
              {
              editor.editarea[0][1]=editor.editstart[1];
              editor.editarea[1][1]=y;
              }
            else
              {
              editor.editarea[0][1]=y;
              editor.editarea[1][1]=editor.editstart[1];
              }
            }
          }
        if (editor.editstart[0]!=0 || editor.editstart[1]!=0)
          {
          count=-1;
          if (keyboard[SCAN_5])
            count=0;
          if (keyboard[SCAN_6])
            count=1;
          if (keyboard[SCAN_7])
            count=2;
          if (keyboard[SCAN_8])
            count=3;
          if (count!=-1)
            {
            if (keyboard[SCAN_SHIFT])
              count+=4;

            level.area[count][0]=editor.editarea[0][0];
            level.area[count][1]=editor.editarea[0][1];
            level.area[count][2]=editor.editarea[1][0]+1.0f;
            level.area[count][3]=editor.editarea[1][1]+1.0f;
            }
          }
        if (keyboard[SCAN_ESC] || (!mouse.rmb && prevmouse.rmb))
          {
          editor.editstart[0]=0;
          editor.editstart[1]=0;
          editor.editarea[0][0]=0;
          editor.editarea[0][1]=0;
          editor.editarea[1][0]=0;
          editor.editarea[1][1]=0;
          }
        if (keyboard[SCAN_C] && !prevkeyboard[SCAN_C])
          {
          editor.copysize[0]=editor.editarea[1][0]-editor.editarea[0][0];
          editor.copysize[1]=editor.editarea[1][1]-editor.editarea[0][1];
          for (count=0;count<=editor.copysize[1];count++)
          for (count2=0;count2<=editor.copysize[0];count2++)
            editor.copybuffer[count][count2]=getblock(editor.editarea[0][0]+count2,editor.editarea[0][1]+count);
    
          editor.paste=1;
          editor.editstart[0]=0;
          editor.editstart[1]=0;
          editor.editarea[0][0]=0;
          editor.editarea[0][1]=0;
          editor.editarea[1][0]=0;
          editor.editarea[1][1]=0;
          }
        if (keyboard[SCAN_DELETE] && !prevkeyboard[SCAN_DELETE])
          {
          editor.copysize[0]=editor.editarea[1][0]-editor.editarea[0][0];
          editor.copysize[1]=editor.editarea[1][1]-editor.editarea[0][1];
          for (count=0;count<=editor.copysize[1];count++)
          for (count2=0;count2<=editor.copysize[0];count2++)
            setblock(editor.editarea[0][0]+count2,editor.editarea[0][1]+count,0);
          }
        if (keyboard[SCAN_B] && !prevkeyboard[SCAN_B])
          {
          editor.copysize[0]=editor.editarea[1][0]-editor.editarea[0][0];
          editor.copysize[1]=editor.editarea[1][1]-editor.editarea[0][1];
          for (count=0;count<=editor.copysize[1];count++)
          for (count2=0;count2<=editor.copysize[0];count2++)
            setblock(editor.editarea[0][0]+count2,editor.editarea[0][1]+count,editor.blocknum);
          }
        if (keyboard[SCAN_V] && !prevkeyboard[SCAN_V])
          editor.paste=1;
        }
      else
        {
        if (mouse.lmb && !prevmouse.lmb)
          {
          for (count=0;count<=editor.copysize[1];count++)
          for (count2=0;count2<=editor.copysize[0];count2++)
            setblock(x+count2,y+count,editor.copybuffer[count][count2]);
          }
        if (keyboard[SCAN_ESC] || (!mouse.rmb && prevmouse.rmb))
          editor.paste=0;
        }
      if (keyboard[SCAN_G])
        editor.blocknum=getblock(x,y);
      if (keyboard[SCAN_Q] && !prevkeyboard[SCAN_Q])
        {
        if (!keyboard[SCAN_SHIFT])
          editor.blocknum++;
        else
          editor.blocknum+=10;
        if (editor.blocknum>255)
          editor.blocknum=255;
        }
      if (keyboard[SCAN_Z] && !prevkeyboard[SCAN_Z])
        {
        if (!keyboard[SCAN_SHIFT])
          editor.blocknum--;
        else
          editor.blocknum-=10;
        if (editor.blocknum<0)
          editor.blocknum=0;
        }

      if (keyboard[SCAN_LFT_BRACKET] && !prevkeyboard[SCAN_LFT_BRACKET])
      if (level.tileset>0)
        level.tileset--;
      if (keyboard[SCAN_RGT_BRACKET] && !prevkeyboard[SCAN_RGT_BRACKET])
      if (level.tileset<7)
        level.tileset++;
  
      if (keyboard[SCAN_1])
        editor.mode=0;
      if (keyboard[SCAN_2])
        editor.mode=1;
      if (keyboard[SCAN_3])
        editor.mode=2;
      if (keyboard[SCAN_4])
        editor.mode=3;
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
    if (!menuinputkeyboard)
      {
      if (keyboard[SCAN_F7] && !prevkeyboard[SCAN_F7])
        {
        loadlevel(editor.filename);
        setuplevel();
        setupgame();
        }
      if (keyboard[SCAN_F5] && !prevkeyboard[SCAN_F5])
        {
        setuplevel();
        setupgame();
        }
      if (keyboard[SCAN_F9] && !prevkeyboard[SCAN_F9])
        savelevel(editor.filename);
      if (keyboard[SCAN_F2] && !prevkeyboard[SCAN_F2])
        {
        editblock();
        simtimer=SDL_GetTicks();
        }
      if (keyboard[SCAN_F3] && !prevkeyboard[SCAN_F3])
        {
        editlevelobjects();
        simtimer=SDL_GetTicks();
        }
      if (keyboard[SCAN_F4] && !prevkeyboard[SCAN_F4])
        {
        editlevelrope();
        simtimer=SDL_GetTicks();
        }
      if (keyboard[SCAN_T] && !prevkeyboard[SCAN_T])
        {
        edittextures();
        simtimer=SDL_GetTicks();
        }
      }
    }

  editor.active=0;

  joystickmenu=1;

  resetmenuitems();
  }

void setblock(int x,int y,int blocknum)
  {
  if (x<0)
    return;
  if (x>=256)
    return;
  if (y<0)
    return;
  if (y>=256)
    return;

  if (editor.mode==0)
    level.backgrid[y][x]=blocknum;
  if (editor.mode==1)
    level.grid[y][x]=blocknum;
  if (editor.mode==2)
    level.foregrid[y][x]=blocknum;

  setuplevellines(x-1,y-1,x+1,y+1);
  }

int getblock(int x,int y)
  {
  int blocknum;

  if (x<0)
    return(0);
  if (x>=256)
    return(0);
  if (y<0)
    return(0);
  if (y>=256)
    return(0);

  if (editor.mode==0)
    blocknum=level.backgrid[y][x];
  if (editor.mode==1)
    blocknum=level.grid[y][x];
  if (editor.mode==2)
    blocknum=level.foregrid[y][x];

  return(blocknum);
  }

void rendereditblocks(void)
  {
  int count,count2;
  int x,y;
  int blocknum;
  float vec[3];

  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);

  glColor4f(1.0f,1.0f,1.0f,1.0f);

  if (!editor.paste)
    {
    for (count=editor.editarea[0][1];count<=editor.editarea[1][1];count++)
    for (count2=editor.editarea[0][0];count2<=editor.editarea[1][0];count2++)
      {
      glVertex3f((float)count2+0.0f,(float)count+1.0f,0.0f);
      glVertex3f((float)count2+1.0f,(float)count+1.0f,0.0f);
  
      glVertex3f((float)count2+1.0f,(float)count+1.0f,0.0f);
      glVertex3f((float)count2+1.0f,(float)count+0.0f,0.0f);
  
      glVertex3f((float)count2+1.0f,(float)count+0.0f,0.0f);
      glVertex3f((float)count2+0.0f,(float)count+0.0f,0.0f);
  
      glVertex3f((float)count2+0.0f,(float)count+0.0f,0.0f);
      glVertex3f((float)count2+0.0f,(float)count+1.0f,0.0f);
      }
    }
  else
    {
    x=view.position[0]+(float)(mouse.x-320)/32.0f;
    y=view.position[1]+(float)(240-mouse.y)/32.0f;

    for (count=0;count<=editor.copysize[1];count++)
    for (count2=0;count2<=editor.copysize[0];count2++)
      {
      glVertex3f((float)(x+count2)+0.0f,(float)(y+count)+1.0f,0.0f);
      glVertex3f((float)(x+count2)+1.0f,(float)(y+count)+1.0f,0.0f);
  
      glVertex3f((float)(x+count2)+1.0f,(float)(y+count)+1.0f,0.0f);
      glVertex3f((float)(x+count2)+1.0f,(float)(y+count)+0.0f,0.0f);
  
      glVertex3f((float)(x+count2)+1.0f,(float)(y+count)+0.0f,0.0f);
      glVertex3f((float)(x+count2)+0.0f,(float)(y+count)+0.0f,0.0f);
  
      glVertex3f((float)(x+count2)+0.0f,(float)(y+count)+0.0f,0.0f);
      glVertex3f((float)(x+count2)+0.0f,(float)(y+count)+1.0f,0.0f);
      }
    }
  glEnd();

  glEnable(GL_TEXTURE_2D);
  }

void editblock(void)
  {
  int count,count2,count3;
  int x,y;
  int simtimer;
  int simcount;
  float friction;
  float vec[3],vec2[3];
  float normal[3];
  char filename[13]="text000.tga";
  int changeddir;

  /*
  changeddir=changetilesetdir();

  filename[4]=48+(editor.blocknum/100)%10;
  filename[5]=48+(editor.blocknum/10)%10;
  filename[6]=48+editor.blocknum%10;
  loadtexturetga(999,filename,0,GL_CLAMP,GL_CLAMP,GL_NEAREST,GL_NEAREST);

  if (changeddir==0)
    chdir("..");
  */

  copytexture(999,editor.blocknum);
  texture[999].magfilter=GL_NEAREST;
  texture[999].minfilter=GL_NEAREST;
  setuptexture(999);

  simtimer=SDL_GetTicks();

  friction=1.0f;

  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_EXIT,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    count=32;
    createmenuitem(TXT_FRICTION,(640|TEXT_END),count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_FLOATINPUT,&block[editor.blocknum].friction);
    setmenuitem(MO_HOTKEY,SCAN_F);
    count+=32;
    createmenuitem(TXT_BREAKPOINT,(640|TEXT_END),count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_FLOATINPUT,&block[editor.blocknum].breakpoint);
    setmenuitem(MO_HOTKEY,SCAN_B);
    count+=32;
    createmenuitem(TXT_MIDDAMAGE,(640|TEXT_END),count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_INTINPUT,&block[editor.blocknum].middamage);
    setmenuitem(MO_HOTKEY,SCAN_M);
    count+=32;
    createmenuitem(TXT_FOREDAMAGE,(640|TEXT_END),count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_INTINPUT,&block[editor.blocknum].foredamage);
    setmenuitem(MO_HOTKEY,SCAN_O);
    count+=32;
    createmenuitem(TXT_DENSITY,(640|TEXT_END),count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_FLOATINPUT,&block[editor.blocknum].density);
    setmenuitem(MO_HOTKEY,SCAN_D);
    count+=32;
    createmenuitem(TXT_DRAG"   ",(640|TEXT_END),count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_FLOATINPUT,&block[editor.blocknum].drag);
    setmenuitem(MO_HOTKEY,SCAN_R);
    count+=32;
    createmenuitem(TXT_ANIMATION,(640|TEXT_END),count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_INTINPUT,&block[editor.blocknum].animation);
    setmenuitem(MO_HOTKEY,SCAN_N);
    count+=32;
    createmenuitem(TXT_ANIMATESPD,(640|TEXT_END),count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_INTINPUT,&block[editor.blocknum].animationspeed);
    setmenuitem(MO_HOTKEY,SCAN_S);
    count+=32;

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkmenuitems();

    if (!menuinputkeyboard)
      {
      if (keyboard[SCAN_DELETE] && !prevkeyboard[SCAN_DELETE])
      if (block[editor.blocknum].numoflines>0)
        block[editor.blocknum].numoflines--;
      }
    if (mouse.x<464)
      {
      if (mouse.lmb && !prevmouse.lmb)
        {
        x=(mouse.x+6-32)/12;
        y=(mouse.y+6-32)/12;
        if (x<0)
          x=0;
        if (y<0)
          y=0;
        if (x>32)
          x=32;
        if (y>32)
          y=32;
        vec[0]=(float)x/32.0f;
        vec[1]=1.0f-(float)y/32.0f;
  
        block[editor.blocknum].line[block[editor.blocknum].numoflines][0]=vec[0];
        block[editor.blocknum].line[block[editor.blocknum].numoflines][1]=vec[1];
        }
      x=abs(mouse.x+6-32)/12;
      y=abs(mouse.y+6-32)/12;
      if (x<0)
        x=0;
      if (y<0)
        y=0;
      if (x>32)
        x=32;
      if (y>32)
        y=32;
      vec[0]=(float)x/32.0f;
      vec[1]=1.0f-(float)y/32.0f;
  
      block[editor.blocknum].line[block[editor.blocknum].numoflines][2]=vec[0];
      block[editor.blocknum].line[block[editor.blocknum].numoflines][3]=vec[1];
      block[editor.blocknum].line[block[editor.blocknum].numoflines][4]=friction;
      if (!mouse.lmb && prevmouse.lmb)
      if (block[editor.blocknum].line[block[editor.blocknum].numoflines][0]!=block[editor.blocknum].line[block[editor.blocknum].numoflines][2] || block[editor.blocknum].line[block[editor.blocknum].numoflines][1]!=block[editor.blocknum].line[block[editor.blocknum].numoflines][3])
        block[editor.blocknum].numoflines++;
      }

    setupblockflags(editor.blocknum);

    setuptextdisplay();

    glDisable(GL_TEXTURE_2D);
  
    glBegin(GL_LINES);


    glColor4f(0.0f,1.0f,0.0f,1.0f);

    for (count=0;count<=4;count++)
      {
      vec[0]=16.0f;
      vec[1]=32.0f+96.0f*(float)count;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glVertex3f(vec[0],vec[1],-1.0f);
  
      vec[0]=32.0f+400.0f;
      vec[1]=32.0f+96.0f*(float)count;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=32.0f+96.0f*(float)count;
      vec[1]=16.0f;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glVertex3f(vec[0],vec[1],-1.0f);
  
      vec[0]=32.0f+96.0f*(float)count;
      vec[1]=32.0f+400.0f;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glVertex3f(vec[0],vec[1],-1.0f);
      }
    glEnd();
  
    glEnable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D,texture[999].glname);

    glBegin(GL_QUADS);

    glColor4f(1.0f,1.0f,1.0f,1.0f);

    vec[0]=32.0f;
    vec[1]=32.0f;
    convertscreenvertex(vec,font.sizex,font.sizey);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(vec[0],vec[1],-1.0f);

    vec[0]=32.0f+384.0f;
    vec[1]=32.0f;
    convertscreenvertex(vec,font.sizex,font.sizey);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(vec[0],vec[1],-1.0f);

    vec[0]=32.0f+384.0f;
    vec[1]=32.0f+384.0f;
    convertscreenvertex(vec,font.sizex,font.sizey);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(vec[0],vec[1],-1.0f);

    vec[0]=32.0f;
    vec[1]=32.0f+384.0f;
    convertscreenvertex(vec,font.sizex,font.sizey);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(vec[0],vec[1],-1.0f);

    glEnd();


    glDisable(GL_TEXTURE_2D);
  
    glBegin(GL_LINES);
  
    if (mouse.x<464)
    if (mouse.lmb)
      block[editor.blocknum].numoflines++;

    for (count=0;count<block[editor.blocknum].numoflines;count++)
      {
      glColor4f(1.0f,0.0f,0.0f,1.0f);

      vec[0]=32.0f+block[editor.blocknum].line[count][0]*384.0f;
      vec[1]=32.0f+384.0f-block[editor.blocknum].line[count][1]*384.0f;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glVertex3f(vec[0],vec[1],-1.0f);

      glColor4f(0.0f,0.0f,1.0f,1.0f);

      vec[0]=32.0f+block[editor.blocknum].line[count][2]*384.0f;
      vec[1]=32.0f+384.0f-block[editor.blocknum].line[count][3]*384.0f;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glVertex3f(vec[0],vec[1],-1.0f);
      }

    if (mouse.x<464)
    if (mouse.lmb)
      block[editor.blocknum].numoflines--;

    glEnd();
  
    glEnable(GL_TEXTURE_2D);

    drawtext(TXT_LINES":/i",0,432,12,1.0f,1.0f,1.0f,1.0f,block[editor.blocknum].numoflines);
    drawtext(TXT_ALPHA":/i",0,448,12,1.0f,1.0f,1.0f,1.0f,texture[editor.blocknum].isalpha);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (keyboard[SCAN_A] && !prevkeyboard[SCAN_A])
      {
      for (count=0;count<texture[editor.blocknum].sizey;count++)
      for (count2=0;count2<texture[editor.blocknum].sizex;count2++)
      if (!bigendian)
        texture[editor.blocknum].rgba[0][count*texture[editor.blocknum].sizex+count2]&=0xFFFFFF;
      else
        texture[editor.blocknum].rgba[0][count*texture[editor.blocknum].sizex+count2]&=0xFFFFFF00;

      setupblockalpha(editor.blocknum);

      texture[editor.blocknum].isalpha=0;
      for (count=0;count<texture[editor.blocknum].sizey;count++)
      for (count2=0;count2<texture[editor.blocknum].sizex;count2++)
        {
        if (!bigendian)
        if ((texture[editor.blocknum].rgba[0][count*texture[editor.blocknum].sizex+count2]&0xFF000000)!=0xFF000000)
          texture[editor.blocknum].isalpha=1;
  
        if (bigendian)
        if ((texture[editor.blocknum].rgba[0][count*texture[editor.blocknum].sizex+count2]&0x000000FF)!=0x000000FF)
          texture[editor.blocknum].isalpha=1;
        }

      /*
      texture[editor.blocknum].isalpha=0;

      for (count=0;count<texture[editor.blocknum].sizey;count++)
      for (count2=0;count2<texture[editor.blocknum].sizex;count2++)
        {
        texture[editor.blocknum].rgba[0][count*texture[editor.blocknum].sizex+count2]|=0xFF000000;

        for (count3=0;count3<block[editor.blocknum].numoflines;count3++)
          {
          vec[0]=((float)count2+0.5f)/(float)texture[editor.blocknum].sizex;
          vec[1]=1.0f-((float)count+0.5f)/(float)texture[editor.blocknum].sizey;
          vec[2]=0.0f;
          vec[0]-=block[editor.blocknum].line[count3][0];
          vec[1]-=block[editor.blocknum].line[count3][1];
          vec2[0]=block[editor.blocknum].line[count3][2]-block[editor.blocknum].line[count3][0];
          vec2[1]=block[editor.blocknum].line[count3][3]-block[editor.blocknum].line[count3][1];
          vec2[2]=0.0f;
          crossproduct(normal,vec,vec2);
          if (normal[2]>0.0f)
            {
            texture[editor.blocknum].rgba[0][count*texture[editor.blocknum].sizex+count2]&=0xFFFFFF;
            texture[editor.blocknum].isalpha=1;
            }
          }
        }
      */

      setuptexture(editor.blocknum);

      memcpy(texture[999].rgba[0],texture[editor.blocknum].rgba[0],texture[editor.blocknum].sizex*texture[editor.blocknum].sizey*4);
      setuptexture(999);
      }

    if (keyboard[SCAN_Q] && !prevkeyboard[SCAN_Q])
      {
      if (!keyboard[SCAN_SHIFT])
        editor.blocknum++;
      else
        editor.blocknum+=10;
      if (editor.blocknum>255)
        editor.blocknum=255;

      copytexture(999,editor.blocknum);
      texture[999].magfilter=GL_NEAREST;
      texture[999].minfilter=GL_NEAREST;
      setuptexture(999);
      /*
      changeddir=changetilesetdir();
    
      filename[4]=48+(editor.blocknum/100)%10;
      filename[5]=48+(editor.blocknum/10)%10;
      filename[6]=48+editor.blocknum%10;
      loadtexturetga(999,filename,0,GL_CLAMP,GL_CLAMP,GL_NEAREST,GL_NEAREST);
    
      if (changeddir==0)
        chdir("..");
      */
      }
    if (keyboard[SCAN_Z] && !prevkeyboard[SCAN_Z])
      {
      if (!keyboard[SCAN_SHIFT])
        editor.blocknum--;
      else
        editor.blocknum-=10;
      if (editor.blocknum<0)
        editor.blocknum=0;

      copytexture(999,editor.blocknum);
      texture[999].magfilter=GL_NEAREST;
      texture[999].minfilter=GL_NEAREST;
      setuptexture(999);

      /*
      changeddir=changetilesetdir();
    
      filename[4]=48+(editor.blocknum/100)%10;
      filename[5]=48+(editor.blocknum/10)%10;
      filename[6]=48+editor.blocknum%10;
      loadtexturetga(999,filename,0,GL_CLAMP,GL_CLAMP,GL_NEAREST,GL_NEAREST);
    
      if (changeddir==0)
        chdir("..");
      */
      }
    /*
    if (keyboard[SCAN_F4] && !prevkeyboard[SCAN_F4])
      {
      changeddir=changetilesetdir();
      loadblock(editor.blocknum);

      if (changeddir==0)
        chdir("..");
      }
    if (keyboard[SCAN_F9] && !prevkeyboard[SCAN_F9])
      {
      changeddir=changetilesetdir();
      saveblock(editor.blocknum);

      if (changeddir==0)
        chdir("..");
      }
    */

    simcount=0;
    while (SDL_GetTicks()-simtimer>20 && simcount<5)
      {
      simcount++;
      count=SDL_GetTicks()-simtimer-20;
      simtimer=SDL_GetTicks()-count;
      }
    }

  resetmenuitems();
  }

void renderlevellines(void)
  {
  int count,count2,count3;
  int blocknum;
  float vec[3];

  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);

  glColor4f(0.0f,0.0f,1.0f,1.0f);

  for (count=view.position[1]-32;count<view.position[1]+32;count++)
  if (count>=0 && count<256)
  for (count2=view.position[0]-32;count2<view.position[0]+32;count2++)
  if (count2>=0 && count2<256)
    {
    blocknum=level.grid[count][count2];
    for (count3=0;count3<block[blocknum].numoflines;count3++)
    if (((level.gridflags[count][count2]>>count3)&1)==0)
      {
      vec[0]=(float)count2+block[blocknum].line[count3][0];
      vec[1]=(float)count+block[blocknum].line[count3][1];
      glVertex3f(vec[0],vec[1],0.0f);

      vec[0]=(float)count2+block[blocknum].line[count3][2];
      vec[1]=(float)count+block[blocknum].line[count3][3];
      glVertex3f(vec[0],vec[1],0.0f);
      }
    }

  glEnd();

  glEnable(GL_TEXTURE_2D);
  }
