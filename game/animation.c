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

void objectanimation(void)
  {
  int count,count2;
  int particlelist[2];
  float vec[3];
  float intersectpoint[3];
  float normal[3];
  float scale;

  for (count=0;count<numofobjects;count++)
    {
    if (object[count].type==1)
      {
      /*
      for (count2=0;count2<object[count].numofparticles;count2++)
      if ((rand()&8191)==0)
        createparticle(5,particle[object[count].particle[count2]].position,particle[object[count].particle[count2]].velocity,0.125f,-1,100);
      */

      if (object[count].frame==12)
        {
        object[count].framedelay+=0.125f;
        if (object[count].framedelay>=1.0f)
          {
          object[count].frame=0;
          object[count].framedelay=0.0f;
          }
        }

      if (object[count].numoforientations==0)
        {
        if (object[count].frame>=5 && object[count].frame<=7)
          object[count].frame=1;
        if (object[count].frame<4)
          {
          object[count].framedelay+=1.0f;
          if (object[count].framedelay>=4.0f)
            {
            object[count].frame++;
            object[count].framedelay=0.0f;
            }
          }
        }
      else
        {
        if (object[count].frame>0 && object[count].frame<=4)
          {
          object[count].framedelay+=1.0f;
          if (object[count].framedelay>=4.0f)
            {
            object[count].frame--;
            object[count].framedelay=0.0f;
            }
          }
        if (object[count].frame==0)
          if ((rnd()&255)==0)
            object[count].frame=5;

        if (object[count].frame>=5 && object[count].frame<=7)
          {
          object[count].framedelay+=1.0f;
          if (object[count].framedelay>=4.0f)
            {
            object[count].frame++;
            if (object[count].frame==8)
              object[count].frame=0;
            object[count].framedelay=0.0f;
            }
          }
        }
      if ((object[count].button&8)==8)
      if (object[count].frame<8)
        {
        object[count].frame=8;
        object[count].framedelay=0.0f;
        }

      if (object[count].frame>=8 && object[count].frame<=11)
        {
        object[count].framedelay+=1.0f;
        if (object[count].framedelay>=4.0f)
          {
          if ((object[count].button&8)==8)
            {
            if (object[count].frame<11)
              object[count].frame++;
            }
          else
            {
            if (object[count].frame>7)
              object[count].frame--;
            if (object[count].frame==7)
              object[count].frame=0;
            }
          object[count].framedelay=0.0f;
          }
        }
      }
    if (object[count].type==4)
      {
      if (object[count].animationtype==0 || object[count].animationtype==1)
      if ((object[count].button&1)==1)
        {
        object[count].animationtype=2;
        object[count].frame=0;
        object[count].framedelay=0.0f;
        }
      if (object[count].beasttype==12)
      if (object[count].animationtype==0)
      if ((object[count].button&2)==2)
        {
        object[count].animationtype=1;
        object[count].frame=0;
        object[count].framedelay=0.0f;
        }
      if (object[count].animationtype==0)
        {
        if (object[count].link!=-1)
          {
          object[object[count].link].texturenum=animation[object[count].animationnum+32].stand[0];
          if (fabs(object[0].position[0]-object[count].position[0])<1.5f)
          if (object[0].position[1]>object[count].position[1])
            object[object[count].link].texturenum=animation[object[count].animationnum+32].stand[1];
          }

        object[count].framedelay+=0.1f;
        if (object[count].framedelay>=1.0f)
          {
          object[count].framedelay=0.0f;
          object[count].frame++;
          if (object[count].frame>=animation[object[count].animationnum].stand[1])
            object[count].frame=0;
          }
        object[count].texturenum=animation[object[count].animationnum].stand[0]+object[count].frame;
        if (vectorlength(object[count].velocity)>=0.01f)
          {
          object[count].animationtype=1;
          object[count].frame=0;
          object[count].framedelay=0.0f;
          }
        }
      if (object[count].animationtype==1)
        {
        if (object[count].link!=-1)
          {
          object[object[count].link].texturenum=animation[object[count].animationnum+32].walk[0];
          if (fabs(object[0].position[0]-object[count].position[0])<1.5f)
          if (object[0].position[1]>object[count].position[1])
            object[object[count].link].texturenum=animation[object[count].animationnum+32].stand[1];
          }
        if (object[count].beasttype!=12)
          object[count].framedelay+=vectorlength(object[count].velocity)*6.0f;
        else
          object[count].framedelay+=0.2f;
        if (object[count].framedelay>=1.0f)
          {
          object[count].framedelay=0.0f;
          object[count].frame++;
          if (object[count].frame>=animation[object[count].animationnum].walk[1])
            {
            object[count].frame=0;
            if (object[count].beasttype==12)
              object[count].animationtype=0;
            }
          }
        object[count].texturenum=animation[object[count].animationnum].walk[0]+object[count].frame;
        if (object[count].beasttype!=12)
        if (vectorlength(object[count].velocity)<0.01f)
          {
          object[count].animationtype=0;
          object[count].frame=0;
          object[count].framedelay=0.0f;
          }
        if (object[count].beasttype==12)
        if (object[count].frame==4)
        if (object[count].framedelay==0.0f)
          {
          addvectors(vec,object[count].position,yaxis);
          createbeast(11,vec,1.0f,1.0f,1.0f,0.2f);
          object[numofobjects-1].timetolive=512;
          object[numofobjects-1].link=-1;
          for (count2=0;count2<4;count2++)
            {
            particle[object[numofobjects-1].particle[count2]].velocity[1]=0.08f;
            if (object[count].direction==0)
              particle[object[numofobjects-1].particle[count2]].velocity[0]=-0.04f;
            else
              particle[object[numofobjects-1].particle[count2]].velocity[0]=0.04f;
            }
          }
        }
      if (object[count].animationtype==2)
        {
        if (object[count].link!=-1)
          object[object[count].link].texturenum=animation[object[count].animationnum+32].attack[0];

        object[count].framedelay+=0.2f;
        if (object[count].framedelay>=1.0f)
          {
          object[count].framedelay=0.0f;
          object[count].frame++;
          if (object[count].frame>=animation[object[count].animationnum].attack[1])
            {
            object[count].animationtype=0;
            object[count].frame=0;
            }
          }
        object[count].texturenum=animation[object[count].animationnum].attack[0]+object[count].frame;

        if (object[count].frame==1)
        if (object[count].framedelay==0.0f)
          {
          if (object[count].beasttype<3 || object[count].beasttype==8 || object[count].beasttype==11 || object[count].beasttype==16)
            playsound(11,object[count].position,NULL,0.25f,0,0.7f,-1,0);
          else if (object[count].beasttype==7 || object[count].beasttype==13)
            playsound(12,object[count].position,NULL,0.5f,0,1.0f,-1,0);
          else
            playsound(13,object[count].position,NULL,0.5f,0,1.0f,-1,0);
          }

        if (object[count].frame==5)
          {
          //if (object[count].beasttype!=7 && object[count].beasttype!=13)
            {
            scale=1.25f;
            if (object[count].beasttype<3 || object[count].beasttype==8 || object[count].beasttype==11 || object[count].beasttype==16)
              scale=0.75f;
            if (object[count].beasttype==15)
              scale=1.5f;
            if (object[count].beasttype==7 || object[count].beasttype==13)
              scale=3.0f;
  
            if (object[count].direction==0)
              scaleaddvectors(vec,object[count].position,object[count].orientation[0],-scale);
            if (object[count].direction==1)
              scaleaddvectors(vec,object[count].position,object[count].orientation[0],scale);
            if (lineintersectobject(intersectpoint,normal,&scale,object[count].position,vec,0,particlelist))
              {
              scale=0.06f;
              if (object[count].beasttype<3)
                scale=0.03f;
              if (object[count].beasttype==15)
                scale=0.15f;
  
              if (object[count].direction==0)
                {
                scaleaddvectors(particle[particlelist[0]].velocity,particle[particlelist[0]].velocity,object[count].orientation[0],-scale);
                scaleaddvectors(particle[particlelist[1]].velocity,particle[particlelist[1]].velocity,object[count].orientation[0],-scale);
                }
              if (object[count].direction==1)
                {
                scaleaddvectors(particle[particlelist[0]].velocity,particle[particlelist[0]].velocity,object[count].orientation[0],scale);
                scaleaddvectors(particle[particlelist[1]].velocity,particle[particlelist[1]].velocity,object[count].orientation[0],scale);
                }
              if (object[count].beasttype<3 || object[count].beasttype==11)
                object[0].hitpoints-=20;
              else
                object[0].hitpoints-=40;
              if (object[count].beasttype==15)
                object[0].hitpoints-=40;
              }
            }
          if (object[count].beasttype==7 || object[count].beasttype==13)
          if (object[count].framedelay==0.0f)
            {
            if (object[count].beasttype==7)
              createbeast(2,object[count].position,1.0f,1.0f,1.0f,0.2f);
            else
              createbeast(8,object[count].position,1.0f,1.0f,1.0f,0.2f);
            object[numofobjects-1].timetolive=512;
            object[numofobjects-1].link=-1;
            for (count2=0;count2<4;count2++)
              {
              if (object[count].direction==0)
                particle[object[numofobjects-1].particle[count2]].velocity[0]=-0.08f;
              else
                particle[object[numofobjects-1].particle[count2]].velocity[0]=0.08f;
              }
            }
          }
        }
      if (object[count].timetolive>=0 && object[count].timetolive<45)
        {
        if (object[count].timetolive==44)
          {
          if (object[count].beasttype<3 || object[count].beasttype==8 || object[count].beasttype==11 || object[count].beasttype==16)
            {
            game.score[0]+=100*game.combo;
            createsprite(100*game.combo,object[count].position);
            game.combo++;
            game.combodelay+=100;
            if (game.combodelay>250)
              game.combodelay=250;
            playsound(7,object[count].position,NULL,1.0f,0,1.0f,-1,0);
            }
          else
            {
            game.score[0]+=200*game.combo;
            createsprite(200*game.combo,object[count].position);
            game.combo++;
            game.combodelay+=100;
            if (game.combodelay>250)
              game.combodelay=250;
            playsound(19,object[count].position,NULL,1.0f,0,1.0f,-1,0);
            }

          for (count2=0;count2<10;count2++)
            {
            vec[0]=(float)((rnd()&255)-127)/1270.0f;
            vec[1]=(float)((rnd()&255)-127)/1270.0f;
            vec[2]=0.0f;
            addvectors(vec,vec,object[count].velocity);

            createparticle(5,object[count].position,vec,0.25f,-1,100+(rnd()&63));
            particle[numofparticles-1].rendersize=0.125+(float)(rnd()&127)/1000.0f;
            particle[numofparticles-1].texturenum=367;
            if (object[count].beasttype==11 || object[count].beasttype==12)
              particle[numofparticles-1].texturenum=364;
            if (object[count].beasttype==0 || object[count].beasttype==3 || object[count].beasttype==4)
              particle[numofparticles-1].texturenum=365;
            }
          }

        if (object[count].link!=-1)
          {
          object[object[count].link].texturenum=animation[object[count].animationnum+32].die[0];
          if (object[object[count].link].timetolive>150)
            object[object[count].link].timetolive=150;
          }
        object[count].animationtype=3;
        object[count].frame=8-object[count].timetolive/5;
        object[count].framedelay=0.0f;
        object[count].texturenum=animation[object[count].animationnum].die[0]+object[count].frame;
        }
      }
    }
  if (game.levelnum==34)
  if (object[1].type==2)
  if ((rnd()&255)==0)
    {
    object[1].texturenum=64+(rnd()&3);
    }
  }

void loadanimations(void)
  {
  int count,count2;
  int changeddir;
  char filename[32]="bibatk01.tga";

  changeddir=chdir("animation");

  count2=0;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"bibsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"bibwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"bibatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"nibdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=1;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"nibsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"nibwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"nibatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"nibdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=2;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"ribsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"ribwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"ribatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"ribdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=3;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"mumsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"mumwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"mumatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"mumdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    count2+=32;
  
    animation[count2].stand[0]=numofanimations;
    loadtexturetga(numofanimations,"mumhed01.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].walk[0]=numofanimations;
    loadtexturetga(numofanimations,"mumhed02.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].attack[0]=numofanimations;
    loadtexturetga(numofanimations,"mumhed03.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].stand[1]=numofanimations;
    loadtexturetga(numofanimations,"mumhed05.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].die[0]=numofanimations;
    loadtexturetga(numofanimations,"mumhed06.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
    }

  count2=4;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"sklsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"sklwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"sklatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"skldie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    count2+=32;
  
    animation[count2].stand[0]=numofanimations;
    loadtexturetga(numofanimations,"sklhed01.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].walk[0]=numofanimations;
    loadtexturetga(numofanimations,"sklhed02.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].attack[0]=numofanimations;
    loadtexturetga(numofanimations,"sklhed03.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].stand[1]=numofanimations;
    loadtexturetga(numofanimations,"sklhed05.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].die[0]=numofanimations;
    loadtexturetga(numofanimations,"sklhed06.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
    }

  count2=5;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"zomsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"zomwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"zomatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"zomdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    count2+=32;
  
    animation[count2].stand[0]=numofanimations;
    loadtexturetga(numofanimations,"zomhed01.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].walk[0]=numofanimations;
    loadtexturetga(numofanimations,"zomhed02.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].attack[0]=numofanimations;
    loadtexturetga(numofanimations,"zomhed03.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].stand[1]=numofanimations;
    loadtexturetga(numofanimations,"zomhed05.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].die[0]=numofanimations;
    loadtexturetga(numofanimations,"zomhed06.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
    }

  count2=6;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"gimsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"gimwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"gimatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"gimdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    count2+=32;
  
    animation[count2].stand[0]=numofanimations;
    loadtexturetga(numofanimations,"gimhed01.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].walk[0]=numofanimations;
    loadtexturetga(numofanimations,"gimhed02.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].attack[0]=numofanimations;
    loadtexturetga(numofanimations,"gimhed03.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].stand[1]=numofanimations;
    loadtexturetga(numofanimations,"gimhed05.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].die[0]=numofanimations;
    loadtexturetga(numofanimations,"gimhed06.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
    }

  count2=7;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"vissta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"viswlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"visatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"visdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=8;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"aibsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"aibwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"aibatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"aibdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=9;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"altsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"altwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"altatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"altdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    count2+=32;

    animation[count2].stand[0]=numofanimations;
    loadtexturetga(numofanimations,"gimhed01.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].walk[0]=numofanimations;
    loadtexturetga(numofanimations,"gimhed02.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].attack[0]=numofanimations;
    loadtexturetga(numofanimations,"gimhed03.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].stand[1]=numofanimations;
    loadtexturetga(numofanimations,"gimhed05.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].die[0]=numofanimations;
    loadtexturetga(numofanimations,"gimhed06.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
    }

  count2=10;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"frksta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"frkwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"frkatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"frkdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    count2+=32;
  
    animation[count2].stand[0]=numofanimations;
    loadtexturetga(numofanimations,"frkhed01.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].walk[0]=numofanimations;
    loadtexturetga(numofanimations,"frkhed02.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].attack[0]=numofanimations;
    loadtexturetga(numofanimations,"frkhed03.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].stand[1]=numofanimations;
    loadtexturetga(numofanimations,"frkhed05.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
  
    animation[count2].die[0]=numofanimations;
    loadtexturetga(numofanimations,"frkhed06.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    numofanimations++;
    }

  count2=11;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"pibsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"pibwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"pibatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"pibdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=12;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"sepsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"sepspw");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=8;
    strcpy(filename,"sepatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"sepdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=13;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"sissta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"siswlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"sisatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"sisdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=14;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=5;
    strcpy(filename,"ghosta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=5;
    strcpy(filename,"ghowlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=8;
    strcpy(filename,"ghoatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"ghodie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=15;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"bassta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"baswlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"basatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"basdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  count2=16;
  if (animation[count2].loaded==2)
    {
    animation[count2].loaded=1;

    animation[count2].stand[0]=numofanimations;
    animation[count2].stand[1]=6;
    strcpy(filename,"satsta");
    for (count=1;count<=animation[count2].stand[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].walk[0]=numofanimations;
    animation[count2].walk[1]=9;
    strcpy(filename,"satwlk");
    for (count=1;count<=animation[count2].walk[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].attack[0]=numofanimations;
    animation[count2].attack[1]=9;
    strcpy(filename,"satatk");
    for (count=1;count<=animation[count2].attack[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
  
    animation[count2].die[0]=numofanimations;
    animation[count2].die[1]=9;
    strcpy(filename,"ribdie");
    for (count=1;count<=animation[count2].die[1];count++)
      {
      filename[6]=48+(count/10)%10;
      filename[7]=48+count%10;
      loadtexturetga(numofanimations,filename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
      numofanimations++;
      }
    }

  if (changeddir==0)
    chdir("..");
  }
