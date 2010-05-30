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

void highscoremenu(int levelnum)
  {
  int count,count2;
  int replaysaved;
  float bright;

  replaysaved=0;

  count2=-1;

  if (game.exit==4)
    {
    count2=10;

    while (count2>0 && game.time>highscore[levelnum][count2-1].time)
      count2--;

    if (count2!=10)
      {
      for (count=10;count>=count2;count--)
        {
        highscore[levelnum][count+1].time=highscore[levelnum][count].time;
        memcpy(highscore[levelnum][count+1].name,highscore[levelnum][count].name,32);
        }
      highscore[levelnum][count2].time=game.time;
      memcpy(highscore[levelnum][count2].name,player[playernum].name,32);
      }
    }
  
  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    if (game.exit==4)
    if (!replaysaved)
      createmenuitem(TXT_SAVEREPLAY,96,356,16,1.0f,1.0f,1.0f,1.0f);

    if (game.exit!=4)
      {
      count=320;
      createmenuitem(TXT_LEVEL" 1",64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,1);
      count+=16;
      createmenuitem(TXT_LEVEL" 2",64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,2);
      count+=16;
      createmenuitem(TXT_LEVEL" 3",64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,3);
      count+=16;
      createmenuitem(TXT_LEVEL" 4",64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,4);
      count+=16;
      createmenuitem(TXT_LEVEL" 5",64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,5);
      count+=16;
      createmenuitem(TXT_LEVEL" 6",64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,6);
      count+=16;
      createmenuitem(TXT_LEVEL" 7",64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,7);
      count+=16;
      createmenuitem(TXT_LEVEL" 8",64,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,8);
      count+=16;
  
      count=320;
      createmenuitem(TXT_LEVEL" 9",240,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,9);
      count+=16;
      createmenuitem(TXT_LEVEL" 10",240,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,10);
      count+=16;
      createmenuitem(TXT_LEVEL" 11",240,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,11);
      count+=16;
      createmenuitem(TXT_LEVEL" 12",240,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,12);
      count+=16;
      createmenuitem(TXT_LEVEL" 13",240,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,13);
      count+=16;
      createmenuitem(TXT_LEVEL" 14",240,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,14);
      count+=16;
      createmenuitem(TXT_LEVEL" 15",240,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,15);
      count+=16;
      createmenuitem(TXT_LEVEL" 16",240,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,16);
      count+=16;
  
      count=320;
      createmenuitem(TXT_LEVEL" 17",416,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,17);
      count+=16;
      createmenuitem(TXT_LEVEL" 18",416,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,18);
      count+=16;
      createmenuitem(TXT_LEVEL" 19",416,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,19);
      count+=16;
      createmenuitem(TXT_LEVEL" 20",416,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,20);
      count+=16;
      createmenuitem(TXT_LEVEL" 21",416,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,21);
      count+=16;
      createmenuitem(TXT_LEVEL" 22",416,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,22);
      count+=16;
      createmenuitem(TXT_LEVEL" 23",416,count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_SET,&levelnum,23);
      count+=16;
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
    displaybackground(580);

    drawtext(TXT_LEVEL_HIGHSCORE,(320|TEXT_CENTER),48,16,1.0f,1.0f,1.0f,1.0f,levelnum);

    drawtext(TXT_NAME,96+64,80,16,1.0f,1.0f,1.0f,1.0f);
    drawtext(TXT_TIME,96+320,80,16,1.0f,1.0f,1.0f,1.0f);
    for (count=0;count<10;count++)
      {
      if (count==count2 || count2==-1)
        bright=1.0f;
      else
        bright=0.5f;

      drawtext("/i.",96,112+count*16,16,bright,bright,bright,1.0f,count+1);
      drawtext(highscore[levelnum][count].name,96+64,112+count*16,16,bright,bright,bright,1.0f);
      if (((highscore[levelnum][count].time/50)%60)>=10)
        drawtext("/i:/i./i",96+320,112+count*16,16,bright,bright,bright,1.0f,(highscore[levelnum][count].time/3000),((highscore[levelnum][count].time/50)%60),((highscore[levelnum][count].time/5)%10));
      else
        drawtext("/i:0/i./i",96+320,112+count*16,16,bright,bright,bright,1.0f,(highscore[levelnum][count].time/3000),((highscore[levelnum][count].time/50)%60),((highscore[levelnum][count].time/5)%10));
      }
    if (game.exit==4)
      {
      drawtext(player[playernum].name,96+64,292,16,1.0f,1.0f,1.0f,1.0f);
      if (((game.time/50)%60)>=10)
        drawtext("/i:/i./i",96+320,292,16,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60),((game.time/5)%10));
      else
        drawtext("/i:0/i./i",96+320,292,16,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60),((game.time/5)%10));
      }
    if (game.exit==4)
    if (replaysaved)
      createmenuitem(TXT_REPLAYSAVED,96,356,16,1.0f,1.0f,1.0f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (game.exit==4)
    if (menuitem[1].active)
      {
      savereplay(levelnum);
      replaysaved=1;
      menuitem[1].active=0;
      }
    }

  resetmenuitems();
  }

void savescores(void)
  {
  int count,count2;
  int version;

  if ((fp=fopen("gish.his","wb"))!=NULL)
    {
    version=2;
    fwrite2(&version,4,1,fp);
    for (count=0;count<32;count++)
    for (count2=0;count2<16;count2++)
      {
      fwrite2(&highscore[count][count2].time,4,1,fp);
      fwrite2(highscore[count][count2].name,1,32,fp);
      }
    fclose(fp);
    }
  }

void loadscores(void)
  {
  int count,count2;
  int version;

  for (count=0;count<32;count++)
  for (count2=0;count2<16;count2++)
    {
    highscore[count][count2].time=0;
    strcpy(highscore[count][count2].name,"Empty");
    }

  if ((fp=fopen("gish.his","rb"))!=NULL)
    {
    fread2(&version,4,1,fp);
    if (version==2)
      {
      for (count=0;count<32;count++)
      for (count2=0;count2<16;count2++)
        {
        fread2(&highscore[count][count2].time,4,1,fp);
        fread2(highscore[count][count2].name,1,32,fp);
        }
      }
    fclose(fp);
    }
  }

