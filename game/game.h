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

void gameloop(void);
void renderlevel(void);
void simulation(void);
void getinputs(void);

struct
  {
  float position[3];
  float orientation[3][3];
  float zoom;
  int zoomx;
  int zoomy;
  } view;

struct
  {
  int pause;
  int type;
  int framenum;
  int levelnum;
  int bosslevel;
  int dialog;
  int dialogdelay;
  int songnum;
  int currentsongnum;
  int time;
  int score[4];
  int combo;
  int combodelay;
  int totalscore;
  int difficulty;
  int bonus[16];
  int numofbonus[16];
  int scoredelay;
  int startdelay;
  int exitdelay;
  int over;
  int numoflives;
  char text[256];
  int exit;
  int oldschool;
  int oldschoolsound;
  int turbomode;
  int supersize;
  int simspeed;
  int playreplay;
  int editing;
  int godmode;
  int godparticle;
  } game;
