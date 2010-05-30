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

void custommenu(void)
  {
  int count;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_EXIT,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    count=352;
    createmenuitem(TXT_PLAY_CAMPAIGN,48,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_C);
    count+=16;
    createmenuitem(TXT_LOAD_LEVEL,48,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_L);
    count+=16;
    createmenuitem(TXT_LEVEL_EDITOR,48,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_E);
    count+=16;
    createmenuitem(TXT_CAMPAIGN_EDITOR,48,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_A);
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

    drawtext(TXT_CUSTOM_LEVELS,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[1].active)
      {
      game.songnum=-1;
      checkmusic();

      game.editing=0;

      playcampaignmenu();
      }
    if (menuitem[2].active)
      {
      game.songnum=-1;
      checkmusic();

      game.editing=0;

      loadlevelmenu();
      }
    if (menuitem[3].active)
      {
      game.songnum=-1;
      checkmusic();

      game.editing=1;
      game.levelnum=0;
      createlevel();
      gameloop();

      game.editing=0;
      }
    if (menuitem[4].active)
      {
      newmappackmenu();
      }
    }

  resetmenuitems();
  }

void loadlevelmenu(void)
  {
  int count,count2;
  int changeddir;
  int numoffiles;
  int pagenum;

  changeddir=chdir("level");

  listfiles("*.lvl",levellist,0);

  if (changeddir==0)
    chdir("..");

  numoffiles=0;
  while (levellist[numoffiles][0]!=0)
    numoffiles++;

  pagenum=0;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    count=0;
    for (count2=0;count2<8;count2++)
    if (pagenum+count<numoffiles)
      {
      createmenuitem(levellist[pagenum+count],64,320+count2*12,12,1.0f,1.0f,1.0f,1.0f);
      count++;
      }
    for (count2=0;count2<8;count2++)
    if (pagenum+count<numoffiles)
      {
      createmenuitem(levellist[pagenum+count],256,320+count2*12,12,1.0f,1.0f,1.0f,1.0f);
      count++;
      }
    for (count2=0;count2<8;count2++)
    if (pagenum+count<numoffiles)
      {
      createmenuitem(levellist[pagenum+count],448,320+count2*12,12,1.0f,1.0f,1.0f,1.0f);
      count++;
      }

    createmenuitem(TXT_PAGE_UP,(304|TEXT_END),416,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_PAGEUP);
    setmenuitem(MO_SET,&pagenum,pagenum-24);
    if (pagenum<24)
      setmenuitem(MO_HIGHLIGHT,0);

    createmenuitem(TXT_PAGE_DOWN,320,416,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_PAGEDOWN);
    setmenuitem(MO_SET,&pagenum,pagenum+24);
    if (pagenum+24>=numoffiles)
      setmenuitem(MO_HIGHLIGHT,0);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(620);

    drawtext(TXT_LOAD_LEVEL,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    for (count=1;count<=24;count++)
    if (pagenum+count-1<numoffiles)
    if (menuitem[count].active)
      {
      game.editing=0;
      game.levelnum=0;
      loadlevel(levellist[pagenum+count-1]);
      gameloop();

      joymenunum=count;
      }
    }

  resetmenuitems();
  }

void playcampaignmenu(void)
  {
  int count,count2;
  int changeddir;
  int numoffiles;
  int pagenum;

  changeddir=chdir("level");

  listfiles("*.gmp",levellist,0);

  if (changeddir==0)
    chdir("..");

  numoffiles=0;
  while (levellist[numoffiles][0]!=0)
    numoffiles++;

  pagenum=0;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    count=0;
    for (count2=0;count2<8;count2++)
    if (pagenum+count<numoffiles)
      {
      createmenuitem(levellist[pagenum+count],64,320+count2*12,12,1.0f,1.0f,1.0f,1.0f);
      count++;
      }
    for (count2=0;count2<8;count2++)
    if (pagenum+count<numoffiles)
      {
      createmenuitem(levellist[pagenum+count],256,320+count2*12,12,1.0f,1.0f,1.0f,1.0f);
      count++;
      }
    for (count2=0;count2<8;count2++)
    if (pagenum+count<numoffiles)
      {
      createmenuitem(levellist[pagenum+count],448,320+count2*12,12,1.0f,1.0f,1.0f,1.0f);
      count++;
      }

    createmenuitem(TXT_PAGE_UP,(304|TEXT_END),416,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_PAGEUP);
    setmenuitem(MO_SET,&pagenum,pagenum-24);
    if (pagenum<24)
      setmenuitem(MO_HIGHLIGHT,0);

    createmenuitem(TXT_PAGE_DOWN,320,416,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_PAGEDOWN);
    setmenuitem(MO_SET,&pagenum,pagenum+24);
    if (pagenum+24>=numoffiles)
      setmenuitem(MO_HIGHLIGHT,0);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(620);

    drawtext(TXT_PLAY_CAMPAIGN,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    for (count=1;count<=24;count++)
    if (pagenum+count-1<numoffiles)
    if (menuitem[count].active)
      {
      strcpy(mappack.filename,levellist[pagenum+count-1]);
      loadmappack();
      campaignmenu();
      }
    }

  resetmenuitems();
  }

void campaignmenu(void)
  {
  int count;

  loadplayermappack();

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
    if (playermappack[playernum].levelnum>0)
      {
      createmenuitem(TXT_CONTINUE,48,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_C);
      count+=16;
      }
    else
      createmenuitemempty();
    createmenuitem(TXT_NEW_GAME,48,count,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_N);
    count+=16;

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(620);

    drawtext(mappack.name,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);

    if (player[playernum].levelnum>0)
      drawtext(TXT_PLAYER_INFO_MAPPACK,(320|TEXT_CENTER),320,12,1.0f,1.0f,1.0f,1.0f,mappack.levelname[playermappack[playernum].levelnum-1],playermappack[playernum].numoflives,playermappack[playernum].totalscore,playermappack[playernum].highscore);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[1].active || menuitem[2].active)
      {
      if (menuitem[2].active)
        {
        playerdifficultymenu();
        if (game.difficulty==-1)
          {
          game.difficulty=0;
          goto newgamebypass;
          }

        playermappack[playernum].difficulty=game.difficulty;

        playermappack[playernum].levelnum=1;
        playermappack[playernum].totalscore=0;
        playermappack[playernum].numoflives=5;
        if (playermappack[playernum].difficulty==3)
          playermappack[playernum].numoflives=0;
        }

      mappackpregamemenu();

      newgamebypass:;
      }
    }

  resetmenuitems();

  saveplayermappack();
  }

void loadplayermappack(void)
  {
  int count;
  int version;
  int changeddir;
  char filename[32];

  changeddir=chdir("player");

  count=0;
  while (count<24 && mappack.filename[count]!='.')
    {
    filename[count]=mappack.filename[count];
    count++;
    }
  filename[count]=0;

  strcat(filename,".gpp");

  playermappack[playernum].levelnum=0;

  if ((fp=fopen(filename,"rb"))!=NULL)
    {
    fread2(&version,4,1,fp);
    if (version==1)
      {
      for (count=0;count<8;count++)
        {
        fread2(&playermappack[count].levelnum,4,1,fp);
        fread2(&playermappack[count].numoflives,4,1,fp);
        fread2(&playermappack[count].totalscore,4,1,fp);
        fread2(&playermappack[count].difficulty,4,1,fp);
        fread2(&player[count].highscore,4,1,fp);
        }
      }
    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");
  }

void saveplayermappack(void)
  {
  int count;
  int version;
  int changeddir;
  char filename[32];

  changeddir=chdir("player");

  count=0;
  while (count<24 && mappack.filename[count]!='.')
    {
    filename[count]=mappack.filename[count];
    count++;
    }
  filename[count]=0;

  strcat(filename,".gpp");

  if ((fp=fopen(filename,"wb"))!=NULL)
    {
    version=1;
    fwrite2(&version,4,1,fp);
    for (count=0;count<8;count++)
      {
      fwrite2(&playermappack[count].levelnum,4,1,fp);
      fwrite2(&playermappack[count].numoflives,4,1,fp);
      fwrite2(&playermappack[count].totalscore,4,1,fp);
      fwrite2(&playermappack[count].difficulty,4,1,fp);
      fwrite2(&player[count].highscore,4,1,fp);
      }
    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");
  }

void loadmappack(void)
  {
  int count;
  int version;
  int changeddir;

  changeddir=chdir("level");

  if ((fp=fopen(mappack.filename,"rb"))!=NULL)
    {
    fread2(&version,4,1,fp);

    if (version==1)
      {
      fread2(&mappack.numoflevels,4,1,fp);
      fread2(mappack.name,1,32,fp);
      for (count=0;count<64;count++)
        {
        fread2(mappack.level[count],1,32,fp);
        fread2(mappack.levelname[count],1,32,fp);
        fread2(mappack.levelmusic[count],1,32,fp);
        }
      for (count=0;count<16;count++)
        fread2(mappack.ending[count],1,64,fp);
      }

    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");
  }

void savemappack(void)
  {
  int count;
  int version;
  int changeddir;

  changeddir=chdir("level");

  if ((fp=fopen(mappack.filename,"wb"))!=NULL)
    {
    version=1;
    fwrite2(&version,4,1,fp);

    fwrite2(&mappack.numoflevels,4,1,fp);
    fwrite2(mappack.name,1,32,fp);
    for (count=0;count<64;count++)
      {
      fwrite2(mappack.level[count],1,32,fp);
      fwrite2(mappack.levelname[count],1,32,fp);
      fwrite2(mappack.levelmusic[count],1,32,fp);
      }
    for (count=0;count<16;count++)
      fwrite2(mappack.ending[count],1,64,fp);

    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");
  }

void newmappackmenu(void)
  {
  int count;

  joystickmenu=0;

  resetmenuitems();

  while (!menuitem[0].active && !menuitem[1].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    createmenuitem(TXT_SAVE,(640|TEXT_END),0,16,1.0f,1.0f,1.0f,1.0f);
    createmenuitem(TXT_ADD_LEVEL,(640|TEXT_END),464,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_A);
    createmenuitem(TXT_DELETE_LEVEL,0,464,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_DELETE);

    createmenuitem(TXT_FILENAME"        ",0,32,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_STRINGINPUT,mappack.filename);
    setmenuitem(MO_HOTKEY,SCAN_ENTER);

    createmenuitem(TXT_NAME"            ",0,64,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_STRINGINPUT,mappack.name);

    createmenuitem(TXT_LEVEL" "TXT_FILENAME"    ",0,128,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_STRINGINPUT,mappack.level[mappack.numoflevels]);
    setmenuitem(MO_HOTKEY,SCAN_F);

    createmenuitem(TXT_LEVELNAME"      ",0,160,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_STRINGINPUT,mappack.levelname[mappack.numoflevels]);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    drawtext(TXT_FILENAME,320,52,12,1.0f,1.0f,1.0f,1.0f);
    drawtext(TXT_LEVELNAME,480,52,12,1.0f,1.0f,1.0f,1.0f);

    for (count=0;count<mappack.numoflevels;count++)
      {
      drawtext(mappack.level[count],320,64+count*12,12,1.0f,1.0f,1.0f,1.0f);
      drawtext(mappack.levelname[count],480,64+count*12,12,1.0f,1.0f,1.0f,1.0f);
      }

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[2].active)
      {
      if (mappack.level[mappack.numoflevels][0]!=0)
      if (mappack.numoflevels<63)
        {
        strcpy(mappack.level[mappack.numoflevels+1],mappack.level[mappack.numoflevels]);
        strcpy(mappack.levelname[mappack.numoflevels+1],mappack.levelname[mappack.numoflevels]);
        mappack.numoflevels++;
        }
      menuitem[2].active=0;
      }
    if (menuitem[3].active)
      {
      if (mappack.numoflevels>0)
        mappack.numoflevels--;
      menuitem[3].active=0;
      }
    }

  if (menuitem[1].active)
    savemappack();

  resetmenuitems();

  joystickmenu=1;
  }

