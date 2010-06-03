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

void objectcycle(void)
  {
  int count,count2,count3,count4;
  int x,y;
  float vec[3],vec2[3];
  float veclength,bondlength;
  float angle,spin;
  float intersectpoint[3];
  float normal[3];
  float scale,scale2;

  for (count=0;count<numofropes;count++)
    {
    updateogg();

    if (rope[count].type>=5 && rope[count].type<9)
      {
      bond[rope[count].bondnum].length=bond[rope[count].bondnum].maxlength+(rope[count].range-cos(rope[count].angle)*rope[count].range);

      if (rope[count].cyclelength==0.0f)
        {
        if (rope[count].link==-1 || object[rope[count].link].idata[0]==1)
          {
          rope[count].angle+=2.0f*pi/(50.0f*rope[count].cycle);
          if (rope[count].angle>2.0f*pi)
            rope[count].angle-=2.0f*pi;
          }
        }
      else
        {
        if (rope[count].link==-1)
          {
          if (rope[count].cyclecount<rope[count].cyclelength*2.0f*pi)
            {
            rope[count].angle+=2.0f*pi/(50.0f*rope[count].cycle);
            if (rope[count].angle>2.0f*pi)
              rope[count].angle-=2.0f*pi;
            rope[count].cyclecount+=2.0f*pi/(50.0f*rope[count].cycle);
            }
          }
        else
          {
          count2=0;
          if (object[rope[count].link].idata[0]==1 && rope[count].cyclecount==0.0f)
            count2=1;
          if (rope[count].cyclecount>0.0f && rope[count].cyclecount<rope[count].cyclelength*2.0f*pi)
            count2=1;
          if (rope[count].cyclecount>rope[count].cyclelength*2.0f*pi+2.0f*pi/(50.0f*rope[count].cycle))
            count2=1;
          if (object[rope[count].link].idata[0]==0 && rope[count].cyclecount>0.0f)
            count2=1;

          if (count2==1)
            {
            rope[count].angle+=2.0f*pi/(50.0f*rope[count].cycle);
            if (rope[count].angle>2.0f*pi)
              rope[count].angle-=2.0f*pi;
            rope[count].cyclecount+=2.0f*pi/(50.0f*rope[count].cycle);
            if (rope[count].cyclecount>=rope[count].cyclelength*4.0f*pi)
              rope[count].cyclecount=0.0f;
            }
          }
        }
      }
    }

  for (count=0;count<numofobjects;count++)
    {
    updateogg();

    if (object[count].damagedelay>0)
      object[count].damagedelay--;

    if (object[count].numofparticles!=0)
      {
      zerovector(object[count].velocity);
      for (count2=0;count2<object[count].numofparticles;count2++)
        addvectors(object[count].velocity,object[count].velocity,particle[object[count].particle[count2]].velocity);
      scalevector(object[count].velocity,object[count].velocity,1.0f/(float)object[count].numofparticles);
  
      zerovector(object[count].position);
      for (count2=0;count2<object[count].numofparticles;count2++)
        addvectors(object[count].position,object[count].position,particle[object[count].particle[count2]].position);
      scalevector(object[count].position,object[count].position,1.0f/(float)object[count].numofparticles);
      }

    objectsound(count);

    if (object[count].link!=-1)
      {
      if (object[count].lighttype==1 || object[count].lighttype==3)
        {
        if (object[object[count].link].idata[0])
          object[count].lighton=0;
        else
          object[count].lighton=1;
        }
      if (object[count].lighttype==2)
        {
        if (object[object[count].link].idata[0])
          object[count].lighton=1;
        else
          object[count].lighton=0;
        }
      }
    if (object[count].lighttype==3)
      {
      object[count].lightintensity+=((rand()&255)/255.0f-0.5f)*0.2f*object[count].lightintensitymax;
      if (object[count].lightintensity<object[count].lightintensitymax*0.5f)
        object[count].lightintensity=object[count].lightintensitymax*0.5f;
      if (object[count].lightintensity>object[count].lightintensitymax*1.5f)
        object[count].lightintensity=object[count].lightintensitymax*1.5f;
      }

    if (object[count].type==9)
    if (object[count].idata[0]==0 || object[count].idata[1]==0)
      {
      vec[1]=particle[object[count].particle[6]].position[1]-particle[object[count].particle[4]].position[1];
      vec[1]*=0.08f;
      vec[1]-=particle[object[count].particle[4]].velocity[1];
      particle[object[count].particle[4]].velocity[1]+=vec[1];

      vec[1]=particle[object[count].particle[6]].position[1]-particle[object[count].particle[5]].position[1];
      vec[1]*=0.08f;
      vec[1]-=particle[object[count].particle[5]].velocity[1];
      particle[object[count].particle[5]].velocity[1]+=vec[1];

      if (particle[object[count].particle[4]].position[1]>particle[object[count].particle[6]].position[1]-0.1f)
      if (particle[object[count].particle[5]].position[1]>particle[object[count].particle[6]].position[1]-0.1f)
        {
        if (object[count].idata[0]==1)
          playsound(14,object[count].position,NULL,0.2f,0,1.0f,-1,0);
        object[count].idata[0]=0;
        }
      if (particle[object[count].particle[4]].position[1]<particle[object[count].particle[6]].position[1]-0.2f)
      if (particle[object[count].particle[5]].position[1]<particle[object[count].particle[6]].position[1]-0.2f)
        {
        if (object[count].idata[0]==0)
          playsound(14,object[count].position,NULL,0.2f,0,1.0f,-1,0);
        object[count].idata[0]=1;
        }

      if (object[count].link!=-1)
        if (object[object[count].link].idata[0]==1)
          object[count].idata[0]=1;
      }
    if (object[count].type==9)
    if (object[count].idata[0]==1 && object[count].idata[1]==1)
      {
      vec[1]=particle[object[count].particle[6]].position[1]-0.375f-particle[object[count].particle[4]].position[1];
      vec[1]*=0.08f;
      vec[1]-=particle[object[count].particle[4]].velocity[1];
      particle[object[count].particle[4]].velocity[1]+=vec[1];

      vec[1]=particle[object[count].particle[6]].position[1]-0.375f-particle[object[count].particle[5]].position[1];
      vec[1]*=0.08f;
      vec[1]-=particle[object[count].particle[5]].velocity[1];
      particle[object[count].particle[5]].velocity[1]+=vec[1];
      }
    if (object[count].type==16)
    if (object[count].idata[0]==0 || object[count].idata[1]==0)
      {
      object[count].idata[0]=0;
      if (fabs(object[0].position[0]-object[count].position[0])<object[count].size[0]*0.5f)
      if (fabs(object[0].position[1]-object[count].position[1])<object[count].size[1]*0.5f)
        {
        object[count].idata[0]=1;
        if (object[count].idata[1]==2)
          {
          if ((rand()&3)==0)
            playsound(8,object[count].position,NULL,1.0f,0,1.0f,-1,0);
          else
            playsound(9,object[count].position,NULL,1.0f,0,1.0f,-1,0);
          game.bonus[8]++;
          }
        }
      if (level.gametype==11)
      if (fabs(object[1].position[0]-object[count].position[0])<object[count].size[0]*0.5f)
      if (fabs(object[1].position[1]-object[count].position[1])<object[count].size[1]*0.5f)
        {
        object[count].idata[0]=1;
        if (object[count].idata[1]==2)
          {
          if ((rand()&3)==0)
            playsound(8,object[count].position,NULL,1.0f,0,1.0f,-1,0);
          else
            playsound(9,object[count].position,NULL,1.0f,0,1.0f,-1,0);
          game.bonus[8]++;
          }
        }
      }
    if (object[count].type==15)
      {
      if (object[count].link==-1 || object[object[count].link].idata[0]==1)
      if ((game.framenum&255)==128)
        {
        createwheel(object[count].position,object[count].size[0],object[count].size[1],object[count].mass,0.8f,0);
        object[numofobjects-1].texturenum=object[count].texturenum;
        object[numofobjects-1].timetolive=512;
        object[numofobjects-1].link=-1;
        for (count2=0;count2<object[numofobjects-1].numofparticles;count2++)
          {
          particle[object[numofobjects-1].particle[count2]].velocity[0]=object[count].lightcolor[0]/PHYSICSCYCLE;
          particle[object[numofobjects-1].particle[count2]].velocity[1]=object[count].lightcolor[1]/PHYSICSCYCLE;
          }
        }
      }

    if (object[count].type==10)
      {
      if (object[count].rotate==0 || object[count].rotate==2)
        count3=1;
      else
        count3=0;
      for (count2=1;count2<=2;count2++)
        {
        vec[count3]=particle[object[count].particle[4]].position[count3]-particle[object[count].particle[count2]].position[count3];

        if (vec[count3]<0.0f)
          vec[count3]+=0.25f;
        else
          vec[count3]-=0.25f;

        if (vec[count3]<0.0f)
          {
          vec[2]=-0.04f;
          if (vec[2]<vec[count3])
            vec[2]=vec[count3];
          }
        else
          {
          vec[2]=0.04f;
          if (vec[2]>vec[count3])
            vec[2]=vec[count3];
          }


        vec[2]-=particle[object[count].particle[count2]].velocity[count3];

        particle[object[count].particle[count2]].velocity[count3]+=vec[2];

        if (particle[object[count].particle[count2]].position[count3]>particle[object[count].particle[4]].position[count3]+0.25f)
          particle[object[count].particle[count2]].position[count3]=particle[object[count].particle[4]].position[count3]+0.25f;
        if (particle[object[count].particle[count2]].position[count3]<particle[object[count].particle[4]].position[count3]-0.25f)
          particle[object[count].particle[count2]].position[count3]=particle[object[count].particle[4]].position[count3]-0.25f;
        }

      vec[0]=particle[object[count].particle[4]].position[count3]-particle[object[count].particle[1]].position[count3];
      if (object[count].rotate==3)
        vec[0]=-vec[0];

      if (vec[0]<-0.2f)
        {
        if (object[count].idata[0]==1)
          playsound(14,object[count].position,NULL,0.2f,0,1.0f,-1,0);
        object[count].idata[0]=0;
        }
      if (vec[0]>0.2f)
        {
        if (object[count].idata[0]==0)
          playsound(14,object[count].position,NULL,0.2f,0,1.0f,-1,0);
        object[count].idata[0]=1;
        }

      if (object[count].link!=-1)
        if (object[object[count].link].idata[0]==1)
          object[count].idata[0]=1;
      }
    if (object[count].type==1)
      {
      if (count!=0)
      if (level.gametype==0 && game.levelnum==34)
        objectai(count);

      for (count2=0;count2<16;count2++)
        {
        x=particle[object[count].particle[count2]].position[0];
        y=particle[object[count].particle[count2]].position[1];

        if (x>0 && x<254)
        if (y>0 && y<254)
          {
          if (block[level.foregrid[y][x]].density!=0.0f)
          if ((rand()&255)==0)
            {
            createparticle(5,object[count].position,object[count].velocity,0.125f*0.25f,-1,100+(rand()&63));
            particle[numofparticles-1].rendersize=0.125+(float)(rand()&127)/1000.0f;
            particle[numofparticles-1].texturenum=366;
            }
          if (block[level.foregrid[y][x]].foredamage!=0)
            object[count].hitpoints-=block[level.foregrid[y][x]].foredamage;
          if ((level.grid[y][x]>=248 && level.grid[y][x]<=255 && level.gridmod[y][x]==0) || (level.grid[y][x]>=240 && level.grid[y][x]<=247 && level.gridmod[y][x]==2))
            {
            vec[0]=(float)x+0.5f;
            vec[1]=(float)y+0.5f;
            vec[2]=0.0f;
            subtractvectors(vec2,vec,particle[object[count].particle[count2]].position);
            if (vectorlength(vec2)<0.45f)
              {
              scale=1.0f;

              if (level.grid[y][x]==251 || (level.grid[y][x]==251-8 && level.gridmod[y][x]==2))
                {
                if (game.numoflives<99 && game.difficulty!=3)
                  {
                  game.numoflives++;
                  createsprite(0,vec);
                  sprintf(sprite[numofsprites-1].text,"1UP");
                  sprite[numofsprites-1].size=14;
                  }
                else
                  {
                  game.score[0]+=1000;
                  createsprite(1000,vec);
                  }
                }
              if (level.grid[y][x]==252 || (level.grid[y][x]==252-8 && level.gridmod[y][x]==2))
                {
                if (object[count].hitpoints<900)
                  object[count].hitpoints+=100;
                else
                  object[count].hitpoints=1000;
                }
              if (level.grid[y][x]==253 || (level.grid[y][x]==253-8 && level.gridmod[y][x]==2))
                {
                if (level.gametype!=15)
                  {
                  game.score[0]+=50;
                  createsprite(50,vec);
                  }
                else
                  game.score[count]++;
                }
              if (level.grid[y][x]==254 || (level.grid[y][x]==254-8 && level.gridmod[y][x]==2))
                {
                game.score[0]+=100;
                createsprite(100,vec);
                if (game.oldschool==0)
                  scale=0.9f;
                }
              if (level.grid[y][x]==255 || (level.grid[y][x]==255-8 && level.gridmod[y][x]==2))
                {
                game.score[0]+=1000;
                createsprite(1000,vec);
                if (game.oldschool==0)
                  scale=0.8f;
                }

              if (level.grid[y][x]==252 || (level.grid[y][x]==252-8 && level.gridmod[y][x]==2))
                playsound(20,vec,NULL,0.7f,0,scale,-1,0);
              else
                playsound(10,vec,NULL,0.4f,0,scale,-1,0);

              level.gridmod[y][x]=1;

              if (level.grid[y][x]>=248 && level.grid[y][x]<=255)
                game.bonus[level.grid[y][x]-248]++;
              if (level.grid[y][x]>=240 && level.grid[y][x]<=247)
                game.bonus[level.grid[y][x]-240]++;
              }
            }
          }
        }

      count4=0;
      for (count2=0;count2<16;count2++)
      for (count3=0;count3<16;count3++)
      if (abs(count2-count3)>6)
        {
        subtractvectors(vec,particle[object[count].particle[count3]].position,particle[object[count].particle[count2]].position);
        veclength=vectorlength(vec);
        if (veclength<0.15f)
          count4++;
        //if (veclength<0.15f)
        //  object[count].hitpoints-=(0.2f-veclength)*500.0f;
        }

      if (count4>=2)
        object[count].hitpoints-=(count4-1)*50;

      if (object[count].numoforientations==0)
        copyvector(object[count].orientation[1],yaxis);
      else
        normalizevector(object[count].orientation[1],object[count].orientation[1]);
      crossproduct(object[count].orientation[0],zaxis,object[count].orientation[1]);
      normalizevector(object[count].orientation[0],object[count].orientation[0]);

      if (dotproduct(object[count].velocity,object[count].orientation[0])<-0.02f)
        object[count].direction=0;
      if (dotproduct(object[count].velocity,object[count].orientation[0])>0.02f)
        object[count].direction=1;

      angle=atan2(object[count].orientation[0][1],object[count].orientation[0][0]);
      spin=cos(angle)*fabs(cos(angle))*object[count].axis[0]+sin(angle)*fabs(sin(angle))*object[count].axis[1];

      if (spin<-1.0f)
        spin=-1.0f;
      if (spin>1.0f)
        spin=1.0f;
      if (angle<object[count].angle-pi)
        angle+=2.0f*pi;
      if (angle>object[count].angle+pi)
        angle-=2.0f*pi;
      /*
      scale=(angle-object[count].angle);
      if (scale<-0.1f)
        scale=-0.1f;
      if (scale>0.1f)
        scale=0.1f;

      object[count].angle+=scale;
      */
      object[count].angle+=(angle-object[count].angle)*0.05f;

      if (object[count].angle<0.0f)
        object[count].angle+=2.0f*pi;
      if (object[count].angle>2.0f*pi)
        object[count].angle-=2.0f*pi;

      for (count2=0;count2<16;count2++)
        {
        subtractvectors(vec,particle[object[count].particle[count2]].position,object[count].position);
        crossproduct(vec2,zaxis,vec);
        normalizevector(vec2,vec2);

        if (object[count].numoforientations!=0)
          {
          scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,vec2,spin*0.004f);
          }

        //if (object[count].numoforientations==0)
          {
          scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,xaxis,object[count].axis[0]*0.001f);
          if (object[count].axis[1]<0.0f)
            scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,yaxis,object[count].axis[1]*0.001f);
          else
            scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,yaxis,object[count].axis[1]*0.0005f);
          }
        }

      if ((object[count].button&4)==4)
        object[count].friction=0.01f;
      else
        object[count].friction=1.2f;
      if ((object[count].button&2)==2 || (object[count].button&8)==8)
        {
        for (count2=0;count2<numofbonds;count2++)
        if (bond[count2].objectnum==count && bond[count2].type==2)
          {
          bond[count2].cycles=0;
          //bond[count2].elasticity=0.02f;
          }
        }
      else
        {
        for (count2=0;count2<numofbonds;count2++)
        if (bond[count2].objectnum==count && bond[count2].type==2)
          {
          bond[count2].cycles=31;
          /*
          if ((object[count].button&4)==4)
            bond[count2].elasticity=0.005f;
          else
            bond[count2].elasticity=0.02f;
          */
          }
        }
      if ((object[count].button&8)==8)
        {
        for (count2=0;count2<object[count].numofparticles;count2++)
          {
          particle[object[count].particle[count2]].gravity=10.0f/(PHYSICSCYCLE*PHYSICSCYCLE);
          particle[object[count].particle[count2]].mass=0.5f;
          }
        }
      else
        {
        for (count2=0;count2<object[count].numofparticles;count2++)
          {
          particle[object[count].particle[count2]].gravity=4.0f/(PHYSICSCYCLE*PHYSICSCYCLE);
          particle[object[count].particle[count2]].mass=0.25f;
          }
        }
      }
    if (object[count].type==20)
      {
      subtractvectors(object[count].orientation[1],particle[object[count].particle[0]].position,particle[object[count].particle[3]].position);
      normalizevector(object[count].orientation[1],object[count].orientation[1]);
      object[count].orientation[0][0]=object[count].orientation[1][1];
      object[count].orientation[0][1]=-object[count].orientation[1][0];
      object[count].orientation[0][2]=0.0f;

      object[count].data[0]+=object[count].axis[0]*0.05f;
      if (object[count].data[0]<0.0f)
        object[count].data[0]+=0.02f;
      if (object[count].data[0]>0.0f)
        object[count].data[0]-=0.02f;
      if (object[count].data[0]<-0.5f)
        object[count].data[0]=-0.5f;
      if (object[count].data[0]>0.5f)
        object[count].data[0]=0.5f;

      object[count].data[1]+=object[count].axis[1]*0.008f;
      if ((object[count].button&2)==2)
        object[count].data[1]=0.0f;
      if (object[count].data[1]<0.0f)
        object[count].data[1]+=0.004f;
      if (object[count].data[1]>0.0f)
        object[count].data[1]-=0.004f;
      if (object[count].data[1]<-0.3f)
        object[count].data[1]=-0.3f;
      if (object[count].data[1]>0.3f)
        object[count].data[1]=0.3f;

      for (count2=0;count2<4;count2++)
        {
        copyvector(vec,particle[object[count].particle[count2]].velocity);
        if (count2==1 || count2==2)
          {
          //normal[0]=object[count].orientation[0][0]*cos(object[count].data[0])+object[count].orientation[0][1]*sin(object[count].data[0]);
          //normal[1]=object[count].orientation[1][1]*cos(object[count].data[0])-object[count].orientation[1][0]*sin(object[count].data[0]);
          scalevector(normal,object[count].orientation[0],cos(object[count].data[0]));
          scaleaddvectors(normal,normal,object[count].orientation[1],-sin(object[count].data[0]));
          calculatefriction(vec,vec2,normal,0.8f);
          subtractvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,vec2);
          }
        else
          {
          copyvector(normal,object[count].orientation[0]);
          scaleaddvectors(vec,vec,normal,-object[count].data[1]);
          vec[2]=1.0f/PHYSICSCYCLE;
          calculatefriction(vec,vec2,zaxis,0.8f);
          vec2[2]=0.0f;
          subtractvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,vec2);
          }
        //copyvector(particle[object[count].particle[count2]].velocity,vec);
        }

      for (count2=0;count2<4;count2++)
        {
        subtractvectors(vec,particle[object[count].particle[count2]].position,object[count].position);
        crossproduct(vec2,zaxis,vec);
        normalizevector(vec2,vec2);

        //scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,vec2,object[count].axis[0]*0.002f);
        //scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,object[count].orientation[0],object[count].axis[1]*0.003f);
        }
      }
    if (object[count].type==4)
      {
      for (count2=0;count2<4;count2++)
        {
        x=particle[object[count].particle[count2]].position[0];
        y=particle[object[count].particle[count2]].position[1];

        if (x>0 && x<254)
        if (y>0 && y<254)
          {
          if (block[level.foregrid[y][x]].foredamage!=0)
            object[count].hitpoints-=block[level.foregrid[y][x]].foredamage*4;
          }
        }
      if (object[count].hitpoints<0)
      if (object[count].timetolive>45)
        object[count].timetolive=45;

      subtractvectors(object[count].orientation[1],particle[object[count].particle[0]].position,particle[object[count].particle[3]].position);
      normalizevector(object[count].orientation[1],object[count].orientation[1]);
      object[count].orientation[0][0]=object[count].orientation[1][1];
      object[count].orientation[0][1]=-object[count].orientation[1][0];
      object[count].orientation[0][2]=0.0f;

      objectai(count);

      if (object[0].position[0]<object[count].position[0])
        object[count].direction=0;
      else
        object[count].direction=1;

      if (object[count].velocity[0]<-0.01f)
        object[count].direction=0;
      if (object[count].velocity[0]>0.01f)
        object[count].direction=1;
      if (object[count].link!=-1)
        object[object[count].link].direction=object[count].direction;

      if (dotproduct(object[count].orientation[1],yaxis)>0.7f)
      if (object[count].numoforientations!=0)
        {
        if (object[count].beasttype>=0 && object[count].beasttype<=2)
          scale=2.0f;
        if (object[count].beasttype==8 || object[count].beasttype==11)
          scale=2.0f;
        if (object[count].beasttype==16)
          scale=2.0f;
        if (object[count].beasttype>=3 && object[count].beasttype<=6)
          scale=2.0f;
        if (object[count].beasttype==9 || object[count].beasttype==10)
          scale=2.0f;
        if (object[count].beasttype==7 || object[count].beasttype==13)
          scale=1.5f;
        if (object[count].beasttype==15)
          scale=2.5f;

        if (object[count].axis[0]==-1.0f)
          {
          for (count2=0;count2<4;count2++)
          if (particle[object[count].particle[count2]].velocity[0]>-3.0f/PHYSICSCYCLE)
            particle[object[count].particle[count2]].velocity[0]-=scale/(PHYSICSCYCLE*PHYSICSCYCLE);
          }
        if (object[count].axis[0]==1.0f)
          {
          for (count2=0;count2<4;count2++)
          if (particle[object[count].particle[count2]].velocity[0]<3.0f/PHYSICSCYCLE)
            particle[object[count].particle[count2]].velocity[0]+=scale/(PHYSICSCYCLE*PHYSICSCYCLE);
          }
        }

      if (object[count].beasttype==0 || object[count].beasttype==2 || object[count].beasttype==8 || object[count].beasttype==16)
      if (object[count].numoforientations!=0)
      if ((object[count].button&2)==2)
        for (count2=0;count2<4;count2++)
          {
          if (object[count].beasttype!=8)
            scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,yaxis,0.08f);
          else
            scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,yaxis,0.12f);
          }
      if (object[count].beasttype==15)
      if (object[count].numoforientations!=0)
      if ((object[count].button&2)==2)
        for (count2=0;count2<2;count2++)
          scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,yaxis,0.08f);

      if (object[count].numoforientations!=0)
      if (dotproduct(object[count].orientation[1],yaxis)<0.7f)
        {
        if (object[count].orientation[1][0]<0.0f)
          spin=1.0f;
        else
          spin=-1.0f;
        for (count2=0;count2<4;count2++)
          {
          subtractvectors(vec,particle[object[count].particle[count2]].position,object[count].position);
          crossproduct(vec2,zaxis,vec);
          normalizevector(vec2,vec2);
  
          scaleaddvectors(particle[object[count].particle[count2]].velocity,particle[object[count].particle[count2]].velocity,vec2,spin*0.003f);
          }
        }
      }
    }
  }

void objectsound(int objectnum)
  {
  int x,y;
  float vec[3];
  float scale;
  float pitch;

  x=object[objectnum].position[0];
  y=object[objectnum].position[1];
  if (block[level.foregrid[y][x]].density!=0.0f)
    {
    x=object[objectnum].prevposition[0];
    y=object[objectnum].prevposition[1];
    if (block[level.foregrid[y][x]].density==0.0f)
      {
      pitch=4.0f/object[objectnum].mass;

      if (pitch<0.5f)
        pitch=0.5f;

      if (pitch>1.0f)
        pitch=1.0f;

      scale=vectorlength(object[objectnum].velocity)*2.5f;

      x=object[objectnum].position[0];
      y=object[objectnum].position[1];

      if (block[level.foregrid[y][x]].foredamage==0)
        playsound(17,object[objectnum].position,NULL,scale,0,pitch,objectnum,3);
      else
        playsound(18,object[objectnum].position,NULL,scale,0,pitch,objectnum,3);
      }
    }
  if (object[objectnum].type==2 || object[objectnum].type==3)
    {
    subtractvectors(vec,object[objectnum].velocity,object[objectnum].prevvelocity);
    scale=vectorlength(vec);
    if (scale>0.025f)
      {
      pitch=1.0f/(object[objectnum].mass*0.2f);

      scale*=(1.0f/pitch);

      if (pitch<0.2f)
        pitch=0.2f;

      if (pitch>1.0f)
        pitch=1.0f;

      playsound(1,object[objectnum].position,NULL,scale*5.0f,0,pitch,objectnum,0);
      }
    }
  /*
  if (object[objectnum].type==2 || object[objectnum].type==3)
    {
    //scale=object[objectnum].frictionapplied;

    if (object[objectnum].numoforientations!=0)
      {
      vec[0]=vectorlength(object[objectnum].velocity);
      vec[1]=dotproduct(object[objectnum].velocity,object[objectnum].orientation[1]);
      scale=sqrt(vec[0]*vec[0]-vec[1]*vec[1]);
      }
    else
      scale=0.0f;

    if (scale>0.01f)
      {
      pitch=1.0f/(object[objectnum].mass*0.2f);
      scale*=(1.0f/pitch);

      if (pitch<0.2f)
        pitch=0.2f;

      if (pitch>1.0f)
        pitch=1.0f;

      if (object[objectnum].soundnum[1]==-1)
        playsound(6,object[objectnum].position,NULL,scale*5.0f,1,pitch,objectnum,1);
      }
    if (object[objectnum].soundnum[1]!=-1)
      {
      if (scale<0.005f)
        deletesound(object[objectnum].soundnum[1]);
      else
        {
        pitch=1.0f/(object[objectnum].mass*0.2f);
        scale*=(1.0f/pitch);

        alSourcef(sound[object[objectnum].soundnum[1]].alname,AL_GAIN,scale*5.0f);
        }
      }
    }
  */
  if (object[objectnum].type==4)
    {
    subtractvectors(vec,object[objectnum].velocity,object[objectnum].prevvelocity);
    scale=vectorlength(vec);
    if (scale>0.025f)
      {
      pitch=1.0f/(object[objectnum].mass*0.2f);

      scale*=(2.0f/pitch);

      if (pitch<0.2f)
        pitch=0.2f;

      if (pitch>1.0f)
        pitch=1.0f;

      playsound(2,object[objectnum].position,NULL,scale*5.0f,0,pitch,objectnum,0);
      }
    }
  if (object[objectnum].type==1)
    {
    subtractvectors(vec,object[objectnum].velocity,object[objectnum].prevvelocity);
    scale=vectorlength(vec);
    if (scale>0.025f)
      {
      if ((object[objectnum].button&8)==0)
        playsound(5,object[objectnum].position,NULL,scale*7.0f,0,1.0f,objectnum,0);
      else
        playsound(2,object[objectnum].position,NULL,scale*7.0f,0,1.0f,objectnum,0);
      }
    }

  copyvector(object[objectnum].prevvelocity,object[objectnum].velocity);
  object[objectnum].frictionapplied=0.0f;
  }
