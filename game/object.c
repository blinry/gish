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

void createbox(float position[3],float sizex,float sizey,float mass,float friction)
  {
  int count,count2;
  float vec[3];

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=2;
  object[numofobjects].timetolive=10000;
  object[numofobjects].mass=mass;

  object[numofobjects].numofparticles=4;
  if (sizex>=sizey)
    object[numofobjects].radius=sizex*1.5f;
  else
    object[numofobjects].radius=sizey*1.5f;

  object[numofobjects].size[0]=sizex;
  object[numofobjects].size[1]=sizey;

  object[numofobjects].friction=friction;

  count=0;

  vec[0]=-sizex*0.5f;
  vec[1]=sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=sizex*0.5f;
  vec[1]=sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=sizex*0.5f;
  vec[1]=-sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=-sizex*0.5f;
  vec[1]=-sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  for (count=0;count<object[numofobjects].numofparticles;count++)
  for (count2=count+1;count2<object[numofobjects].numofparticles;count2++)
    createbond(object[numofobjects].particle[count],object[numofobjects].particle[count2],1,-1);

  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=4;

  for (count=0;count<4;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    object[numofobjects].cdline[count][1]=((count+1)&3);
    }
  object[numofobjects].texcoord[0][0]=0.0f;
  object[numofobjects].texcoord[0][1]=0.0f;
  object[numofobjects].texcoord[1][0]=1.0f;
  object[numofobjects].texcoord[1][1]=0.0f;
  object[numofobjects].texcoord[2][0]=1.0f;
  object[numofobjects].texcoord[2][1]=1.0f;
  object[numofobjects].texcoord[3][0]=0.0f;
  object[numofobjects].texcoord[3][1]=1.0f;

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createtarboy(float position[3])
  {
  int count;
  float vec[3];
  float angle;
  float size;

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=1;
  object[numofobjects].timetolive=10000;
  object[numofobjects].radius=1.5f;

  object[numofobjects].mass=4.0f;

  object[numofobjects].friction=1.2f;

  if (numofobjects==0)
    object[numofobjects].direction=1;

  object[numofobjects].hitpoints=1000;

  object[numofobjects].numofparticles=16;
  for (count=0;count<16;count++)
    {
    angle=(float)count*pi/8.0f;
    size=0.9f;
    if (game.supersize)
      size=0.9f*1.25f;
    if (game.difficulty==4)
      size=0.9f*0.8f;
    vec[0]=position[0]+cos(angle)*size;
    vec[1]=position[1]-sin(angle)*size;
    vec[2]=0.0f;
    createparticle(1,vec,NULL,0.25f,numofobjects,10000);
    object[numofobjects].particle[count]=numofparticles-1;
    }

  for (count=0;count<16;count++)
    {
    createbond(object[numofobjects].particle[((count+1)&15)],object[numofobjects].particle[(count&15)],3,-1);
    createbond(object[numofobjects].particle[((count+2)&15)],object[numofobjects].particle[(count&15)],3,-1);
    createbond(object[numofobjects].particle[((count+8)&15)],object[numofobjects].particle[(count&15)],2,numofobjects);
    }
  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=16;

  for (count=0;count<16;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    object[numofobjects].cdline[count][1]=((count+1)&15);
    }

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createwheel(float position[3],float sizex,float sizey,float mass,float friction,int anchor)
  {
  int count;
  float vec[3];
  float angle;

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=3;
  object[numofobjects].timetolive=10000;
  if (sizex>=sizey)
    object[numofobjects].radius=sizex*1.25f;
  else
    object[numofobjects].radius=sizey*1.25f;

  object[numofobjects].mass=mass;

  object[numofobjects].friction=friction;

  object[numofobjects].numofparticles=17;
  for (count=0;count<16;count++)
    {
    angle=(float)count*pi/8.0f;
    vec[0]=position[0]+cos(angle)*sizex*0.5f;
    vec[1]=position[1]-sin(angle)*sizey*0.5f;
    vec[2]=0.0f;

    createparticle(3,vec,NULL,mass/20.0f,numofobjects,10000);
    object[numofobjects].particle[count]=numofparticles-1;
    }

  count=16;
  if (!anchor)
    createparticle(3,position,NULL,mass/5.0f,numofobjects,10000);
  else
    createparticle(2,position,NULL,mass/5.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;


  for (count=0;count<16;count++)
    {
    createbond(object[numofobjects].particle[((count+1)&15)],object[numofobjects].particle[(count&15)],1,numofobjects);
    createbond(object[numofobjects].particle[((count+2)&15)],object[numofobjects].particle[(count&15)],1,numofobjects);
    createbond(object[numofobjects].particle[((count+3)&15)],object[numofobjects].particle[(count&15)],1,numofobjects);
    //createbond(object[numofobjects].particle[((count+4)&15)],object[numofobjects].particle[(count&15)],1,numofobjects);
    //createbond(object[numofobjects].particle[((count+8)&15)],object[numofobjects].particle[(count&15)],1,numofobjects);
    createbond(object[numofobjects].particle[16],object[numofobjects].particle[(count&15)],1,numofobjects);
    }
  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=16;

  for (count=0;count<16;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    object[numofobjects].cdline[count][1]=((count+1)&15);
    }

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void setupobjecttypes(void)
  {
  int count;

  count=1;
  objecttype[count].collide[1]=1;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=1;
  objecttype[count].collide[10]=1;
  objecttype[count].collide[20]=1;

  count=2;
  objecttype[count].collide[1]=0;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=1;
  objecttype[count].collide[10]=1;
  objecttype[count].collide[20]=1;

  count=3;
  objecttype[count].collide[1]=0;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=1;
  objecttype[count].collide[10]=1;
  objecttype[count].collide[20]=1;

  count=4;
  objecttype[count].collide[1]=0;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=1;
  objecttype[count].collide[10]=1;
  objecttype[count].collide[20]=1;

  count=5;
  objecttype[count].collide[1]=0;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=1;
  objecttype[count].collide[10]=1;
  objecttype[count].collide[20]=1;

  count=6;
  objecttype[count].collide[1]=0;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=1;
  objecttype[count].collide[10]=1;
  objecttype[count].collide[20]=1;

  count=9;
  objecttype[count].collide[1]=0;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=0;
  objecttype[count].collide[10]=0;
  objecttype[count].collide[20]=1;

  count=10;
  objecttype[count].collide[1]=0;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=0;
  objecttype[count].collide[10]=0;
  objecttype[count].collide[20]=1;

  count=20;
  objecttype[count].collide[1]=0;
  objecttype[count].collide[2]=1;
  objecttype[count].collide[3]=1;
  objecttype[count].collide[4]=1;
  objecttype[count].collide[5]=1;
  objecttype[count].collide[6]=1;
  objecttype[count].collide[9]=1;
  objecttype[count].collide[10]=1;
  objecttype[count].collide[20]=1;
  }

void createrope(int type,int particlenum,int particlenum2,int objectnum,int objectnum2,int texturenum)
  {
  int count,count2;
  int length;
  float vec[3],vec2[3];
  float mass;

  if (type<5)
    {
    if (type==1)
      mass=0.125f;
    if (type==2)
      mass=0.25f;
    if (type==3)
      mass=1.0f;
    if (type==4)
      mass=2.0f;

    subtractvectors(vec,particle[particlenum2].position,particle[particlenum].position);
    length=vectorlength(vec);
    if (length<1)
      length=1;
    length*=2;
  
    scalevector(vec,vec,1.0f/(float)length);
    copyvector(vec2,particle[particlenum].position);
    addvectors(vec2,vec2,vec);
    createparticle(4,vec2,NULL,mass,-1,10000);
    createbond(particlenum,numofparticles-1,4,numofropes);
    rope[numofropes].type=type;
    rope[numofropes].part1=particlenum;
    rope[numofropes].part2=numofparticles-1;
    if (type<3)
      rope[numofropes].texturenum=360;
    else
      rope[numofropes].texturenum=361;
    numofropes++;
  
    for (count=1;count<length-1;count++)
      {
      addvectors(vec2,vec2,vec);
      createparticle(4,vec2,NULL,mass,-1,10000);
      createbond(numofparticles-2,numofparticles-1,4,numofropes);
      rope[numofropes].type=type;
      rope[numofropes].part1=numofparticles-2;
      rope[numofropes].part2=numofparticles-1;
      if (type<3)
        rope[numofropes].texturenum=360;
      else
        rope[numofropes].texturenum=361;
      numofropes++;
      }
    createbond(numofparticles-1,particlenum2,4,numofropes);
    rope[numofropes].type=type;
    rope[numofropes].part1=numofparticles-1;
    rope[numofropes].part2=particlenum2;
    if (type<3)
      rope[numofropes].texturenum=360;
    else
      rope[numofropes].texturenum=361;
    numofropes++;
    }
  else 
    {
    if (type<10)
      createbond(particlenum,particlenum2,7,numofropes);
    else
      createbond(particlenum,particlenum2,8,numofropes);

    if (type<9)
      {
      if (level.object[objectnum2].type==6 || level.object[objectnum2].type==7)
        {
        subtractvectors(vec,level.object[objectnum2].position,particle[particlenum].position);
        subtractvectors(vec2,particle[particlenum2].position,object[objectnum2].position);
        rope[numofropes].range=vectorlength(vec2);
  
        bond[numofbonds-1].length=vectorlength(vec)-rope[numofropes].range;
        bond[numofbonds-1].maxlength=vectorlength(vec)-rope[numofropes].range;
        }
      if (level.object[objectnum2].type>=2 && level.object[objectnum2].type<6)
        {
        subtractvectors(vec2,level.object[objectnum2].position,object[objectnum].position);
        subtractvectors(vec,particle[particlenum2].position,particle[particlenum].position);
  
        if (fabs(vec2[0])>fabs(vec2[1]))
          vec[1]=0.0f;
        else
          vec[0]=0.0f;
  
        normalizevector(vec,vec);
  
        if (type==5 || type==9)
          copyvector(vec2,particle[particlenum2].position);
        if (type==6 || type==8)
          scaleaddvectors(vec2,particle[particlenum2].position,vec,-level.object[objectnum].lightcolor[0]*0.5f);
        if (type==7)
          scaleaddvectors(vec2,particle[particlenum2].position,vec,-level.object[objectnum].lightcolor[0]);
        subtractvectors(vec2,particle[particlenum].position,vec2);
        bond[numofbonds-1].length=vectorlength(vec2);
        bond[numofbonds-1].maxlength=vectorlength(vec2);
  
        if (type==5)
          scaleaddvectors(vec2,particle[particlenum2].position,vec,level.object[objectnum].lightcolor[0]);
        if (type==6 || type==8)
          scaleaddvectors(vec2,particle[particlenum2].position,vec,level.object[objectnum].lightcolor[0]*0.5f);
        if (type==7 || type==9)
          copyvector(vec2,particle[particlenum2].position);
        subtractvectors(vec2,particle[particlenum].position,vec2);
        rope[numofropes].range=(vectorlength(vec2)-bond[numofbonds-1].maxlength)*0.5f;
        }
      }

    rope[numofropes].type=type;
    rope[numofropes].part1=particlenum;
    rope[numofropes].part2=particlenum2;
    rope[numofropes].bondnum=numofbonds-1;
    if (type==5)
      rope[numofropes].angle=0.0f;
    if (type==6)
      rope[numofropes].angle=pi/2.0f;
    if (type==7)
      rope[numofropes].angle=pi;
    if (type==8)
      rope[numofropes].angle=3.0f*pi/2.0f;

    rope[numofropes].cycle=level.object[objectnum].lightcolor[1];
    rope[numofropes].cyclelength=level.object[objectnum].lightcolor[2];
    rope[numofropes].cyclecount=0.0f;
    rope[numofropes].link=level.object[objectnum].link;
    if (texturenum==0)
      rope[numofropes].texturenum=0;
    if (texturenum==1)
      rope[numofropes].texturenum=362;
    if (texturenum==2)
      rope[numofropes].texturenum=362;
    if (texturenum==3)
      rope[numofropes].texturenum=362;

    numofropes++;
    }
  }

void createanchor(float position[3])
  {
  int count;
  float vec[3];

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=8;
  object[numofobjects].timetolive=10000;

  object[numofobjects].radius=1.0f;

  object[numofobjects].friction=0.8f;

  object[numofobjects].numofparticles=0;

  copyvector(vec,position);
  vec[0]+=0.00001f;
  createparticle(2,position,NULL,10000.0f,numofobjects,10000);
  object[numofobjects].particle[0]=numofparticles-1;
  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=0;

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createbutton(float position[3],float mass)
  {
  int count,count2;
  float vec[3];

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=9;
  object[numofobjects].timetolive=10000;

  object[numofobjects].friction=0.3f;
  object[numofobjects].radius=1.5f;

  object[numofobjects].numofparticles=7;

  count=0;

  vec[0]=position[0]-0.499f;
  vec[1]=position[1]+0.5f;
  vec[2]=0.0f;
  createparticle(3,vec,NULL,mass/16.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=position[0]-0.125f;
  vec[1]=position[1]+0.75f;
  vec[2]=0.0f;
  createparticle(3,vec,NULL,mass/16.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=position[0]+0.125f;
  vec[1]=position[1]+0.75f;
  vec[2]=0.0f;
  createparticle(3,vec,NULL,mass/16.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=position[0]+0.499f;
  vec[1]=position[1]+0.5f;
  vec[2]=0.0f;
  createparticle(3,vec,NULL,mass/16.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=position[0]+0.499f;
  vec[1]=position[1]-0.125f;
  vec[2]=0.0f;
  createparticle(3,vec,NULL,mass/16.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=position[0]-0.499f;
  vec[1]=position[1]-0.125f;
  vec[2]=0.0f;
  createparticle(3,vec,NULL,mass/16.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=position[0];
  vec[1]=position[1]-0.125f;
  vec[2]=0.0f;
  createparticle(2,vec,NULL,1.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  for (count=0;count<6;count++)
  for (count2=count+1;count2<6;count2++)
    createbond(object[numofobjects].particle[count],object[numofobjects].particle[count2],1,numofobjects);

  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=6;
  for (count=0;count<6;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    object[numofobjects].cdline[count][1]=((count+1)%6);
    }

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createswitch(float position[3],float mass,int rotate)
  {
  int count,count2;
  float vec[3],vec2[3];
  float orientation[2][2];

  if (rotate==0)
    {
    orientation[0][0]=1.0f;
    orientation[0][1]=0.0f;
    orientation[1][0]=0.0f;
    orientation[1][1]=1.0f;
    }
  if (rotate==1)
    {
    orientation[0][0]=0.0f;
    orientation[0][1]=-1.0f;
    orientation[1][0]=1.0f;
    orientation[1][1]=0.0f;
    }
  if (rotate==2)
    {
    orientation[0][0]=-1.0f;
    orientation[0][1]=0.0f;
    orientation[1][0]=0.0f;
    orientation[1][1]=-1.0f;
    }
  if (rotate==3)
    {
    orientation[0][0]=0.0f;
    orientation[0][1]=-1.0f;
    orientation[1][0]=-1.0f;
    orientation[1][1]=0.0f;
    }

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=10;
  object[numofobjects].timetolive=10000;

  object[numofobjects].radius=1.5f;

  object[numofobjects].friction=0.3f;

  object[numofobjects].rotate=rotate;

  object[numofobjects].numofparticles=5;

  count=0;

  vec[0]=-0.875f;
  vec[1]=0.875f;
  vec2[0]=position[0]+vec[0]*orientation[0][0]+vec[1]*orientation[1][0];
  vec2[1]=position[1]+vec[0]*orientation[0][1]+vec[1]*orientation[1][1];
  vec2[2]=0.0f;
  createparticle(3,vec2,NULL,mass/8.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=0.25f;
  vec[1]=0.0f;
  vec2[0]=position[0]+vec[0]*orientation[0][0]+vec[1]*orientation[1][0];
  vec2[1]=position[1]+vec[0]*orientation[0][1]+vec[1]*orientation[1][1];
  vec2[2]=0.0f;
  createparticle(3,vec2,NULL,mass/8.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=-0.25f;
  vec[1]=-0.5f;
  vec[2]=0.0f;
  vec2[0]=position[0]+vec[0]*orientation[0][0]+vec[1]*orientation[1][0];
  vec2[1]=position[1]+vec[0]*orientation[0][1]+vec[1]*orientation[1][1];
  vec2[2]=0.0f;
  createparticle(3,vec2,NULL,mass/8.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=-1.125f;
  vec[1]=0.625f;
  vec[2]=0.0f;
  vec2[0]=position[0]+vec[0]*orientation[0][0]+vec[1]*orientation[1][0];
  vec2[1]=position[1]+vec[0]*orientation[0][1]+vec[1]*orientation[1][1];
  vec2[2]=0.0f;
  createparticle(3,vec2,NULL,mass/8.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  vec[0]=0.0f;
  vec[1]=-0.25f;
  vec[2]=0.0f;
  vec2[0]=position[0]+vec[0]*orientation[0][0]+vec[1]*orientation[1][0];
  vec2[1]=position[1]+vec[0]*orientation[0][1]+vec[1]*orientation[1][1];
  vec2[2]=0.0f;
  createparticle(2,vec2,NULL,10000.0f,numofobjects,10000);
  object[numofobjects].particle[count]=numofparticles-1;
  count++;

  for (count=0;count<5;count++)
  for (count2=count+1;count2<5;count2++)
    createbond(object[numofobjects].particle[count],object[numofobjects].particle[count2],1,numofobjects);

  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=4;
  for (count=0;count<4;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    if (rotate!=3)
      object[numofobjects].cdline[count][1]=((count+1)&3);
    else
      object[numofobjects].cdline[count][1]=((count-1)&3);
    }

  object[numofobjects].texcoord[0][0]=0.0f;
  object[numofobjects].texcoord[0][1]=0.0f;
  object[numofobjects].texcoord[1][0]=1.0f;
  object[numofobjects].texcoord[1][1]=0.0f;
  object[numofobjects].texcoord[2][0]=1.0f;
  object[numofobjects].texcoord[2][1]=1.0f;
  object[numofobjects].texcoord[3][0]=0.0f;
  object[numofobjects].texcoord[3][1]=1.0f;

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createbeast(int beasttype,float position[3],float sizex,float sizey,float mass,float friction)
  {
  int count,count2;
  float vec[3];

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=4;
  object[numofobjects].timetolive=10000;

  object[numofobjects].beasttype=beasttype;
  object[numofobjects].animationnum=beasttype;
  object[numofobjects].texturenum=animation[object[numofobjects].animationnum].stand[0];
  object[numofobjects].mass=mass;

  object[numofobjects].hitpoints=250;
  if (beasttype==7 || beasttype==13)
    object[numofobjects].hitpoints=15000;

  object[numofobjects].size[0]=sizex;
  object[numofobjects].size[1]=sizey;

  object[numofobjects].numofparticles=4;

  if (sizex>=sizey)
    object[numofobjects].radius=sizex*1.5f;
  else
    object[numofobjects].radius=sizey*1.5f;

  object[numofobjects].friction=friction;

  count=0;

  vec[0]=-sizex*0.5f;
  vec[1]=sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.5f,-1,10000);

  vec[0]=sizex*0.5f;
  vec[1]=sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.5f,-1,10000);

  vec[0]=sizex*0.5f;
  vec[1]=-sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  if (beasttype!=12)
    createparticle(3,vec,NULL,mass*0.5f,-1,10000);
  else
    createparticle(2,vec,NULL,mass*0.5f,-1,10000);

  vec[0]=-sizex*0.5f;
  vec[1]=-sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  if (beasttype!=12)
    createparticle(3,vec,NULL,mass*0.5f,-1,10000);
  else
    createparticle(2,vec,NULL,mass*0.5f,-1,10000);

  for (count=0;count<object[numofobjects].numofparticles;count++)
  for (count2=count+1;count2<object[numofobjects].numofparticles;count2++)
    createbond(object[numofobjects].particle[count],object[numofobjects].particle[count2],6,numofobjects);

  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=4;

  for (count=0;count<4;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    object[numofobjects].cdline[count][1]=((count+1)&3);
    }

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createbobble(int beasttype,float position[3],float sizex,float sizey,float mass,float friction)
  {
  int count,count2;
  float vec[3];

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=4;
  object[numofobjects].timetolive=10000;
  object[numofobjects].mass=mass;

  object[numofobjects].beasttype=beasttype;
  if (beasttype==1)
    object[numofobjects].texturenum=500;
  if (beasttype==2)
    object[numofobjects].texturenum=540;

  object[numofobjects].numofparticles=6;

  if (sizex>=sizey)
    object[numofobjects].radius=sizex*1.5f;
  else
    object[numofobjects].radius=sizey*1.5f;

  object[numofobjects].friction=friction;

  count=0;

  vec[0]=-sizex*0.5f;
  vec[1]=sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=sizex*0.5f;
  vec[1]=sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=sizex*0.5f;
  vec[1]=-sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=-sizex*0.5f;
  vec[1]=-sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=-sizex*0.25f;
  vec[1]=sizey*0.65f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=sizex*0.25f;
  vec[1]=sizey*0.65f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(3,vec,NULL,mass*0.25f,-1,10000);

  for (count=0;count<object[numofobjects].numofparticles;count++)
  for (count2=count+1;count2<object[numofobjects].numofparticles;count2++)
    createbond(object[numofobjects].particle[count],object[numofobjects].particle[count2],6,numofobjects);

  object[numofobjects].numofcdlines=6;

  count=0;
  object[numofobjects].cdline[count][0]=4;
  object[numofobjects].cdline[count][1]=5;
  count=1;
  object[numofobjects].cdline[count][0]=5;
  object[numofobjects].cdline[count][1]=1;
  count=2;
  object[numofobjects].cdline[count][0]=1;
  object[numofobjects].cdline[count][1]=2;
  count=3;
  object[numofobjects].cdline[count][0]=2;
  object[numofobjects].cdline[count][1]=3;
  count=4;
  object[numofobjects].cdline[count][0]=3;
  object[numofobjects].cdline[count][1]=0;
  count=5;
  object[numofobjects].cdline[count][0]=0;
  object[numofobjects].cdline[count][1]=4;

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createhead(float position[3],float sizex,float sizey,float mass,float friction)
  {
  int count;
  float vec[3];
  float angle;

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=5;
  object[numofobjects].timetolive=10000;
  if (sizex>=sizey)
    object[numofobjects].radius=sizex*1.25f;
  else
    object[numofobjects].radius=sizey*1.25f;

  object[numofobjects].mass=mass;

  object[numofobjects].texturenum=animation[19].stand[0];

  object[numofobjects].friction=friction;

  object[numofobjects].numofparticles=8;
  for (count=0;count<8;count++)
    {
    angle=(float)count*pi/4.0f;
    vec[0]=position[0]+cos(angle)*sizex*0.5f;
    vec[1]=position[1]-sin(angle)*sizey*0.5f;
    vec[2]=0.0f;

    createparticle(3,vec,NULL,mass/8.0f,numofobjects,10000);
    object[numofobjects].particle[count]=numofparticles-1;
    }

  for (count=0;count<8;count++)
    {
    createbond(object[numofobjects].particle[((count+1)&7)],object[numofobjects].particle[count],1,numofobjects);
    createbond(object[numofobjects].particle[((count+2)&7)],object[numofobjects].particle[count],1,numofobjects);
    createbond(object[numofobjects].particle[((count+4)&7)],object[numofobjects].particle[count],1,numofobjects);
    }
  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=8;

  for (count=0;count<8;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    object[numofobjects].cdline[count][1]=((count+1)&7);
    }

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createamber(float position[3])
  {
  int count;
  float vec[3];
  float angle;

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=6;
  object[numofobjects].timetolive=10000;
  object[numofobjects].radius=1.0f;
  object[numofobjects].texturenum=369;

  object[numofobjects].friction=0.3f;

  object[numofobjects].numofparticles=8;
  for (count=0;count<8;count++)
    {
    angle=(float)count*pi/4.0f;
    vec[0]=position[0]+cos(angle)*0.35f;
    vec[1]=position[1]-sin(angle)*0.35f;
    vec[2]=0.0f;

    createparticle(3,vec,NULL,0.125f,numofobjects,10000);
    object[numofobjects].particle[count]=numofparticles-1;
    }

  for (count=0;count<8;count++)
    {
    createbond(object[numofobjects].particle[((count+1)&7)],object[numofobjects].particle[count],1,numofobjects);
    createbond(object[numofobjects].particle[((count+2)&7)],object[numofobjects].particle[count],1,numofobjects);
    createbond(object[numofobjects].particle[((count+4)&7)],object[numofobjects].particle[count],1,numofobjects);
    }
  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=8;

  for (count=0;count<8;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    object[numofobjects].cdline[count][1]=((count+1)&7);
    }

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void createareaswitch(float position[3],float sizex,float sizey)
  {
  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=16;
  object[numofobjects].timetolive=10000;
  copyvector(object[numofobjects].position,position);
  object[numofobjects].size[0]=sizex;
  object[numofobjects].size[1]=sizey;

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void creategenerator(float position[3],float mass)
  {
  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=15;
  object[numofobjects].timetolive=10000;
  object[numofobjects].mass=mass;
  copyvector(object[numofobjects].position,position);

  object[numofobjects].radius=2.0f;

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }

void deleteobject(int objectnum)
  {
  int count;

  if (objectnum<0)
    return;
  if (objectnum>=numofobjects)
    return;

  for (count=0;count<object[objectnum].numofparticles;count++)
    {
    particle[object[objectnum].particle[count]].timetolive=1;
    particle[object[objectnum].particle[count]].objectnum=-1;
    }
  for (count=0;count<numofobjects;count++)
  if (object[count].link==objectnum)
    object[count].link=-1;

  for (count=0;count<numofropes;count++)
  if (rope[count].link==objectnum)
    rope[count].link=-1;

  for (count=0;count<numofbonds;count++)
  if (bond[count].type!=4 && bond[count].type!=7)
    if (bond[count].objectnum==objectnum)
      bond[count].objectnum=-1;

  deletesound(object[objectnum].soundnum[0]);
  deletesound(object[objectnum].soundnum[1]);
  deletesound(object[objectnum].soundnum[2]);
  deletesound(object[objectnum].soundnum[3]);

  numofobjects--;

  if (objectnum==numofobjects)
    return;

  memcpy(&object[objectnum],&object[numofobjects],sizeof(object[objectnum]));

  for (count=0;count<object[objectnum].numofparticles;count++)
  if (particle[object[objectnum].particle[count]].objectnum!=-1)
    particle[object[objectnum].particle[count]].objectnum=objectnum;

  for (count=0;count<numofobjects;count++)
  if (object[count].link==numofobjects)
    object[count].link=objectnum;

  for (count=0;count<numofropes;count++)
  if (rope[count].link==numofobjects)
    rope[count].link=objectnum;

  for (count=0;count<numofbonds;count++)
  if (bond[count].type!=4 && bond[count].type!=7)
    if (bond[count].objectnum==numofobjects)
      bond[count].objectnum=objectnum;

  for (count=0;count<numofsounds;count++)
  if (sound[count].objectnum==numofobjects)
    sound[count].objectnum=objectnum;
  }

void deleterope(int ropenum)
  {
  int count;

  if (ropenum<0)
    return;
  if (ropenum>=numofropes)
    return;

  if (rope[ropenum].type==1)
    playsound(3,particle[rope[ropenum].part1].position,NULL,1.0f,0,1.0f,-1,0);
  if (rope[ropenum].type==2)
    playsound(3,particle[rope[ropenum].part1].position,NULL,1.0f,0,0.75f,-1,0);
  if (rope[ropenum].type==3)
    playsound(4,particle[rope[ropenum].part1].position,NULL,1.0f,0,1.0f,-1,0);
  if (rope[ropenum].type==4)
    playsound(4,particle[rope[ropenum].part1].position,NULL,1.0f,0,0.75f,-1,0);

  numofropes--;

  if (ropenum==numofropes)
    return;

  memcpy(&rope[ropenum],&rope[numofropes],sizeof(rope[0]));

  for (count=0;count<numofbonds;count++)
    if (bond[count].type==4 || bond[count].type==7)
      if (bond[count].objectnum==numofropes)
        bond[count].objectnum=ropenum;
  }

void objecttimetolive(void)
  {
  int count;

  count=0;
  while (count<numofobjects)
    {
    if (object[count].timetolive<10000)
      object[count].timetolive--;
    while (count<numofobjects && object[count].timetolive<0)
      {
      deleteobject(count);

      if (object[count].timetolive<10000)
        object[count].timetolive--;
      }
    count++;
    }
  }

void createcar(float position[3],float sizex,float sizey,float mass,float friction)
  {
  int count,count2;
  float vec[3];

  memset(&object[numofobjects],0,sizeof(object[numofobjects]));

  object[numofobjects].type=20;
  object[numofobjects].timetolive=10000;
  object[numofobjects].mass=mass;

  object[numofobjects].numofparticles=4;
  if (sizex>=sizey)
    object[numofobjects].radius=sizex*1.5f;
  else
    object[numofobjects].radius=sizey*1.5f;

  object[numofobjects].size[0]=sizex;
  object[numofobjects].size[1]=sizey;

  object[numofobjects].friction=friction;

  count=0;

  vec[0]=-sizex*0.5f;
  vec[1]=sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(6,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=sizex*0.5f;
  vec[1]=sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(6,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=sizex*0.5f;
  vec[1]=-sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(6,vec,NULL,mass*0.25f,-1,10000);

  vec[0]=-sizex*0.5f;
  vec[1]=-sizey*0.5f;
  vec[2]=0.0f;
  addvectors(vec,vec,position);
  object[numofobjects].particle[count]=numofparticles;
  count++;
  createparticle(6,vec,NULL,mass*0.25f,-1,10000);

  for (count=0;count<object[numofobjects].numofparticles;count++)
  for (count2=count+1;count2<object[numofobjects].numofparticles;count2++)
    createbond(object[numofobjects].particle[count],object[numofobjects].particle[count2],9,-1);

  copyvector(object[numofobjects].position,position);

  object[numofobjects].numofcdlines=4;

  for (count=0;count<4;count++)
    {
    object[numofobjects].cdline[count][0]=count;
    object[numofobjects].cdline[count][1]=((count+1)&3);
    }
  object[numofobjects].texcoord[0][0]=0.0f;
  object[numofobjects].texcoord[0][1]=0.0f;
  object[numofobjects].texcoord[1][0]=1.0f;
  object[numofobjects].texcoord[1][1]=0.0f;
  object[numofobjects].texcoord[2][0]=1.0f;
  object[numofobjects].texcoord[2][1]=1.0f;
  object[numofobjects].texcoord[3][0]=0.0f;
  object[numofobjects].texcoord[3][1]=1.0f;

  object[numofobjects].soundnum[0]=-1;
  object[numofobjects].soundnum[1]=-1;
  object[numofobjects].soundnum[2]=-1;
  object[numofobjects].soundnum[3]=-1;

  numofobjects++;
  }
