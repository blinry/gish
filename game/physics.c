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

void setupphysics(void)
  {
  int count;

  count=1;
  particletype[count].drag=0.995f;
  particletype[count].gravity=4.0f/(PHYSICSCYCLE*PHYSICSCYCLE);
  particletype[count].elasticity=1.2f;
  particletype[count].friction=1.2f;
  particletype[count].levelcollision=0;
  particletype[count].objectcollision=0;
  particletype[count].rendertype=0;

  count=2;
  particletype[count].drag=0.0f;
  particletype[count].gravity=0.0f;
  particletype[count].elasticity=1.2f;
  particletype[count].friction=1.2f;
  particletype[count].levelcollision=0;
  particletype[count].objectcollision=0;
  particletype[count].rendertype=0;

  count=3;
  particletype[count].drag=0.999f;
  particletype[count].gravity=4.0f/(PHYSICSCYCLE*PHYSICSCYCLE);
  particletype[count].elasticity=1.2f;
  particletype[count].friction=1.2f;
  particletype[count].levelcollision=0;
  particletype[count].objectcollision=0;
  particletype[count].rendertype=0;

  count=4;
  particletype[count].drag=0.995f;
  particletype[count].gravity=4.0f/(PHYSICSCYCLE*PHYSICSCYCLE);
  particletype[count].elasticity=1.2f;
  particletype[count].friction=0.2f;
  particletype[count].levelcollision=1;
  particletype[count].objectcollision=0;
  particletype[count].rendertype=0;

  count=5;
  particletype[count].drag=0.99f;
  particletype[count].gravity=4.0f/(PHYSICSCYCLE*PHYSICSCYCLE);
  particletype[count].elasticity=1.2f;
  particletype[count].friction=0.2f;
  particletype[count].levelcollision=1;
  particletype[count].objectcollision=0;
  particletype[count].rendertype=0;

  count=6;
  particletype[count].drag=0.999f;
  particletype[count].gravity=0.0f;
  particletype[count].elasticity=1.2f;
  particletype[count].friction=0.3f;
  particletype[count].levelcollision=1;
  particletype[count].objectcollision=0;
  particletype[count].rendertype=0;

  count=16;
  particletype[count].drag=0.999f;
  particletype[count].gravity=0.0f;
  particletype[count].elasticity=1.2f;
  particletype[count].friction=0.3f;
  particletype[count].levelcollision=0;
  particletype[count].objectcollision=0;
  particletype[count].rendertype=0;

  count=1;
  bondtype[count].elasticity=0.2f;
  bondtype[count].cycles=1;
  bondtype[count].compression=0.1f;
  bondtype[count].tension=1.9f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=2;
  bondtype[count].elasticity=0.02f;
  bondtype[count].cycles=31;
  bondtype[count].compression=0.1f;
  bondtype[count].tension=1.9f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=3;
  bondtype[count].elasticity=0.2f;
  bondtype[count].cycles=3;
  bondtype[count].compression=0.1f;
  bondtype[count].tension=1.9f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=4;
  bondtype[count].elasticity=0.5f;
  bondtype[count].cycles=1;
  bondtype[count].compression=0.0f;
  bondtype[count].tension=1.15f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=5;
  bondtype[count].elasticity=0.1f;
  bondtype[count].cycles=31;
  bondtype[count].compression=0.1f;
  bondtype[count].tension=1.9f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=6;
  bondtype[count].elasticity=0.2f;
  bondtype[count].cycles=15;
  bondtype[count].compression=0.75f;
  bondtype[count].tension=1.25f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=7;
  bondtype[count].elasticity=0.2f;
  bondtype[count].cycles=0;
  bondtype[count].compression=0.5f;
  bondtype[count].tension=1.5f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=8;
  bondtype[count].elasticity=0.002f;
  bondtype[count].cycles=0;
  bondtype[count].compression=0.5f;
  bondtype[count].tension=1.5f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=9;
  bondtype[count].elasticity=0.2f;
  bondtype[count].cycles=0;
  bondtype[count].compression=0.5f;
  bondtype[count].tension=1.5f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;

  count=16;
  bondtype[count].elasticity=0.1f;
  bondtype[count].cycles=31;
  bondtype[count].compression=0.5f;
  bondtype[count].tension=1.5f;
  bondtype[count].rendertype=1;
  bondtype[count].rendersize=0.4f;
  }

void particlecollision(int particlenum)
  {
  float vec[3],vec2[3],vec3[3];
  float intersectpoint[3];
  float normal[3];
  float scale;

  if (pointintersectlevel(intersectpoint,normal,&scale,particle[particlenum].position))
    {
    subtractvectors(vec2,intersectpoint,particle[particlenum].position);
    scaleaddvectors(vec,particle[particlenum].position,normal,dotproduct(vec2,normal));

    physicstemp.bond[physicstemp.numofbonds].part1=particlenum;
    physicstemp.bond[physicstemp.numofbonds].type=0;
    physicstemp.bond[physicstemp.numofbonds].cycles=3;
    physicstemp.bond[physicstemp.numofbonds].length=0.0f;
    physicstemp.bond[physicstemp.numofbonds].elasticity=0.2f;
    physicstemp.bond[physicstemp.numofbonds].friction=particle[particlenum].friction;
    if (collision.friction<particle[particlenum].friction)
      physicstemp.bond[physicstemp.numofbonds].friction=collision.friction;
    physicstemp.bond[physicstemp.numofbonds].objectnum[0]=-1;
    physicstemp.bond[physicstemp.numofbonds].blocknum=collision.blocknum;
    physicstemp.bond[physicstemp.numofbonds].blockx=collision.blockx;
    physicstemp.bond[physicstemp.numofbonds].blocky=collision.blocky;

    copyvector(physicstemp.bond[physicstemp.numofbonds].point,vec);
    copyvector(physicstemp.bond[physicstemp.numofbonds].normal,normal);
    physicstemp.numofbonds++;
    }
  }

void objectcollision(int objectnum)
  {
  int count,count2;
  int part1,part2;
  int blocknum;
  int particlenum;
  int particlelist[2];
  float vec[3],vec2[3],vec3[3];
  float intersectpoint[3];
  float normal[3];
  float force[2];
  float scale;
  float friction;

  copyvector(object[objectnum].prevposition,object[objectnum].position);

  if (object[objectnum].numofparticles!=0)
    {
    zerovector(object[objectnum].position);
    for (count=0;count<object[objectnum].numofparticles;count++)
      addvectors(object[objectnum].position,object[objectnum].position,particle[object[objectnum].particle[count]].position);
    scalevector(object[objectnum].position,object[objectnum].position,1.0f/(float)object[objectnum].numofparticles);

    object[objectnum].numoforientations=0;
    zerovector(object[objectnum].orientation[1]);

    if (object[objectnum].type!=1)
    if (object[objectnum].type!=2 || object[objectnum].size[0]>0.5f)
      {
      getlevellines(objectnum);
      for (count=0;count<numoflevellines;count++)
        {
        if (lineintersectobject(intersectpoint,normal,&scale,levelline[count].line[0],levelline[count].line[1],objectnum,particlelist))
          {
          part1=particlelist[0];
          part2=particlelist[1];
  
          if (dotproduct(normal,levelline[count].normal)<-0.707f)
            {
            subtractvectors(object[objectnum].orientation[1],object[objectnum].orientation[1],normal);
            object[objectnum].numoforientations++;
  
            collision.friction=levelline[count].friction;
            collision.blocknum=levelline[count].blocknum;
            collision.blockx=levelline[count].blockx;
            collision.blocky=levelline[count].blocky;
  
            subtractvectors(vec,intersectpoint,levelline[count].line[1]);
            scaleaddvectors(vec2,levelline[count].line[1],normal,dotproduct(vec,normal));
  
            subtractvectors(vec,particle[object[objectnum].particle[part2]].position,particle[object[objectnum].particle[part1]].position);
            scale=vectorlength(vec);
            subtractvectors(vec,particle[object[objectnum].particle[part1]].position,intersectpoint);
            force[0]=vectorlength(vec)/scale;
            subtractvectors(vec,particle[object[objectnum].particle[part2]].position,intersectpoint);
            force[1]=vectorlength(vec)/scale;
            if (force[0]>1.0f)
              force[0]=1.0f;
            if (force[1]>1.0f)
              force[1]=1.0f;
  
            physicstemp.bond[physicstemp.numofbonds].part1=object[objectnum].particle[part1];
            physicstemp.bond[physicstemp.numofbonds].part2=object[objectnum].particle[part2];
            physicstemp.bond[physicstemp.numofbonds].type=2;
            subtractvectors(vec,vec2,intersectpoint);
            physicstemp.bond[physicstemp.numofbonds].length=vectorlength(vec);
  
            copyvector(physicstemp.bond[physicstemp.numofbonds].normal,normal);
            physicstemp.bond[physicstemp.numofbonds].cycles=0;
            physicstemp.bond[physicstemp.numofbonds].elasticity=0.2f;
            physicstemp.bond[physicstemp.numofbonds].friction=object[objectnum].friction;
            if (collision.friction<object[objectnum].friction)
              physicstemp.bond[physicstemp.numofbonds].friction=collision.friction;
            physicstemp.bond[physicstemp.numofbonds].force[0]=force[1];
            physicstemp.bond[physicstemp.numofbonds].force[1]=force[0];
            physicstemp.bond[physicstemp.numofbonds].objectnum[0]=objectnum;
            physicstemp.bond[physicstemp.numofbonds].objectnum[1]=objectnum;
            physicstemp.bond[physicstemp.numofbonds].blocknum=collision.blocknum;
            physicstemp.bond[physicstemp.numofbonds].blockx=collision.blockx;
            physicstemp.bond[physicstemp.numofbonds].blocky=collision.blocky;
    
            physicstemp.numofbonds++;
            }
          }
        }
      }
    for (count=0;count<object[objectnum].numofparticles;count++)
      {
      if (object[objectnum].particlestick[count])
        {
        scaleaddvectors(object[objectnum].orientation[1],object[objectnum].orientation[1],object[objectnum].particlesticknormal[count],0.5f);
        object[objectnum].numoforientations++;
        }

      particlenum=object[objectnum].particle[count];
      if (pointintersectlevel(intersectpoint,normal,&scale,particle[particlenum].position))
        {
        addvectors(object[objectnum].orientation[1],object[objectnum].orientation[1],normal);
        object[objectnum].numoforientations++;

        if (object[objectnum].timetolive==10001)
          object[objectnum].timetolive=50;

        if (object[objectnum].type==1 || object[objectnum].type==4)
          {
          blocknum=collision.blocknum;

          if (block[blocknum].animation!=0)
          if (block[blocknum].animationspeed!=0)
            blocknum+=(game.framenum/block[blocknum].animationspeed)%block[blocknum].animation;

          if (block[blocknum].middamage!=0)
            {
            if (object[objectnum].type==1)
              object[objectnum].hitpoints-=block[blocknum].middamage;
            if (object[objectnum].type==4)
              object[objectnum].hitpoints-=block[blocknum].middamage*4;
            }
          }

        subtractvectors(vec2,intersectpoint,particle[particlenum].position);
        scaleaddvectors(vec,particle[particlenum].position,normal,dotproduct(vec2,normal));

        physicstemp.bond[physicstemp.numofbonds].part1=particlenum;
        physicstemp.bond[physicstemp.numofbonds].type=0;
        physicstemp.bond[physicstemp.numofbonds].cycles=0;
        physicstemp.bond[physicstemp.numofbonds].length=0.0f;
        physicstemp.bond[physicstemp.numofbonds].elasticity=0.2f;
        physicstemp.bond[physicstemp.numofbonds].friction=object[objectnum].friction;
        if (collision.friction<object[objectnum].friction)
          physicstemp.bond[physicstemp.numofbonds].friction=collision.friction;
        physicstemp.bond[physicstemp.numofbonds].objectnum[0]=objectnum;
        physicstemp.bond[physicstemp.numofbonds].blocknum=collision.blocknum;
        physicstemp.bond[physicstemp.numofbonds].blockx=collision.blockx;
        physicstemp.bond[physicstemp.numofbonds].blocky=collision.blocky;

        copyvector(physicstemp.bond[physicstemp.numofbonds].point,vec);
        copyvector(physicstemp.bond[physicstemp.numofbonds].normal,normal);
        physicstemp.numofbonds++;

        if ((object[objectnum].button&1)==1 && object[objectnum].type==1)
        if (collision.friction>0.1f)
          {
          if (!object[objectnum].particlestick[count])
            {
            object[objectnum].particlestick[count]=1;
            copyvector(object[objectnum].particlesticknormal[count],normal);

            copyvector(object[objectnum].particlestickposition[count],intersectpoint);

            physicstemp.bond[physicstemp.numofbonds].part1=object[objectnum].particle[count];
            physicstemp.bond[physicstemp.numofbonds].part4=count;
            physicstemp.bond[physicstemp.numofbonds].type=1;
            physicstemp.bond[physicstemp.numofbonds].cycles=0;
            physicstemp.bond[physicstemp.numofbonds].length=0.0f;
            physicstemp.bond[physicstemp.numofbonds].elasticity=0.2f;
            physicstemp.bond[physicstemp.numofbonds].breakpoint=0.25f;
            if (fabs(normal[1])<0.707f)
              physicstemp.bond[physicstemp.numofbonds].breakpoint=0.2f;
            physicstemp.bond[physicstemp.numofbonds].objectnum[0]=objectnum;
            physicstemp.bond[physicstemp.numofbonds].blocknum=collision.blocknum;
            physicstemp.bond[physicstemp.numofbonds].blockx=collision.blockx;
            physicstemp.bond[physicstemp.numofbonds].blocky=collision.blocky;

    
            copyvector(physicstemp.bond[physicstemp.numofbonds].point,vec);
            copyvector(physicstemp.bond[physicstemp.numofbonds].normal,normal);
            physicstemp.numofbonds++;
            }
          }
        }
      }
    }
  }

void objectcollisionobject(int objectnum)
  {
  int count,count2;
  int part1,part2;
  int objectcount;
  int particlenum;
  int particlelist[2];
  float vec[3],vec2[3],vec3[3];
  float intersectpoint[3];
  float normal[3];
  float force[2];
  float scale;
  float friction;

  if (object[objectnum].type==3)
    for (count=0;count<object[objectnum].numofparticles;count++)
      {
      particlenum=object[objectnum].particle[count];

      for (count2=0;count2<numofropes;count2++)
      if (rope[count2].type<=4)
      if (lineintersectline(intersectpoint,normal,&scale,object[objectnum].position,particle[object[objectnum].particle[count]].position,particle[rope[count2].part1].position,particle[rope[count2].part2].position))
        {
        subtractvectors(vec,intersectpoint,particle[particlenum].position);
        scaleaddvectors(vec2,particle[particlenum].position,normal,dotproduct(vec,normal));

        subtractvectors(vec,particle[rope[count2].part2].position,particle[rope[count2].part1].position);
        scale=vectorlength(vec);
        subtractvectors(vec,particle[rope[count2].part1].position,intersectpoint);
        force[0]=vectorlength(vec)/scale;
        subtractvectors(vec,particle[rope[count2].part2].position,intersectpoint);
        force[1]=vectorlength(vec)/scale;
        if (force[0]>1.0f)
          force[0]=1.0f;
        if (force[1]>1.0f)
          force[1]=1.0f;

        physicstemp.bond[physicstemp.numofbonds].part1=rope[count2].part1;
        physicstemp.bond[physicstemp.numofbonds].part2=rope[count2].part2;
        physicstemp.bond[physicstemp.numofbonds].part3=particlenum;
        physicstemp.bond[physicstemp.numofbonds].type=4;
        subtractvectors(vec,vec2,intersectpoint);
        physicstemp.bond[physicstemp.numofbonds].length=vectorlength(vec);
  
        copyvector(physicstemp.bond[physicstemp.numofbonds].normal,normal);
        physicstemp.bond[physicstemp.numofbonds].cycles=0;
        physicstemp.bond[physicstemp.numofbonds].elasticity=0.2f;
        physicstemp.bond[physicstemp.numofbonds].friction=0.8f;
        physicstemp.bond[physicstemp.numofbonds].objectnum[0]=objectnum;
        physicstemp.bond[physicstemp.numofbonds].objectnum[1]=objectnum;
        physicstemp.bond[physicstemp.numofbonds].force[0]=force[1];
        physicstemp.bond[physicstemp.numofbonds].force[1]=force[0];
        physicstemp.bond[physicstemp.numofbonds].blocknum=0;
        physicstemp.bond[physicstemp.numofbonds].blockx=0;
        physicstemp.bond[physicstemp.numofbonds].blocky=0;
        physicstemp.numofbonds++;
        }
      }

  updateogg();

  for (objectcount=0;objectcount<numofobjects;objectcount++)
  if (objectnum!=objectcount)
  if (objecttype[object[objectnum].type].collide[object[objectcount].type])
  if ((object[objectnum].type!=2 || object[objectnum].timetolive>175) && (object[objectcount].type!=2 || object[objectcount].timetolive>175))
  if (object[objectnum].timetolive>40 && object[objectcount].timetolive>40)
    {
    subtractvectors(vec,object[objectnum].position,object[objectcount].position);

    if (vectorlength(vec)<object[objectnum].radius+object[objectcount].radius)
    for (count=0;count<object[objectnum].numofparticles;count++)
      {
      particlenum=object[objectnum].particle[count];
      //for (count2=0;count2<object[objectcount].numofcdlines;count2++)
      if (pointintersectobject(intersectpoint,normal,&scale,particle[object[objectnum].particle[count]].position,objectcount,objectnum,particlelist))
        {
        //part1=object[objectcount].cdline[count2][0];
        //part2=object[objectcount].cdline[count2][1];
        part1=particlelist[0];
        part2=particlelist[1];

        //if (lineintersectline2(intersectpoint,normal,&scale,object[objectnum].position,particle[object[objectnum].particle[count]].position,particle[object[objectcount].particle[part1]].position,particle[object[objectcount].particle[part2]].position))
          {
          scaleaddvectors(object[objectnum].orientation[1],object[objectnum].orientation[1],normal,0.5f);
          object[objectnum].numoforientations++;

          if (object[objectnum].type==1)
          if (game.levelnum==29)
          if (objectcount==38)
          if (game.godmode==0)
            {
            game.godmode=1;
            playsound(10,object[objectnum].position,NULL,0.4f,0,1.0f,-1,0);
            }

          if (object[objectnum].type==1)
          if (object[objectcount].type==4)
          if (object[objectcount].beasttype==15)
            object[objectnum].hitpoints--;
            
          if (object[objectnum].type==1)
          if (object[objectcount].type==6)
          if (object[objectcount].timetolive>16)
            {
            object[objectcount].timetolive=16;
            if (level.gametype==12)
              {
              if (objectnum==0)
                game.score[0]++;
              if (objectnum==1)
                game.score[1]++;
              }
            }

          //subtractvectors(vec,intersectpoint,particle[particlenum].position);
          //scaleaddvectors(vec2,particle[particlenum].position,normal,dotproduct(vec,normal));
          //copyvector(vec,intersectpoint);

          subtractvectors(vec,particle[object[objectcount].particle[part2]].position,particle[object[objectcount].particle[part1]].position);
          scale=vectorlength(vec);
          subtractvectors(vec,particle[object[objectcount].particle[part1]].position,intersectpoint);
          force[0]=vectorlength(vec)/scale;
          subtractvectors(vec,particle[object[objectcount].particle[part2]].position,intersectpoint);
          force[1]=vectorlength(vec)/scale;
          if (force[0]>1.0f)
            force[0]=1.0f;
          if (force[1]>1.0f)
            force[1]=1.0f;

          friction=object[objectnum].friction;
          if (friction>object[objectcount].friction)
            friction=object[objectcount].friction;

          physicstemp.bond[physicstemp.numofbonds].part1=object[objectcount].particle[part1];
          physicstemp.bond[physicstemp.numofbonds].part2=object[objectcount].particle[part2];
          physicstemp.bond[physicstemp.numofbonds].part3=particlenum;
          physicstemp.bond[physicstemp.numofbonds].type=4;
          subtractvectors(vec,particle[particlenum].position,intersectpoint);
          physicstemp.bond[physicstemp.numofbonds].length=vectorlength(vec);

          copyvector(physicstemp.bond[physicstemp.numofbonds].normal,normal);
          physicstemp.bond[physicstemp.numofbonds].cycles=0;
          if (object[objectnum].type==2 && object[objectcount].type==2)
          if (object[objectnum].size[0]<=0.5f && object[objectcount].size[0]<=0.5f)
            physicstemp.bond[physicstemp.numofbonds].cycles=3;
          physicstemp.bond[physicstemp.numofbonds].elasticity=0.2f;
          physicstemp.bond[physicstemp.numofbonds].friction=friction;
          physicstemp.bond[physicstemp.numofbonds].objectnum[0]=objectnum;
          physicstemp.bond[physicstemp.numofbonds].objectnum[1]=objectcount;
          physicstemp.bond[physicstemp.numofbonds].force[0]=force[1];
          physicstemp.bond[physicstemp.numofbonds].force[1]=force[0];
          physicstemp.bond[physicstemp.numofbonds].blocknum=0;
          physicstemp.bond[physicstemp.numofbonds].blockx=0;
          physicstemp.bond[physicstemp.numofbonds].blocky=0;
          physicstemp.numofbonds++;

          if ((object[objectnum].button&1)==1 && object[objectnum].type==1)
          if (object[objectcount].type!=1 || (object[objectcount].button&4)==0)
            {
            //if (!object[objectnum].particlestick[count])
              {
              if (object[objectnum].particlestick[count])
                {
                for (count2=0;count2<physicstemp.numofbonds;count2++)
                if (physicstemp.bond[count2].type==5)
                if (physicstemp.bond[count2].objectnum[0]==objectnum)
                if (physicstemp.bond[count2].part4==count)
                  physicstemp.bond[count2].type=-1;
                }

              object[objectnum].particlestick[count]=1;

              physicstemp.bond[physicstemp.numofbonds].part1=object[objectcount].particle[part1];
              physicstemp.bond[physicstemp.numofbonds].part2=object[objectcount].particle[part2];
              physicstemp.bond[physicstemp.numofbonds].part3=particlenum;
              physicstemp.bond[physicstemp.numofbonds].part4=count;
              physicstemp.bond[physicstemp.numofbonds].type=5;
              physicstemp.bond[physicstemp.numofbonds].length=vectorlength(vec);
    
              copyvector(physicstemp.bond[physicstemp.numofbonds].normal,normal);
              physicstemp.bond[physicstemp.numofbonds].cycles=0;
              physicstemp.bond[physicstemp.numofbonds].elasticity=0.2f;
              physicstemp.bond[physicstemp.numofbonds].breakpoint=0.3f;
              if (fabs(normal[1])<0.707f)
                physicstemp.bond[physicstemp.numofbonds].breakpoint=0.25f;
              if (object[objectcount].type>=3 && object[objectcount].type<=5)
                physicstemp.bond[physicstemp.numofbonds].breakpoint*=1.5f;
              physicstemp.bond[physicstemp.numofbonds].friction=friction;
              physicstemp.bond[physicstemp.numofbonds].objectnum[0]=objectnum;
              physicstemp.bond[physicstemp.numofbonds].objectnum[1]=objectcount;
              physicstemp.bond[physicstemp.numofbonds].force[0]=force[1];
              physicstemp.bond[physicstemp.numofbonds].force[1]=force[0];
              physicstemp.bond[physicstemp.numofbonds].blocknum=0;
              physicstemp.bond[physicstemp.numofbonds].blockx=0;
              physicstemp.bond[physicstemp.numofbonds].blocky=0;
              physicstemp.numofbonds++;

              if (game.oldschool==2)
              if (object[objectcount].type==3)
              if (game.framenum-game.oldschoolsound>200)
                {
                playsound(22,object[objectnum].position,NULL,1.0f,0,1.0f,objectnum,1);
                game.oldschoolsound=game.framenum;
                }
              }
            }
          }
        }
      }
    }

  if (level.gametype>=10)
  for (objectcount=0;objectcount<numofobjects;objectcount++)
  if (object[objectcount].type==1)
    {
    for (count=0;count<object[objectcount].numofparticles;count++)
      {
      particlenum=object[objectcount].particle[count];
      part1=object[objectcount].particle[((count+4)&15)];
      part2=object[objectcount].particle[((count-4)&15)];

      //for (count2=-6;count2<6;count2++)
        {
        //part1=object[objectcount].particle[((count+8+count2)&15)];
        //part2=object[objectcount].particle[((count+8+count2+1)&15)];

        normal[0]=particle[part2].position[1]-particle[part1].position[1];
        normal[1]=particle[part1].position[0]-particle[part2].position[0];
        normal[2]=0.0f;
        normalizevector(normal,normal);
        scaleaddvectors(vec,particle[particlenum].position,normal,1.0f);
        if (lineintersectline2(intersectpoint,normal,&scale,vec,particle[particlenum].position,particle[part1].position,particle[part2].position))
          {
          subtractvectors(vec,particle[part2].position,particle[part1].position);
          scale=vectorlength(vec);
          if (scale>0.00000001f)
            {
            subtractvectors(vec,particle[part1].position,intersectpoint);
            force[0]=vectorlength(vec)/scale;
            subtractvectors(vec,particle[part2].position,intersectpoint);
            force[1]=vectorlength(vec)/scale;
            }
          else
            {
            force[0]=0.5f;
            force[1]=0.5f;
            }
          if (force[0]>1.0f)
            force[0]=1.0f;
          if (force[1]>1.0f)
            force[1]=1.0f;
  
          physicstemp.bond[physicstemp.numofbonds].part1=part1;
          physicstemp.bond[physicstemp.numofbonds].part2=part2;
          physicstemp.bond[physicstemp.numofbonds].part3=particlenum;
          physicstemp.bond[physicstemp.numofbonds].type=4;
          subtractvectors(vec,particle[particlenum].position,intersectpoint);
          physicstemp.bond[physicstemp.numofbonds].length=vectorlength(vec);
  
          copyvector(physicstemp.bond[physicstemp.numofbonds].normal,normal);
          physicstemp.bond[physicstemp.numofbonds].cycles=0;
          physicstemp.bond[physicstemp.numofbonds].elasticity=0.5f;
          physicstemp.bond[physicstemp.numofbonds].friction=1.0f;
          physicstemp.bond[physicstemp.numofbonds].objectnum[0]=-1;
          physicstemp.bond[physicstemp.numofbonds].objectnum[1]=-1;
          physicstemp.bond[physicstemp.numofbonds].force[0]=force[1];
          physicstemp.bond[physicstemp.numofbonds].force[1]=force[0];
          physicstemp.bond[physicstemp.numofbonds].blocknum=0;
          physicstemp.bond[physicstemp.numofbonds].blockx=0;
          physicstemp.bond[physicstemp.numofbonds].blocky=0;
          physicstemp.numofbonds++;
          }
        }
      }
    }
  }

void bondsimulation2(void)
  {
  int count,count2;
  int part1,part2,part3;
  int blocknum;
  unsigned int x;
  float vec[3],vec2[3],vec3[3];
  float bondnormal[3];
  float veclength;
  float force[2];
  float temp;
  float scale;

  for (count2=0;count2<physicstemp.numofbonds;count2++)
    {
    zerovector(physicstemp.bond[count2].forceapplied[0]);
    zerovector(physicstemp.bond[count2].forceapplied[1]);
    }

  for (count2=0;count2<numofbonds;count2++)
    {
    part1=bond[count2].part1;
    part2=bond[count2].part2;
    subtractvectors(bond[count2].bondnormal,particle[part2].position,particle[part1].position);
    bond[count2].veclength=vectorlength(bond[count2].bondnormal);
    normalizevector(bond[count2].bondnormal,bond[count2].bondnormal);
    bond[count2].oomass=1.0f/(particle[part1].mass+particle[part2].mass);
    }

  for (count=0;count<32;count++)
    {
    //starttimer(0);

    updateogg();

    for (count2=0;count2<numofparticles;count2++)
      copyvector(particle[count2].prevvelocity,particle[count2].velocity);

    for (count2=0;count2<numofbonds;count2++)
    if ((count&bond[count2].cycles)==0)
      {
      part1=bond[count2].part1;
      part2=bond[count2].part2;

      temp=bond[count2].veclength;
      veclength=temp-bond[count2].length;
      copyvector(bondnormal,bond[count2].bondnormal);

      zerovector(vec);
      scaleaddvectors2(vec,vec,particle[part2].prevvelocity,1.0f);
      scaleaddvectors2(vec,vec,particle[part1].prevvelocity,-1.0f);

      veclength+=dotproduct(vec,bondnormal);

      if (bondtype[bond[count2].type].compression==0.0f)
        if (veclength<0.0f)
          veclength=0.0f;

      veclength*=bond[count2].elasticity;
      //if (bond[count2].type==2 && temp<bond[count2].length*0.35f)
      //  veclength*=10.0f;
      if (bond[count2].type==2 && temp<bond[count2].length*0.25f)
        bond[count2].cycles=0;

      veclength*=bond[count2].oomass;

      force[0]=veclength*particle[part2].mass;
      force[1]=veclength*particle[part1].mass;

      scaleaddvectors2(particle[part1].velocity,particle[part1].velocity,bondnormal,force[0]);
      scaleaddvectors2(particle[part2].velocity,particle[part2].velocity,bondnormal,-force[1]);
      }
    //stoptimer(0);

    //starttimer(1);

    for (count2=0;count2<physicstemp.numofbonds;count2++)
    if ((count&physicstemp.bond[count2].cycles)==0)
      {
      if (physicstemp.bond[count2].type==0)
        {
        part1=physicstemp.bond[count2].part1;
    
        subtractvectors2(bondnormal,physicstemp.bond[count2].point,particle[part1].position);
        scalevector2(vec,bondnormal,0.2f);
        veclength=(vectorlength(bondnormal)-physicstemp.bond[count2].length);
        scaleaddvectors2(vec,vec,particle[part1].prevvelocity,-1.0f);
  
        if (dotproduct(vec,physicstemp.bond[count2].normal)>0.0f)
          {
          scalevector2(vec,vec,physicstemp.bond[count2].elasticity);
          calculatefriction(vec,vec2,physicstemp.bond[count2].normal,physicstemp.bond[count2].friction);
          addvectors2(vec,vec,vec2);
          addvectors2(particle[part1].velocity,particle[part1].velocity,vec);

          if (particle[part1].type!=5)
            {
            addvectors2(physicstemp.bond[count2].forceapplied[0],physicstemp.bond[count2].forceapplied[0],vec);
            if (block[physicstemp.bond[count2].blocknum].breakpoint!=0.0f)
              {
              level.gridforce[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]+=vectorlength(vec)*particle[part1].mass;
              if (level.gridforce[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]>block[physicstemp.bond[count2].blocknum].breakpoint)
                physicstemp.bond[count2].type=-1;
              }
            }
          }
        }
      if (physicstemp.bond[count2].type==1)
        {
        part1=physicstemp.bond[count2].part1;
    
        subtractvectors2(bondnormal,physicstemp.bond[count2].point,particle[part1].position);
        scalevector2(vec,bondnormal,1.0f);
        veclength=(vectorlength(bondnormal)-physicstemp.bond[count2].length);
        scaleaddvectors2(vec,vec,particle[part1].prevvelocity,-1.0f);

        veclength=(vectorlength(bondnormal)-physicstemp.bond[count2].length)-dotproduct(bondnormal,particle[part1].prevvelocity)/vectorlength(bondnormal);

        scalevector2(vec,vec,physicstemp.bond[count2].elasticity);
        scalevector2(vec,vec,0.04f);
        addvectors2(particle[part1].velocity,particle[part1].velocity,vec);
        addvectors2(physicstemp.bond[count2].forceapplied[0],physicstemp.bond[count2].forceapplied[0],vec);
        if (block[physicstemp.bond[count2].blocknum].breakpoint!=0.0f)
          {
          level.gridforce[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]+=vectorlength(vec)*particle[part1].mass;
          if (level.gridforce[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]>block[physicstemp.bond[count2].blocknum].breakpoint || level.gridmod[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]!=0)
            {
            physicstemp.bond[count2].type=-1;
            object[physicstemp.bond[count2].objectnum[0]].particlestick[physicstemp.bond[count2].part4]=0;
            }
          }
        }
      if (physicstemp.bond[count2].type==2)
        {
        part1=physicstemp.bond[count2].part1;
        part2=physicstemp.bond[count2].part2;
    
        scalevector2(bondnormal,physicstemp.bond[count2].normal,-physicstemp.bond[count2].length*0.2f);
        scaleaddvectors2(bondnormal,bondnormal,particle[part2].prevvelocity,-physicstemp.bond[count2].force[1]);
        scaleaddvectors2(bondnormal,bondnormal,particle[part1].prevvelocity,-physicstemp.bond[count2].force[0]);
        copyvector(vec,bondnormal);
  
        if (dotproduct(vec,physicstemp.bond[count2].normal)<0.0f)
          {
          scalevector2(vec,vec,physicstemp.bond[count2].elasticity);
          calculatefriction(vec,vec2,physicstemp.bond[count2].normal,physicstemp.bond[count2].friction);
          addvectors2(vec,vec,vec2);
          scaleaddvectors2(particle[part1].velocity,particle[part1].velocity,vec,physicstemp.bond[count2].force[0]);
          scaleaddvectors2(particle[part2].velocity,particle[part2].velocity,vec,physicstemp.bond[count2].force[1]);
          addvectors2(physicstemp.bond[count2].forceapplied[0],physicstemp.bond[count2].forceapplied[0],vec);
          if (block[physicstemp.bond[count2].blocknum].breakpoint!=0.0f)
            {
            level.gridforce[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]+=vectorlength(vec)*particle[part1].mass;
            if (level.gridforce[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]>block[physicstemp.bond[count2].blocknum].breakpoint)
              physicstemp.bond[count2].type=-1;
            }
          }
        }
      if (physicstemp.bond[count2].type==4)
        {
        part1=physicstemp.bond[count2].part1;
        part2=physicstemp.bond[count2].part2;
        part3=physicstemp.bond[count2].part3;
    
        scalevector2(bondnormal,physicstemp.bond[count2].normal,-physicstemp.bond[count2].length*0.2f);
  
        scaleaddvectors2(bondnormal,bondnormal,particle[part3].prevvelocity,1.0f);
        scaleaddvectors2(bondnormal,bondnormal,particle[part2].prevvelocity,-physicstemp.bond[count2].force[1]);
        scaleaddvectors2(bondnormal,bondnormal,particle[part1].prevvelocity,-physicstemp.bond[count2].force[0]);
  
        veclength=physicstemp.bond[count2].elasticity/(particle[part1].mass*physicstemp.bond[count2].force[0]+particle[part2].mass*physicstemp.bond[count2].force[1]+particle[part3].mass);
  
        force[0]=veclength*particle[part3].mass;
        force[1]=veclength*(particle[part1].mass*physicstemp.bond[count2].force[0]+particle[part2].mass*physicstemp.bond[count2].force[1]);
  
        if (dotproduct(bondnormal,physicstemp.bond[count2].normal)*force[0]<0.0f)
          {
          scalevector2(vec,bondnormal,force[0]);
  
          calculatefriction(vec,vec2,physicstemp.bond[count2].normal,physicstemp.bond[count2].friction);
          addvectors2(vec,vec,vec2);
  
          scaleaddvectors2(particle[part1].velocity,particle[part1].velocity,vec,physicstemp.bond[count2].force[0]);
          scaleaddvectors2(particle[part2].velocity,particle[part2].velocity,vec,physicstemp.bond[count2].force[1]);
          addvectors2(physicstemp.bond[count2].forceapplied[0],physicstemp.bond[count2].forceapplied[0],vec);
  
          scalevector2(vec,bondnormal,-force[1]);
  
          calculatefriction(vec,vec2,physicstemp.bond[count2].normal,physicstemp.bond[count2].friction);
          addvectors2(vec,vec,vec2);
  
          addvectors2(particle[part3].velocity,particle[part3].velocity,vec);
          addvectors2(physicstemp.bond[count2].forceapplied[1],physicstemp.bond[count2].forceapplied[1],vec);
          }
        }
      if (physicstemp.bond[count2].type==5)
        {
        part1=physicstemp.bond[count2].part1;
        part2=physicstemp.bond[count2].part2;
        part3=physicstemp.bond[count2].part3;
    
        //scalevector(bondnormal,physicstemp.bond[count2].normal,-physicstemp.bond[count2].length*0.2f);
        scalevector2(vec,particle[part1].position,physicstemp.bond[count2].force[0]);
        scaleaddvectors2(vec,vec,particle[part2].position,physicstemp.bond[count2].force[1]);
        subtractvectors2(bondnormal,particle[part3].position,vec);

  
        scaleaddvectors2(bondnormal,bondnormal,particle[part3].prevvelocity,1.0f);
        scaleaddvectors2(bondnormal,bondnormal,particle[part2].prevvelocity,-physicstemp.bond[count2].force[1]*1.0f);
        scaleaddvectors2(bondnormal,bondnormal,particle[part1].prevvelocity,-physicstemp.bond[count2].force[0]*1.0f);

        veclength=physicstemp.bond[count2].elasticity/(particle[part1].mass*physicstemp.bond[count2].force[0]+particle[part2].mass*physicstemp.bond[count2].force[1]+particle[part3].mass);
        veclength*=0.2f;
        veclength*=0.2f;
  
        force[0]=veclength*particle[part3].mass;
        force[1]=veclength*(particle[part1].mass*physicstemp.bond[count2].force[0]+particle[part2].mass*physicstemp.bond[count2].force[1]);
  
        scalevector2(vec,bondnormal,force[0]);

        scaleaddvectors2(particle[part1].velocity,particle[part1].velocity,vec,physicstemp.bond[count2].force[0]);
        scaleaddvectors2(particle[part2].velocity,particle[part2].velocity,vec,physicstemp.bond[count2].force[1]);
        addvectors2(physicstemp.bond[count2].forceapplied[0],physicstemp.bond[count2].forceapplied[0],vec);

        scalevector2(vec,bondnormal,-force[1]);

        addvectors2(particle[part3].velocity,particle[part3].velocity,vec);
        addvectors2(physicstemp.bond[count2].forceapplied[1],physicstemp.bond[count2].forceapplied[1],vec);
        }
      }
    //stoptimer(1);
    }

  for (count2=0;count2<physicstemp.numofbonds;count2++)
    {
    if (physicstemp.bond[count2].type==0)
    if (physicstemp.bond[count2].objectnum[0]!=-1)
      {
      force[0]=dotproduct(physicstemp.bond[count2].forceapplied[0],physicstemp.bond[count2].normal);
      force[1]=vectorlength(physicstemp.bond[count2].forceapplied[0]);
      scale=sqrt(force[1]*force[1]-force[0]*force[0]);

      object[physicstemp.bond[count2].objectnum[0]].frictionapplied+=scale;
      }
    }

  for (count2=0;count2<physicstemp.numofbonds;count2++)
  if (particle[physicstemp.bond[count2].part1].type!=5)
    {
    if (physicstemp.bond[count2].type==1)
      {
      part1=physicstemp.bond[count2].part1;
  
      subtractvectors(bondnormal,physicstemp.bond[count2].point,particle[part1].position);
      scalevector(vec,bondnormal,1.0f);
      veclength=(vectorlength(bondnormal)-physicstemp.bond[count2].length);
      scaleaddvectors(vec,vec,particle[part1].prevvelocity,-1.0f);

      veclength=(vectorlength(bondnormal)-physicstemp.bond[count2].length)-dotproduct(bondnormal,particle[part1].prevvelocity)/vectorlength(bondnormal);
      if (fabs(veclength)>physicstemp.bond[count2].breakpoint || (object[physicstemp.bond[count2].objectnum[0]].button&1)==0)
        {
        physicstemp.bond[count2].type=-1;
        object[physicstemp.bond[count2].objectnum[0]].particlestick[physicstemp.bond[count2].part4]=0;
        }
      }
    if (physicstemp.bond[count2].type==5)
      {
      part1=physicstemp.bond[count2].part1;
      part2=physicstemp.bond[count2].part2;
      part3=physicstemp.bond[count2].part3;
  
      scalevector(vec,particle[part1].position,physicstemp.bond[count2].force[0]);
      scaleaddvectors(vec,vec,particle[part2].position,physicstemp.bond[count2].force[1]);

      copyvector(object[physicstemp.bond[count2].objectnum[0]].particlestickposition[physicstemp.bond[count2].part4],vec);

      subtractvectors(bondnormal,particle[part3].position,vec);

      subtractvectors(vec,particle[part2].position,particle[part1].position);
      vec2[0]=-vec[1];
      vec2[1]=vec[0];
      vec2[2]=0.0f;
      normalizevector(object[physicstemp.bond[count2].objectnum[0]].particlesticknormal[physicstemp.bond[count2].part4],vec2);

      scaleaddvectors(bondnormal,bondnormal,particle[part3].prevvelocity,1.0f);
      scaleaddvectors(bondnormal,bondnormal,particle[part2].prevvelocity,-physicstemp.bond[count2].force[1]*1.0f);
      scaleaddvectors(bondnormal,bondnormal,particle[part1].prevvelocity,-physicstemp.bond[count2].force[0]*1.0f);

      veclength=vectorlength(bondnormal);
      if (fabs(veclength)>physicstemp.bond[count2].breakpoint || (object[physicstemp.bond[count2].objectnum[0]].button&1)==0 || (object[physicstemp.bond[count2].objectnum[0]].button&4)==4 || (object[physicstemp.bond[count2].objectnum[1]].button&4)==4)
        {
        physicstemp.bond[count2].type=-1;
        object[physicstemp.bond[count2].objectnum[0]].particlestick[physicstemp.bond[count2].part4]=0;
        }
      }

    blocknum=physicstemp.bond[count2].blocknum;
    if (block[blocknum].breakpoint!=0.0f)
      {
      if (level.gridforce[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]>block[blocknum].breakpoint)
        {
        level.gridmod[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]=1;
        if (blocknum>=240 && blocknum<248)
          level.gridmod[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]=2;
        setuplevellines(physicstemp.bond[count2].blockx-1,physicstemp.bond[count2].blocky-1,physicstemp.bond[count2].blockx+1,physicstemp.bond[count2].blocky+1);

        vec[0]=(float)physicstemp.bond[count2].blockx+0.5f;
        vec[1]=(float)physicstemp.bond[count2].blocky+0.5f;
        vec[2]=0.0f;
        playsound(0,vec,NULL,0.75f,0,0.5f/block[blocknum].breakpoint,-1,0);

        if (level.gametype==0)
          {
          game.score[0]+=10;
          createsprite(10,vec);
          }
        /*
        vec[0]=(float)physicstemp.bond[count2].blockx+0.5f;
        vec[1]=(float)physicstemp.bond[count2].blocky+0.5f;
        vec[2]=0.0f;
        createbox(vec,0.99f,0.99f,block[blocknum].breakpoint*4.0f,block[blocknum].friction);
        object[numofobjects-1].timetolive=200+(rand()&63);
        object[numofobjects-1].texturenum=blocknum-256;
        object[numofobjects-1].texcoord[0][0]=0.0f;
        object[numofobjects-1].texcoord[0][1]=0.0f;
        object[numofobjects-1].texcoord[1][0]=1.0f;
        object[numofobjects-1].texcoord[1][1]=0.0f;
        object[numofobjects-1].texcoord[2][0]=1.0f;
        object[numofobjects-1].texcoord[2][1]=1.0f;
        object[numofobjects-1].texcoord[3][0]=0.0f;
        object[numofobjects-1].texcoord[3][1]=1.0f;
        */
        if (numofobjects<500)
          {
          vec[0]=(float)physicstemp.bond[count2].blockx+0.25f;
          vec[1]=(float)physicstemp.bond[count2].blocky+0.75f;
          vec[2]=0.0f;
          createbox(vec,0.49f,0.49f,block[blocknum].breakpoint,block[blocknum].friction);
          object[numofobjects-1].timetolive=200;
          object[numofobjects-1].texturenum=blocknum-256;
          object[numofobjects-1].texcoord[0][0]=0.0f;
          object[numofobjects-1].texcoord[0][1]=0.0f;
          object[numofobjects-1].texcoord[1][0]=0.5f;
          object[numofobjects-1].texcoord[1][1]=0.0f;
          object[numofobjects-1].texcoord[2][0]=0.5f;
          object[numofobjects-1].texcoord[2][1]=0.5f;
          object[numofobjects-1].texcoord[3][0]=0.0f;
          object[numofobjects-1].texcoord[3][1]=0.5f;
  
          vec[0]=(float)physicstemp.bond[count2].blockx+0.75f;
          vec[1]=(float)physicstemp.bond[count2].blocky+0.75f;
          vec[2]=0.0f;
          createbox(vec,0.49f,0.49f,block[blocknum].breakpoint,block[blocknum].friction);
          object[numofobjects-1].timetolive=200;
          object[numofobjects-1].texturenum=blocknum-256;
          object[numofobjects-1].texcoord[0][0]=0.0f+0.5f;
          object[numofobjects-1].texcoord[0][1]=0.0f;
          object[numofobjects-1].texcoord[1][0]=0.5f+0.5f;
          object[numofobjects-1].texcoord[1][1]=0.0f;
          object[numofobjects-1].texcoord[2][0]=0.5f+0.5f;
          object[numofobjects-1].texcoord[2][1]=0.5f;
          object[numofobjects-1].texcoord[3][0]=0.0f+0.5f;
          object[numofobjects-1].texcoord[3][1]=0.5f;
  
          vec[0]=(float)physicstemp.bond[count2].blockx+0.75f;
          vec[1]=(float)physicstemp.bond[count2].blocky+0.25f;
          vec[2]=0.0f;
          createbox(vec,0.49f,0.49f,block[blocknum].breakpoint,block[blocknum].friction);
          object[numofobjects-1].timetolive=200;
          object[numofobjects-1].texturenum=blocknum-256;
          object[numofobjects-1].texcoord[0][0]=0.0f+0.5f;
          object[numofobjects-1].texcoord[0][1]=0.0f+0.5f;
          object[numofobjects-1].texcoord[1][0]=0.5f+0.5f;
          object[numofobjects-1].texcoord[1][1]=0.0f+0.5f;
          object[numofobjects-1].texcoord[2][0]=0.5f+0.5f;
          object[numofobjects-1].texcoord[2][1]=0.5f+0.5f;
          object[numofobjects-1].texcoord[3][0]=0.0f+0.5f;
          object[numofobjects-1].texcoord[3][1]=0.5f+0.5f;
  
          vec[0]=(float)physicstemp.bond[count2].blockx+0.25f;
          vec[1]=(float)physicstemp.bond[count2].blocky+0.25f;
          vec[2]=0.0f;
          createbox(vec,0.49f,0.49f,block[blocknum].breakpoint,block[blocknum].friction);
          object[numofobjects-1].timetolive=200;
          object[numofobjects-1].texturenum=blocknum-256;
          object[numofobjects-1].texcoord[0][0]=0.0f;
          object[numofobjects-1].texcoord[0][1]=0.0f+0.5f;
          object[numofobjects-1].texcoord[1][0]=0.5f;
          object[numofobjects-1].texcoord[1][1]=0.0f+0.5f;
          object[numofobjects-1].texcoord[2][0]=0.5f;
          object[numofobjects-1].texcoord[2][1]=0.5f+0.5f;
          object[numofobjects-1].texcoord[3][0]=0.0f;
          object[numofobjects-1].texcoord[3][1]=0.5f+0.5f;
          }
        }
      level.gridforce[physicstemp.bond[count2].blocky][physicstemp.bond[count2].blockx]=0.0f;
      }
    }

  count2=0;
  while (count2<physicstemp.numofbonds)
    {
    while (count2<physicstemp.numofbonds && physicstemp.bond[count2].type!=1 && physicstemp.bond[count2].type!=5)
      {
      physicstemp.numofbonds--;
      memcpy(&physicstemp.bond[count2],&physicstemp.bond[physicstemp.numofbonds],sizeof(physicstemp.bond[0]));
      }
    count2++;
    }
  }

int lineintersectline2(float *intersectpoint,float *normal,float *scale,float *startpoint,float *endpoint,float *vertex1,float *vertex2)
  {
  float vec[3],vec2[3];
  float dot1,dot2;

  normal[0]=vertex1[1]-vertex2[1];
  normal[1]=vertex2[0]-vertex1[0];
  normal[2]=0.0f;

  vec[0]=startpoint[0]-vertex1[0];
  vec[1]=startpoint[1]-vertex1[1];
  vec[2]=0.0f;

  vec2[0]=endpoint[0]-vertex1[0];
  vec2[1]=endpoint[1]-vertex1[1];
  vec2[2]=0.0f;

  dot1=dotproduct(normal,vec);
  dot2=dotproduct(normal,vec2);
  if (dot1>0.0f)
  if (dot2>0.0f)
    return(0);

  if (dot1<0.0f)
    return(0);

  normalizevector(normal,normal);

  vec[0]=vertex1[0]-startpoint[0];
  vec[1]=vertex1[1]-startpoint[1];
  vec[2]=0.0f;
  *scale=dotproduct(vec,normal);
  vec[0]=endpoint[0]-startpoint[0];
  vec[1]=endpoint[1]-startpoint[1];
  vec[2]=0.0f;
  *scale/=dotproduct(vec,normal);

  scaleaddvectors(intersectpoint,startpoint,vec,*scale);

  vec[0]=intersectpoint[0]-vertex1[0];
  vec[1]=intersectpoint[1]-vertex1[1];
  vec[2]=0.0f;

  vec2[0]=vertex2[0]-vertex1[0];
  vec2[1]=vertex2[1]-vertex1[1];
  vec2[2]=0.0f;

  if (dotproduct(vec,vec2)<0.0f)
    return(0);

  vec[0]=intersectpoint[0]-vertex2[0];
  vec[1]=intersectpoint[1]-vertex2[1];
  vec[2]=0.0f;

  vec2[0]=vertex1[0]-vertex2[0];
  vec2[1]=vertex1[1]-vertex2[1];
  vec2[2]=0.0f;

  if (dotproduct(vec,vec2)<0.0f)
    return(0);

  return(1);
  }

