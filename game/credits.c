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

#include "../game/credits.h"
#include "../game/gameaudio.h"
#include "../game/english.h"
#include "../game/game.h"
#include "../game/mainmenu.h"
#include "../game/music.h"
#include "../game/socket.h"
#include "../audio/audio.h"
#include "../input/joystick.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../menu/menu.h"
#include "../sdl/event.h"
#include "../video/text.h"

void creditsmenu(void)
  {
  int count,count2=0;
  int secretsequence;
  float vec[3];

  secretsequence=0;

  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_BACK,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkjoystick();

    if (secretsequence==0)
      count2=SCAN_S;
    if (secretsequence==1)
      count2=SCAN_U;
    if (secretsequence==2)
      count2=SCAN_P;
    if (secretsequence==3)
      count2=SCAN_E;
    if (secretsequence==4)
      count2=SCAN_R;
    if (secretsequence==5)
      count2=SCAN_S;
    if (secretsequence==6)
      count2=SCAN_I;
    if (secretsequence==7)
      count2=SCAN_Z;
    if (secretsequence==8)
      count2=SCAN_E;
    if (secretsequence==9)
      count2=SCAN_M;
    if (secretsequence==10)
      count2=SCAN_E;

    if (secretsequence==11)
      {
      if (game.supersize==0)
        {
        vec[0]=0.0f;
        vec[1]=0.0f;
        vec[2]=0.0f;
        playsound(12,vec,NULL,0.4f,0,1.0f,-1,0);
        }
      game.supersize=1;
      }

    for (count=0;count<256;count++)
    if (keyboard[count] && !prevkeyboard[count])
      {
      if (count==count2)
        secretsequence++;
      else
        secretsequence=0;
      }

    updateogg();
    checkmusic();
    game.songnum=8;
    soundsimulation(view.position,view.orientation);

    setuptextdisplay();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    displaybackground(580);

    drawtext(TXT_CREDITS,(320|TEXT_CENTER),48,16,1.0f,1.0f,1.0f,1.0f);

    count=64;
    count+=12;
    drawtext(TXT_DESIGN,64,count,12,0.5f,0.5f,0.5f,1.0f);
    count+=12;
    drawtext("Edmund McMillen",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    drawtext("Alex Austin",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    drawtext("Josiah Pisciotta",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    count+=12;
    drawtext(TXT_PROGRAMMING,64,count,12,0.5f,0.5f,0.5f,1.0f);
    count+=12;
    drawtext("Alex Austin, Josiah Pisciotta",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    drawtext("Sebastian Morr, FrozenCow",64,count,12,1.0f,1.0f,1.0f,1.0f); // freegish
    count+=12;
    drawtext("Sven-Hendrik Haase, Steve Pinkham, Etam",64,count,12,1.0f,1.0f,1.0f,1.0f); // freegish
    count+=12;
    drawtext("Shish Moom, Harry Roberts, James Le Cuirot",64,count,12,1.0f,1.0f,1.0f,1.0f); // freegish
    count+=12;
    count+=12;
    drawtext(TXT_ART,64,count,12,0.5f,0.5f,0.5f,1.0f);
    count+=12;
    drawtext("Megagun, Asmageddon",64,count,12,1.0f,1.0f,1.0f,1.0f); // freegish
    count+=12;
    count+=12;
    drawtext(TXT_SOUND_MUSIC,64,count,12,0.5f,0.5f,0.5f,1.0f);
    count+=12;
    drawtext("Diablo Swing Orchestra, Gladius Noctis",64,count,12,1.0f,1.0f,1.0f,1.0f); // freegish
    count+=12;
    count+=12;
    /*drawtext(TXT_ADDITIONAL_DIALOG,64,count,12,0.5f,0.5f,0.5f,1.0f);
    count+=12;
    drawtext("Dave Strock",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    count+=12;
    drawtext(TXT_ADDITIONAL_CONTENT,64,count,12,0.5f,0.5f,0.5f,1.0f);
    count+=12;
    drawtext("Riftmaster",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    drawtext("Will Stamper",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    count+=12;*/
    drawtext(TXT_THANKS,64,count,12,0.5f,0.5f,0.5f,1.0f);
    count+=12;
    drawtext("Ed thanks Danielle",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    drawtext("Beta Testers",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    drawtext("Roy Sawyers",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    //drawtext("Mendo Mate",64,count,12,1.0f,1.0f,1.0f,1.0f);
    createmenuitem("Mendo Mate",64,count,12,1.0f,1.0f,1.0f,1.0f); // original gish
    count+=12;
    count+=12;
    drawtext(TXT_GISHUSES"    ,       ,       , ",64,count,12,1.0f,1.0f,1.0f,1.0f);
    createmenuitem("SDL",        sizeof(TXT_GISHUSES)       *12+64,count,12,1.0f,1.0f,1.0f,1.0f);
    createmenuitem("OpenGL",    (sizeof(TXT_GISHUSES)+5)    *12+64,count,12,1.0f,1.0f,1.0f,1.0f);
    createmenuitem("OpenAL",    (sizeof(TXT_GISHUSES)+5+8)  *12+64,count,12,1.0f,1.0f,1.0f,1.0f);
    createmenuitem("Ogg Vorbis",(sizeof(TXT_GISHUSES)+5+8+8)*12+64,count,12,1.0f,1.0f,1.0f,1.0f);

    checkmenuitems();
    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[1].active)
      {
      launchwebpage("www.libsdl.org");
      menuitem[1].active=0;
      }
    if (menuitem[2].active)
      {
      launchwebpage("www.opengl.org");
      menuitem[2].active=0;
      }
    if (menuitem[3].active)
      {
      launchwebpage("www.openal.org");
      menuitem[3].active=0;
      }
    if (menuitem[4].active)
      {
      launchwebpage("www.xiph.org");
      menuitem[4].active=0;
      }
    if (menuitem[5].active)
      {
      launchwebpage("www.mendomate.com");
      menuitem[5].active=0;
      }
    }

  resetmenuitems();
  }
