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

void playermenu(void)
  {
  int count,count2,count3;
  int deleteplayer;

  resetmenuitems();

  joymenunum=1;
  playernum=-1;
  deleteplayer=0;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    if (playernum==-1)
      {
      count=128;
      createmenuitem("",64,count,32,0.25f,0.25f,0.25f,1.0f);
      setmenuitem(MO_SET,&playernum,0);
      setmenuitem(MO_HOTKEY,SCAN_1);
      count+=40;
      createmenuitem("",64,count,32,0.25f,0.25f,0.25f,1.0f);
      setmenuitem(MO_SET,&playernum,1);
      setmenuitem(MO_HOTKEY,SCAN_2);
      count+=40;
      createmenuitem("",64,count,32,0.25f,0.25f,0.25f,1.0f);
      setmenuitem(MO_SET,&playernum,2);
      setmenuitem(MO_HOTKEY,SCAN_3);
      count+=40;
      createmenuitem("",64,count,32,0.25f,0.25f,0.25f,1.0f);
      setmenuitem(MO_SET,&playernum,3);
      setmenuitem(MO_HOTKEY,SCAN_4);
      count+=40;
      createmenuitem("",64,count,32,0.25f,0.25f,0.25f,1.0f);
      setmenuitem(MO_SET,&playernum,4);
      setmenuitem(MO_HOTKEY,SCAN_5);
      count+=40;
      createmenuitem("",64,count,32,0.25f,0.25f,0.25f,1.0f);
      setmenuitem(MO_SET,&playernum,5);
      setmenuitem(MO_HOTKEY,SCAN_6);
      count+=40;

      count+=16;
      createmenuitem(TXT_DELETE_PLAYER,64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_TOGGLE,&deleteplayer);
      }
    else if (!deleteplayer)
      {
      count=128+playernum*40-16;
      createmenuitem("                    ",96,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_STRINGINPUT,player[playernum].name);
      if (player[playernum].name[0]!=0)
        {
        createmenuitem(TXT_CREATE,432,count+16,16,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_HOTKEY,SCAN_C);
        }
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

    if (playernum!=-1)
      {
      if (numofmenuitems>3)
        {
        if (player[playernum].name[0]!=0)
          menuitem[2].active=1;
        else
          menuitem[1].active=1;
        }
      }

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(580);

    drawmenuitems();

    for (count=0;count<6;count++)
      {
      if (count!=playernum || deleteplayer)
        {
        if (player[count].name[0]!=0)
          {
          count2=(player[count].levelnum-1)/7+1;
          count3=(player[count].levelnum-1)%7+1;
          if (count3==0)
            count3=1;
  
          if (!player[count].gamepassed)
            {
            drawtext("/i-/s",64,128+count*40,16,1.0f,1.0f,1.0f,1.0f,count+1,player[count].name);
            drawtext(TXT_PLAYER_INFO,64,128+count*40+16,12,1.0f,1.0f,1.0f,1.0f,count2,count3,player[count].numoflives,player[count].totalscore,player[count].highscore);
            }
          else
            {
            drawtext("/i-/s",64,128+count*40,16,1.0f,1.0f,0.0f,1.0f,count+1,player[count].name);
            drawtext(TXT_PLAYER_INFO,64,128+count*40+16,12,1.0f,1.0f,0.0f,1.0f,count2,count3,player[count].numoflives,player[count].totalscore,player[count].highscore);
            }
          if (count==playernum && deleteplayer)
            {
            drawtext("/i-/s",64,128+count*40,16,1.0f,0.0f,0.0f,1.0f,count+1,player[count].name);
            drawtext(TXT_PLAYER_INFO,64,128+count*40+16,12,1.0f,0.0f,0.0f,1.0f,count2,count3,player[count].numoflives,player[count].totalscore,player[count].highscore);
            }
          }
        else
          drawtext(TXT_NEW_PLAYER,64,128+count*40,16,1.0f,1.0f,1.0f,1.0f,count+1);
        }
      else
        drawtext("/i-",64,128+count*40,16,1.0f,1.0f,1.0f,1.0f,count+1);
      }

    if (playernum==-1)
      drawtext(TXT_CHOOSE_PLAYER,(320|TEXT_CENTER),64,16,1.0f,1.0f,1.0f,1.0f);
    else
      {
      if (!deleteplayer || player[playernum].name[0]==0)
        drawtext(TXT_ENTER_NAME,(320|TEXT_CENTER),64,16,1.0f,1.0f,1.0f,1.0f);
      else
        drawtext(TXT_DELETE_Y_N,(320|TEXT_CENTER),64,16,1.0f,1.0f,1.0f,1.0f,player[playernum].name);
      }

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (deleteplayer)
    if (playernum!=-1)
      {
      if (player[playernum].name[0]==0)
        deleteplayer=0;
      else
        {
#ifdef GERMAN
        if (keyboard[SCAN_J])
#else
        if (keyboard[SCAN_Y])
#endif
          {
          memset(&player[playernum],0,sizeof(player[playernum]));
          playernum=-1;
          deleteplayer=0;
          resetmenuitems();
          }
        if (keyboard[SCAN_N] || keyboard[SCAN_ESC])
          {
          playernum=-1;
          deleteplayer=0;
          resetmenuitems();
          }
        }
      }
    if (playernum!=-1)
    if (player[playernum].name[0]!=0)
    if (menuitem[2].active)
      {
      if (!deleteplayer)
        {
        playerstartmenu();
  
        joymenunum=0;//playernum+1;
  
        playernum=-1;
        }
      /*
      else
        {
        //menuitem[2].active=0;
        //playernum=-1;
        }
      */
      }
    }

  if (playernum!=-1)
    player[playernum].name[0]=0;

  resetmenuitems();
  }

void saveplayers(void)
  {
  int count;
  int version;

  if ((fp=fopen("gish.pla","wb"))!=NULL)
    {
    version=3;
    fwrite2(&version,4,1,fp);
    for (count=0;count<8;count++)
      {
      fwrite2(player[count].name,1,32,fp);
      fwrite2(&player[count].levelnum,4,1,fp);
      fwrite2(&player[count].numoflives,4,1,fp);
      fwrite2(&player[count].totalscore,4,1,fp);
      fwrite2(&player[count].difficulty,4,1,fp);
      fwrite2(&player[count].gamepassed,4,1,fp);
      fwrite2(&player[count].highscore,4,1,fp);
      fwrite2(player[count].unlock,4,16,fp);
      }
    fclose(fp);
    }
  }

void loadplayers(void)
  {
  int count;
  int version;

  if ((fp=fopen("gish.pla","rb"))!=NULL)
    {
    fread2(&version,4,1,fp);
    if (version==2)
      {
      for (count=0;count<8;count++)
        {
        fread2(player[count].name,1,32,fp);
        fread2(&player[count].levelnum,4,1,fp);
        fread2(&player[count].numoflives,4,1,fp);
        fread2(&player[count].totalscore,4,1,fp);
        player[count].difficulty=1;
        fread2(&player[count].gamepassed,4,1,fp);
        fread2(&player[count].highscore,4,1,fp);
        fread2(player[count].unlock,4,16,fp);
        }
      }
    if (version==3)
      {
      for (count=0;count<8;count++)
        {
        fread2(player[count].name,1,32,fp);
        fread2(&player[count].levelnum,4,1,fp);
        fread2(&player[count].numoflives,4,1,fp);
        fread2(&player[count].totalscore,4,1,fp);
        fread2(&player[count].difficulty,4,1,fp);
        fread2(&player[count].gamepassed,4,1,fp);
        fread2(&player[count].highscore,4,1,fp);
        fread2(player[count].unlock,4,16,fp);
        }
      }
    fclose(fp);
    }
  }

void playerstartmenu(void)
  {
  int count,count2,count3;

  if (playernum==-1)
    return;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    count=352;
    if (player[playernum].levelnum>0)
      {
      createmenuitem(TXT_CONTINUE,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_C);
      count+=16;
      createmenuitem(TXT_COLLECTION_GAME,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_O);
      count+=16;
      createmenuitem(TXT_NEW_GAME,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_N);
      count+=16;
      createmenuitem(TXT_PRACTICE,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_P);
      count+=16;
      createmenuitem(TXT_REPLAY,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_R);
      count+=16;
#ifndef DEMO
      /*
      if (player[playernum].unlock[0])
        {
        createmenuitem(TXT_SINGLE_LEVEL,48,count,16,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_HOTKEY,SCAN_S);
        count+=16;
        }
      else
      */
        createmenuitemempty();
#endif
#ifndef DEMO
      createmenuitem(TXT_CUSTOM_LEVELS,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_U);
      count+=16;
#endif
      }
    else
      {
      createmenuitem(TXT_NEW_GAME,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_N);
      count+=16;
      createmenuitem(TXT_COLLECTION_GAME,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_O);
      count+=16;
      createmenuitemempty();
      createmenuitem(TXT_PRACTICE,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_P);
      count+=16;
      createmenuitem(TXT_REPLAY,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_R);
      count+=16;
      /*
      if (player[playernum].unlock[0])
        {
        createmenuitem(TXT_SINGLE_LEVEL,48,count,16,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_HOTKEY,SCAN_S);
        count+=16;
        }
      else
      */
        createmenuitemempty();
#ifndef DEMO
      createmenuitem(TXT_CUSTOM_LEVELS,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_U);
      count+=16;
#endif
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
    displaybackground(620);

    count2=(player[playernum].levelnum-1)/7+1;
    count3=(player[playernum].levelnum-1)%7+1;
    if (count3==0)
      count3=1;

    if (!player[playernum].gamepassed)
      {
      drawtext(player[playernum].name,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);
      if (player[playernum].levelnum>0)
        {
        drawtext(TXT_PLAYER_INFO,(320|TEXT_CENTER),320,12,1.0f,1.0f,1.0f,1.0f,count2,count3,player[playernum].numoflives,player[playernum].totalscore,player[playernum].highscore);
        if (player[playernum].difficulty==0)
          drawtext(TXT_EASY,(320|TEXT_CENTER),332,12,1.0f,1.0f,1.0f,1.0f);
        if (player[playernum].difficulty==1)
          drawtext(TXT_NORMAL,(320|TEXT_CENTER),332,12,1.0f,1.0f,1.0f,1.0f);
        if (player[playernum].difficulty==2)
          drawtext(TXT_HARD,(320|TEXT_CENTER),332,12,1.0f,1.0f,1.0f,1.0f);
        if (player[playernum].difficulty==3)
          drawtext(TXT_LUDICROUS,(320|TEXT_CENTER),332,12,1.0f,1.0f,1.0f,1.0f);
        if (player[playernum].difficulty==4)
          drawtext(TXT_MINI_GISH,(320|TEXT_CENTER),332,12,1.0f,1.0f,1.0f,1.0f);
        }
      }
    else
      {
      drawtext(player[playernum].name,(320|TEXT_CENTER),304,16,1.0f,1.0f,0.0f,1.0f);
      if (player[playernum].levelnum>0)
        {
        drawtext(TXT_PLAYER_INFO,(320|TEXT_CENTER),320,12,1.0f,1.0f,0.0f,1.0f,count2,count3,player[playernum].numoflives,player[playernum].totalscore,player[playernum].highscore);
        if (player[playernum].difficulty==0)
          drawtext(TXT_EASY,(320|TEXT_CENTER),332,12,1.0f,1.0f,0.0f,1.0f);
        if (player[playernum].difficulty==1)
          drawtext(TXT_NORMAL,(320|TEXT_CENTER),332,12,1.0f,1.0f,0.0f,1.0f);
        if (player[playernum].difficulty==2)
          drawtext(TXT_HARD,(320|TEXT_CENTER),332,12,1.0f,1.0f,0.0f,1.0f);
        if (player[playernum].difficulty==3)
          drawtext(TXT_LUDICROUS,(320|TEXT_CENTER),332,12,1.0f,1.0f,0.0f,1.0f);
        if (player[playernum].difficulty==4)
          drawtext(TXT_MINI_GISH,(320|TEXT_CENTER),332,12,1.0f,1.0f,0.0f,1.0f);
        }
      }
    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[1].active)
      {
      if (player[playernum].levelnum>0)
        {
        game.levelnum=player[playernum].levelnum;
        game.totalscore=player[playernum].totalscore;
        game.difficulty=player[playernum].difficulty;
        game.numoflives=player[playernum].numoflives;
        }
      else
        {
        playerdifficultymenu();
        if (game.difficulty==-1)
          {
          game.difficulty=0;
          goto newgamebypass;
          }

        player[playernum].difficulty=game.difficulty;

        game.levelnum=1;
        game.totalscore=0;
        game.numoflives=5;
        if (player[playernum].difficulty==3)
          {
          game.numoflives=0;
          game.turbomode=1;
          }

        storyscreen();
        }

      game.songnum=-1;
      checkmusic();

      pregamemenu();

      player[playernum].levelnum=game.levelnum;
      player[playernum].totalscore=game.totalscore;
      player[playernum].numoflives=game.numoflives;
      if (player[playernum].highscore<player[playernum].totalscore)
        player[playernum].highscore=player[playernum].totalscore;

#ifdef DEMO
      if (player[playernum].levelnum==6)
        {
        player[playernum].levelnum=0;
        player[playernum].totalscore=0;
        player[playernum].numoflives=5;
        player[playernum].gamepassed=1;
        }
#endif
      if (player[playernum].levelnum==35)
        {
        if (player[playernum].difficulty==1 || player[playernum].difficulty==2)
          player[playernum].unlock[0]=1;
        if (player[playernum].difficulty==2)
          player[playernum].unlock[1]=1;
        if (player[playernum].difficulty==3)
          player[playernum].unlock[2]=1;
        if (player[playernum].difficulty==4)
          player[playernum].unlock[3]=1;
        player[playernum].levelnum=0;
        player[playernum].totalscore=0;
        player[playernum].numoflives=5;
        player[playernum].gamepassed=1;
        }

      //game.difficulty=0;

      //menuitem[0].active=1;

      newgamebypass:;
      }
    if (menuitem[2].active)
      {
      collectionmenu();

      //menuitem[0].active=1;
      }
    if (menuitem[3].active)
      {
      playerdifficultymenu();
      if (game.difficulty==-1)
        {
        game.difficulty=0;
        goto newgamebypass2;
        }

      player[playernum].difficulty=game.difficulty;

      game.levelnum=1;
      game.totalscore=0;
      game.numoflives=5;
      if (player[playernum].difficulty==3)
        {
        game.numoflives=0;
        game.turbomode=1;
        }

      storyscreen();

      game.songnum=-1;
      checkmusic();

      pregamemenu();

      player[playernum].levelnum=game.levelnum;
      player[playernum].totalscore=game.totalscore;
      player[playernum].numoflives=game.numoflives;
      if (player[playernum].highscore<player[playernum].totalscore)
        player[playernum].highscore=player[playernum].totalscore;

#ifdef DEMO
      if (player[playernum].levelnum==6)
        {
        player[playernum].levelnum=0;
        player[playernum].totalscore=0;
        player[playernum].numoflives=5;
        player[playernum].gamepassed=1;
        }
#endif
      if (player[playernum].levelnum==35)
        {
        if (player[playernum].difficulty==1 || player[playernum].difficulty==2)
          player[playernum].unlock[0]=1;
        if (player[playernum].difficulty==2)
          player[playernum].unlock[1]=1;
        if (player[playernum].difficulty==3)
          player[playernum].unlock[2]=1;
        if (player[playernum].difficulty==4)
          player[playernum].unlock[3]=1;
        player[playernum].levelnum=0;
        player[playernum].totalscore=0;
        player[playernum].numoflives=5;
        player[playernum].gamepassed=1;
        }

      //game.difficulty=0;

      //menuitem[0].active=1;

      newgamebypass2:;
      }
    if (menuitem[4].active)
      {
      game.songnum=-1;
      checkmusic();

      game.editing=0;
      game.levelnum=0;
      loadlevel("playroom.lvl");
      gameloop();
      }
    if (menuitem[5].active)
      {
      game.songnum=-1;
      checkmusic();

      replaymenu();
      }
    if (menuitem[6].active)
      {
      singlelevelmenu();
      }
    if (menuitem[7].active)
      {
      custommenu();
      }
    }

  resetmenuitems();
  }

void playerdifficultymenu(void)
  {
  int count;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !menuitem[1].active && !menuitem[2].active && !menuitem[3].active && !menuitem[4].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_CANCEL,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    count=352;
    createmenuitem(TXT_EASY,48,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_E);
    count+=16;
    createmenuitem(TXT_NORMAL,48,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_N);
    count+=16;
    createmenuitem(TXT_HARD,48,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_H);
    count+=16;
    if (player[playernum].unlock[1])
      {
      createmenuitem(TXT_LUDICROUS,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_L);
      count+=16;
      if (player[playernum].unlock[2])
        {
        createmenuitem(TXT_MINI_GISH,48,count,16,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_HOTKEY,SCAN_M);
        count+=16;
        }
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
    displaybackground(620);

    if (!player[playernum].gamepassed)
      drawtext(player[playernum].name,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);
    else
      drawtext(player[playernum].name,(320|TEXT_CENTER),304,16,1.0f,1.0f,0.0f,1.0f);

    drawtext(TXT_SELECT_DIFFICULTY,48,336,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[0].active)
      game.difficulty=-1;
    if (menuitem[1].active)
      game.difficulty=0;
    if (menuitem[2].active)
      game.difficulty=1;
    if (menuitem[3].active)
      game.difficulty=2;
    if (menuitem[4].active)
      game.difficulty=3;
    if (menuitem[5].active)
      game.difficulty=4;
    }

  resetmenuitems();
  }

void collectionmenu(void)
  {
  int count;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    count=320;
    createmenuitem(TXT_LEVEL" 1",64,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 2",64,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 3",64,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 4",64,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 5",64,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 6",64,count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;
    createmenuitem(TXT_LEVEL" 7",64,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 8",64,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;

    count=320;
    createmenuitem(TXT_LEVEL" 9",240,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 10",240,count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;
    createmenuitem(TXT_LEVEL" 11",240,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 12",240,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 13",240,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 14",240,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 15",240,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 16",240,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;

    count=320;
    createmenuitem(TXT_LEVEL" 17",416,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 18",416,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 19",416,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 20",416,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 21",416,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 22",416,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_LEVEL" 23",416,count,16,1.0f,1.0f,1.0f,1.0f);
#ifdef DEMO
    setmenuitem(MO_HIGHLIGHT,0);
#endif
    count+=16;
    createmenuitem(TXT_HIGH_SCORE,416,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_H);
    count+=16;

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
    displaybackground(620);

    drawtext(TXT_COLLECTION_MODE,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    for (count=1;count<24;count++)
    if (menuitem[count].active)
      {
      game.songnum=-1;
      checkmusic();

      game.editing=0;
      game.levelnum=0;

      loadcollectionlevel(count);

      gameloop();

      if (!game.playreplay)
      if (game.exit==4)
        highscoremenu(count);

      joymenunum=count;
      }
    if (menuitem[24].active)
      {
      game.exit=3;
      highscoremenu(1);
      }
    }

  resetmenuitems();
  }

void singlelevelmenu(void)
  {
  int count;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    count=320;
    createmenuitem(TXT_LEVEL" 1-1",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 1-2",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 1-3",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 1-4",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 1-5",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 1-6",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 1-7",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 2-1",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 2-2",64,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;

    count=320;
    createmenuitem(TXT_LEVEL" 2-3",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 2-4",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 2-5",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 2-6",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 2-7",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 3-1",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 3-2",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 3-3",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 3-4",192,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;

    count=320;
    createmenuitem(TXT_LEVEL" 3-5",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 3-6",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 3-7",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 4-1",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 4-2",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 4-3",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 4-4",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 4-5",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 4-6",320,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;

    count=320;
    createmenuitem(TXT_LEVEL" 4-7",448,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 5-1",448,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 5-2",448,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 5-3",448,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 5-4",448,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 5-5",448,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;
    createmenuitem(TXT_LEVEL" 5-6",448,count,12,1.0f,1.0f,1.0f,1.0f);
    count+=12;

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
    displaybackground(620);

    drawtext(TXT_SINGLE_LEVEL,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    for (count=1;count<=34;count++)
    if (menuitem[count].active)
      {
      game.songnum=-1;
      checkmusic();

      game.editing=0;
      game.levelnum=0;

      loadstorylevel(count);

      gameloop();

      savereplay(count+100);

      joymenunum=count;
      }
    }

  resetmenuitems();
  }

