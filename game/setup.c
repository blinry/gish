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

void setuplevel(void)
  {
  int count,count2;
  int numofobjectstemp;
  float vec[3];

  for (count=0;count<256;count++)
  for (count2=0;count2<256;count2++)
    level.gridmod[count][count2]=0;

  setuplevellines(1,1,254,254);

  numofparticles=0;
  numofbonds=0;
  numofobjects=0;
  numofropes=0;
  physicstemp.numofbonds=0;
  numofsprites=0;
  numofbosses=0;

  for (count=0;count<level.numofobjects;count++)
    if (level.object[count].type>=20 && level.object[count].type<40)
      {
      if (animation[level.object[count].type-20].loaded==0)
        animation[level.object[count].type-20].loaded=2;
      if (level.object[count].type-20==7)
        if (animation[2].loaded==0)
          animation[2].loaded=2;
      if (level.object[count].type-20==13)
        if (animation[8].loaded==0)
          animation[8].loaded=2;
      if (level.object[count].type-20==12)
        if (animation[11].loaded==0)
          animation[11].loaded=2;
      }
  loadanimations();

  for (count=0;count<level.numofobjects;count++)
    {
    numofobjectstemp=numofobjects;

    if (level.object[count].type==1)
      {
      createtarboy(level.object[count].position);
      object[numofobjects-1].texturenum=1;
      }
    if (level.object[count].type==2)
      createbox(level.object[count].position,level.object[count].size[0],level.object[count].size[1],level.object[count].mass,level.object[count].friction);
    if (level.object[count].type==3)
      {
      createbox(level.object[count].position,level.object[count].size[0],level.object[count].size[1],level.object[count].mass,level.object[count].friction);
      createparticle(2,level.object[count].position,NULL,10000.0f,-1,10000);
      createbond(numofparticles-5,numofparticles-1,1,-1);
      createbond(numofparticles-4,numofparticles-1,1,-1);
      createbond(numofparticles-3,numofparticles-1,1,-1);
      createbond(numofparticles-2,numofparticles-1,1,-1);
      }
    if (level.object[count].type==4)
      {
      if (level.gametype!=16)
        {
        createbox(level.object[count].position,level.object[count].size[0],level.object[count].size[1],level.object[count].mass,level.object[count].friction);
        vec[0]=level.object[count].position[0]-(level.object[count].size[0]-1.0f)*0.5f;
        vec[1]=level.object[count].position[1]-(level.object[count].size[1]-1.0f)*0.5f;
        vec[2]=0.0f;
        createparticle(2,vec,NULL,10000.0f,-1,10000);
        createbond(numofparticles-5,numofparticles-1,1,-1);
        createbond(numofparticles-4,numofparticles-1,1,-1);
        createbond(numofparticles-3,numofparticles-1,1,-1);
        createbond(numofparticles-2,numofparticles-1,1,-1);
        }
      else
        createcar(level.object[count].position,level.object[count].size[0],level.object[count].size[1],level.object[count].mass,level.object[count].friction);
      }
    if (level.object[count].type==5)
      {
      createbox(level.object[count].position,level.object[count].size[0],level.object[count].size[1],level.object[count].mass,level.object[count].friction);
      vec[0]=level.object[count].position[0]+(level.object[count].size[0]-1.0f)*0.5f;
      vec[1]=level.object[count].position[1]+(level.object[count].size[1]-1.0f)*0.5f;
      vec[2]=0.0f;
      createparticle(2,vec,NULL,10000.0f,-1,10000);
      createbond(numofparticles-5,numofparticles-1,1,-1);
      createbond(numofparticles-4,numofparticles-1,1,-1);
      createbond(numofparticles-3,numofparticles-1,1,-1);
      createbond(numofparticles-2,numofparticles-1,1,-1);
      }
    if (level.object[count].type==6)
      {
      createwheel(level.object[count].position,level.object[count].size[0],level.object[count].size[1],level.object[count].mass,level.object[count].friction,0);
      }
    if (level.object[count].type==7)
      {
      createwheel(level.object[count].position,level.object[count].size[0],level.object[count].size[1],level.object[count].mass,level.object[count].friction,1);
      //createparticle(2,level.object[count].position,NULL,10000.0f,-1,10000);
      //for (count2=0;count2<16;count2++)
      //  createbond(numofparticles-17+count2,numofparticles-1,1,-1);
      }
    if (level.object[count].type==8)
      createanchor(level.object[count].position);
    if (level.object[count].type==9)
      createbutton(level.object[count].position,level.object[count].mass);
    if (level.object[count].type==10)
      {
      createbutton(level.object[count].position,level.object[count].mass);
      object[numofobjects-1].idata[1]=1;
      }
    if (level.object[count].type==11)
      createswitch(level.object[count].position,level.object[count].mass,0);
    if (level.object[count].type==12)
      createswitch(level.object[count].position,level.object[count].mass,1);
    if (level.object[count].type==13)
      createswitch(level.object[count].position,level.object[count].mass,2);
    if (level.object[count].type==14)
      createswitch(level.object[count].position,level.object[count].mass,3);
    if (level.object[count].type==15)
      createareaswitch(level.object[count].position,level.object[count].size[0],level.object[count].size[1]);
    if (level.object[count].type==16)
      {
      createareaswitch(level.object[count].position,level.object[count].size[0],level.object[count].size[1]);
      object[numofobjects-1].idata[1]=1;
      }
    if (level.object[count].type==18)
      {
      createareaswitch(level.object[count].position,level.object[count].size[0],level.object[count].size[1]);
      object[numofobjects-1].idata[1]=2;
      }
    if (level.object[count].type==17)
      creategenerator(level.object[count].position,level.object[count].mass);

    if (level.object[count].type==20)
      createbeast(0,level.object[count].position,1.0f,1.0f,1.0f,0.2f);
    if (level.object[count].type==21)
      createbeast(1,level.object[count].position,1.0f,1.0f,1.0f,0.2f);
    if (level.object[count].type==22)
      createbeast(2,level.object[count].position,1.0f,1.0f,1.0f,0.2f);
    if (level.object[count].type==23)
      createbeast(3,level.object[count].position,1.5f,1.1f,8.0f,0.2f);
    if (level.object[count].type==24)
      createbeast(4,level.object[count].position,1.5f,1.1f,8.0f,0.2f);
    if (level.object[count].type==25)
      createbeast(5,level.object[count].position,1.5f,1.1f,8.0f,0.2f);
    if (level.object[count].type==26)
      createbeast(6,level.object[count].position,1.5f,1.1f,8.0f,0.2f);
    if (level.object[count].type==27)
      createbeast(7,level.object[count].position,3.0f,3.0f,20.0f,0.2f);
    if (level.object[count].type==28)
      createbeast(8,level.object[count].position,1.0f,1.0f,1.0f,0.2f);
    if (level.object[count].type==29)
      createbeast(9,level.object[count].position,1.5f,1.1f,8.0f,0.2f);
    if (level.object[count].type==30)
      createbeast(10,level.object[count].position,1.5f,1.1f,8.0f,0.2f);
    if (level.object[count].type==31)
      createbeast(11,level.object[count].position,1.0f,1.0f,1.0f,0.2f);
    if (level.object[count].type==32)
      createbeast(12,level.object[count].position,2.0f,0.85f,3.0f,0.2f);
    if (level.object[count].type==33)
      createbeast(13,level.object[count].position,3.0f,3.0f,20.0f,0.2f);
    if (level.object[count].type==34)
      createboss(14,level.object[count].position);
    if (level.object[count].type==35)
      createbeast(15,level.object[count].position,2.0f,2.0f,8.0f,0.2f);
    if (level.object[count].type==36)
      createbeast(16,level.object[count].position,1.0f,1.0f,1.0f,0.2f);

    if (numofobjects!=numofobjectstemp)
      {
      if (level.object[count].type>1 && level.object[count].type<20)
        object[numofobjects-1].texturenum=level.object[count].texturenum;
      object[numofobjects-1].link=level.object[count].link;
      object[numofobjects-1].lighttype=level.object[count].lighttype;
      if (level.object[count].lighttype==1 || level.object[count].lighttype==3)
        object[numofobjects-1].lighton=1;
      if (level.object[count].lighttype==2)
        object[numofobjects-1].lighton=0;
  
      object[numofobjects-1].size[0]=level.object[count].size[0];
      object[numofobjects-1].size[1]=level.object[count].size[1];
  
      object[numofobjects-1].lightcolor[0]=level.object[count].lightcolor[0];
      object[numofobjects-1].lightcolor[1]=level.object[count].lightcolor[1];
      object[numofobjects-1].lightcolor[2]=level.object[count].lightcolor[2];
      object[numofobjects-1].lightintensity=level.object[count].lightintensity;
      object[numofobjects-1].lightintensitymax=level.object[count].lightintensity;
      }
    }

  for (count=0;count<level.numofobjects;count++)
    {
    if ((level.object[count].type>=23 && level.object[count].type<=26) || level.object[count].type==29 || level.object[count].type==30)
      {
      vec[0]=level.object[count].position[0];
      vec[1]=level.object[count].position[1]+1.4f;//+1.42f;
      vec[2]=0.0f;
      createhead(vec,2.0f,1.6f,2.0f,0.5f);

      object[count].link=numofobjects-1;

      //createbond(object[numofobjects-1].particle[0],object[count].particle[0],6,count);
      createbond(object[numofobjects-1].particle[2],object[count].particle[0],6,count);
      createbond(object[numofobjects-1].particle[4],object[count].particle[0],6,count);
      createbond(object[numofobjects-1].particle[0],object[count].particle[1],6,count);
      createbond(object[numofobjects-1].particle[2],object[count].particle[1],6,count);
      //createbond(object[numofobjects-1].particle[4],object[count].particle[1],6,count);
      }
    }

  for (count=0;count<level.numofropes;count++)
    {
    createrope(level.rope[count].type,object[level.rope[count].obj1].particle[level.rope[count].obj1part],object[level.rope[count].obj2].particle[level.rope[count].obj2part],level.rope[count].obj1,level.rope[count].obj2,level.rope[count].texturenum);
    }
  }

void setupgame(void)
  {
  int count,count2;

  srand(time(NULL));
  randomnum=0;

  for (count=numofsounds-1;count>=0;count--)
    deletesound(count);

  numofreplayframes=0;

  game.score[0]=0;
  game.score[1]=0;
  game.combo=1;
  game.combodelay=0;
  game.scoredelay=0;
  game.startdelay=0;
  game.exitdelay=0;
  game.over=0;
  game.exit=0;
  game.time=level.time;
  game.pause=0;
  game.framenum=0;
  game.bosslevel=0;
  game.dialog=0;

  if (game.levelnum==6)
    {
    game.bosslevel=1;
    game.dialog=2;
    game.dialogdelay=1000;
    }
  if (game.levelnum==13)
    {
    game.bosslevel=1;
    game.dialog=3;
    game.dialogdelay=1000;
    }
  if (game.levelnum==20)
    {
    game.bosslevel=1;
    game.dialog=3;
    game.dialogdelay=1000;
    }
  if (game.levelnum==27)
    {
    game.bosslevel=1;
    game.dialog=3;
    game.dialogdelay=1000;
    }
  if (game.levelnum==33)
    {
    game.bosslevel=1;
    game.dialog=3;
    game.dialogdelay=1000;
    }
  if (game.levelnum==34)
    {
    game.bosslevel=1;
    game.dialog=8;
    game.dialogdelay=1000;
    }
  if (game.levelnum==68)
    {
    game.bosslevel=1;
    game.dialog=16;
    game.dialogdelay=1000;
    }

  if (level.gametype==10)
    game.time=6000;
  if (level.gametype==12)
    game.time=6000;
  if (level.gametype==17)
    game.time=6000;

  for (count=0;count<16;count++)
    {
    game.bonus[count]=0;
    game.numofbonus[count]=0;
    }

  for (count=0;count<256;count++)
  for (count2=0;count2<256;count2++)
    {
    if (level.grid[count][count2]>=240 && level.grid[count][count2]<=247)
      game.numofbonus[level.grid[count][count2]-240]++;
    if (level.grid[count][count2]>=248 && level.grid[count][count2]<=255)
      game.numofbonus[level.grid[count][count2]-248]++;
    }

  for (count=0;count<numofobjects;count++)
  if (object[count].type==16)
  if (object[count].idata[1]==2)
    game.numofbonus[8]++;

  if (level.gametype==1)
    game.startdelay=100;

  if ((level.gametype>=10 && level.gametype<=14) || level.gametype==17 || level.gametype==18)
    game.startdelay=100;

  if (level.gametype<10 && !editor.active)
    {
    view.position[0]=object[0].position[0];
    view.position[1]=object[0].position[1];
    view.position[2]=10.0f;
    if (game.levelnum==64)
      view.position[1]=131.5f;
    if (game.levelnum==65)
      {
      count=object[0].position[0]+16.0f;
      count/=32;
      count*=32;
      view.position[0]=count;
      view.position[1]=126.0f;
      }
    }
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
    view.position[0]=127.0f;
    view.position[1]=127.5f;
    view.position[2]=10.0f;
    }

  resetorientation(view.orientation);
  }

void loadstorylevel(int levelnum)
  {
#ifndef DEMO
  if (levelnum==1)
    loadlevel("sewer1.lvl");
  if (levelnum==2)
    loadlevel("sewer2.lvl");
  if (levelnum==3)
    loadlevel("sewer3.lvl");
  if (levelnum==4)
    loadlevel("sewer4.lvl");
  if (levelnum==5)
    loadlevel("sewer5.lvl");
  if (levelnum==6)
    loadlevel("sewer6.lvl");
  if (levelnum==7)
    loadlevel("sewer7.lvl");

  if (levelnum==8)
    loadlevel("cave1.lvl");
  if (levelnum==9)
    loadlevel("cave2.lvl");
  if (levelnum==10)
    loadlevel("cave3.lvl");
  if (levelnum==11)
    loadlevel("cave4.lvl");
  if (levelnum==12)
    loadlevel("cave5.lvl");
  if (levelnum==13)
    loadlevel("cave6.lvl");
  if (levelnum==14)
    loadlevel("cave7.lvl");

  if (levelnum==15)
    loadlevel("hell1.lvl");
  if (levelnum==16)
    loadlevel("hell2.lvl");
  if (levelnum==17)
    loadlevel("hell3.lvl");
  if (levelnum==18)
    loadlevel("hell4.lvl");
  if (levelnum==19)
    loadlevel("hell5.lvl");
  if (levelnum==20)
    loadlevel("hell6.lvl");
  if (levelnum==21)
    loadlevel("hell7.lvl");

  if (levelnum==22)
    loadlevel("egypt1.lvl");
  if (levelnum==23)
    loadlevel("egypt2.lvl");
  if (levelnum==24)
    loadlevel("egypt3.lvl");
  if (levelnum==25)
    loadlevel("egypt4.lvl");
  if (levelnum==26)
    loadlevel("egypt5.lvl");
  if (levelnum==27)
    loadlevel("egypt6.lvl");
  if (levelnum==28)
    loadlevel("egypt7.lvl");

  if (levelnum==29)
    loadlevel("church1.lvl");
  if (levelnum==30)
    loadlevel("church2.lvl");
  if (levelnum==31)
    loadlevel("church3.lvl");
  if (levelnum==32)
    loadlevel("church4.lvl");
  if (levelnum==33)
    loadlevel("church5.lvl");
  if (levelnum==34)
    loadlevel("church6.lvl");
  if (levelnum==64)
    loadlevel("sewer8.lvl");
  if (levelnum==65)
    loadlevel("cave8.lvl");
  if (levelnum==66)
    loadlevel("egypt8.lvl");
  if (levelnum==67)
    loadlevel("death.lvl");
  if (levelnum==68)
    loadlevel("death2.lvl");
#else
  if (levelnum==1)
    loadlevel("demo1.lvl");
  if (levelnum==2)
    loadlevel("demo2.lvl");
  if (levelnum==3)
    loadlevel("demo3.lvl");
  if (levelnum==4)
    loadlevel("demo4.lvl");
  if (levelnum==5)
    loadlevel("demo5.lvl");
#endif
  }

void loadcollectionlevel(int levelnum)
  {
  char loadfilename[32]="co00.lvl";

  loadfilename[2]=48+levelnum/10;
  loadfilename[3]=48+levelnum%10;

  loadlevel(loadfilename);
  }

