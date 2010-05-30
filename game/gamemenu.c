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

void postgamemenu(void)
  {
  int count;
  int scoretemp;
  int scorecountdelay;
  int simtimer;
  int simcount;

  savereplay(game.levelnum+100);

  scoretemp=game.totalscore;
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
    if (game.levelnum!=34)
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

    if (!game.bosslevel)
      {
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
      }
    else
      {
      if (game.levelnum==34 && game.exit==4)
        drawtext(TXT_GF_RESCUING_BONUS,64,336,16,1.0f,1.0f,1.0f,1.0f);
      drawtext(TXT_LIFE_BONUS":/i",64,352,16,1.0f,1.0f,1.0f,1.0f,(object[0].hitpoints/50)*10);
      if (game.levelnum==34 && game.exit==4)
        drawtext(TXT_BOSS_POINTS":/i",64,368,16,1.0f,1.0f,1.0f,1.0f,game.score[0]-(object[0].hitpoints/50)*10-1);
      else
        drawtext(TXT_BOSS_POINTS":/i",64,368,16,1.0f,1.0f,1.0f,1.0f,game.score[0]-(object[0].hitpoints/50)*10);
      }

    drawtext(TXT_TOTAL_POINTS":/i",64,384,16,1.0f,1.0f,1.0f,1.0f,scoretemp);
    drawtext("+/i",64+19*16,384,16,1.0f,1.0f,1.0f,1.0f,game.score[0]-(scoretemp-game.totalscore));

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
      if (scoretemp<game.totalscore+game.score[0])
        {
        if (scoretemp<=game.totalscore+game.score[0]-10)
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

void pregamemenu(void)
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

#ifdef TESTIT
  if (game.levelnum>=1 && game.levelnum<=34)
    {
    if (keyboard[SCAN_R] && !prevkeyboard[SCAN_R])
    if (game.levelnum<34)
      game.levelnum++;
    if (keyboard[SCAN_F] && !prevkeyboard[SCAN_F])
    if (game.levelnum>1)
      game.levelnum--;
    }
#endif

    if (game.levelnum<35)
      {
      count=(game.levelnum-1)/7+1;
      count2=(game.levelnum-1)%7+1;
      if (count==1)
        drawbackground(521,(320|TEXT_CENTER),48,192,192,640,480);
      if (count==2)
        drawbackground(522,(320|TEXT_CENTER),48,192,192,640,480);
      if (count==3)
        drawbackground(523,(320|TEXT_CENTER),48,192,192,640,480);
      if (count==4)
        drawbackground(524,(320|TEXT_CENTER),48,192,192,640,480);
      if (count==5)
        drawbackground(525,(320|TEXT_CENTER),48,192,192,640,480);

      drawtext("/i-/i",(320|TEXT_CENTER),256,16,1.0f,1.0f,1.0f,1.0f,count,count2);
      drawtext(TXT_LIVES" /i",(320|TEXT_CENTER),272,16,1.0f,1.0f,1.0f,1.0f,game.numoflives);
      drawtext(TXT_POINTS" /i",(320|TEXT_CENTER),288,16,1.0f,1.0f,1.0f,1.0f,game.totalscore);
      }
    if (game.levelnum==64)
      {
      drawbackground(526,(320|TEXT_CENTER),48,192,192,640,480);
      drawtext(" -1",(320|TEXT_CENTER),256,16,1.0f,1.0f,1.0f,1.0f);
      }
    if (game.levelnum==65)
      {
      drawbackground(526,(320|TEXT_CENTER),48,192,192,640,480);
      drawtext(" -2",(320|TEXT_CENTER),256,16,1.0f,1.0f,1.0f,1.0f);
      }
    if (game.levelnum==66)
      {
      drawbackground(526,(320|TEXT_CENTER),48,192,192,640,480);
      drawtext(" -3",(320|TEXT_CENTER),256,16,1.0f,1.0f,1.0f,1.0f);
      }
    if (game.levelnum==67)
      {
      drawbackground(526,(320|TEXT_CENTER),48,192,192,640,480);
      drawtext(TXT_ISLE_OF_THE,(320|TEXT_CENTER),256,16,1.0f,1.0f,1.0f,1.0f);
      drawtext(TXT_DEAD,(320|TEXT_CENTER),272,16,1.0f,1.0f,1.0f,1.0f);
      }
    if (game.levelnum==68)
      {
      drawbackground(526,(320|TEXT_CENTER),48,192,192,640,480);
      drawtext(TXT_SATANS_LAIR,(320|TEXT_CENTER),256,16,1.0f,1.0f,1.0f,1.0f);
      }

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[1].active)// || startdelay>=150)
      {
      loadstorylevel(game.levelnum);

      gameloop();

      if (game.exit==2 || game.exit==3)
      if (game.levelnum<64)
        {
        if (game.numoflives<99)
          game.numoflives--;
        if (game.numoflives<0)
          {
          if (player[playernum].highscore<game.totalscore)
            player[playernum].highscore=game.totalscore;

          game.totalscore=0;
          game.numoflives=5;
          if (game.difficulty==1)
            {
            count2=(game.levelnum-1)%7+1;
            if (count2!=7)
              {
              count=(game.levelnum-1)/7;
              game.levelnum=count*7+1;
              }
            }
          if (game.difficulty>=2)
            game.levelnum=0;

          gameovermenu();

          goto changelevelbypass;
          }
        }

#ifdef DEMO
      if (game.levelnum==4)
      if (game.exit==4 || game.exit==5)
        {
        game.score[0]+=(object[0].hitpoints/50)*10;
        postgamemenu();
        game.totalscore+=game.score[0];

        endingmenu();
        menuitem[0].active=1;

        game.levelnum=5;

        goto changelevelbypass;
        }
#endif
      if (game.levelnum==34)
      if (game.exit==4 || game.exit==5)
        {
        game.score[0]=10000;
        if (game.levelnum==34 && game.exit==4)
          game.score[0]+=1;

        game.score[0]+=(object[0].hitpoints/50)*10;
        postgamemenu();
        game.totalscore+=game.score[0];

        endingmenu();
        menuitem[0].active=1;

        game.levelnum=35;

        goto changelevelbypass;
        }

      if (game.exit==4)
        {
        //if (!game.bosslevel)
        if (game.levelnum!=68 || game.dialog==0)
          {
          if (game.levelnum==6)
            game.score[0]=1000;
          if (game.levelnum==13)
            game.score[0]=2000;
          if (game.levelnum==20)
            game.score[0]=3000;
          if (game.levelnum==27)
            game.score[0]=4000;
          if (game.levelnum==33)
            game.score[0]=5000;
          if (game.levelnum==34)
            game.score[0]=10000;
          if (game.levelnum==68)
            game.score[0]=20000;

          //if (game.levelnum==34 && game.exit==4)
          //  game.score[0]+=10;

          game.oldschool=0;
          game.score[0]+=(object[0].hitpoints/50)*10;
          postgamemenu();
          game.totalscore+=game.score[0];
          if (game.exit==2)
            {
            game.exit=4;
            menuitem[0].active=1;
            }
          }
        if (game.levelnum<35)
          game.levelnum++;
        }
      if (game.levelnum==64)
        {
        game.levelnum=4;
        if (game.over==3)
          game.levelnum=22;
        if (game.over==4)
          game.levelnum=15;
        if (game.over==5)
          game.levelnum=8;

        goto changelevelbypass;
        }
      if (game.levelnum==65)
        {
        game.levelnum=9;

        goto changelevelbypass;
        }
      if (game.levelnum==66)
        {
        game.levelnum=26;

        goto changelevelbypass;
        }
      if (game.levelnum==67)
        {
        if (game.exit==2 || game.exit==3)
          game.levelnum=19;
        else
          game.levelnum=68;

        goto changelevelbypass;
        }
      if (game.levelnum==68)
        {
        game.levelnum=19;

        goto changelevelbypass;
        }
      if (game.exit==5)
        {
        game.totalscore+=game.score[0];

        if (game.levelnum==3)
          game.levelnum=64;
        if (game.levelnum==4)
          game.levelnum=24;
        if (game.levelnum==8)
          game.levelnum=65;
        if (game.levelnum==18)
          game.levelnum=67;
        if (game.levelnum==25)
          game.levelnum=66;

        goto changelevelbypass;
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

      //startdelay++;
      }

    if (game.exit==2)
      menuitem[0].active=1;
    }

  resetmenuitems();
  }

void gameovermenu(void)
  {
  int count;
  int scoretemp;
  int scorecountdelay;
  int simtimer;
  int simcount;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !menuitem[1].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    if (game.difficulty<2)
      {
      createmenuitem(TXT_CONTINUE,(320|TEXT_CENTER),256,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_C);
      }

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(580);

    drawtext(TXT_GAME_OVER,(320|TEXT_CENTER),224,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();
    }

  if (menuitem[0].active)
    game.exit=2;
  if (menuitem[1].active)
    game.exit=3;

  resetmenuitems();
  }

void endingmenu(void)
  {
#ifndef DEMO
  int count;

  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem("Next",(640|TEXT_END),0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(580);

    count=192;
    if (game.exit==4)
      {
      drawbackground(520,(320|TEXT_CENTER),48,256,128,640,480);

      drawtext(TXT_ENDING_LINE1,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE2,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE3,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE4,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE5,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE6,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      count+=14;
      drawtext(TXT_ENDING_LINE7,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE8,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE9,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE10,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE11,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_LINE12,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      }
    if (game.exit==5)
      {
      drawbackground(519,(320|TEXT_CENTER),48,256,128,640,480);

      drawtext(TXT_ENDING_BAD_LINE1,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE2,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE3,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE4,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE5,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE6,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE7,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE8,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE9,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE10,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE11,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE12,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      drawtext(TXT_ENDING_BAD_LINE13,64,count,14,1.0f,1.0f,1.0f,1.0f);
      count+=14;
      }

    drawtext(TXT_TOTAL_POINTS":/i",64,400,16,1.0f,1.0f,1.0f,1.0f,game.totalscore);
    if (player[playernum].difficulty==1 || player[playernum].difficulty==2)
      drawtext(TXT_NEW_VS_MODE,64,416,16,1.0f,1.0f,1.0f,1.0f);
    if (player[playernum].difficulty==2)
      drawtext(TXT_NEW_VS_LEVEL,64,432,16,1.0f,1.0f,1.0f,1.0f);
    if (player[playernum].difficulty==3)
      drawtext(TXT_MINI_GISH_MODE,64,432,16,1.0f,1.0f,1.0f,1.0f);
    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();
    }

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

    if (game.exit==5)
      drawbackground(256+68,288,320,96,96,640,480);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();
    }

  resetmenuitems();
#endif
#ifdef DEMO
  int count;

  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem("Next",(640|TEXT_END),0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(580);

    count=128;

    drawtext("Congratulations, you have completed",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;
    drawtext("the demo.  Buy the full game and get:",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;
    count+=14;
    drawtext("-34 action packed story mode levels",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;
    drawtext("-23 time trial collection challenges",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;
    drawtext("-5 competitive versus modes",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;
    drawtext("-5 hidden bonus levels",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;
    drawtext("-6 intense boss fights",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;
    drawtext("-Over 55 secrets to discover",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;
    drawtext("-And much much more...",64,count,14,1.0f,1.0f,1.0f,1.0f);
    count+=14;

    drawtext("Total Points:/i",64,400,16,1.0f,1.0f,1.0f,1.0f,game.totalscore);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();
    }

  resetmenuitems();
#endif
  }

