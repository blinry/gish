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

#include "../config.h"

#include "../video/opengl.h"

#include <stdlib.h>
#include <time.h>

#include "../game/mainmenu.h"
#include "../game/animation.h"
#include "../game/gameaudio.h"
#include "../game/config.h"
#include "../game/credits.h"
#include "../game/editor.h"
#include "../game/english.h"
#include "../game/game.h"
#include "../game/lighting.h"
#include "../game/music.h"
#include "../game/gameobject.h"
#include "../game/options.h"
#include "../game/physics.h"
#include "../game/player.h"
#include "../game/socket.h"
#include "../game/vsmode.h"
#include "../game/debug.h"
#include "../audio/audio.h"
#include "../input/joystick.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../math/vector.h"
#include "../menu/menu.h"
#include "../sdl/event.h"
#include "../video/text.h"
#include "../video/texture.h"

void mainmenu(void)
  {
  int count,temp;
  int prevjoymenunum;
  //int registered;
  char loadfilename[32]="loading00.png";
  char texfilename[32]="text000.png";
  //unsigned int x,y;

  srand(time(NULL));
  count=(rand()%11)+1;

  loadfilename[7]=48+count/10;
  loadfilename[8]=48+count%10;
  loadbackground(800,loadfilename);

  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  setuptextdisplay();

  glColor4f(1.0f,1.0f,1.0f,1.0f);
  displaybackground(800);

  drawtext(TXT_LOADING,(320|TEXT_CENTER),448,16,1.0f,1.0f,1.0f,1.0f);

  SDL_GL_SwapBuffers();

  for (count=0;count<64;count++)
    {
    texfilename[4]=48+(count/100)%10;
    texfilename[5]=48+(count/10)%10;
    texfilename[6]=48+count%10;
    loadtexture(count+256,texfilename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    }

  loadtexture(256+64,"cage1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(256+65,"cage2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(256+66,"cage3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(256+67,"cage4.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(256+68,"x.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  setuplightingtextures();

  loadbackground(470,"gishtitle.png");

  loadtexture(462,"complete.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(465,"breatalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(468,"lvlcomplete.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(469,"gishy.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(512,"gishtalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(513,"honeytalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(514,"paunchytalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(515,"vistalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(516,"bastalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(517,"sistalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(518,"heratalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(519,"badending.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(520,"goodending.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(521,"sewerimg.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(522,"caveimg.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(523,"hellimg.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(524,"egyptimg.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(525,"churchimg.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(526,"warpimg.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(527,"satantalk.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(528,"crypticsea.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(529,"turbo.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(530,"sumo.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(531,"football.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(532,"greed.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(533,"duel.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(534,"dragster.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(535,"collect.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadbackground(540,"level.png");

  loadbackground(560,"congrats.png");
  loadbackground(580,"blank.png");

  loadbackground(600,"vsmode.png");
  loadbackground(620,"storymode.png");

  loadtexturepartial(640,"border.png",0,0,256,256);
  loadtexturepartial(641,"border.png",256,0,256,256);
  loadtexturepartial(642,"border.png",512,0,256,256);
  loadtexturepartial(643,"border.png",0,256,256,256);
  loadtexturepartial(644,"border.png",256,256,256,256);
  loadtexturepartial(645,"border.png",512,256,256,256);

  loadtexture(820,"gishwin.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(821,"graywin.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(822,"fight.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(823,"ready.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(700,"0.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(701,"1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(702,"2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(703,"3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(704,"4.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(705,"5.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(706,"6.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(707,"7.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(708,"8.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(709,"9.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(710,"10.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(711,"11.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(712,"12.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(720,"gishhud.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(721,"greyhud.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(722,"tarballs.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(723,"key.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(360,"rope.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(361,"chain.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(362,"piston1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(363,"tar2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(364,"poop.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(365,"dust.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(366,"bubble.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(367,"blood.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(368,"tar.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(369,"amber.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(370,"face.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(371,"facem1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(372,"facem2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(373,"facem3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(374,"facem4.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(375,"faceb1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(376,"faceb2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(377,"faceb1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(378,"faceh1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(379,"faceh2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(380,"faceh3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(381,"faceh4.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(382,"gishhurt.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(370+20,"gface.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(371+20,"gfacem1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(372+20,"gfacem2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(373+20,"gfacem3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(374+20,"gfacem4.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(375+20,"gfaceb1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(376+20,"gfaceb2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(377+20,"gfaceb1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(378+20,"gfaceh01.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(379+20,"gfaceh02.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(380+20,"gfaceh03.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(381+20,"gfaceh03.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(382+20,"grayhurt.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(370+40,"bface.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(371+40,"bfacem1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(372+40,"bfacem2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(373+40,"bfacem3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(374+40,"bfacem4.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(375+40,"bfaceb1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(376+40,"bfaceb2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(377+40,"bfaceb1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(378+40,"bfaceh1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(379+40,"bfaceh2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(380+40,"bfaceh3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(381+40,"bfaceh3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(382+40,"bhurt.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(383+40,"btar.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  loadtexture(370+60,"rface.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(371+60,"rfacem1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(372+60,"rfacem2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(373+60,"rfacem3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(374+60,"rfacem4.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(375+60,"rfaceb1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(376+60,"rfaceb2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(377+60,"rfaceb1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(378+60,"rfaceh1.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(379+60,"rfaceh2.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(380+60,"rfaceh3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(381+60,"rfaceh3.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(382+60,"rhurt.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexture(383+60,"rtar.png",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);

  numofanimations=1024;

  //loadanimations();

  if (config.sound)
    loadoggs();

  setupphysics();

  setupobjecttypes();

  editor.mode=1;

  game.songnum=-1;
  game.currentsongnum=-1;
  resetorientation(view.orientation);
  soundsimulation(view.position,view.orientation);

  introscreen();

  resetmenuitems();

  joymenunum=1;
  game.turbomode=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
		temp=(sizeof(TXT_EXIT)+sizeof(TXT_CREDITS)+sizeof(TXT_OPTIONS)+sizeof(TXT_VERSUS)+sizeof(TXT_START)-1)*8;

    createmenuitem(TXT_EXIT,(320+temp)|TEXT_END,380,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    createmenuitem(TXT_START,320-temp,380,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_S);
		temp-=(sizeof(TXT_START))*16;
    createmenuitem(TXT_VERSUS,320-temp,380,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_V);
		temp-=(sizeof(TXT_VERSUS))*16;
    createmenuitem(TXT_OPTIONS,320-temp,380,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_O);
		temp-=(sizeof(TXT_OPTIONS))*16;
    createmenuitem(TXT_CREDITS,320-temp,380,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_C);
    createmenuitem("Cryptic Sea",0,0,1,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_IMAGE,528);
    setmenuitem(MO_RESIZE,16,0,96,48);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    if (keyboard[SCAN_T] && !prevkeyboard[SCAN_T])
      game.turbomode^=1;

    updateogg();
    checkmusic();
    game.songnum=8;
    soundsimulation(view.position,view.orientation);

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(470);

    if (game.turbomode)
      drawtext(TXT_TURBO_EDITION,(640|TEXT_END),470,10,1.0f,1.0f,1.0f,1.0f);
    drawtext("Version 1.53",0,470,10,1.0f,1.0f,1.0f,1.0f);

    drawtext(TXT_COPYRIGHT,(320|TEXT_CENTER),470,10,0.75f,0.75f,0.75f,1.0f);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[5].active)
      {
      launchwebpage("www.crypticsea.com");
      menuitem[5].active=0;
      }
    if (menuitem[4].active)
      {
      //game.songnum=-1;
      //checkmusic();

      prevjoymenunum=4;
      creditsmenu();
      joymenunum=prevjoymenunum;
      }
    if (menuitem[3].active)
      {
      game.songnum=-1;
      checkmusic();

      prevjoymenunum=3;
      optionsmenu();
      joymenunum=prevjoymenunum;
      }
    if (menuitem[2].active)
      {
      //game.songnum=-1;
      //checkmusic();

      prevjoymenunum=2;
      versusmenu();
      joymenunum=prevjoymenunum;
      }
    if (menuitem[1].active)
      {
      //game.songnum=-1;
      //checkmusic();

      prevjoymenunum=1;
      playermenu();
      joymenunum=prevjoymenunum;
      }
    }

  game.songnum=-1;
  checkmusic();
  }

void loadbackground(int texturenum,char *filename)
  {
  loadtexturepartial(texturenum,filename,0,0,256,256);
  loadtexturepartial(texturenum+1,filename,256,0,256,256);
  loadtexturepartial(texturenum+2,filename,512,0,256,256);
  loadtexturepartial(texturenum+3,filename,768,0,256,256);
  loadtexturepartial(texturenum+4,filename,0,256,256,256);
  loadtexturepartial(texturenum+5,filename,256,256,256,256);
  loadtexturepartial(texturenum+6,filename,512,256,256,256);
  loadtexturepartial(texturenum+7,filename,768,256,256,256);
  loadtexturepartial(texturenum+8,filename,0,512,256,256);
  loadtexturepartial(texturenum+9,filename,256,512,256,256);
  loadtexturepartial(texturenum+10,filename,512,512,256,256);
  loadtexturepartial(texturenum+11,filename,768,512,256,256);
  }

void displaybackground(int texturenum)
  {
  drawbackground(texturenum,0,0,256,256,800,600);
  drawbackground(texturenum+1,256,0,256,256,800,600);
  drawbackground(texturenum+2,512,0,256,256,800,600);
  drawbackground(texturenum+3,768,0,256,256,800,600);
  drawbackground(texturenum+4,0,256,256,256,800,600);
  drawbackground(texturenum+5,256,256,256,256,800,600);
  drawbackground(texturenum+6,512,256,256,256,800,600);
  drawbackground(texturenum+7,768,256,256,256,800,600);
  drawbackground(texturenum+8,0,512,256,256,800,600);
  drawbackground(texturenum+9,256,512,256,256,800,600);
  drawbackground(texturenum+10,512,512,256,256,800,600);
  drawbackground(texturenum+11,768,512,256,256,800,600);
  }

void versusmenu(void)
  {
  int count;
  int unlocked;

  unlocked=0;
  for (count=0;count<6;count++)
  if (player[count].unlock[0])
    unlocked=1;

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    count=64;
    createmenuitem(TXT_SUMO,(144|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_S);
    createmenuitem(TXT_FOOTBALL,(320|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_F);
    createmenuitem(TXT_GREED,(512|TEXT_CENTER),304,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_G);
    createmenuitem(TXT_DUEL,(152|TEXT_CENTER),444,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_U);
    createmenuitem(TXT_DRAGSTER,(320|TEXT_CENTER),444,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_D);
    if (unlocked)
      {
      createmenuitem(TXT_COLLECTION,(512|TEXT_CENTER),444,16,1.0f,1.0f,1.0f,1.0f);
      setmenuitem(MO_HOTKEY,SCAN_C);
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
    displaybackground(600);

    if (!unlocked)
      {
      drawbackground(256+68,448,328,96,96,640,480);
      drawtext("?????",(512|TEXT_CENTER),444,16,1.0f,1.0f,1.0f,1.0f);
      }

    drawmenuitems();


    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    for (count=1;count<=7;count++)
    if (menuitem[count].active)
      versusmodemenu(count-1);
    }

  resetmenuitems();
  }

void storyscreen(void)
  {
  int count;
  int simtimer;
  int simcount;
  int loaddelay;
  int screennum;

  loaddelay=0;
  screennum=0;

  loadbackground(824,"story1.png");

  simtimer=SDL_GetTicks();

  resetmenuitems();

  joymenunum=1;

  while (!menuitem[0].active && screennum<8 && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    createmenuitem(TXT_NEXT,(640|TEXT_END),0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_N);

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
    displaybackground(824);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    simcount=0;
    while (SDL_GetTicks()-simtimer>20 && simcount<5)
      {
      simcount++;
      count=SDL_GetTicks()-simtimer-20;
      simtimer=SDL_GetTicks()-count;

      loaddelay++;
      if (loaddelay>=400)
        {
        screennum++;
        if (screennum==1)
          loadbackground(824,"story2.png");
        if (screennum==2)
          loadbackground(824,"story3.png");
        if (screennum==3)
          loadbackground(824,"story4.png");
        if (screennum==4)
          loadbackground(824,"story5.png");
        if (screennum==5)
          loadbackground(824,"story6.png");
        if (screennum==6)
          loadbackground(824,"story7.png");
        if (screennum==7)
          loadbackground(824,"story8.png");
        loaddelay=0;
        }
      }
    if (menuitem[1].active)
      {
      screennum++;
      if (screennum==1)
        loadbackground(824,"story2.png");
      if (screennum==2)
        loadbackground(824,"story3.png");
      if (screennum==3)
        loadbackground(824,"story4.png");
      if (screennum==4)
        loadbackground(824,"story5.png");
      if (screennum==5)
        loadbackground(824,"story6.png");
      if (screennum==6)
        loadbackground(824,"story7.png");
      if (screennum==7)
        loadbackground(824,"story8.png");
      loaddelay=0;
      menuitem[1].active=0;
      }
    }

  resetmenuitems();
  }

void introscreen(void)
  {
  int count,count2=0;
  int simtimer;
  int simcount;
  int loaddelay;
  float alpha;
  int secretsequence;
  float vec[3];

  srand(time(NULL));

  loaddelay=0;

  secretsequence=0;

  simtimer=SDL_GetTicks();

  resetmenuitems();

  while (!menuitem[0].active && loaddelay<200 && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(" ",0,0,640,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();
    checkmenuitems();

    if (secretsequence==0)
      count2=3;
    if (secretsequence==1)
      count2=3;
    if (secretsequence==2)
      count2=2;
    if (secretsequence==3)
      count2=2;
    if (secretsequence==4)
      count2=0;
    if (secretsequence==5)
      count2=1;
    if (secretsequence==6)
      count2=0;
    if (secretsequence==7)
      count2=1;
    if (secretsequence==8)
      count2=4;
    if (secretsequence==9)
      count2=5;
    if (secretsequence==10)
      {
      if (game.turbomode==0)
        {
        vec[0]=0.0f;
        vec[1]=0.0f;
        vec[2]=0.0f;
        playsound(10,vec,NULL,0.4f,0,1.0f,-1,0);
        }
      game.turbomode=1;
      }

    for (count=0;count<KEYALIAS_LENGTH;count++)
      {
      if (keyboard[control[0].key[count]] && !prevkeyboard[control[0].key[count]])
        {
        if (count==count2)
          secretsequence++;
        else
          secretsequence=0;
        }

      if (control[0].joysticknum!=-1)
        {
        if (count==0)
        if (joystick[control[0].joysticknum].axis[0]<=-0.5f && prevjoystick[control[0].joysticknum].axis[0]>-0.5f)
          {
          if (count==count2)
            secretsequence++;
          else
            secretsequence=0;
          }
        if (count==1)
        if (joystick[control[0].joysticknum].axis[0]>=0.5f && prevjoystick[control[0].joysticknum].axis[0]<0.5f)
          {
          if (count==count2)
            secretsequence++;
          else
            secretsequence=0;
          }
        if (count==2)
        if (joystick[control[0].joysticknum].axis[1]<=-0.5f && prevjoystick[control[0].joysticknum].axis[1]>-0.5f)
          {
          if (count==count2)
            secretsequence++;
          else
            secretsequence=0;
          }
        if (count==3)
        if (joystick[control[0].joysticknum].axis[1]>=0.5f && prevjoystick[control[0].joysticknum].axis[1]<0.5f)
          {
          if (count==count2)
            secretsequence++;
          else
            secretsequence=0;
          }
        if (control[0].button[count]!=-1)
        if (joystick[control[0].joysticknum].button[control[0].button[count]] && !prevjoystick[control[0].joysticknum].button[control[0].button[count]])
          {
          if (count==count2)
            secretsequence++;
          else
            secretsequence=0;
          }
        }
      }

    updateogg();
    checkmusic();
    game.songnum=8;
    soundsimulation(view.position,view.orientation);

    setuptextdisplay();

    if (loaddelay<100)
      {
      alpha=(float)(100-loaddelay)/100.0f;
      glColor4f(1.0f,1.0f,1.0f,alpha);
      displaybackground(800);
      }
    else
      {
      alpha=(float)(loaddelay-100)/100.0f;
      glColor4f(1.0f,1.0f,1.0f,alpha);
      displaybackground(470);

      drawtext(TXT_EXIT,(320+72+128),380,16,0.5f,0.5f,0.5f,alpha);
      drawtext(TXT_START,(320-72-112)|TEXT_END,380,16,0.5f,0.5f,0.5f,alpha);
      drawtext(TXT_VERSUS,(320-72)|TEXT_END,380,16,0.5f,0.5f,0.5f,alpha);
      drawtext(TXT_OPTIONS,(320)|TEXT_CENTER,380,16,0.5f,0.5f,0.5f,alpha);
      drawtext(TXT_CREDITS,(320+72),380,16,0.5f,0.5f,0.5f,alpha);

      if (game.turbomode)
        drawtext(TXT_TURBO_EDITION,(640|TEXT_END),470,10,1.0f,1.0f,1.0f,1.0f);
      drawtext("Version 1.53",0,470,10,1.0f,1.0f,1.0f,1.0f);

      drawtext(TXT_COPYRIGHT,(320|TEXT_CENTER),470,10,0.75f,0.75f,0.75f,alpha);
      }
    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    simcount=0;
    while (SDL_GetTicks()-simtimer>20 && simcount<5)
      {
      simcount++;
      count=SDL_GetTicks()-simtimer-20;
      simtimer=SDL_GetTicks()-count;

      loaddelay++;
      }
    }

  resetmenuitems();
  }
