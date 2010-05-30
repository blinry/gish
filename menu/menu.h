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

#define MAXMENUITEMS   256
#define MO_HOTKEY       1
#define MO_HIGHLIGHT    2
#define MO_INTINPUT     3
#define MO_UINTINPUT    4
#define MO_FLOATINPUT   5
#define MO_STRINGINPUT  6
#define MO_FUNCTION     7
#define MO_TOGGLE       8
#define MO_SET          9
#define MO_REPEAT      10
#define MO_IMAGE 			 11
#define MO_RESIZE      12
#define MO_CURSOR      13
#define MO_BACKGROUND  14

void checkmenuitems(void);
void drawmenuitems(void);
void createmenuitem(char *label,int x,int y,int textsize,float r,float g,float b,float a);
void setmenuitem(int option,...);
void createmenuitemempty(void);
void resetmenuitems(void);
void setupmenuitems(void);
void menutextbox(void);
void menutoggle(void);
void menuset(void);
int getinputletter(int repeat,int inputflags);
void addmenuinputchar(int charinput);
int deleteselectedtext(void);

int numofmenuitems;
struct
  {
  char label[64];
	int x;
	int y;
	int textsize;
	float r;
	float g;
	float b;
	int type;
	int sizex;
	int sizey;
	int hotkey;
  int repeat;
	int highlight;
	int prevhighlight;
  int prevactive;
	int active;
  int value;
  int inputtype;
	int texturenum;
  int cursornum;
  int background;
  void *inputpointer;
  void (*function)();
  } menuitem[MAXMENUITEMS];

int menuinputkeyboard=0;
int menuinputselectpos;
int menuinputcursorpos;
int menuinputinsert;
char menuinput[256];
char menuinputtemp[256];

int joymenunum;
int joystickmenu=1;

int currentmenuitem;

char keyboardlabel[323][16];
