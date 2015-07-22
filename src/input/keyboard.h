#ifndef GISH_INPUT_KEYBOARD_H
#define GISH_INPUT_KEYBOARD_H
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

void checkkeyboard(void);

extern unsigned char keyboard[323];
extern unsigned char prevkeyboard[323];

typedef enum {
	SCAN_ESC = 27,
	SCAN_0 = 48,
	SCAN_1 = 49,
	SCAN_2 = 50,
	SCAN_3 = 51,
	SCAN_4 = 52,
	SCAN_5 = 53,
	SCAN_6 = 54,
	SCAN_7 = 55,
	SCAN_8 = 56,
	SCAN_9 = 57,
	SCAN_MINUS = 45,
	SCAN_EQUALS = 61,
	SCAN_BKSP = 8,
	SCAN_TAB = 9,
	SCAN_LFT_BRACKET = 91,
	SCAN_RGT_BRACKET = 93,
	SCAN_ENTER = 13,
	SCAN_CTRL = 306,
	SCAN_RCTRL = 305,
	SCAN_SEMI = 59,
	SCAN_APOS = 39,
	SCAN_TILDE = 96,
	SCAN_SHIFT = 304,
	SCAN_BACK_SLASH = 92,
	SCAN_COMMA = 44,
	SCAN_PERIOD = 46,
	SCAN_FOWARD_SLASH = 47,
	SCAN_RSHIFT = 303,
	SCAN_PRT_SCRN = 316,
	SCAN_ALT = 308,
	SCAN_SPACE = 32,
	SCAN_CAPS_LOCK = 301,
	SCAN_F1 = 282,
	SCAN_F2 = 283,
	SCAN_F3 = 284,
	SCAN_F4 = 285,
	SCAN_F5 = 286,
	SCAN_F6 = 287,
	SCAN_F7 = 288,
	SCAN_F8 = 289,
	SCAN_F9 = 290,
	SCAN_F10 = 291,
	SCAN_F11 = 292,
	SCAN_F12 = 293,
	SCAN_NUM_LOCK = 300,
	SCAN_SCROLL_LOCK = 302,
	SCAN_NUMHOME = 263,
	SCAN_UP = 273,
	SCAN_NUMPGUP = 265,
	SCAN_NUM_MINUS = 269,
	SCAN_LEFT = 276,
	SCAN_CENTER = 261,
	SCAN_RIGHT = 275,
	SCAN_NUMPLUS = 270,
	SCAN_NUMEND = 257,
	SCAN_DOWN = 274,
	SCAN_NUMPGDWN = 259,
	SCAN_NUMINS = 256,
	SCAN_NUMDEL = 266,
	SCAN_LWIN = 311,
	SCAN_RWIN = 312,
	SCAN_APPS = 313,
	SCAN_NUMENTER = 271,
	SCAN_NUMLEFT = 260,
	SCAN_NUMRIGHT = 262,
	SCAN_NUMUP = 264,
	SCAN_NUMDOWN = 258, 
	SCAN_LEFTARROW = 276,
	SCAN_RIGHTARROW = 275,
	SCAN_UPARROW = 273,
	SCAN_DOWNARROW = 274,
	SCAN_INSERT = 277,
	SCAN_DELETE = 127,
	SCAN_HOME = 278,
	SCAN_END = 279,
	SCAN_PAGEUP = 280,
	SCAN_PAGEDOWN = 281,
	SCAN_A = 97,
	SCAN_B = 98,
	SCAN_C = 99,
	SCAN_D = 100,
	SCAN_E = 101,
	SCAN_F = 102,
	SCAN_G = 103,
	SCAN_H = 104,
	SCAN_I = 105,
	SCAN_J = 106,
	SCAN_K = 107,
	SCAN_L = 108,
	SCAN_M = 109,
	SCAN_N = 110,
	SCAN_O = 111,
	SCAN_P = 112,
	SCAN_Q = 113,
	SCAN_R = 114,
	SCAN_S = 115,
	SCAN_T = 116,
	SCAN_U = 117,
	SCAN_V = 118,
	SCAN_W = 119,
	SCAN_X = 120,
	SCAN_Y = 121,
	SCAN_Z = 122
} keyboardkey;

#endif /* GISH_INPUT_KEYBOARD_H */
