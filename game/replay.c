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

void saveinputs(void)
  {
  if (numofreplayframes>=65535)
    return;

  replayframe[numofreplayframes].button=object[0].button;
  if (object[0].axis[0]==-1.0f)
    replayframe[numofreplayframes].button|=16;
  if (object[0].axis[0]==1.0f)
    replayframe[numofreplayframes].button|=32;
  if (object[0].axis[1]==-1.0f)
    replayframe[numofreplayframes].button|=64;
  if (object[0].axis[1]==1.0f)
    replayframe[numofreplayframes].button|=128;
  numofreplayframes++;
  }

void loadinputs(void)
  {
  if (numofreplayframes>=65535)
    return;

  object[0].axis[0]=0.0f;
  object[0].axis[1]=0.0f;
  if ((replayframe[numofreplayframes].button&16)==16)
    object[0].axis[0]=-1.0f;
  if ((replayframe[numofreplayframes].button&32)==32)
    object[0].axis[0]=1.0f;
  if ((replayframe[numofreplayframes].button&64)==64)
    object[0].axis[1]=-1.0f;
  if ((replayframe[numofreplayframes].button&128)==128)
    object[0].axis[1]=1.0f;
  object[0].button=replayframe[numofreplayframes].button&15;
  numofreplayframes++;
  }

void savereplay(int levelnum)
  {
  int count;
  int version;
  int changeddir;
  char filename[32];

  count=0;
  while (count<12 && player[playernum].name[count]!=0)
    {
    filename[count]=player[playernum].name[count];
    count++;
    }
  filename[count]='-';
  count++;
  if (levelnum<100)
    {
    filename[count]='C';
    count++;
    filename[count]=48+levelnum/10;
    count++;
    filename[count]=48+levelnum%10;
    count++;
    }
  else
    {
    filename[count]=48+(levelnum-100)/10;
    count++;
    filename[count]=48+(levelnum-100)%10;
    count++;
    }
  filename[count]='.';
  count++;
  filename[count]='g';
  count++;
  filename[count]='r';
  count++;
  filename[count]='e';
  count++;
  filename[count]=0;
  count++;

  changeddir=chdir("replay");

  if ((fp=fopen(filename,"wb"))!=NULL)
    {
    version=1;
    fwrite2(&version,4,1,fp);
    fwrite2(&levelnum,4,1,fp);
    fwrite2(&numofreplayframes,4,1,fp);
    if (numofreplayframes<65536)
    for (count=0;count<numofreplayframes;count++)
      fwrite2(&replayframe[count].button,1,1,fp);
    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");
  }

int loadreplay(char *filename)
  {
  int count;
  int version;
  int levelnum;
  int changeddir;
  char filenametemp[32];

  count=0;
  while (count<16 && filename[count]!=0 && filename[count]!='.')
    {
    filenametemp[count]=filename[count];
    count++;
    }
  filenametemp[count]='.';
  count++;
  filenametemp[count]='g';
  count++;
  filenametemp[count]='r';
  count++;
  filenametemp[count]='e';
  count++;
  filenametemp[count]=0;
  count++;

  changeddir=chdir("replay");

  levelnum=-1;

  if ((fp=fopen(filenametemp,"rb"))!=NULL)
    {
    fread2(&version,4,1,fp);
    if (version==1)
      {
      fread2(&levelnum,4,1,fp);
      fread2(&numofreplayframes,4,1,fp);
      if (numofreplayframes<65536)
      for (count=0;count<numofreplayframes;count++)
        fread2(&replayframe[count].button,1,1,fp);
      }
    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");

  return(levelnum);
  }

void replaymenu(void)
  {
#ifndef DEMO
  int count,count2;
  int changeddir;
  int numoffiles;
  int pagenum;

  changeddir=chdir("replay");

  listfiles("*.gre",levellist,0);

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
    createmenuitem(TXT_EXIT,0,0,16,1.0f,1.0f,1.0f,1.0f);
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

    drawtext(TXT_REPLAY_MODE,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    for (count=1;count<=24;count++)
    if (pagenum+count-1<numoffiles)
    if (menuitem[count].active)
      {
      game.editing=0;
      game.levelnum=0;
      count2=loadreplay(levellist[pagenum+count-1]);

      if (count2!=-1)
        {
        if (count2<100)
          loadcollectionlevel(count2);
        else
          {
          game.levelnum=count2-100;
          loadstorylevel(game.levelnum);
          }
        game.playreplay=1;
        gameloop();
        game.playreplay=0;
        }
      joymenunum=count;
      }
    }

  resetmenuitems();
#else
  int count;
  char filename[32];

  filename[0]=0;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_EXIT,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    createmenuitem(TXT_PLAY_REPLAY" 1",64,352,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_1);
    createmenuitem(TXT_PLAY_REPLAY" 2",64,368,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_2);
    createmenuitem(TXT_PLAY_REPLAY" 3",64,384,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_3);
    createmenuitem(TXT_PLAY_REPLAY" 4",64,400,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_4);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(620);

    drawtext("Replay Mode",(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[1].active)
      {
      count=loadreplay("demo01.gre");
    
      if (count!=-1)
        {
        game.levelnum=count-100;
        loadstorylevel(game.levelnum);
      
        game.playreplay=1;
        gameloop();
        game.playreplay=0;
        }
      menuitem[1].active=0;
      }
    if (menuitem[2].active)
      {
      count=loadreplay("demo02.gre");
    
      if (count!=-1)
        {
        game.levelnum=count-100;
        loadstorylevel(game.levelnum);
      
        game.playreplay=1;
        gameloop();
        game.playreplay=0;
        }
      menuitem[2].active=0;
      }
    if (menuitem[3].active)
      {
      count=loadreplay("demo03.gre");
    
      if (count!=-1)
        {
        game.levelnum=count-100;
        loadstorylevel(game.levelnum);
      
        game.playreplay=1;
        gameloop();
        game.playreplay=0;
        }
      menuitem[3].active=0;
      }
    if (menuitem[4].active)
      {
      count=loadreplay("demo04.gre");
    
      if (count!=-1)
        {
        game.levelnum=count-100;
        loadstorylevel(game.levelnum);
      
        game.playreplay=1;
        gameloop();
        game.playreplay=0;
        }
      menuitem[4].active=0;
      }
    }

  resetmenuitems();
#endif
  }

