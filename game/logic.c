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

void gamelogic(void)
  {
  int count;
  float vec[3];

  vec[0]=127.5f;
  vec[1]=127.5f;
  vec[2]=10.0f;

  if (level.gametype<10)
    {
    if (view.position[0]<object[0].position[0]-2.0f)
      view.position[0]=object[0].position[0]-2.0f;
    if (view.position[0]>object[0].position[0]+2.0f)
      view.position[0]=object[0].position[0]+2.0f;
    if (view.position[1]<object[0].position[1]-1.5f)
      view.position[1]=object[0].position[1]-1.5f;
    if (view.position[1]>object[0].position[1]+1.5f)
      view.position[1]=object[0].position[1]+1.5f;

    if (game.oldschool==1)
      view.position[1]=131.5f;

    if (game.oldschool==2)
      {
      count=object[0].position[0]+16.0f;
      count/=32;
      count*=32;
      view.position[0]=count;
      view.position[1]=126.0f;
      }
    if (game.oldschool==3)
      {
      view.position[0]=128.0f;
      view.position[1]=134.0f;
      }
    }
  else
    {
    if (level.gametype==10)
      {
      view.position[0]=127.5f;
      view.position[1]=127.5f;
      view.position[2]=10.0f;
      }
    if (level.gametype==11)
      {
      view.position[0]=127.0f;
      view.position[1]=124.5f;
      view.position[2]=10.0f;
      }
    if (level.gametype==12)
      {
      view.position[0]=126.5f;
      view.position[1]=130.0f;
      view.position[2]=10.0f;
      }
    if (level.gametype==13)
      {
      view.position[0]=127.0f;
      view.position[1]=124.5f;
      view.position[2]=10.0f;
      }
    if (level.gametype==14)
      {
      if (view.position[0]<object[0].position[0]-4.0f)
        view.position[0]=object[0].position[0]-4.0f;
      if (view.position[0]<object[1].position[0]-4.0f)
        view.position[0]=object[1].position[0]-4.0f;
      view.position[1]=127.5f;
      view.position[2]=10.0f;
      }
    if (level.gametype==15)
      {
      view.position[0]=122.0f;
      view.position[1]=133.5f;
      view.position[2]=10.0f;
      }
    if (level.gametype==16)
      {
      view.position[0]=127.5f;
      view.position[1]=127.5f;
      view.position[2]=10.0f;
      }
    if (level.gametype==17)
      {
      view.position[0]=127.5f;
      view.position[1]=127.5f;
      view.position[2]=10.0f;
      }
    if (level.gametype==18)
      {
      view.position[0]=127.5f;
      view.position[1]=127.5f;
      view.position[2]=10.0f;
      }
    }

  if (game.over!=0)
    return;

  if (level.gametype==0)
    {
    if (game.combo>1)
      {
      if (game.combodelay>0)
        game.combodelay--;
      if (game.combodelay<=0)
        {
        game.combo=1;
        game.combodelay=0;
        }
      }
    else
      {
      game.combo=1;
      game.combodelay=0;
      }

    if (object[0].hitpoints<=0)
      {
      object[0].hitpoints=0;
      game.over=1;
      if (game.levelnum==65)
        playsound(24,object[0].position,NULL,1.0f,0,1.0f,-1,0);
      }

    if (object[0].position[0]>=level.area[0][0] && object[0].position[0]<level.area[0][2])
    if (object[0].position[1]>=level.area[0][1] && object[0].position[1]<level.area[0][3])
      game.over=2;

    if (game.levelnum==34)
    if (object[2].position[0]>=level.area[1][0] && object[2].position[0]<level.area[1][2])
    if (object[2].position[1]>=level.area[1][1] && object[2].position[1]<level.area[1][3])
      game.over=2;
    if (game.levelnum==34)
    if (object[2].position[0]>=level.area[2][0] && object[2].position[0]<level.area[2][2])
    if (object[2].position[1]>=level.area[2][1] && object[2].position[1]<level.area[2][3])
      game.over=3;

    if (game.levelnum==3)
    if (object[0].position[0]>=level.area[1][0] && object[0].position[0]<level.area[1][2])
    if (object[0].position[1]>=level.area[1][1] && object[0].position[1]<level.area[1][3])
      game.over=3;

    if (game.levelnum==4)
    if (object[0].position[0]>=level.area[1][0] && object[0].position[0]<level.area[1][2])
    if (object[0].position[1]>=level.area[1][1] && object[0].position[1]<level.area[1][3])
      game.over=3;

    if (game.levelnum==8)
    if (object[0].position[0]>=level.area[1][0] && object[0].position[0]<level.area[1][2])
    if (object[0].position[1]>=level.area[1][1] && object[0].position[1]<level.area[1][3])
      game.over=3;

    if (game.levelnum==18)
    if (object[0].position[0]>=level.area[1][0] && object[0].position[0]<level.area[1][2])
    if (object[0].position[1]>=level.area[1][1] && object[0].position[1]<level.area[1][3])
      game.over=3;

    if (game.levelnum==25)
    if (object[0].position[0]>=level.area[1][0] && object[0].position[0]<level.area[1][2])
    if (object[0].position[1]>=level.area[1][1] && object[0].position[1]<level.area[1][3])
      game.over=3;

    if (game.levelnum==64)
    if (object[0].position[0]>=level.area[1][0] && object[0].position[0]<level.area[1][2])
    if (object[0].position[1]>=level.area[1][1] && object[0].position[1]<level.area[1][3])
      game.over=3;

    if (game.levelnum==64)
    if (object[0].position[0]>=level.area[2][0] && object[0].position[0]<level.area[2][2])
    if (object[0].position[1]>=level.area[2][1] && object[0].position[1]<level.area[2][3])
      game.over=4;

    if (game.levelnum==64)
    if (object[0].position[0]>=level.area[3][0] && object[0].position[0]<level.area[3][2])
    if (object[0].position[1]>=level.area[3][1] && object[0].position[1]<level.area[3][3])
      game.over=5;

    if (game.over==0)
    if (game.bosslevel)
    if (game.levelnum!=34)
      {
      game.over=2;
      for (count=0;count<numofobjects;count++)
        if (object[count].type==4)
          game.over=0;
      if (numofbosses>0)
        game.over=0;
      }

    game.time++;
    }
  if (level.gametype==1)
  if (game.startdelay==0)
    {
    if (object[0].hitpoints<=0)
      {
      object[0].hitpoints=0;
      game.over=1;
      }
    game.time--;
    if (game.time<=0)
      game.over=1;
    if (game.bonus[5]==game.numofbonus[5])
    if (game.bonus[6]==game.numofbonus[6])
    if (game.bonus[7]==game.numofbonus[7])
      game.over=2;
    }

  if (level.gametype==12)
    {
    if (game.startdelay==0)
      {
      if ((rand()&255)==0)
        {
        vec[0]=126.5f+(float)((rand()%15)-7);
        vec[1]=136.5f;
        vec[2]=10.0f;
    
        createamber(vec);
        }
      for (count=0;count<numofobjects;count++)
      if (object[count].type==6)
      if (object[count].position[1]<122.0f)
      if (object[count].timetolive>25)
        object[count].timetolive=25;

      game.time--;
      if (game.time<=0)
        game.over=1;
      }
    }

  if (level.gametype==10)
    {
    if (game.scoredelay==0)
      {
      if (game.startdelay==0)
        {
        game.time--;
        if (game.time<=0)
          game.over=1;
        }
      if (object[2].position[0]>=level.area[0][0] && object[2].position[0]<level.area[0][2])
      if (object[2].position[1]>=level.area[0][1] && object[2].position[1]<level.area[0][3])
        {
        game.score[1]+=7;
        game.scoredelay++;
        strcpy(game.text,TXT_TOUCHDOWN_GRAY);

        //playsound(6+(rand()&1),object[2].position,NULL,0.6f,0,1.0f);
        }
      if (object[2].position[0]>=level.area[1][0] && object[2].position[0]<level.area[1][2])
      if (object[2].position[1]>=level.area[1][1] && object[2].position[1]<level.area[1][3])
        {
        game.score[1]+=3;
        game.scoredelay++;
        strcpy(game.text,TXT_FIELDGOAL_GRAY);

        //playsound(6+(rand()&1),object[2].position,NULL,0.4f,0,1.0f);
        }
      if (object[2].position[0]>=level.area[2][0] && object[2].position[0]<level.area[2][2])
      if (object[2].position[1]>=level.area[2][1] && object[2].position[1]<level.area[2][3])
        {
        game.score[0]+=7;
        game.scoredelay++;
        strcpy(game.text,TXT_TOUCHDOWN_GISH);

        //playsound(6+(rand()&1),object[2].position,NULL,0.6f,0,1.0f);
        }
      if (object[2].position[0]>=level.area[3][0] && object[2].position[0]<level.area[3][2])
      if (object[2].position[1]>=level.area[3][1] && object[2].position[1]<level.area[3][3])
        {
        game.score[0]+=3;
        game.scoredelay++;
        strcpy(game.text,TXT_FIELDGOAL_GISH);

        //playsound(6+(rand()&1),object[2].position,NULL,0.4f,0,1.0f);
        }
      }
    else
      {
      game.scoredelay++;
      if (game.scoredelay==150)
        {
        setuplevel();
        game.scoredelay=0;
        game.startdelay=100;
        }
      }
    }
  if (level.gametype==11)
    {
    if (game.scoredelay==0)
      {
      if (object[0].position[0]>=level.area[0][0] && object[0].position[0]<level.area[0][2])
      if (object[0].position[1]>=level.area[0][1] && object[0].position[1]<level.area[0][3])
        {
        game.score[1]++;
        if (game.score[1]>=4)
          game.over=1;
        game.scoredelay++;
        strcpy(game.text,TXT_GRAYWINS_ROUND);

        //playsound(6+(rand()&1),object[2].position,NULL,0.6f,0,1.0f);
        }
      if (object[1].position[0]>=level.area[0][0] && object[1].position[0]<level.area[0][2])
      if (object[1].position[1]>=level.area[0][1] && object[1].position[1]<level.area[0][3])
        {
        game.score[0]++;
        if (game.score[0]>=4)
          game.over=1;
        game.scoredelay++;
        strcpy(game.text,TXT_GISHWINS_ROUND);

        //playsound(6+(rand()&1),object[2].position,NULL,0.6f,0,1.0f);
        }
      }
    else
      {
      game.scoredelay++;
      if (game.scoredelay==100)
        {
        setuplevel();
        game.scoredelay=0;
        game.startdelay=100;
        }
      }
    }
  if (level.gametype==13)
    {
    if (game.scoredelay==0)
      {
      if (object[0].hitpoints<=0)
        {
        object[0].hitpoints=0;
        game.score[1]++;
        if (game.score[1]>=4)
          game.over=1;
        game.scoredelay++;
        strcpy(game.text,TXT_GRAYWINS_ROUND);
        }
      if (object[1].hitpoints<=0)
        {
        object[1].hitpoints=0;
        game.score[0]++;
        if (game.score[0]>=4)
          game.over=1;
        game.scoredelay++;
        strcpy(game.text,TXT_GISHWINS_ROUND);
        }
      }
    else
      {
      if (object[0].hitpoints<0)
        object[0].hitpoints=0;
      if (object[1].hitpoints<0)
        object[1].hitpoints=0;

      game.scoredelay++;
      if (game.scoredelay==100)
        {
        setuplevel();
        game.scoredelay=0;
        game.startdelay=100;
        }
      }
    }
  if (level.gametype==14)
    {
    if (game.scoredelay==0)
      {
      if (object[6].position[0]>=level.area[2][0] && object[6].position[0]<level.area[2][2])
      if (object[6].position[1]>=level.area[2][1] && object[6].position[1]<level.area[2][3])
        {
        for (count=0;count<numofobjects;count++)
          {
          if (object[count].lighttype==2)
            {
            object[count].lightcolor[0]=0.0f;
            object[count].lightcolor[1]=1.0f;
            object[count].lightcolor[2]=0.0f;
            object[count].lighton=1;
            }
          }
        }
      if (object[6].position[0]>=level.area[3][0] && object[6].position[0]<level.area[3][2])
      if (object[6].position[1]>=level.area[3][1] && object[6].position[1]<level.area[3][3])
        {
        for (count=0;count<numofobjects;count++)
          {
          if (object[count].lighttype==2)
            {
            object[count].lightcolor[0]=1.0f;
            object[count].lightcolor[1]=1.0f;
            object[count].lightcolor[2]=0.0f;
            object[count].lighton=1;
            }
          }
        }
      if (object[6].position[0]>=level.area[4][0] && object[6].position[0]<level.area[4][2])
      if (object[6].position[1]>=level.area[4][1] && object[6].position[1]<level.area[4][3])
        {
        for (count=0;count<numofobjects;count++)
          {
          if (object[count].lighttype==2)
            {
            object[count].lightcolor[0]=1.0f;
            object[count].lightcolor[1]=0.0f;
            object[count].lightcolor[2]=0.0f;
            object[count].lighton=1;
            }
          }
        }

      if (object[0].position[0]>=level.area[0][0] && object[0].position[0]<level.area[0][2])
      if (object[0].position[1]>=level.area[0][1] && object[0].position[1]<level.area[0][3])
        {
        game.score[0]++;
        if (game.score[0]>=4)
          game.over=1;
        game.scoredelay++;
        strcpy(game.text,TXT_GISHWINS_ROUND);
        }
      if (object[1].position[0]>=level.area[1][0] && object[1].position[0]<level.area[1][2])
      if (object[1].position[1]>=level.area[1][1] && object[1].position[1]<level.area[1][3])
        {
        game.score[1]++;
        if (game.score[1]>=4)
          game.over=1;
        game.scoredelay++;
        strcpy(game.text,TXT_GRAYWINS_ROUND);
        }
      }
    else
      {
      game.scoredelay++;
      if (game.scoredelay==100)
        {
        setuplevel();
        view.position[0]=127.5f;
        view.position[1]=127.5f;
        view.position[2]=10.0f;
        game.scoredelay=0;
        game.startdelay=100;
        }
      }
    }
  if (level.gametype==15)
    {
    if (game.score[0]==game.numofbonus[5]/2)
      game.over=1;
    if (game.score[1]==game.numofbonus[5]/2)
      game.over=1;
    }

  if (level.gametype==17)
    {
    if (game.scoredelay==0)
      {
      if (game.startdelay==0)
        {
        game.time--;
        if (game.time<=0)
          game.over=1;
        }
      if (object[4].position[0]>=level.area[0][0] && object[4].position[0]<level.area[0][2])
      if (object[4].position[1]>=level.area[0][1] && object[4].position[1]<level.area[0][3])
        {
        game.score[1]+=7;
        game.scoredelay++;
        strcpy(game.text,TXT_TOUCHDOWN_GRAY);

        //playsound(6+(rand()&1),object[2].position,NULL,0.6f,0,1.0f);
        }
      if (object[4].position[0]>=level.area[1][0] && object[4].position[0]<level.area[1][2])
      if (object[4].position[1]>=level.area[1][1] && object[4].position[1]<level.area[1][3])
        {
        game.score[1]+=3;
        game.scoredelay++;
        strcpy(game.text,TXT_FIELDGOAL_GRAY);

        //playsound(6+(rand()&1),object[2].position,NULL,0.4f,0,1.0f);
        }
      if (object[4].position[0]>=level.area[2][0] && object[4].position[0]<level.area[2][2])
      if (object[4].position[1]>=level.area[2][1] && object[4].position[1]<level.area[2][3])
        {
        game.score[0]+=7;
        game.scoredelay++;
        strcpy(game.text,TXT_TOUCHDOWN_GISH);

        //playsound(6+(rand()&1),object[2].position,NULL,0.6f,0,1.0f);
        }
      if (object[4].position[0]>=level.area[3][0] && object[4].position[0]<level.area[3][2])
      if (object[4].position[1]>=level.area[3][1] && object[4].position[1]<level.area[3][3])
        {
        game.score[0]+=3;
        game.scoredelay++;
        strcpy(game.text,TXT_FIELDGOAL_GISH);

        //playsound(6+(rand()&1),object[2].position,NULL,0.4f,0,1.0f);
        }
      }
    else
      {
      game.scoredelay++;
      if (game.scoredelay==150)
        {
        setuplevel();
        game.scoredelay=0;
        game.startdelay=100;
        }
      }
    }
  if (level.gametype==18)
    {
    if (game.scoredelay==0)
      {
      if (object[0].position[0]>=level.area[0][0] && object[0].position[0]<level.area[0][2])
      if (object[0].position[1]>=level.area[0][1] && object[0].position[1]<level.area[0][3])
      if (object[2].position[0]>=level.area[0][0] && object[2].position[0]<level.area[0][2])
      if (object[2].position[1]>=level.area[0][1] && object[2].position[1]<level.area[0][3])
        {
        game.score[1]++;
        if (game.score[1]>=4)
          game.over=1;
        game.scoredelay++;
        strcpy(game.text,TXT_GRAYWINS_ROUND);

        //playsound(6+(rand()&1),object[2].position,NULL,0.6f,0,1.0f);
        }
      if (object[1].position[0]>=level.area[0][0] && object[1].position[0]<level.area[0][2])
      if (object[1].position[1]>=level.area[0][1] && object[1].position[1]<level.area[0][3])
      if (object[3].position[0]>=level.area[0][0] && object[3].position[0]<level.area[0][2])
      if (object[3].position[1]>=level.area[0][1] && object[3].position[1]<level.area[0][3])
        {
        game.score[0]++;
        if (game.score[0]>=4)
          game.over=1;
        game.scoredelay++;
        strcpy(game.text,TXT_GISHWINS_ROUND);

        //playsound(6+(rand()&1),object[2].position,NULL,0.6f,0,1.0f);
        }
      }
    else
      {
      game.scoredelay++;
      if (game.scoredelay==100)
        {
        setuplevel();
        game.scoredelay=0;
        game.startdelay=100;
        }
      }
    }

  if (game.startdelay>0)
    {
    //if (level.gametype==11 && game.startdelay==100)
    //  playsound(8,vec,NULL,0.8f,0,1.0f);
      
    game.startdelay--;
    }
  }

void gamedisplay(void)
  {
  int count;
  int keyhighlight;
  int keyhighlight2;
  float miny,maxy;
  float red,green,blue;

  if (game.over==0)
    {
    if ((level.gametype>=10 && level.gametype<=14) || level.gametype==17 || level.gametype==18)
      {
      if (game.scoredelay>0)
        drawtext(game.text,(320|TEXT_CENTER),(240|TEXT_CENTER),24,1.0f,1.0f,0.0f,1.0f);
      else if (game.startdelay>0)
        {
        if (game.startdelay>50)
          drawbackground(823,320-128,480-128,256,128,640,480);
        else
          drawbackground(822,320-128,480-128,256,128,640,480);
        //drawtext("Get Ready",(320|TEXT_CENTER),(240|TEXT_CENTER),24,0.0f,1.0f,0.0f,1.0f);
        }
      }
    }
  if (level.gametype==0 || level.gametype==1)
    {
    drawbackground(720,16,0,48,48,640,480);

    red=1.0f;
    green=(float)(object[0].hitpoints)/500.0f;
    if (green>1.0f)
      green=1.0f;
    blue=(float)(object[0].hitpoints-500)/500.0f;
    if (blue<0.0f)
      blue=0.0f;
    if (blue>1.0f)
      blue=1.0f;
    drawtext("/i",0,0,0,red,green,blue,1.0f,object[0].hitpoints/10);
    drawtextbitmap(64,12,24,24);
    glColor3f(1.0f,1.0f,1.0f);

    //drawtext("/i",(40|TEXT_CENTER),24,16,1.0f,1.0f,1.0f,1.0f,object[0].hitpoints/10);
    if (level.gametype==0)
      {
      if (!game.bosslevel)
        {
        drawtext("/i",0,0,0,1.0f,1.0f,1.0f,1.0f,game.score[0]);
        drawtextbitmap((608|TEXT_END),10,20,20);
        if (game.combo>2)
          {
          red=(float)game.combodelay/50.0f;
          if (red>1.0f)
            red=1.0f;
          drawtext(TXT_COMBO" x/i",(608|TEXT_END),30,16,1.0f,1.0f,1.0f,red,game.combo-1);
          }
        }
      if (!mappack.active)
        drawtext("/i",0,0,0,1.0f,1.0f,1.0f,1.0f,game.numoflives);
      else
        drawtext("/i",0,0,0,1.0f,1.0f,1.0f,1.0f,playermappack[playernum].numoflives);
      drawtextbitmap((40|TEXT_CENTER),38,16,16);

      if (game.dialog>0)
        {
        if (game.levelnum==6)
          {
          if (game.dialog==2)
            {
            drawbackground(513,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG2_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE7,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE8,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE9,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG2_LINE10,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==1)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          }
        if (game.levelnum==13)
          {
          if (game.dialog==3)
            {
            drawbackground(514,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG3_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG3_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG3_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG3_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG3_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG3_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG3_LINE7,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG3_LINE8,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG3_LINE9,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==2)
            {
            drawbackground(514,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG4_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG4_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG4_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG4_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG4_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG4_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG4_LINE7,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG4_LINE8,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG4_LINE9,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==1)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          }
        if (game.levelnum==20)
          {
          if (game.dialog==3)
            {
            drawbackground(515,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG5_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE7,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE8,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE9,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG5_LINE10,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==2)
            {
            drawbackground(515,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG6_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG6_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG6_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG6_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG6_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG6_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG6_LINE7,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==1)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          }
        if (game.levelnum==27)
          {
          if (game.dialog==3)
            {
            drawbackground(516,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG7_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG7_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG7_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG7_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG7_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG7_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG7_LINE7,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG7_LINE8,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG7_LINE9,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==2)
            {
            drawbackground(516,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG8_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG8_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG8_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG8_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG8_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG8_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==1)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          }
        if (game.levelnum==33)
          {
          if (game.dialog==3)
            {
            drawbackground(517,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG9_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG9_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG9_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG9_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG9_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG9_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG9_LINE7,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG9_LINE8,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG9_LINE9,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==2)
            {
            drawbackground(517,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG10_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG10_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG10_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG10_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG10_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==1)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          }
        if (game.levelnum==34)
          {
          if (game.dialog==8)
            {
            drawbackground(518,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG11_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==7)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          if (game.dialog==6)
            {
            drawbackground(518,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG11_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE7,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE8,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE9,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE10,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE11,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==5)
            {
            drawbackground(518,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG11_LINE12,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE13,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE14,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE15,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE16,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE17,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE18,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE19,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE20,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE21,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==4)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          if (game.dialog==3)
            {
            drawbackground(518,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG11_LINE22,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE23,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE24,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE25,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE26,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE27,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE28,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==2)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext(TXT_DIALOG11_LINE29,340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            if (game.dialogdelay>75)
              game.dialogdelay=75;
            }
          if (game.dialog==1)
            {
            drawbackground(518,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG11_LINE30,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE31,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE32,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE33,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG11_LINE34,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          }
        if (game.levelnum==68)
          {
          if (game.dialog==16)
            {
            drawbackground(527,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG12_LINE1,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==15)
            {
            drawbackground(527,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG12_LINE2,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE3,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE4,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE5,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE6,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==14)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext(TXT_DIALOG12_LINE7,340,104,12,1.0f,1.0f,1.0f,1.0f);
            drawtext(TXT_DIALOG12_LINE8,340,128,12,1.0f,1.0f,1.0f,1.0f);
            drawtext(TXT_DIALOG12_LINE9,340,140,12,0.5f,0.5f,0.5f,1.0f);
            }
          if (game.dialog==13)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext(TXT_DIALOG12_LINE10,340,104,12,1.0f,1.0f,1.0f,1.0f);
            drawtext(TXT_DIALOG12_LINE11,340,128,12,0.5f,0.5f,0.5f,1.0f);
            drawtext(TXT_DIALOG12_LINE12,340,140,12,1.0f,1.0f,1.0f,1.0f);
            }
          if (game.dialog==12)
            {
            drawbackground(527,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG12_LINE13,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE14,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE15,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE16,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==11)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          if (game.dialog==10)
            {
            drawbackground(527,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG12_LINE17,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE18,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE19,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==9)
            {
            drawbackground(527,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG12_LINE20,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE21,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==8)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext(TXT_DIALOG12_LINE22,340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          if (game.dialog==7)
            {
            drawbackground(527,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG12_LINE23,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE24,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE25,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE26,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==6)
            {
            drawbackground(512,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            drawtext("...",340,(128|TEXT_CENTER),12,1.0f,1.0f,1.0f,1.0f);
            }
          if (game.dialog==5)
            {
            drawbackground(527,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG12_LINE27,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE28,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE29,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          if (game.dialog==1)
            {
            drawbackground(527,(320|TEXT_CENTER),(128|TEXT_CENTER),384,128,640,480);
            count=68;
            drawtext(TXT_DIALOG12_LINE30,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            drawtext(TXT_DIALOG12_LINE31,132,count,12,1.0f,1.0f,1.0f,1.0f);
            count+=12;
            }
          }
        }
      }
    if (level.gametype==1)
      {
      drawbackground(722,528,0,96,48,640,480);

      drawtext("/i///i",0,0,0,1.0f,1.0f,1.0f,1.0f,game.bonus[5]+game.bonus[6]+game.bonus[7],game.numofbonus[5]+game.numofbonus[6]+game.numofbonus[7]);
      drawtextbitmap((576|TEXT_END),16,16,16);

      if (game.startdelay!=0)
        drawtext(TXT_GETREADY,(320|TEXT_CENTER),(240|TEXT_END),24,1.0f,1.0f,0.0f,1.0f);
      }

    if (level.gametype==0)
      {
      if (((game.time/50)%60)>=10)
        drawtext("/i:/i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60));
      else
        drawtext("/i:0/i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60));
      }
    if (level.gametype==1)
      {
      if (((game.time/50)%60)>=10)
        drawtext("/i:/i./i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60),((game.time/5)%10));
      else
        drawtext("/i:0/i./i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60),((game.time/5)%10));
      }
    if (level.gametype==0)
      drawtextbitmap((320|TEXT_CENTER),16,24,24);
    if (level.gametype==1)
      drawtextbitmap((320|TEXT_CENTER),16,32,32);
    }

  if ((level.gametype>=10 && level.gametype<=14) || level.gametype==17 || level.gametype==18)
    {
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    drawbackground(720,16,0,48,48,640,480);

    drawtext("/i",0,0,0,1.0f,1.0f,1.0f,1.0f,game.score[0]);
    drawtextbitmap(64,8,32,32);

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    drawbackground(721,576,0,48,48,640,480);

    drawtext("/i",0,0,0,1.0f,1.0f,1.0f,1.0f,game.score[1]);
    drawtextbitmap((576|TEXT_END),8,32,32);
    }
  if (level.gametype==15)
    {
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    drawbackground(720,16,0,48,48,640,480);

    drawtext("/i///i",0,0,0,1.0f,1.0f,1.0f,1.0f,game.score[0],game.numofbonus[5]/2);
    drawtextbitmap(64,8,24,24);

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    drawbackground(721,576,0,48,48,640,480);

    drawtext("/i///i",0,0,0,1.0f,1.0f,1.0f,1.0f,game.score[1],game.numofbonus[5]/2);
    drawtextbitmap((576|TEXT_END),8,24,24);
    }
  if (level.gametype==10 || level.gametype==17)
    {
    if (((game.time/50)%60)>=10)
      drawtext("/i:/i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60));
    else
      drawtext("/i:0/i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60));

    drawtextbitmap((320|TEXT_CENTER),16,32,32);

    if (game.over!=0)
      {
      if (game.score[0]>game.score[1])
        drawbackground(820,0,480-256,512,256,640,480);
        //drawtext("Gish Wins!",(320|TEXT_CENTER),(240|TEXT_CENTER),24,0.0f,1.0f,0.0f,1.0f);
      else  if (game.score[1]>game.score[0])
        drawbackground(821,640-512,480-256,512,256,640,480);
        //drawtext("Gray Wins!",(320|TEXT_CENTER),(240|TEXT_CENTER),24,0.0f,1.0f,0.0f,1.0f);
      else
        drawtext(TXT_TIE,(320|TEXT_CENTER),(240|TEXT_CENTER),24,0.0f,1.0f,0.0f,1.0f);
      }
    }
  if (level.gametype==11 || level.gametype==18)
    {
    if (game.over!=0)
      {
      if (game.score[0]>game.score[1])
        drawbackground(820,0,480-256,512,256,640,480);
        //drawtext("Gish Wins!",(320|TEXT_CENTER),(240|TEXT_CENTER),24,0.0f,1.0f,0.0f,1.0f);
      else
        drawbackground(821,640-512,480-256,512,256,640,480);
        //drawtext("Gray Wins!",(320|TEXT_CENTER),(240|TEXT_CENTER),24,0.0f,1.0f,0.0f,1.0f);
      }
    }
  if (level.gametype==12)
    {
    if (((game.time/50)%60)>=10)
      drawtext("/i:/i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60));
    else
      drawtext("/i:0/i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60));

    drawtextbitmap((320|TEXT_CENTER),16,32,32);
    if (game.over!=0)
      {
      if (game.score[0]>game.score[1])
        drawbackground(820,0,480-256,512,256,640,480);
      else
        drawbackground(821,640-512,480-256,512,256,640,480);
      }
    }
  if (level.gametype==13)
    {
    red=1.0f;
    green=(float)(object[0].hitpoints)/500.0f;
    if (green>1.0f)
      green=1.0f;
    blue=(float)(object[0].hitpoints-500)/500.0f;
    if (blue<0.0f)
      blue=0.0f;
    if (blue>1.0f)
      blue=1.0f;

    drawtext("/i",0,0,0,red,green,blue,1.0f,object[0].hitpoints/10);
    drawtextbitmap(64,40,16,16);
    glColor3f(1.0f,1.0f,1.0f);

    red=1.0f;
    green=(float)(object[1].hitpoints)/500.0f;
    if (green>1.0f)
      green=1.0f;
    blue=(float)(object[1].hitpoints-500)/500.0f;
    if (blue<0.0f)
      blue=0.0f;
    if (blue>1.0f)
      blue=1.0f;

    drawtext("/i",0,0,0,red,green,blue,1.0f,object[1].hitpoints/10);
    drawtextbitmap((576|TEXT_END),40,16,16);
    glColor3f(1.0f,1.0f,1.0f);
    /*
    if (((game.time/50)%60)>=10)
      drawtext("/i:/i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60));
    else
      drawtext("/i:0/i",0,0,0,1.0f,1.0f,1.0f,1.0f,(game.time/3000),((game.time/50)%60));
    drawtextbitmap((320|TEXT_CENTER),16,32,32);
    */
    if (game.over!=0)
      {
      if (game.score[0]>game.score[1])
        drawbackground(820,0,480-256,512,256,640,480);
      else
        drawbackground(821,640-512,480-256,512,256,640,480);
      }
    }
  if (level.gametype==14)
    {
    if (game.over!=0)
      {
      if (game.score[0]>game.score[1])
        drawbackground(820,0,480-256,512,256,640,480);
      else
        drawbackground(821,640-512,480-256,512,256,640,480);
      }
    }
  if (level.gametype==15)
    {
    if (game.over!=0)
      {
      if (game.score[0]>game.score[1])
        drawbackground(820,0,480-256,512,256,640,480);
      else
        drawbackground(821,640-512,480-256,512,256,640,480);
      }
    }
  if (game.levelnum==1)
    {
    keyhighlight=-1;
    keyhighlight2=-1;
    if (object[0].position[0]>=level.area[1][0] && object[0].position[0]<level.area[1][2])
    if (object[0].position[1]>=level.area[1][1] && object[0].position[1]<level.area[1][3])
      {
      count=68;
      drawtext(TXT_TUTORIAL_LINE1,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[6]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE2,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;

      keyhighlight=control[0].key[6];
      }
    if (object[0].position[0]>=level.area[2][0] && object[0].position[0]<level.area[2][2])
    if (object[0].position[1]>=level.area[2][1] && object[0].position[1]<level.area[2][3])
      {
      count=68;
      drawtext(TXT_TUTORIAL_LINE3,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[6]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE4,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;
      }
    if (object[0].position[0]>=level.area[3][0] && object[0].position[0]<level.area[3][2])
    if (object[0].position[1]>=level.area[3][1] && object[0].position[1]<level.area[3][3])
      {
      count=68;
      drawtext(TXT_TUTORIAL_LINE5,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[4]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE6,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[3]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE7,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;

      keyhighlight=control[0].key[4];
      keyhighlight2=control[0].key[3];
      }
    if (object[0].position[0]>=level.area[4][0] && object[0].position[0]<level.area[4][2])
    if (object[0].position[1]>=level.area[4][1] && object[0].position[1]<level.area[4][3])
      {
      count=68;
      drawtext(TXT_TUTORIAL_LINE8,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[5]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE9,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE10,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE11,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE12,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;

      miny=object[0].position[1];
      maxy=object[0].position[1];
      for (count=0;count<16;count++)
        {
        if (miny>particle[object[0].particle[count]].position[1])
          miny=particle[object[0].particle[count]].position[1];
        if (maxy<particle[object[0].particle[count]].position[1])
          maxy=particle[object[0].particle[count]].position[1];
        }

      if (maxy-miny<1.6f && maxy-level.area[4][1]<2.0f)
        keyhighlight=control[0].key[5];
      if (object[0].velocity[1]>0.02f)
        keyhighlight2=control[0].key[3];
      if (object[0].velocity[1]<-0.02f)
        keyhighlight2=control[0].key[2];
      }
    if (object[0].position[0]>=level.area[5][0] && object[0].position[0]<level.area[5][2])
    if (object[0].position[1]>=level.area[5][1] && object[0].position[1]<level.area[5][3])
      {
      count=68;
      drawtext(TXT_TUTORIAL_LINE13,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[7]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE14,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;

      keyhighlight=control[0].key[7];
      }
    if (object[0].position[0]>=level.area[6][0] && object[0].position[0]<level.area[6][2])
    if (object[0].position[1]>=level.area[6][1] && object[0].position[1]<level.area[6][3])
      {
      count=68;
      drawtext(TXT_TUTORIAL_LINE15,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[4]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE16,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[3]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE17,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f,keyboardlabel[control[0].key[0]]);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE18,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;
      drawtext(TXT_TUTORIAL_LINE19,(320|TEXT_CENTER),count,12,1.0f,1.0f,1.0f,1.0f);
      count+=12;

      keyhighlight=control[0].key[4];
      keyhighlight2=control[0].key[3];
      }

    drawtext(TXT_TUTORIAL_MOVEMENT,(536|TEXT_CENTER),(382|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    drawkeybitmap((512|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[0],keyhighlight,keyhighlight2);
    drawkeybitmap((536|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[2],keyhighlight,keyhighlight2);
    drawkeybitmap((560|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[1],keyhighlight,keyhighlight2);
    drawkeybitmap((536|TEXT_CENTER),(400|TEXT_CENTER),12,12,control[0].key[3],keyhighlight,keyhighlight2);

    count=sizeof(TXT_TUTORIAL_STICK)*6+24;
    drawtext(TXT_TUTORIAL_STICK,(count|TEXT_CENTER),(406|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    drawkeybitmap((count|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[4],keyhighlight,keyhighlight2);
    count+=(((sizeof(TXT_TUTORIAL_STICK)+sizeof(TXT_TUTORIAL_JUMP))/2)+1)*12;  //96;
    drawtext(TXT_TUTORIAL_JUMP,(count|TEXT_CENTER),(406|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    drawkeybitmap((count|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[5],keyhighlight,keyhighlight2);
    count+=(((sizeof(TXT_TUTORIAL_SLIDE)+sizeof(TXT_TUTORIAL_JUMP))/2)+1)*12;  //96;
    drawtext(TXT_TUTORIAL_SLIDE,(count|TEXT_CENTER),(406|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    drawkeybitmap((count|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[6],keyhighlight,keyhighlight2);
    count+=(((sizeof(TXT_TUTORIAL_SLIDE)+sizeof(TXT_TUTORIAL_HEAVY))/2)+1)*12; //96;
    drawtext(TXT_TUTORIAL_HEAVY,(count|TEXT_CENTER),(406|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    drawkeybitmap((count|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[7],keyhighlight,keyhighlight2);
    count+=96;
    }
  if (game.playreplay)
  if (keyboard[SCAN_K])
    {
    drawtext(TXT_TUTORIAL_MOVEMENT,(536|TEXT_CENTER),(382|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    keyhighlight=0;
    if (object[0].axis[0]==-1.0f)
      keyhighlight=1;
    drawkeybitmap2((512|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[0],keyhighlight);
    keyhighlight=0;
    if (object[0].axis[1]==-1.0f)
      keyhighlight=1;
    drawkeybitmap2((536|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[2],keyhighlight);
    keyhighlight=0;
    if (object[0].axis[0]==1.0f)
      keyhighlight=1;
    drawkeybitmap2((560|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[1],keyhighlight);
    keyhighlight=0;
    if (object[0].axis[1]==1.0f)
      keyhighlight=1;
    drawkeybitmap2((536|TEXT_CENTER),(400|TEXT_CENTER),12,12,control[0].key[3],keyhighlight);

    count=64;
    drawtext(TXT_TUTORIAL_STICK,(count|TEXT_CENTER),(406|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    keyhighlight=0;
    if ((object[0].button&1)==1)
      keyhighlight=1;
    drawkeybitmap2((count|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[4],keyhighlight);
    count+=96;
    drawtext(TXT_TUTORIAL_JUMP,(count|TEXT_CENTER),(406|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    keyhighlight=0;
    if ((object[0].button&2)==2)
      keyhighlight=1;
    drawkeybitmap2((count|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[5],keyhighlight);
    count+=96;
    drawtext(TXT_TUTORIAL_SLIDE,(count|TEXT_CENTER),(406|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    keyhighlight=0;
    if ((object[0].button&4)==4)
      keyhighlight=1;
    drawkeybitmap2((count|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[6],keyhighlight);
    count+=96;
    drawtext(TXT_TUTORIAL_HEAVY,(count|TEXT_CENTER),(406|TEXT_CENTER),12,0.75f,0.75f,0.75f,1.0f);
    keyhighlight=0;
    if ((object[0].button&8)==8)
      keyhighlight=1;
    drawkeybitmap2((count|TEXT_CENTER),(424|TEXT_CENTER),12,12,control[0].key[7],keyhighlight);
    count+=96;
    }
  }

void drawtextbitmap(int x,int y,int sizex,int sizey)
  {
  int count,count2;

  count=0;
  count2=0;
  while (textstring2[count]!=0)
    {
    if (textstring2[count]>=48 && textstring2[count]<58)
      count2++;
    if (textstring2[count]==58)
      count2++;
    if (textstring2[count]==47)
      count2++;
    count++;
    }

  if ((x&TEXT_CENTER)==TEXT_CENTER)
    x=x-(count2*sizex)/2;
  if ((y&TEXT_CENTER)==TEXT_CENTER)
    y=y-(sizey)/2;
  if ((x&TEXT_END)==TEXT_END)
    x=x-(count2*sizex);
  if ((y&TEXT_END)==TEXT_END)
    y=y-sizey;
  x&=0xFFFF;
  y&=0xFFFF;

  count=0;
  count2=0;
  while (textstring2[count]!=0)
    {
    if (textstring2[count]>=48 && textstring2[count]<58)
      {
      drawbackground(700+(textstring2[count]-48),x+count2*sizex,y,sizex,sizey,640,480);
      count2++;
      }
    if (textstring2[count]==58)
      {
      drawbackground(711,x+count2*sizex,y,sizex,sizey,640,480);
      count2++;
      }
    if (textstring2[count]==47)
      {
      drawbackground(710,x+count2*sizex,y,sizex,sizey,640,480);
      count2++;
      }
    if (textstring2[count]==46)
      {
      drawbackground(712,x+count2*sizex,y,sizex,sizey,640,480);
      count2++;
      }
    count++;
    }
  }

void drawkeybitmap(int x,int y,int sizex,int sizey,int keynum,int keyhighlight,int keyhighlight2)
  {
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  drawbackground(723,x,y,sizex*2+(strlen(keyboardlabel[keynum])-1)*sizex,sizey*2,640,480);

  if (!keyboard[keynum])
    {
    if (keyhighlight!=keynum && keyhighlight2!=keynum)
      drawtext("/s",x,y,sizex,0.0f,0.0f,0.0f,1.0f,keyboardlabel[keynum]);
    else
      drawtext("/s",x,y,sizex,1.0f,1.0f,0.0f,1.0f,keyboardlabel[keynum]);
    }
  else
    {
    if (keyhighlight!=keynum && keyhighlight2!=keynum)
      drawtext("/s",x,y,sizex,0.5f,0.5f,1.0f,1.0f,keyboardlabel[keynum]);
    else
      drawtext("/s",x,y,sizex,0.0f,1.0f,0.0f,1.0f,keyboardlabel[keynum]);
    }
  }

void drawkeybitmap2(int x,int y,int sizex,int sizey,int keynum,int highlight)
  {
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  drawbackground(723,x,y,sizex*2+(strlen(keyboardlabel[keynum])-1)*sizex,sizey*2,640,480);

  if (!highlight)
    drawtext("/s",x,y,sizex,0.5f,0.5f,0.5f,1.0f,keyboardlabel[keynum]);
  else
    drawtext("/s",x,y,sizex,0.0f,1.0f,0.0f,1.0f,keyboardlabel[keynum]);
  }
