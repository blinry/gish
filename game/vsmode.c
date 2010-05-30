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

void versusmodemenu(int versusnum)
  {
  int count;
  int unlocked;
  char filename[32];

  unlocked=0;
  for (count=0;count<6;count++)
  if (player[count].unlock[1])
    unlocked=1;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_EXIT,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    count=250;
    createmenuitem(TXT_LEVEL" 1",(320|TEXT_CENTER),count,20,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_1);
    count+=20;
    createmenuitem(TXT_LEVEL" 2",(320|TEXT_CENTER),count,20,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_2);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=20;
    createmenuitem(TXT_LEVEL" 3",(320|TEXT_CENTER),count,20,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_3);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=20;
#ifndef DEMO
    if (unlocked)
      {
      createmenuitem(TXT_LEVEL" 4",(320|TEXT_CENTER),count,20,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_4);
      count+=20;
      }
    else
      createmenuitemempty();
#endif
#ifndef DEMO
    count=360;
    if (versusnum==0 || versusnum==1)
      {
      createmenuitem(TXT_LEVEL" 5",(320|TEXT_CENTER),count,20,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_5);
      count+=20;
      createmenuitem(TXT_LEVEL" 6",(320|TEXT_CENTER),count,20,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_6);
      count+=20;
      }
#endif

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    updateogg();
    checkmusic();
    game.songnum=8;
    soundsimulation(view.position,view.orientation);

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(540);

    drawbackground(530+versusnum,(320|TEXT_CENTER),48,192,192,640,480);

    drawtext("2 "TXT_PLAYER,(320|TEXT_CENTER),234,16,1.0f,1.0f,1.0f,1.0f);
    if (versusnum==0 || versusnum==1)
      drawtext("4 "TXT_PLAYER,(320|TEXT_CENTER),344,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (versusnum==0)
      strcpy(filename,"bathhouse");
    if (versusnum==1)
      strcpy(filename,"field");
    if (versusnum==2)
      strcpy(filename,"amber");
    if (versusnum==3)
      strcpy(filename,"fight");
    if (versusnum==4)
      strcpy(filename,"dragster");
    if (versusnum==5)
      strcpy(filename,"colvs");
    if (versusnum==6)
      strcpy(filename,"racing");

    if (menuitem[1].active)
      {
      game.songnum=-1;
      checkmusic();

      game.levelnum=0;
      strcat(filename,".lvl");
      loadlevel(filename);
      gameloop();
      }
    if (menuitem[2].active)
      {
      game.songnum=-1;
      checkmusic();

      game.levelnum=0;
      strcat(filename,"2.lvl");
      loadlevel(filename);
      gameloop();
      }
    if (menuitem[3].active)
      {
      game.songnum=-1;
      checkmusic();

      game.levelnum=0;
      strcat(filename,"3.lvl");
      loadlevel(filename);
      gameloop();
      }
    if (menuitem[4].active)
      {
      game.songnum=-1;
      checkmusic();

      game.levelnum=0;
      strcat(filename,"4.lvl");
      loadlevel(filename);
      gameloop();
      }
    if (menuitem[5].active)
      {
      game.songnum=-1;
      checkmusic();

      if (versusnum==0)
        strcpy(filename,"4bath");
      if (versusnum==1)
        strcpy(filename,"4field");

      game.levelnum=0;
      strcat(filename,".lvl");
      loadlevel(filename);
      gameloop();
      }
    if (menuitem[6].active)
      {
      game.songnum=-1;
      checkmusic();

      if (versusnum==0)
        strcpy(filename,"4bath");
      if (versusnum==1)
        strcpy(filename,"4field");

      game.levelnum=0;
      strcat(filename,"2.lvl");
      loadlevel(filename);
      gameloop();
      }
    }

  resetmenuitems();
  }
