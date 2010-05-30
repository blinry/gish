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

void custommenu(void);
void loadlevelmenu(void);
void playcampaignmenu(void);
void campaignmenu(void);
void loadplayermappack(void);
void saveplayermappack(void);
void loadmappack(void);
void savemappack(void);
void newmappackmenu(void);

char levellist[1024][32];

struct
  {
  int active;
  int numoflevels;
  char filename[32];
  char name[32];
  char level[64][32];
  char levelname[64][32];
  char levelmusic[64][32];
  char ending[16][64];
  } mappack;

struct
  {
  int levelnum;
  int numoflives;
  int totalscore;
  int difficulty;
  int highscore;
  } playermappack[16];

