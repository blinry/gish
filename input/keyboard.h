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

unsigned char keyboard[323];
unsigned char prevkeyboard[323];

#define SCAN_ESC          27
#define SCAN_0            48
#define SCAN_1            49
#define SCAN_2            50
#define SCAN_3            51
#define SCAN_4            52
#define SCAN_5            53
#define SCAN_6            54
#define SCAN_7            55
#define SCAN_8            56
#define SCAN_9            57
#define SCAN_MINUS        45
#define SCAN_EQUALS       61
#define SCAN_BKSP         8 
#define SCAN_TAB          9 
#define SCAN_LFT_BRACKET  91
#define SCAN_RGT_BRACKET  93
#define SCAN_ENTER        13
#define SCAN_CTRL         306
#define SCAN_RCTRL        305
#define SCAN_SEMI         59
#define SCAN_APOS         39
#define SCAN_TILDE        96
#define SCAN_SHIFT        304
#define SCAN_BACK_SLASH   92
#define SCAN_COMMA        44
#define SCAN_PERIOD       46
#define SCAN_FOWARD_SLASH 47
#define SCAN_RSHIFT       303
#define SCAN_PRT_SCRN     316
#define SCAN_ALT          308
#define SCAN_SPACE        32
#define SCAN_CAPS_LOCK    301
#define SCAN_F1           282
#define SCAN_F2           283
#define SCAN_F3           284
#define SCAN_F4           285
#define SCAN_F5           286
#define SCAN_F6           287
#define SCAN_F7           288
#define SCAN_F8           289
#define SCAN_F9           290
#define SCAN_F10          291
#define SCAN_F11          292
#define SCAN_F12          293
#define SCAN_NUM_LOCK     300
#define SCAN_SCROLL_LOCK  302
#define SCAN_NUMHOME      263
#define SCAN_UP           273
#define SCAN_NUMPGUP      265
#define SCAN_NUM_MINUS    269
#define SCAN_LEFT         276
#define SCAN_CENTER       261
#define SCAN_RIGHT        275
#define SCAN_NUMPLUS      270
#define SCAN_NUMEND       257
#define SCAN_DOWN         274
#define SCAN_NUMPGDWN     259
#define SCAN_NUMINS       256
#define SCAN_NUMDEL       266
#define SCAN_LWIN         311
#define SCAN_RWIN         312
#define SCAN_APPS         313
#define SCAN_NUMENTER     271
#define SCAN_NUMLEFT      260
#define SCAN_NUMRIGHT     262
#define SCAN_NUMUP        264
#define SCAN_NUMDOWN      258 
#define SCAN_LEFTARROW    276
#define SCAN_RIGHTARROW   275
#define SCAN_UPARROW      273
#define SCAN_DOWNARROW    274
#define SCAN_INSERT       277
#define SCAN_DELETE       127
#define SCAN_HOME         278
#define SCAN_END          279
#define SCAN_PAGEUP       280
#define SCAN_PAGEDOWN     281
#define SCAN_A			  97
#define SCAN_B			  98
#define SCAN_C			  99
#define SCAN_D			  100
#define SCAN_E			  101
#define SCAN_F			  102
#define SCAN_G			  103
#define SCAN_H			  104
#define SCAN_I			  105
#define SCAN_J			  106
#define SCAN_K			  107
#define SCAN_L			  108
#define SCAN_M			  109
#define SCAN_N			  110
#define SCAN_O			  111
#define SCAN_P			  112
#define SCAN_Q        113
#define SCAN_R			  114
#define SCAN_S			  115
#define SCAN_T			  116
#define SCAN_U			  117
#define SCAN_V			  118
#define SCAN_W			  119
#define SCAN_X			  120
#define SCAN_Y			  121
#define SCAN_Z			  122
