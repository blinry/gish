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

#include "../config.h"

#include "../video/opengl.h"

#include <string.h>

#include "../game/vsmode.h"
#include "../game/gameaudio.h"
#include "../game/english.h"
#include "../game/game.h"
#include "../game/level.h"
#include "../game/mainmenu.h"
#include "../game/music.h"
#include "../game/player.h"
#include "../audio/audio.h"
#include "../input/joystick.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../menu/menu.h"
#include "../sdl/event.h"
#include "../video/text.h"

void versusmodemenu(int versusnum)
  {
  int count;
  int unlocked;
  char filename[32];
  bool is4Player;
  char* gametypeName;
  bool menuItemClicked = FALSE;

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
    count+=20;
    createmenuitem(TXT_LEVEL" 3",(320|TEXT_CENTER),count,20,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_3);
    count+=20;
    if (unlocked)
      {
      createmenuitem(TXT_LEVEL" 4",(320|TEXT_CENTER),count,20,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_4);
      count+=20;
      }
    else
      createmenuitemempty();
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

	// Is item clicked?
	if (!(menuitem[1].active || menuitem[2].active || menuitem[3].active || menuitem[4].active || menuitem[5].active || menuitem[6].active))
		continue;

	is4Player = menuitem[5].active || menuitem[6].active;
	gametypeName = NULL;
	switch (versusnum)
	{
	case 0: gametypeName = is4Player ? "4sumo" : "2sumo"; break;
	case 1: gametypeName = is4Player ? "4football" : "2football"; break;
	case 2: gametypeName = "2greed"; break;
	case 3: gametypeName = "2duel"; break;
	case 4: gametypeName = "2dragster"; break;
	case 5: gametypeName = "2collection"; break;
	case 6: gametypeName = "2racing"; break;
	}
	strcpy(filename, gametypeName);

	// 2 player.
	if (menuitem[1].active)      strcat(filename, "1");
	else if (menuitem[2].active) strcat(filename, "2");
	else if (menuitem[3].active) strcat(filename, "3");
	else if (menuitem[4].active) strcat(filename, "4");
	// 4 player.
	else if (menuitem[5].active) strcat(filename, "1");
	else if (menuitem[6].active) strcat(filename, "2");
	strcat(filename, ".lvl");

	game.songnum=-1;
	checkmusic();

	game.levelnum=0;
	loadlevel(filename);
	gameloop();
    }

  resetmenuitems();
  }
