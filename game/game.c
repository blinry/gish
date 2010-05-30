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

void gameloop(void)
  {
  int count,count2;
  int simtimer;
  int simcount;
  int frametimer,fps;
  float vec[3];
  char filename[13]="text000.tga";
  int scorenum;
  unsigned int x;

  game.godparticle=-1;

  game.oldschool=0;
  if (game.levelnum==64)
    game.oldschool=1;
  if (game.levelnum==65)
    {
    game.oldschool=2;
    game.oldschoolsound=-200;
    }
  if (game.levelnum==66)
    game.oldschool=3;

  srand(time(NULL));

  setuplevel();
  setupgame();

  simtimer=SDL_GetTicks();

  game.exit=0;

  scorenum=-1;

  resetmenuitems();

  while ((game.exit<2 || game.exitdelay>0) && !windowinfo.shutdown)
    {
    frametimer=SDL_GetTicks();

    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glStencilMask(~0);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_FALSE);
    glStencilMask(0);

    setuptextdisplay();
    glColor3fv(level.ambient[3]);
    if (level.background[0]!=0)
      displaybackground(660);

    if (game.over!=0 && level.gametype<10)
    if (game.exit==0)
      {
      if (game.over>=3 && game.over<=5)
        {
        game.exit=5;
        game.exitdelay=100;
        }
      if (game.over==2)
        {
        game.exit=4;
        game.exitdelay=100;
        }
      if (game.over==1)
        {
        game.exit=3;
        game.exitdelay=100;
        if (game.levelnum==65)
          game.exitdelay=200;
        }
      }

    numofmenuitems=0;
    if (game.exit==0)
      {
      createmenuitem("",0,0,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_ESC);
      setmenuitem(MO_SET,&game.exit,1);
      }
    if (game.exit==1)
      {
      count=240;

      if (game.over==0)
        {
        createmenuitem(TXT_RETURN_TO_GAME,(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_HOTKEY,SCAN_ESC);
        setmenuitem(MO_SET,&game.exit,0);
        }
      else
        createmenuitemempty();
      count+=16;

      if (game.levelnum<64)
        {
        if (level.gametype==0 && (game.levelnum>0 || mappack.active) && !game.playreplay)
          createmenuitem(TXT_RESETLEVEL_MINUSONE,(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
        else
          createmenuitem(TXT_RESETLEVEL,(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_HOTKEY,SCAN_R);
        if (level.gametype==0)
          setmenuitem(MO_SET,&game.exit,3);
        count+=16;
        }
      else
        createmenuitemempty();

      if (game.over==0 && game.levelnum<64 && level.gametype==0 && game.levelnum>0 && !game.playreplay)
        createmenuitem(TXT_EXITGAME_MINUSONE,(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
      else
        createmenuitem(TXT_EXITGAME,(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_E);
      setmenuitem(MO_SET,&game.exit,2);
      count+=16;
      }
    if (game.exit==3)
      {
      if (game.time>0)
        {
        createmenuitem("       ",(320|TEXT_CENTER),(240|TEXT_CENTER),20,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_SET,&game.exitdelay,0);
        }
      else
        {
        createmenuitem(TXT_TIMEUP,(320|TEXT_CENTER),(240|TEXT_CENTER),20,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_SET,&game.exitdelay,0);
        }
      }
    if (game.exit==4)
      {
      createmenuitem(TXT_COMPLETE,524|TEXT_CENTER,266,20,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_IMAGE,462);
      setmenuitem(MO_RESIZE,(320|TEXT_CENTER),(240|TEXT_CENTER),256,128);
      setmenuitem(MO_SET,&game.exitdelay,0);
      }
    if (game.exit==5)
      {
      if (game.levelnum!=34)
        {
        createmenuitem(TXT_WARPZONE,(320|TEXT_CENTER),(240|TEXT_CENTER),24,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_SET,&game.exitdelay,0);
        }
      else
        {
        //createmenuitem("OOPS!",(320|TEXT_CENTER),(240|TEXT_CENTER),24,1.0f,1.0f,1.0f,1.0f);
        //setmenuitem(MO_SET,&game.exitdelay,0);
        createmenuitem(TXT_OOPS,(320|TEXT_CENTER),(240|TEXT_CENTER),24,1.0f,1.0f,1.0f,1.0f);
        setmenuitem(MO_IMAGE,465);
        setmenuitem(MO_RESIZE,(320|TEXT_CENTER),(240|TEXT_CENTER),256,128);
        setmenuitem(MO_SET,&game.exitdelay,0);
        }
      }

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    if (game.exit==1)
    if (level.gametype!=0)
    if (menuitem[1].active)
      {
      setuplevel();
      setupgame();

      game.exit=0;
      menuitem[1].active=0;
      }

    if (game.dialog>0)
      {
      if (game.levelnum!=68 || (game.dialog!=13 && game.dialog!=14))
        {
        if (game.dialogdelay>0)
          game.dialogdelay--;
  
        count2=0;
        if (game.dialogdelay==0)
          count2=1;
        for (count=4;count<8;count++)
        if (keyboard[control[0].key[count]] && !prevkeyboard[control[0].key[count]])
          count2=1;
        if (control[0].joysticknum!=-1)
        for (count=4;count<8;count++)
        if (control[0].button[count]!=-1)
        if (joystick[control[0].joysticknum].button[control[0].button[count]] && !prevjoystick[control[0].joysticknum].button[control[0].button[count]])
          count2=1;
  
        if (count2==1)
          {
          game.dialog--;
          game.dialogdelay=1000;

          if (game.levelnum==68)
          if (game.dialog==4)
            {
            game.numoflives=99;
            game.exit=4;
            game.exitdelay=0;
            }
          }
        }
      else
        {
        count2=0;
        if (keyboard[control[0].key[2]] && !prevkeyboard[control[0].key[2]])
          count2=1;
        if (keyboard[control[0].key[3]] && !prevkeyboard[control[0].key[3]])
          count2=1;
        if (control[0].joysticknum!=-1)
          {
          if (joystick[control[0].joysticknum].axis[1]>=0.5f && prevjoystick[control[0].joysticknum].axis[1]<0.5f)
            count2=1;
          if (joystick[control[0].joysticknum].axis[1]<=-0.5f && prevjoystick[control[0].joysticknum].axis[1]>-0.5f)
            count2=1;
          }
        if (count2==1)
          {
          if (game.dialog==14)
            game.dialog=13;
          else
            game.dialog=14;
          }

        count2=0;
        for (count=4;count<8;count++)
        if (keyboard[control[0].key[count]] && !prevkeyboard[control[0].key[count]])
          count2=1;
        if (control[0].joysticknum!=-1)
        for (count=4;count<8;count++)
        if (control[0].button[count]!=-1)
        if (joystick[control[0].joysticknum].button[control[0].button[count]] && !prevjoystick[control[0].joysticknum].button[control[0].button[count]])
          count2=1;

        if (count2==1)
          {
          if (game.dialog==14)
            game.dialog=12;
          else
            game.dialog=1;
          }
        }
      }
    checkmusic();

    if (game.levelnum>=1 && game.levelnum<=7)
      game.songnum=0;
    if (game.levelnum>=8 && game.levelnum<=14)
      game.songnum=1;
    if (game.levelnum>=15 && game.levelnum<=21)
      game.songnum=2;
    if (game.levelnum>=22 && game.levelnum<=28)
      game.songnum=3;
    if (game.levelnum>=29 && game.levelnum<=32)
      game.songnum=4;
    if (game.bosslevel)
      game.songnum=5;
    if (game.levelnum==64)
      game.songnum=6;
    if (game.levelnum==67)
      game.songnum=2;

    if (game.levelnum==0)
      {
      if (game.songnum==-1)
        game.songnum=rand()%5;
      }
    if (level.gametype==11)
      game.songnum=7;
    /*
    if (level.gametype==10)
      game.songnum=4;
    if (level.gametype==11)
      game.songnum=5;
    if (level.gametype==12)
      game.songnum=4;
    */
#ifdef TESTIT
    if (keyboard[SCAN_M] && !prevkeyboard[SCAN_M])
      {
      game.songnum++;
      if (game.songnum>3)
        game.songnum=0;
      }
    if (keyboard[SCAN_N] && !prevkeyboard[SCAN_N])
      game.songnum=-1;
    if (keyboard[SCAN_T] && !prevkeyboard[SCAN_T])
      game.turbomode^=1;
#endif
    if (game.levelnum==0)
    if (keyboard[SCAN_F5] && !prevkeyboard[SCAN_F5])
      {
      setuplevel();
      setupgame();
      }
    if (keyboard[SCAN_P] && !prevkeyboard[SCAN_P] && game.exit==0)
      game.pause^=1;
    //if (keyboard[SCAN_R] && !prevkeyboard[SCAN_R])
    //  movie.record^=1;

    view.zoom=10.0f;
#ifdef TESTIT
    if (keyboard[SCAN_EQUALS])
      view.zoom=20.0f;
    if (keyboard[SCAN_MINUS])
      view.zoom=5.0f;
#endif
    if (game.oldschool==2)
      view.zoom=16.0f;
    if (game.oldschool==3)
      view.zoom=26.0f;

    if (level.gametype==15)
      view.zoom=24.0f;
    if (level.gametype==16)
      view.zoom=24.0f;
    if (level.gametype==17 || level.gametype==18)
      view.zoom=14.0f;

    view.zoomx=view.zoom+0.5f;
    view.zoomy=view.zoom*0.75f+0.5f;
    //view.zoomy=view.zoom*0.5625f+0.5f;

    setuporthoviewport(0,0,640,480,view.zoom,view.zoom*0.75f,20.0f);
    //setuporthoviewport(0,0,640,480,view.zoom,view.zoom*0.5625f,20.0f);
    setupviewpoint(view.position,view.orientation);

    if (game.oldschool==1)// || game.oldschool==3)
      glViewport(0,0,256,256);
    if (game.oldschool==2)
      glViewport(0,0,128,128);

    soundsimulation(view.position,view.orientation);

    setupframelighting();

    setuprenderobjects();

    /*
    resettimer(4);
    resettimer(5);
    resettimer(6);
    resettimer(7);
    */

    //starttimer(4);

    rendershadows();

    //stoptimer(4);

    //starttimer(5);

    renderlevelback();

    //stoptimer(5);

    //starttimer(6);

    renderparticles();

    //if (!keyboard[SCAN_B])
    renderobjects();

    renderparticles2();

    //stoptimer(6);

    //starttimer(7);

    renderlevel();
#ifdef TESTIT
    if (keyboard[SCAN_B])
      renderbonds();
#endif
    renderlevelfore();

    //stoptimer(7);

    if (game.oldschool==1)// || game.oldschool==3)
      {
      glBindTexture(GL_TEXTURE_2D,texture[334].glname);
      glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,0,0,256,256,0);
      }
    if (game.oldschool==2)
      {
      glBindTexture(GL_TEXTURE_2D,texture[333].glname);
      glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,0,0,128,128,0);
      }

    if (game.oldschool==1 || game.oldschool==2)// || game.oldschool==3)
      {
      setuptextdisplay();
  
      if (game.oldschool==1)// || game.oldschool==3)
        glBindTexture(GL_TEXTURE_2D,texture[334].glname);
      if (game.oldschool==2)
        glBindTexture(GL_TEXTURE_2D,texture[333].glname);
  
      glBegin(GL_QUADS);
    
      glColor4f(1.0f,1.0f,1.0f,1.0f);
    
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(-1.0f,0.75f,-1.0f);
    
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(1.0f,0.75f,-1.0f);
    
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(1.0f,-0.75f,-1.0f);
    
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(-1.0f,-0.75f,-1.0f);
    
      glEnd();
      }

    setuptextdisplay();

    if (game.exit==4 || game.exit==5)
      {
      glDisable(GL_TEXTURE_2D);

      glBegin(GL_QUADS);
    
      glColor4f(0.0f,0.0f,0.0f,(float)(100-game.exitdelay)*0.01f);
    
      glVertex3f(-1.0f,0.75f,-1.0f);
      glVertex3f(1.0f,0.75f,-1.0f);
      glVertex3f(1.0f,-0.75f,-1.0f);
      glVertex3f(-1.0f,-0.75f,-1.0f);
    
      glEnd();

      glEnable(GL_TEXTURE_2D);
      }
    if (game.exit==3)
      {
      glDisable(GL_TEXTURE_2D);

      glBegin(GL_QUADS);

      if (game.exitdelay>50)
        glColor4f(0.5f,0.0f,0.0f,(float)(100-game.exitdelay)*0.01f);
      else
        glColor4f(1.0f-(float)(100-game.exitdelay)*0.01f,0.0f,0.0f,(float)(100-game.exitdelay)*0.01f);
    
      glVertex3f(-1.0f,0.75f,-1.0f);
      glVertex3f(1.0f,0.75f,-1.0f);
      glVertex3f(1.0f,-0.75f,-1.0f);
      glVertex3f(-1.0f,-0.75f,-1.0f);
    
      glEnd();

      glEnable(GL_TEXTURE_2D);
      }

    if (game.oldschool==0 && !game.bosslevel && level.gametype!=15)
      rendersprites();

    glColor4f(1.0f,1.0f,1.0f,1.0f);

    drawbackground(640,0,0,256,256,640,480);
    drawbackground(641,256,0,256,256,640,480);
    drawbackground(642,512,0,256,256,640,480);
    drawbackground(643,0,256,256,256,640,480);
    drawbackground(644,256,256,256,256,640,480);
    drawbackground(645,512,256,256,256,640,480);

    //if (game.turbomode)
    //  drawbackground(529,28,64,64,32,640,480);

    gamedisplay();

    drawmenuitems();

    if (game.exit==3 || game.exit==4 || game.exit==5)
    if (game.exitdelay<20)
      {
      glDisable(GL_TEXTURE_2D);

      glBegin(GL_QUADS);
    
      glColor4f(0.0f,0.0f,0.0f,(float)(20-game.exitdelay)*0.05f);
    
      glVertex3f(-1.0f,0.75f,-1.0f);
      glVertex3f(1.0f,0.75f,-1.0f);
      glVertex3f(1.0f,-0.75f,-1.0f);
      glVertex3f(-1.0f,-0.75f,-1.0f);
    
      glEnd();

      glEnable(GL_TEXTURE_2D);
      }
    if (movie.record)
      {
      if (movie.framenum<game.framenum/2)
        recordframe();
      drawtext("RECORD",0,64,16,1.0f,0.0f,0.0f,1.0f);
      }
#ifdef TESTIT
    /*
    fuckedup[0]=timer[0].totaltime;
    fuckedup[1]=timer[1].totaltime;
    fuckedup[2]=timer[2].totaltime;
    fuckedup[3]=timer[3].totaltime;
    fuckedup[4]=timer[4].totaltime;
    fuckedup[5]=timer[5].totaltime;
    fuckedup[6]=timer[6].totaltime;
    fuckedup[7]=timer[7].totaltime;
    fuckedup[8]=timer[8].totaltime;
    fuckedup[9]=frame.numoflights;
    fuckedup[10]=numofsounds;
    fuckedup[11]=game.bonus[7];
    fuckedup[12]=numofanimations;
    */
    fuckedup[7]=game.levelnum;
    for (count=0;count<16;count++)
      {
      if (fuckedup[count]<8000000)
        drawtext("/i",0,128+count*12,12,1.0f,1.0f,1.0f,1.0f,fuckedup[count]);
      else
        drawtext("/i",0,128+count*12,12,1.0f,0.0f,0.0f,1.0f,fuckedup[count]);
      }

    drawtext("/f",0,368,16,1.0f,1.0f,1.0f,1.0f,object[0].data[0]);
    drawtext("/f",0,384,16,1.0f,1.0f,1.0f,1.0f,object[0].data[1]);
    drawtext("/i",0,400,16,1.0f,1.0f,1.0f,1.0f,fps);
    drawtext("/i",0,416,16,1.0f,1.0f,1.0f,1.0f,numofbonds);
    drawtext("/i",0,432,16,1.0f,1.0f,1.0f,1.0f,numofparticles);
    drawtext("/i",0,448,16,1.0f,1.0f,1.0f,1.0f,numofobjects);
    drawtext("/i",0,464,16,1.0f,1.0f,1.0f,1.0f,numofobjectrenders);
#endif

    if (game.playreplay)
      drawtext(TXT_REPLAY,(612|TEXT_END),64,16,1.0f,1.0f,0.0f,1.0f);

    if (game.pause && game.exit==0)
      {
      drawtext(TXT_PAUSED,(320|TEXT_CENTER),240,16,1.0f,1.0f,1.0f,1.0f);
      drawtext(TXT_PRESS_P,(320|TEXT_CENTER),256,12,1.0f,1.0f,1.0f,1.0f);
      }

    if (game.exit!=0 || game.godmode)
      drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    simcount=0;
    game.simspeed=20;
    if (game.turbomode)
      game.simspeed=15;

    while (SDL_GetTicks()-simtimer<=game.simspeed)
      SDL_Delay(1);

    while (SDL_GetTicks()-simtimer>game.simspeed && simcount<3)
      {
      simcount++;
      count=SDL_GetTicks()-simtimer-game.simspeed;
      simtimer=SDL_GetTicks()-count;
      if (simcount==3)
        simtimer=SDL_GetTicks();

      if (game.exitdelay>0)
      if (!game.editing)
        game.exitdelay--;
      if (keyboard[SCAN_ESC])
        game.exitdelay=0;

      if (game.exit==0 && !game.pause && game.dialog==0 && !game.over)
        {
        getinputs();

        if (!game.playreplay)
          saveinputs();
        else
          loadinputs();

        //resettimer(8);
        //starttimer(8);

        if (game.startdelay==0)
          simulation();
        gamelogic();

        //stoptimer(8);
        }
      }

    if (game.levelnum==0 && game.editing)
    if (keyboard[SCAN_F1] && !prevkeyboard[SCAN_F1])
      {
      game.songnum=-1;
      checkmusic();

      for (count=numofsounds-1;count>=0;count--)
        deletesound(count);

      setuptextdisplay();
    
      drawtext(TXT_LOADINGEDITOR,(320|TEXT_CENTER),240,16,1.0f,1.0f,1.0f,1.0f);
    
      SDL_GL_SwapBuffers();

      for (count=0;count<20;count++)
      if (animation[count].loaded==0)
        animation[count].loaded=2;

      loadanimations();

      editlevel();

      savelevel("backup.lvl");

      simtimer=SDL_GetTicks();
      }

    SDL_GL_SwapBuffers();

    if ((SDL_GetTicks()-frametimer)!=0)
      fps=1000/(SDL_GetTicks()-frametimer);
    }

  game.songnum=-1;
  checkmusic();

  for (count=numofsounds-1;count>=0;count--)
    deletesound(count);

  resetmenuitems();
  }

void simulation(void)
  {
  int count,count2;
  float vec[3],vec2[3];
  float intersectpoint[3];
  float normal[3];
  float scale;

  game.framenum++;

  if (game.godmode)
  if (!game.playreplay)
    {
    vec[0]=view.position[0]+(float)(mouse.x-320)/32.0f;
    vec[1]=view.position[1]+(float)(240-mouse.y)/32.0f;
    vec[2]=0.0f;

    if (mouse.lmb)
      {
      if (game.godparticle==-1)
        {
        game.godparticle=numofparticles;
        createparticle(16,vec,NULL,10000.0f,-1,10000);

        for (count=0;count<numofparticles;count++)
        if (count!=game.godparticle)
        if (particle[count].type==3)
          {
          subtractvectors(vec2,vec,particle[count].position);
          if (vectorlength(vec2)<3.0f)
            createbond(count,game.godparticle,16,-1);
          }
        }
      else
        {
        subtractvectors(vec2,vec,particle[game.godparticle].position);
        scaleaddvectors2(vec2,vec2,particle[game.godparticle].velocity,-4.0f);

        scale=vectorlength(vec2);
        normalizevector(vec2,vec2);
        scale*=0.01f;

        scaleaddvectors2(particle[game.godparticle].velocity,particle[game.godparticle].velocity,vec2,scale);
        }
      }
    else
      {
      if (game.godparticle!=-1)
        {
        deleteparticle(game.godparticle);
        game.godparticle=-1;
        }
      }
    }

  particlesimulation();
  particletimetolive();

  //physicstemp.numofbonds=0;

  for (count=0;count<numofobjects;count++)
    object[count].prevhitpoints=object[count].hitpoints;

  if (level.gametype!=16)
  for (count=0;count<numofparticles;count++)
    particle[count].velocity[1]-=particle[count].gravity;

  for (count=0;count<numofparticles;count++)
    if (particle[count].levelcollision)
      particlecollision(count);

  for (count=0;count<numofobjects;count++)
    {
    updateogg();
    objectcollision(count);
    }

  for (count=0;count<numofobjects;count++)
    {
    updateogg();
    objectcollisionobject(count);
    }

  objectcycle();
  objectanimation();

  updateogg();

  bondsimulation2();
  checkbonds();
  objecttimetolive();

  spritesimulation();
  spritetimetolive();

  bosssimulation();
  bosstimetolive();

  for (count=0;count<numofobjects;count++)
    {
    if (object[count].type==1)
      {
      if (object[count].hitpoints<0)
        object[count].hitpoints=0;

      if (object[count].hitpoints<object[count].prevhitpoints)
        {
        for (count2=0;count2<=(object[count].prevhitpoints-object[count].hitpoints)/20;count2++)
          {
          vec[0]=(float)((rnd()&255)-127)/1270.0f;
          vec[1]=(float)((rnd()&255)-127)/1270.0f;
          vec[2]=0.0f;
          addvectors(vec,vec,object[count].velocity);
  
          createparticle(5,object[count].position,vec,0.25f,-1,100+(rnd()&63));
          particle[numofparticles-1].rendersize=0.125+(float)(rnd()&127)/1000.0f;
          if (count==0)
            particle[numofparticles-1].texturenum=368;
          else if (count==1)
            particle[numofparticles-1].texturenum=363;
          else if (count==2)
            particle[numofparticles-1].texturenum=383+40;
          else
            particle[numofparticles-1].texturenum=383+60;
          }
        object[count].frame=12;
        object[count].framedelay=0.0f;
        playsound(16,object[count].position,NULL,0.5f,0,1.0f,count,2);
        }
      }
    }
  }

void getinputs(void)
  {
  int count;

  for (count=0;count<4;count++)
    {
    object[count].axis[0]=0.0f;
    object[count].axis[1]=0.0f;
    object[count].button=0;
    }
  for (count=0;count<4;count++)
    {
    if (keyboard[control[count].key[0]])
      object[count].axis[0]-=1.0f;
    if (keyboard[control[count].key[1]])
      object[count].axis[0]+=1.0f;
    if (keyboard[control[count].key[2]])
      object[count].axis[1]-=1.0f;
    if (keyboard[control[count].key[3]])
      object[count].axis[1]+=1.0f;
    if (keyboard[control[count].key[4]])
      object[count].button|=1;
    if (keyboard[control[count].key[5]])
      object[count].button|=2;
    if (keyboard[control[count].key[6]])
      object[count].button|=4;
    if (keyboard[control[count].key[7]])
      object[count].button|=8;

    if (control[count].joysticknum!=-1)
      {
      object[count].axis[0]+=joystick[control[count].joysticknum].axis[0];
      object[count].axis[1]+=joystick[control[count].joysticknum].axis[1];

      if (control[count].button[0]!=-1)
      if (joystick[control[count].joysticknum].button[control[count].button[0]])
        object[count].axis[0]-=1.0f;
      if (control[count].button[1]!=-1)
      if (joystick[control[count].joysticknum].button[control[count].button[1]])
        object[count].axis[0]+=1.0f;
      if (control[count].button[2]!=-1)
      if (joystick[control[count].joysticknum].button[control[count].button[2]])
        object[count].axis[1]-=1.0f;
      if (control[count].button[3]!=-1)
      if (joystick[control[count].joysticknum].button[control[count].button[3]])
        object[count].axis[1]+=1.0f;

      if (control[count].button[4]!=-1)
      if (joystick[control[count].joysticknum].button[control[count].button[4]])
        object[count].button|=1;
      if (control[count].button[5]!=-1)
      if (joystick[control[count].joysticknum].button[control[count].button[5]])
        object[count].button|=2;
      if (control[count].button[6]!=-1)
      if (joystick[control[count].joysticknum].button[control[count].button[6]])
        object[count].button|=4;
      if (control[count].button[7]!=-1)
      if (joystick[control[count].joysticknum].button[control[count].button[7]])
        object[count].button|=8;
      }
    if (object[count].axis[0]<-1.0f)
      object[count].axis[0]=-1.0f;
    if (object[count].axis[0]>1.0f)
      object[count].axis[0]=1.0f;
    if (object[count].axis[1]<-1.0f)
      object[count].axis[1]=-1.0f;
    if (object[count].axis[1]>1.0f)
      object[count].axis[1]=1.0f;
    }
  }
