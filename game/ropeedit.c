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

void editlevelrope(void)
  {
  int count,count2;
  int simtimer;
  int simcount;
  float vec[3],vec2[3];

  ropeedit.numofpoints=0;
  for (count=0;count<level.numofobjects;count++)
    {
    if (level.object[count].type>=2 && level.object[count].type<=5)
      {
      for (count2=0;count2<4;count2++)
        {
        if (count2==0 || count2==3)
          vec[0]=level.object[count].position[0]-level.object[count].size[0]*0.5f;
        else
          vec[0]=level.object[count].position[0]+level.object[count].size[0]*0.5f;
        if (count2<2)
          vec[1]=level.object[count].position[1]+level.object[count].size[1]*0.5f;
        else
          vec[1]=level.object[count].position[1]-level.object[count].size[1]*0.5f;
        vec[2]=0.0f;
        copyvector(ropeedit.point[ropeedit.numofpoints].position,vec);
        ropeedit.point[ropeedit.numofpoints].objectnum=count;
        ropeedit.point[ropeedit.numofpoints].particlenum=count2;
        ropeedit.numofpoints++;

        copyvector(level.object[count].vertex[count2],vec);
        }
      }
    if (level.object[count].type>=6 && level.object[count].type<=7)
      {
      for (count2=0;count2<4;count2++)
        {
        vec[0]=level.object[count].position[0];
        vec[1]=level.object[count].position[1];
        if (count2==0)
          vec[0]=level.object[count].position[0]+level.object[count].size[0]*0.5f;
        if (count2==1)
          vec[1]=level.object[count].position[1]-level.object[count].size[1]*0.5f;
        if (count2==2)
          vec[0]=level.object[count].position[0]-level.object[count].size[0]*0.5f;
        if (count2==3)
          vec[1]=level.object[count].position[1]+level.object[count].size[1]*0.5f;
        vec[2]=0.0f;
        copyvector(ropeedit.point[ropeedit.numofpoints].position,vec);
        ropeedit.point[ropeedit.numofpoints].objectnum=count;
        ropeedit.point[ropeedit.numofpoints].particlenum=count2*4;
        ropeedit.numofpoints++;

        copyvector(level.object[count].vertex[count2],vec);
        }

      count2=4;
      vec[0]=level.object[count].position[0];
      vec[1]=level.object[count].position[1];
      vec[2]=0.0f;

      copyvector(ropeedit.point[ropeedit.numofpoints].position,vec);
      ropeedit.point[ropeedit.numofpoints].objectnum=count;
      ropeedit.point[ropeedit.numofpoints].particlenum=16;
      ropeedit.numofpoints++;

      copyvector(level.object[count].vertex[count2],vec);
      }
    if (level.object[count].type==8)
      {
      vec[0]=level.object[count].position[0];
      vec[1]=level.object[count].position[1];
      vec[2]=0.0f;
      copyvector(ropeedit.point[ropeedit.numofpoints].position,vec);
      ropeedit.point[ropeedit.numofpoints].objectnum=count;
      ropeedit.point[ropeedit.numofpoints].particlenum=0;
      ropeedit.numofpoints++;
      copyvector(level.object[count].vertex[0],vec);
      }
    }
  ropeedit.pointnum=-1;

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

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkmenuitems();

    //setupperspectiveviewport(0,0,640,480,1.0f,100.0f);
    setuporthoviewport(0,0,640,480,10.0f,7.5f,20.0f);
    setupviewpoint(view.position,view.orientation);

    setupframelighting();

    rendershadows();

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER,0.0f);

    renderlevelback();
    renderlevel();
    renderlevelobjects();
    renderlevelfore();

    glDisable(GL_ALPHA_TEST);

    renderropeedit();

    setuptextdisplay();

    drawtext(TXT_NUMOFROPES":/i",0,368,16,1.0f,1.0f,1.0f,1.0f,level.numofropes);
    drawtext(TXT_TEXTURENUM":/i",0,384,16,1.0f,1.0f,1.0f,1.0f,ropeedit.texturenum);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    vec[0]=view.position[0]+(float)(mouse.x-320)/32.0f;
    vec[1]=view.position[1]+(float)(240-mouse.y)/32.0f;
    vec[2]=0.0f;

    ropeedit.pointhighlight=-1;
    for (count=0;count<ropeedit.numofpoints;count++)
      {
      subtractvectors(vec2,ropeedit.point[count].position,vec);
      if (vectorlength(vec2)<0.25f)
        ropeedit.pointhighlight=count;
      }

    if (ropeedit.pointnum==-1)
      {
      if (mouse.lmb && !prevmouse.lmb)
      if (ropeedit.pointhighlight!=-1)
        ropeedit.pointnum=ropeedit.pointhighlight;
      }
    else
      {
      if (mouse.lmb && !prevmouse.lmb)
        {
        if (ropeedit.pointhighlight!=-1)
        if (ropeedit.point[ropeedit.pointnum].objectnum!=ropeedit.point[ropeedit.pointhighlight].objectnum)
          {
          level.rope[level.numofropes].type=1;
          if (keyboard[SCAN_2])
            level.rope[level.numofropes].type=2;
          if (keyboard[SCAN_3])
            level.rope[level.numofropes].type=3;
          if (keyboard[SCAN_4])
            level.rope[level.numofropes].type=4;
          if (keyboard[SCAN_5])
            level.rope[level.numofropes].type=5;
          if (keyboard[SCAN_6])
            level.rope[level.numofropes].type=6;
          if (keyboard[SCAN_7])
            level.rope[level.numofropes].type=7;
          if (keyboard[SCAN_8])
            level.rope[level.numofropes].type=8;
          if (keyboard[SCAN_9])
            level.rope[level.numofropes].type=9;
          if (keyboard[SCAN_0])
            level.rope[level.numofropes].type=10;
          level.rope[level.numofropes].obj1=ropeedit.point[ropeedit.pointnum].objectnum;
          level.rope[level.numofropes].obj1part=ropeedit.point[ropeedit.pointnum].particlenum;
  
          level.rope[level.numofropes].obj2=ropeedit.point[ropeedit.pointhighlight].objectnum;
          level.rope[level.numofropes].obj2part=ropeedit.point[ropeedit.pointhighlight].particlenum;
          level.rope[level.numofropes].texturenum=ropeedit.texturenum;
  
          level.numofropes++;
          }
        ropeedit.pointnum=-1;
        }
      }

    if (mouse.rmb && !prevmouse.rmb)
      {
      for (count=0;count<level.numofropes;count++)
        {
        if (ropeedit.point[ropeedit.pointhighlight].objectnum==level.rope[count].obj1 && ropeedit.point[ropeedit.pointhighlight].particlenum==level.rope[count].obj1part)
          deletelevelrope(count);
        }
      for (count=0;count<level.numofropes;count++)
        {
        if (ropeedit.point[ropeedit.pointhighlight].objectnum==level.rope[count].obj2 && ropeedit.point[ropeedit.pointhighlight].particlenum==level.rope[count].obj2part)
          deletelevelrope(count);
        }
      /*
      for (count=0;count<level.numofropes;count++)
        {
        if (pointintersectline(vec,level.object[level.rope[count].obj1].vertex[level.rope[count].obj1part],level.object[level.rope[count].obj2].vertex[level.rope[count].obj2part],0.25f))
          deletelevelrope(count);
        }
      */
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

    if (keyboard[SCAN_Q] && !prevkeyboard[SCAN_Q])
    if (ropeedit.texturenum<3)
      ropeedit.texturenum++;

    if (keyboard[SCAN_Z] && !prevkeyboard[SCAN_Z])
    if (ropeedit.texturenum>0)
      ropeedit.texturenum--;
    }

  resetmenuitems();
  }

void renderropeedit(void)
  {
  int count;
  float vec[3];

  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);

  glColor4f(0.0f,1.0f,0.0f,1.0f);

  for (count=0;count<ropeedit.numofpoints;count++)
    {
    if (count==ropeedit.pointnum)
      glColor4f(1.0f,1.0f,1.0f,1.0f);
    else if (count==ropeedit.pointhighlight)
      glColor4f(0.0f,1.0f,0.0f,1.0f);
    else
      glColor4f(0.0f,0.5f,0.0f,1.0f);

    vec[0]=ropeedit.point[count].position[0];
    vec[1]=ropeedit.point[count].position[1]+0.25f;
    vec[2]=0.0f;

    glVertex3fv(vec);

    vec[0]=ropeedit.point[count].position[0];
    vec[1]=ropeedit.point[count].position[1]-0.25f;
    vec[2]=0.0f;

    glVertex3fv(vec);

    vec[0]=ropeedit.point[count].position[0]-0.25f;
    vec[1]=ropeedit.point[count].position[1];
    vec[2]=0.0f;

    glVertex3fv(vec);

    vec[0]=ropeedit.point[count].position[0]+0.25f;
    vec[1]=ropeedit.point[count].position[1];
    vec[2]=0.0f;

    glVertex3fv(vec);
    }

  glEnd();

  glEnable(GL_TEXTURE_2D);
  }
