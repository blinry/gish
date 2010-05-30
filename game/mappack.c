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

void mappackpostgamemenu(void)
  {
  int count;
  int scoretemp;
  int scorecountdelay;
  int simtimer;
  int simcount;

  scoretemp=playermappack[playernum].totalscore;
  scorecountdelay=0;

  simtimer=SDL_GetTicks();

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !menuitem[1].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    if (playermappack[playernum].levelnum!=mappack.numoflevels)
      {
      createmenuitem(TXT_NEXTLEVEL,(640|TEXT_END),0,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_N);
      }
    else
      {
      createmenuitem(TXT_ENDING,(640|TEXT_END),0,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_N);
      }

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    soundsimulation(view.position,view.orientation);

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(580);

    drawbackground(468,(320|TEXT_CENTER),48,384,64,640,480);
    drawbackground(469,400,160,128,128,640,480);

    count=128;
    drawtext(TXT_SMALL_AMBER" /i///i",64,count,16,1.0f,1.0f,1.0f,1.0f,game.bonus[5],game.numofbonus[5]);
    count+=16;
    drawtext(TXT_MEDIUM_AMBER" /i///i",64,count,16,1.0f,1.0f,1.0f,1.0f,game.bonus[6],game.numofbonus[6]);
    count+=16;
    drawtext(TXT_LARGE_AMBER" /i///i",64,count,16,1.0f,1.0f,1.0f,1.0f,game.bonus[7],game.numofbonus[7]);
    count+=16;
    drawtext(TXT_TARBALLS" /i///i",64,count,16,1.0f,1.0f,1.0f,1.0f,game.bonus[4],game.numofbonus[4]);
    count+=16;
    drawtext(TXT_EXTRA_LIVES" /i///i",64,count,16,1.0f,1.0f,1.0f,1.0f,game.bonus[3],game.numofbonus[3]);
    count+=16;
    drawtext(TXT_SECRETS" /i///i",64,count,16,1.0f,1.0f,1.0f,1.0f,game.bonus[8],game.numofbonus[8]);
    count+=16;

    drawtext(TXT_LIFE_BONUS":/i",64,352,16,1.0f,1.0f,1.0f,1.0f,(object[0].hitpoints/50)*10);
    drawtext(TXT_LEVEL_POINTS":/i",64,368,16,1.0f,1.0f,1.0f,1.0f,game.score[0]-(object[0].hitpoints/50)*10);

    drawtext(TXT_TOTAL_POINTS":/i",64,384,16,1.0f,1.0f,1.0f,1.0f,scoretemp);
    drawtext("+/i",64+19*16,384,16,1.0f,1.0f,1.0f,1.0f,game.score[0]-(scoretemp-playermappack[playernum].totalscore));

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    simcount=0;
    while (SDL_GetTicks()-simtimer>20 && simcount<5)
      {
      simcount++;
      count=SDL_GetTicks()-simtimer-20;
      simtimer=SDL_GetTicks()-count;

      scorecountdelay++;

      if (scorecountdelay>=25)
      if (scoretemp<playermappack[playernum].totalscore+game.score[0])
        {
        if (scoretemp<=playermappack[playernum].totalscore+game.score[0]-10)
          scoretemp+=10;
        else
          scoretemp++;
        if ((scorecountdelay&1)==1)
          playsound(15,view.position,NULL,0.2f,0,1.0f,-1,0);
        }
      }
    }

  if (menuitem[0].active)
    game.exit=2;

  for (count=numofsounds-1;count>=0;count--)
    deletesound(count);

  resetmenuitems();
  }

void mappackpregamemenu(void)
  {
  int count,count2;
  int simtimer;
  int simcount;
  int startdelay;

  game.exit=0;

  startdelay=0;
  simtimer=SDL_GetTicks();

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    createmenuitem(TXT_START,(320|TEXT_CENTER),320,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_S);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(540);

    drawbackground(526,(320|TEXT_CENTER),48,192,192,640,480);

    drawtext(mappack.levelname[playermappack[playernum].levelnum-1],(320|TEXT_CENTER),256,16,1.0f,1.0f,1.0f,1.0f);
    drawtext(TXT_LIVES" /i",(320|TEXT_CENTER),272,16,1.0f,1.0f,1.0f,1.0f,playermappack[playernum].numoflives);
    drawtext(TXT_POINTS" /i",(320|TEXT_CENTER),288,16,1.0f,1.0f,1.0f,1.0f,playermappack[playernum].totalscore);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[1].active)
      {
      if (playermappack[playernum].levelnum<1)
        playermappack[playernum].levelnum=1;
      if (playermappack[playernum].levelnum>mappack.numoflevels)
        playermappack[playernum].levelnum=mappack.numoflevels;

      game.editing=0;
      game.levelnum=0;
      loadlevel(mappack.level[playermappack[playernum].levelnum-1]);

      mappack.active=1;

      gameloop();

      mappack.active=0;

      if (game.exit==2 || game.exit==3)
        {
        if (playermappack[playernum].numoflives<99)
          playermappack[playernum].numoflives--;
        if (playermappack[playernum].numoflives<0)
          {
          if (playermappack[playernum].highscore<playermappack[playernum].totalscore)
            playermappack[playernum].highscore=playermappack[playernum].totalscore;

          playermappack[playernum].totalscore=0;
          playermappack[playernum].numoflives=5;
          if (playermappack[playernum].difficulty>=2)
            playermappack[playernum].levelnum=0;

          gameovermenu();

          goto changelevelbypass;
          }
        }

      if (game.exit==4)
        {
        game.score[0]+=(object[0].hitpoints/50)*10;
        mappackpostgamemenu();
        playermappack[playernum].totalscore+=game.score[0];

        if (playermappack[playernum].highscore<playermappack[playernum].totalscore)
          playermappack[playernum].highscore=playermappack[playernum].totalscore;

        if (playermappack[playernum].levelnum==mappack.numoflevels)
          {
          mappackendingmenu();
          playermappack[playernum].levelnum=0;
          game.exit=2;
          }
        else
          playermappack[playernum].levelnum++;

        if (game.exit==2)
          menuitem[0].active=1;
        }

      changelevelbypass:;

      simtimer=SDL_GetTicks();
      startdelay=0;

      joymenunum=1;
      }

    simcount=0;
    while (SDL_GetTicks()-simtimer>20 && simcount<5)
      {
      simcount++;
      count=SDL_GetTicks()-simtimer-20;
      simtimer=SDL_GetTicks()-count;
      }

    if (game.exit==2)
      menuitem[0].active=1;
    }

  resetmenuitems();
  }

void mappackendingmenu(void)
  {
  int count;

  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(560);

    drawtext(TXT_TOTAL_POINTS":/i",(320|TEXT_CENTER),448,16,1.0f,1.0f,1.0f,1.0f,playermappack[playernum].totalscore);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();
    }

  resetmenuitems();
  }
