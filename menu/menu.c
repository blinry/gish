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

void checkmenuitems(void)
  {
  int count,count2;

  for (count=0;count<numofmenuitems;count++)
    if ((mouse.lmb && !prevmouse.lmb) || menuitem[count].repeat)
      menuitem[count].active=0;

  font.cursornum=0;

	for (count=0;count<numofmenuitems;count++)
    {
		if (menuitem[count].highlight!=0)
      {
      menuitem[count].highlight=1;

      if (mouse.x>=menuitem[count].x)
      if (mouse.x<menuitem[count].x+menuitem[count].sizex*menuitem[count].textsize)
      if (mouse.y>=menuitem[count].y)
      if (mouse.y<menuitem[count].y+menuitem[count].sizey*menuitem[count].textsize)
        {
        menuitem[count].highlight=2;
        if (mouse.lmb && !prevmouse.lmb)
          menuitem[count].active=1;
        font.cursornum=menuitem[count].cursornum;
        }

      if (!menuinputkeyboard)
        if (keyboard[menuitem[count].hotkey] && (!prevkeyboard[menuitem[count].hotkey] || menuitem[count].repeat))
          menuitem[count].active=1;

      if (menuitem[count].type==2 && *(int *)menuitem[count].inputpointer)
        menuitem[count].highlight=3;

      if (menuitem[count].type==3 && *(int *)menuitem[count].inputpointer==menuitem[count].value)
        menuitem[count].highlight=3;

			if (menuitem[count].active)
				menuitem[count].highlight=3;
			menuitem[count].prevhighlight=menuitem[count].highlight;
      }
    }

  if (joystickmenu)
  if (numofmenuitems>0)
    {
    if (joymenunum<0)
      joymenunum=numofmenuitems-1;
    if (joymenunum>=numofmenuitems)
      joymenunum=0;

    if (menuitem[joymenunum].highlight!=0)
      {
      if (keyboard[SCAN_ENTER] && !prevkeyboard[SCAN_ENTER])
        menuitem[joymenunum].active=1;

      if (control[0].joysticknum!=-1)
      if (control[0].button[8]!=-1)
      if (joystick[control[0].joysticknum].button[control[0].button[8]] && !prevjoystick[control[0].joysticknum].button[control[0].button[8]])
        menuitem[joymenunum].active=1;
      }
    if (menuitem[joymenunum].highlight==1)
      menuitem[joymenunum].highlight=2;

    count2=0;
    if (control[0].joysticknum!=-1)
      {
      if (joystick[control[0].joysticknum].axis[1]>=0.5f && prevjoystick[control[0].joysticknum].axis[1]<0.5f)
        count2=-1;
      if (joystick[control[0].joysticknum].axis[1]<=-0.5f && prevjoystick[control[0].joysticknum].axis[1]>-0.5f)
        count2=1;
  
      if (control[0].button[2]!=-1)
      if (joystick[control[0].joysticknum].button[control[0].button[2]] && !prevjoystick[control[0].joysticknum].button[control[0].button[2]])
        count2=1;
      if (control[0].button[3]!=-1)
      if (joystick[control[0].joysticknum].button[control[0].button[3]] && !prevjoystick[control[0].joysticknum].button[control[0].button[3]])
        count2=-1;
      }

    if (keyboard[control[0].key[3]] && !prevkeyboard[control[0].key[3]])
      count2=-1;
    if (keyboard[control[0].key[2]] && !prevkeyboard[control[0].key[2]])
      count2=1;

    joymenunum+=count2;

    if (joymenunum<0)
      joymenunum=numofmenuitems-1;
    if (joymenunum>=numofmenuitems)
      joymenunum=0;

    if (menuitem[joymenunum].highlight==0)
      {
      if (count2==0)
        count2=1;
      joymenunum+=count2;
  
      if (joymenunum<0)
        joymenunum=numofmenuitems-1;
      if (joymenunum>=numofmenuitems)
        joymenunum=0;
      }
    }

	for (currentmenuitem=0;currentmenuitem<numofmenuitems;currentmenuitem++)
    {
    if (menuitem[currentmenuitem].active && menuitem[currentmenuitem].function!=NULL)
      (*menuitem[currentmenuitem].function)();
    if (menuitem[currentmenuitem].type!=1 && menuitem[currentmenuitem].function!=NULL)
			menuitem[currentmenuitem].active=0;

    menuitem[currentmenuitem].prevactive=menuitem[currentmenuitem].active;
    }

  menuinputkeyboard=0;
  for (count=0;count<numofmenuitems;count++)
    if (menuitem[count].active)
      if (menuitem[count].type==1)
        menuinputkeyboard=1;
  }

void drawmenuitems(void)
  {
	int count,count2;
  int xoffset,yoffset;
  char labelascii;
  float vec[3];

	for (count=0;count<numofmenuitems;count++)
    {
    if (menuitem[count].texturenum==-1)
      {
      if (menuitem[count].highlight<2)
        font.texturenum=0;
      else
        font.texturenum=1;

      if (menuitem[count].background==1)
        for (count2=0;count2<menuitem[count].sizex;count2++)
          drawtext("",menuitem[count].x+count2*menuitem[count].textsize,menuitem[count].y,menuitem[count].textsize,0.125f,0.125f,0.125f,1.0f);

      count2=0;
      labelascii=0;
      if (menuitem[count].highlight!=0)
        {
        while (count2<menuitem[count].sizex && menuitem[count].label[count2]!=0 && keyboardlabel[menuitem[count].hotkey][0]!=labelascii)
          {
          labelascii=toupper(menuitem[count].label[count2]);
          if (keyboardlabel[menuitem[count].hotkey][0]==labelascii && keyboardlabel[menuitem[count].hotkey][1]==0)
            drawtext("/c",menuitem[count].x+count2*menuitem[count].textsize,menuitem[count].y,menuitem[count].textsize,menuitem[count].r,menuitem[count].g,menuitem[count].b,1.0f,menuitem[count].label[count2]);
          else
            drawtext("/c",menuitem[count].x+count2*menuitem[count].textsize,menuitem[count].y,menuitem[count].textsize,(float)(menuitem[count].r*(menuitem[count].highlight+1))/4,(float)(menuitem[count].g*(menuitem[count].highlight+1))/4,(float)(menuitem[count].b*(menuitem[count].highlight+1))/4,1.0f,menuitem[count].label[count2]);
         
          count2++;
          }
        }
     
      while (count2<menuitem[count].sizex && menuitem[count].label[count2]!=0)
        {
        drawtext("/c",menuitem[count].x+count2*menuitem[count].textsize,menuitem[count].y,menuitem[count].textsize,(float)(menuitem[count].r*(menuitem[count].highlight+1))/4,(float)(menuitem[count].g*(menuitem[count].highlight+1))/4,(float)(menuitem[count].b*(menuitem[count].highlight+1))/4,1.0f,menuitem[count].label[count2]);
        count2++;
        }
  
      if (menuitem[count].type==1)
        {
        if (menuitem[count].sizey==1)
          {
          yoffset=0;
          xoffset=(strlen(menuitem[count].label))*menuitem[count].textsize;
          }
        else
          {
          yoffset=menuitem[count].textsize;
          xoffset=0;
          }
        for (count2=0;count2<menuitem[count].sizex;count2++)
          drawtext("",menuitem[count].x+xoffset+count2*menuitem[count].textsize,menuitem[count].y+yoffset,menuitem[count].textsize,(float)(menuitem[count].r*(menuitem[count].highlight+1))/32,(float)(menuitem[count].g*(menuitem[count].highlight+1))/32,(float)(menuitem[count].b*(menuitem[count].highlight+1))/32,1.0f);
  
        if (!menuitem[count].active)
          {
          if (menuitem[count].inputtype==0)
            sprintf(menuinputtemp,"%d",*(int*)menuitem[count].inputpointer);
          else if (menuitem[count].inputtype==1)
            sprintf(menuinputtemp,"%u",*(unsigned int*)menuitem[count].inputpointer);
          else if (menuitem[count].inputtype==2)
            sprintf(menuinputtemp,"%g",*(float*)menuitem[count].inputpointer);
          else
            strcpy(menuinputtemp,menuitem[count].inputpointer);
  
          drawtext(menuinputtemp,menuitem[count].x+xoffset,menuitem[count].y+yoffset,menuitem[count].textsize,(float)(menuitem[count].r*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].g*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].b*(menuitem[count].highlight+1))*0.25f,1.0f);
          }
        else
          {
          drawtext(menuinput,menuitem[count].x+xoffset,menuitem[count].y+yoffset,menuitem[count].textsize,(float)(menuitem[count].r*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].g*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].b*(menuitem[count].highlight+1))*0.25f,1.0f);
          for (count2=0;count2<menuitem[count].sizex;count2++)
            if ((count2>=menuinputselectpos && count2<menuinputcursorpos) ||
                (count2>=menuinputcursorpos && count2<menuinputselectpos))
              drawtext("",menuitem[count].x+xoffset+count2*menuitem[count].textsize,menuitem[count].y+yoffset,menuitem[count].textsize,(float)(menuitem[count].r*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].g*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].b*(menuitem[count].highlight+1))*0.25f,0.5f);
           
          if (!menuinputinsert)
            drawtext("_",menuitem[count].x+xoffset+menuinputcursorpos*menuitem[count].textsize,menuitem[count].y+yoffset,menuitem[count].textsize,(float)(menuitem[count].r*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].g*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].b*(menuitem[count].highlight+1))*0.25f,1.0f);
          else
            drawtext("",menuitem[count].x+xoffset+menuinputcursorpos*menuitem[count].textsize,menuitem[count].y+yoffset,menuitem[count].textsize,(float)(menuitem[count].r*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].g*(menuitem[count].highlight+1))*0.25f,(float)(menuitem[count].b*(menuitem[count].highlight+1))*0.25f,0.5f);
          }
        }
      }
		else
      {
      /*
      if (menuitem[count].highlight!=0)
	      glBindTexture(GL_TEXTURE_2D,texture[menuitem[count].texturenum+menuitem[count].highlight-1].glname);
			else
      */
      	glBindTexture(GL_TEXTURE_2D,texture[menuitem[count].texturenum].glname);

      glBegin(GL_QUADS);

      vec[0]=menuitem[count].x;
      vec[1]=menuitem[count].y;
      convertscreenvertex(vec,font.sizex,font.sizey);
      //glColor4f((float)(menuitem[count].r*(menuitem[count].highlight+1))/4,(float)(menuitem[count].g*(menuitem[count].highlight+1))/4,(float)(menuitem[count].b*(menuitem[count].highlight+1))/4,1.0f);
			glColor4f(1.0f,1.0f,1.0f,1.0f);
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(vec[0],vec[1],-1.0f);
  
      vec[0]=menuitem[count].x+menuitem[count].sizex*menuitem[count].textsize;
      vec[1]=menuitem[count].y;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(vec[0],vec[1],-1.0f);
  
      vec[0]=menuitem[count].x+menuitem[count].sizex*menuitem[count].textsize;
      vec[1]=menuitem[count].y+menuitem[count].sizey*menuitem[count].textsize;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(vec[0],vec[1],-1.0f);
  
      vec[0]=menuitem[count].x;
      vec[1]=menuitem[count].y+menuitem[count].sizey*menuitem[count].textsize;
      convertscreenvertex(vec,font.sizex,font.sizey);
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      glEnd();
      }
    }
  font.texturenum=0;
  }   

void createmenuitem(char *label,int x,int y,int textsize,float r,float g,float b,float a)
  {
  if ((x&TEXT_CENTER)==TEXT_CENTER)
    x=x-(strlen(label)*textsize)/2;
  if ((y&TEXT_CENTER)==TEXT_CENTER)
    y=y-(textsize)/2;
  if ((x&TEXT_END)==TEXT_END)
    x=x-(strlen(label)*textsize);
  if ((y&TEXT_END)==TEXT_END)
    y=y-textsize;
  x&=0xFFFF;
  y&=0xFFFF;

  strcpy(menuitem[numofmenuitems].label,label);
	menuitem[numofmenuitems].x=x;
	menuitem[numofmenuitems].y=y;
	menuitem[numofmenuitems].textsize=textsize;
	menuitem[numofmenuitems].r=r;
	menuitem[numofmenuitems].g=g;
	menuitem[numofmenuitems].b=b;
  menuitem[numofmenuitems].type=0;
  menuitem[numofmenuitems].sizex=strlen(label);
  menuitem[numofmenuitems].sizey=1;
  menuitem[numofmenuitems].hotkey=0;
  menuitem[numofmenuitems].repeat=0;
  menuitem[numofmenuitems].highlight=1;
  menuitem[numofmenuitems].value=0;
  menuitem[numofmenuitems].inputtype=0;
  menuitem[numofmenuitems].inputpointer=NULL;
  menuitem[numofmenuitems].function=NULL;
	menuitem[numofmenuitems].texturenum=-1;
  menuitem[numofmenuitems].cursornum=0;
  menuitem[numofmenuitems].background=0;
	numofmenuitems++;
  }

void setmenuitem(int option,...)
  {
  va_list ap;

  if (numofmenuitems==0)
    return;

  va_start(ap,option);

  if (option==MO_HOTKEY)
    menuitem[numofmenuitems-1].hotkey=va_arg(ap,int);
  if (option==MO_HIGHLIGHT)
    menuitem[numofmenuitems-1].highlight=va_arg(ap,int);
  if (option==MO_INTINPUT)
    {
    menuitem[numofmenuitems-1].type=1;
    menuitem[numofmenuitems-1].inputtype=0;
    menuitem[numofmenuitems-1].inputpointer=va_arg(ap,void *);
    menuitem[numofmenuitems-1].function=menutextbox;
    menuitem[numofmenuitems-1].sizey=2;
    }
  if (option==MO_UINTINPUT)
    {
    menuitem[numofmenuitems-1].type=1;
    menuitem[numofmenuitems-1].inputtype=1;
    menuitem[numofmenuitems-1].inputpointer=va_arg(ap,void *);
    menuitem[numofmenuitems-1].function=menutextbox;
    menuitem[numofmenuitems-1].sizey=2;
    }
  if (option==MO_FLOATINPUT)
    {
    menuitem[numofmenuitems-1].type=1;
    menuitem[numofmenuitems-1].inputtype=2;
    menuitem[numofmenuitems-1].inputpointer=va_arg(ap,void *);
    menuitem[numofmenuitems-1].function=menutextbox;
    menuitem[numofmenuitems-1].sizey=2;
    }
  if (option==MO_STRINGINPUT)
    {
    menuitem[numofmenuitems-1].type=1;
    menuitem[numofmenuitems-1].inputtype=3;
    menuitem[numofmenuitems-1].inputpointer=va_arg(ap,void *);
    menuitem[numofmenuitems-1].function=menutextbox;
    menuitem[numofmenuitems-1].sizey=2;
    }
  if (option==MO_FUNCTION)
    menuitem[numofmenuitems-1].function=va_arg(ap,void *);
  if (option==MO_TOGGLE)
    {
    menuitem[numofmenuitems-1].type=2;
    menuitem[numofmenuitems-1].inputpointer=va_arg(ap,void *);
    menuitem[numofmenuitems-1].function=menutoggle;
    }
  if (option==MO_SET)
    {
    menuitem[numofmenuitems-1].type=3;
    menuitem[numofmenuitems-1].inputpointer=va_arg(ap,void *);
    menuitem[numofmenuitems-1].value=va_arg(ap,int);
    menuitem[numofmenuitems-1].function=menuset;
    }
  if (option==MO_REPEAT)
    menuitem[numofmenuitems-1].repeat=1;
  if (option==MO_IMAGE)
    menuitem[numofmenuitems-1].texturenum=va_arg(ap,int);
  if (option==MO_RESIZE)
    {
    menuitem[numofmenuitems-1].x=va_arg(ap,int);
    menuitem[numofmenuitems-1].y=va_arg(ap,int);
    menuitem[numofmenuitems-1].sizex=va_arg(ap,int);
    menuitem[numofmenuitems-1].sizey=va_arg(ap,int);
    menuitem[numofmenuitems-1].textsize=1;
    if ((menuitem[numofmenuitems-1].x&TEXT_CENTER)==TEXT_CENTER)
      menuitem[numofmenuitems-1].x=menuitem[numofmenuitems-1].x-menuitem[numofmenuitems-1].sizex/2;
    if ((menuitem[numofmenuitems-1].y&TEXT_CENTER)==TEXT_CENTER)
      menuitem[numofmenuitems-1].y=menuitem[numofmenuitems-1].y-menuitem[numofmenuitems-1].sizey/2;
    if ((menuitem[numofmenuitems-1].x&TEXT_END)==TEXT_END)
      menuitem[numofmenuitems-1].x=menuitem[numofmenuitems-1].x-menuitem[numofmenuitems-1].sizex;
    if ((menuitem[numofmenuitems-1].y&TEXT_END)==TEXT_END)
      menuitem[numofmenuitems-1].y=menuitem[numofmenuitems-1].y-menuitem[numofmenuitems-1].sizey;
		menuitem[numofmenuitems-1].x&=0xFFFF;
		menuitem[numofmenuitems-1].y&=0xFFFF;
    }
  if (option==MO_CURSOR)
    menuitem[numofmenuitems-1].cursornum=va_arg(ap,int);
  if (option==MO_BACKGROUND)
    menuitem[numofmenuitems-1].background=va_arg(ap,int);

  va_end(ap);
  }

void createmenuitemempty(void)
  {
  memset(menuitem[numofmenuitems].label,0,64);
  menuitem[numofmenuitems].x=0;
  menuitem[numofmenuitems].y=0;
  menuitem[numofmenuitems].textsize=0;
  menuitem[numofmenuitems].r=0.0f;
  menuitem[numofmenuitems].g=0.0f;
  menuitem[numofmenuitems].b=0.0f;
  menuitem[numofmenuitems].type=0;
  menuitem[numofmenuitems].sizex=0;
  menuitem[numofmenuitems].sizey=0;
  menuitem[numofmenuitems].hotkey=0;
  menuitem[numofmenuitems].highlight=0;
  menuitem[numofmenuitems].value=0;
  menuitem[numofmenuitems].inputtype=0;
  menuitem[numofmenuitems].inputpointer=NULL;
  menuitem[numofmenuitems].function=NULL;
	menuitem[numofmenuitems].texturenum=-1;
  menuitem[numofmenuitems].cursornum=0;
  menuitem[numofmenuitems].background=0;
	numofmenuitems++;
  }

void resetmenuitems(void)
  {
	int count;

  joymenunum=0;

	for (count=0;count<MAXMENUITEMS;count++)
    {
		menuitem[count].active=0;
    menuitem[count].prevactive=0;
    }
  }

void setupmenuitems(void)
  {
  strcpy(keyboardlabel[SCAN_A],"A");
  strcpy(keyboardlabel[SCAN_B],"B");
  strcpy(keyboardlabel[SCAN_C],"C");
  strcpy(keyboardlabel[SCAN_D],"D");
  strcpy(keyboardlabel[SCAN_E],"E");
  strcpy(keyboardlabel[SCAN_F],"F");
  strcpy(keyboardlabel[SCAN_G],"G");
  strcpy(keyboardlabel[SCAN_H],"H");
  strcpy(keyboardlabel[SCAN_I],"I");
  strcpy(keyboardlabel[SCAN_J],"J");
  strcpy(keyboardlabel[SCAN_K],"K");
  strcpy(keyboardlabel[SCAN_L],"L");
  strcpy(keyboardlabel[SCAN_M],"M");
  strcpy(keyboardlabel[SCAN_N],"N");
  strcpy(keyboardlabel[SCAN_O],"O");
  strcpy(keyboardlabel[SCAN_P],"P");
  strcpy(keyboardlabel[SCAN_Q],"Q");
  strcpy(keyboardlabel[SCAN_R],"R");
  strcpy(keyboardlabel[SCAN_S],"S");
  strcpy(keyboardlabel[SCAN_T],"T");
  strcpy(keyboardlabel[SCAN_U],"U");
  strcpy(keyboardlabel[SCAN_V],"V");
  strcpy(keyboardlabel[SCAN_W],"W");
  strcpy(keyboardlabel[SCAN_X],"X");
  strcpy(keyboardlabel[SCAN_Y],"Y");
  strcpy(keyboardlabel[SCAN_Z],"Z");
  strcpy(keyboardlabel[SCAN_1],"1");
  strcpy(keyboardlabel[SCAN_2],"2");
  strcpy(keyboardlabel[SCAN_3],"3");
  strcpy(keyboardlabel[SCAN_4],"4");
  strcpy(keyboardlabel[SCAN_5],"5");
  strcpy(keyboardlabel[SCAN_6],"6");
  strcpy(keyboardlabel[SCAN_7],"7");
  strcpy(keyboardlabel[SCAN_8],"8");
  strcpy(keyboardlabel[SCAN_9],"9");
  strcpy(keyboardlabel[SCAN_0],"0");
#ifndef GERMAN
  strcpy(keyboardlabel[SCAN_LEFT],"€");
  strcpy(keyboardlabel[SCAN_RIGHT],"");
  strcpy(keyboardlabel[SCAN_UP],"ƒ");
  strcpy(keyboardlabel[SCAN_DOWN],"‚");
#else
  strcpy(keyboardlabel[SCAN_LEFT],"{");
  strcpy(keyboardlabel[SCAN_RIGHT],"|");
  strcpy(keyboardlabel[SCAN_UP],"~");
  strcpy(keyboardlabel[SCAN_DOWN],"}");
#endif
  strcpy(keyboardlabel[SCAN_SPACE],"Space");
  strcpy(keyboardlabel[SCAN_ENTER],"Enter");
  strcpy(keyboardlabel[SCAN_CENTER],"Center");
  strcpy(keyboardlabel[SCAN_CTRL],"Ctrl");
  strcpy(keyboardlabel[SCAN_ALT],"Alt");
  strcpy(keyboardlabel[SCAN_SHIFT],"Shift");
  strcpy(keyboardlabel[SCAN_COMMA],"Comma");
  strcpy(keyboardlabel[SCAN_PERIOD],"Period");
  strcpy(keyboardlabel[SCAN_NUMHOME],"Home");
  strcpy(keyboardlabel[SCAN_NUMPGUP],"PgUp");
  strcpy(keyboardlabel[SCAN_NUMEND],"End");
  strcpy(keyboardlabel[SCAN_NUMPGDWN],"PgDn");
  strcpy(keyboardlabel[SCAN_NUMPLUS],"Plus");
  strcpy(keyboardlabel[SCAN_NUM_MINUS],"Minus");
  strcpy(keyboardlabel[SCAN_NUMINS],"Ins");
  strcpy(keyboardlabel[SCAN_NUMDEL],"Del");

  strcpy(keyboardlabel[0],TXT_NONE);
  }

void menutextbox(void)
  {
  int count,count2,count3; 

  if (!menuitem[currentmenuitem].prevactive)
    {
		memset(menuinput,0,256);
    if (menuitem[currentmenuitem].inputtype==0)
      sprintf(menuinput,"%d",*(int*)menuitem[currentmenuitem].inputpointer);
    else if (menuitem[currentmenuitem].inputtype==1)
      sprintf(menuinput,"%u",*(unsigned int*)menuitem[currentmenuitem].inputpointer);
    else if(menuitem[currentmenuitem].inputtype==2)
      sprintf(menuinput,"%g",*(float*)menuitem[currentmenuitem].inputpointer);
		else
      strcpy(menuinput,menuitem[currentmenuitem].inputpointer);

    if (mouse.lmb)
      {
      menuinputselectpos=(mouse.x-menuitem[currentmenuitem].x)/menuitem[currentmenuitem].textsize;
      menuinputcursorpos=menuinputselectpos;
      }
    else
      {
      menuinputselectpos=0;
      menuinputcursorpos=strlen(menuinput);
      }

    if (menuinputselectpos<0)
      menuinputselectpos=0;
    if (menuinputselectpos>strlen(menuinput))
      menuinputselectpos=strlen(menuinput);
    if (menuinputcursorpos<0)
      menuinputcursorpos=0;
    if (menuinputcursorpos>strlen(menuinput))
      menuinputcursorpos=strlen(menuinput);

    count2=0xFFFFFFFF;
    }
	else
    {
    if (mouse.lmb)
      {
      if (!prevmouse.lmb)
        menuinputselectpos=(mouse.x-menuitem[currentmenuitem].x)/menuitem[currentmenuitem].textsize;
      menuinputcursorpos=(mouse.x-menuitem[currentmenuitem].x)/menuitem[currentmenuitem].textsize;

      if (menuinputselectpos<0)
        menuinputselectpos=0;
      if (menuinputselectpos>strlen(menuinput))
        menuinputselectpos=strlen(menuinput);
      if (menuinputcursorpos<0)
        menuinputcursorpos=0;
      if (menuinputcursorpos>strlen(menuinput))
        menuinputcursorpos=strlen(menuinput);
      }
    count2=getinputletter(0,0xFF);
    }
	
	if (count2!=0xFFFFFFFF)
    {
		if (count2>=32)
      {
			deleteselectedtext();
      if (strlen(menuinput)<menuitem[currentmenuitem].sizex-1)
				addmenuinputchar(count2);
      }
		
		if (count2==9)
			if (!deleteselectedtext())
        {
				count3=menuinputcursorpos;
				while (menuinput[count3]!=0)
          {
					menuinput[count3]=menuinput[count3+1];
					count3++;
          }
        }
        
		if (count2==10)
			if (!deleteselectedtext())
				if (menuinputcursorpos>0)
          {
					count3=menuinputcursorpos-1;
					while (menuinput[count3]!=0)
            {
						menuinput[count3]=menuinput[count3+1];
						count3++;
            }
					menuinputcursorpos--;
					menuinputselectpos=menuinputcursorpos;
          }
		if (count2==12)
      {
      count3=currentmenuitem+1;
      while (count3!=currentmenuitem)
        {
        if (count3>=numofmenuitems)
					count3=0;
        if (menuitem[count3].type==1)
          {
					menuitem[currentmenuitem].active=0;
					menuitem[count3].active=1;
					count3=currentmenuitem-1;
          }
				count3++;
        }
      }
		if ((keyboard[SCAN_ENTER] && !prevkeyboard[SCAN_ENTER]) || (keyboard[SCAN_ESC] && !prevkeyboard[SCAN_ESC]))
			menuitem[currentmenuitem].active=0;
    }

  if (menuitem[currentmenuitem].inputtype==0)
    sscanf(menuinput,"%d",(int *)menuitem[currentmenuitem].inputpointer);
  else if (menuitem[currentmenuitem].inputtype==1)
    sscanf(menuinput,"%u",(unsigned *)menuitem[currentmenuitem].inputpointer);
  else if (menuitem[currentmenuitem].inputtype==2)
    sscanf(menuinput,"%g",(float *)menuitem[currentmenuitem].inputpointer);
	else
    strcpy(menuitem[currentmenuitem].inputpointer,menuinput);
  }

void menutoggle(void)
  {
  *(int *)menuitem[currentmenuitem].inputpointer^=1;
  }

void menuset(void)
  {
  *(int *)menuitem[currentmenuitem].inputpointer=menuitem[currentmenuitem].value;
  }

int getinputletter(int repeat,int inputflags)
  {
	int count,count2;
	
	count=0xFFFFFFFF;
	
	if ((inputflags&1)==1)
    {
		if (keyboard[SCAN_A] && (repeat || !prevkeyboard[SCAN_A]))
			count='a';
		if (keyboard[SCAN_B] && (repeat || !prevkeyboard[SCAN_B]))
			count='b';
		if (keyboard[SCAN_C] && (repeat || !prevkeyboard[SCAN_C]))
			count='c';
		if (keyboard[SCAN_D] && (repeat || !prevkeyboard[SCAN_D]))
			count='d';
		if (keyboard[SCAN_E] && (repeat || !prevkeyboard[SCAN_E]))
			count='e';
		if (keyboard[SCAN_F] && (repeat || !prevkeyboard[SCAN_F]))
			count='f';
		if (keyboard[SCAN_G] && (repeat || !prevkeyboard[SCAN_G]))
			count='g';
		if (keyboard[SCAN_H] && (repeat || !prevkeyboard[SCAN_H]))
			count='h';
		if (keyboard[SCAN_I] && (repeat || !prevkeyboard[SCAN_I]))
			count='i';
		if (keyboard[SCAN_J] && (repeat || !prevkeyboard[SCAN_J]))
			count='j';
		if (keyboard[SCAN_K] && (repeat || !prevkeyboard[SCAN_K]))
			count='k';            
		if (keyboard[SCAN_L] && (repeat || !prevkeyboard[SCAN_L]))
			count='l';
		if (keyboard[SCAN_M] && (repeat || !prevkeyboard[SCAN_M]))
			count='m';
		if (keyboard[SCAN_N] && (repeat || !prevkeyboard[SCAN_N]))
			count='n';
		if (keyboard[SCAN_O] && (repeat || !prevkeyboard[SCAN_O]))
			count='o';
		if (keyboard[SCAN_P] && (repeat || !prevkeyboard[SCAN_P]))
			count='p';
		if (keyboard[SCAN_Q] && (repeat || !prevkeyboard[SCAN_Q]))
			count='q';
		if (keyboard[SCAN_R] && (repeat || !prevkeyboard[SCAN_R]))
			count='r';
		if (keyboard[SCAN_S] && (repeat || !prevkeyboard[SCAN_S]))
			count='s';
		if (keyboard[SCAN_T] && (repeat || !prevkeyboard[SCAN_T]))
			count='t';
		if (keyboard[SCAN_U] && (repeat || !prevkeyboard[SCAN_U]))
			count='u';
		if (keyboard[SCAN_V] && (repeat || !prevkeyboard[SCAN_V]))
			count='v';
		if (keyboard[SCAN_W] && (repeat || !prevkeyboard[SCAN_W]))
			count='w';
		if (keyboard[SCAN_X] && (repeat || !prevkeyboard[SCAN_X]))
			count='x';            
		if (keyboard[SCAN_Y] && (repeat || !prevkeyboard[SCAN_Y]))
			count='y';
		if (keyboard[SCAN_Z] && (repeat || !prevkeyboard[SCAN_Z]))
			count='z';
    if (count!=0xFFFFFFFF)
      if (keyboard[SCAN_SHIFT])
        count=toupper(count);
    }
	if ((inputflags&8)==8)
    {
		if (keyboard[SCAN_SPACE] && (repeat || !prevkeyboard[SCAN_SPACE]))
			count=' ';
    }
	if (!keyboard[SCAN_SHIFT])
    {
		if ((inputflags&2)==2)
      {
			if (keyboard[SCAN_0] && (repeat || !prevkeyboard[SCAN_0]))
				count='0';
			if (keyboard[SCAN_1] && (repeat || !prevkeyboard[SCAN_1]))
				count='1';
			if (keyboard[SCAN_2] && (repeat || !prevkeyboard[SCAN_2]))
				count='2';
			if (keyboard[SCAN_3] && (repeat || !prevkeyboard[SCAN_3]))
				count='3';
			if (keyboard[SCAN_4] && (repeat || !prevkeyboard[SCAN_4]))
				count='4';
			if (keyboard[SCAN_5] && (repeat || !prevkeyboard[SCAN_5]))
				count='5';
			if (keyboard[SCAN_6] && (repeat || !prevkeyboard[SCAN_6]))
				count='6';
			if (keyboard[SCAN_7] && (repeat || !prevkeyboard[SCAN_7]))
				count='7';
			if (keyboard[SCAN_8] && (repeat || !prevkeyboard[SCAN_8]))
				count='8';
			if (keyboard[SCAN_9] && (repeat || !prevkeyboard[SCAN_9]))
				count='9';
      }
		if ((inputflags&4)==4)
      {
			if (keyboard[SCAN_PERIOD] && (repeat || !prevkeyboard[SCAN_PERIOD]))
				count='.';
      }
		if ((inputflags&16)==16)
      {
			if (keyboard[SCAN_MINUS] && (repeat || !prevkeyboard[SCAN_MINUS]))
				count='-';
      }
		if ((inputflags&32)==32)
      {
			if (keyboard[SCAN_FOWARD_SLASH] && (repeat || !prevkeyboard[SCAN_FOWARD_SLASH]))
				count='/';
			if (keyboard[SCAN_SEMI] && (repeat || !prevkeyboard[SCAN_SEMI]))
				count=';';
			if (keyboard[SCAN_MINUS] && (repeat || !prevkeyboard[SCAN_MINUS]))
				count='-';
			if (keyboard[SCAN_EQUALS] && (repeat || !prevkeyboard[SCAN_EQUALS]))
				count='=';
			if (keyboard[SCAN_COMMA] && (repeat || !prevkeyboard[SCAN_COMMA]))
				count=',';
			if (keyboard[SCAN_BACK_SLASH] && (repeat || !prevkeyboard[SCAN_BACK_SLASH]))
				count=92;
			if (keyboard[SCAN_APOS] && (repeat || !prevkeyboard[SCAN_APOS]))
				count=39;
      }
    }
	else
    {
		if ((inputflags&32)==32)
      {
			if (keyboard[SCAN_0] && (repeat || !prevkeyboard[SCAN_0]))
				count=')';
			if (keyboard[SCAN_1] && (repeat || !prevkeyboard[SCAN_1]))
				count='!';
			if (keyboard[SCAN_2] && (repeat || !prevkeyboard[SCAN_2]))
				count='@';
			if (keyboard[SCAN_3] && (repeat || !prevkeyboard[SCAN_3]))
				count='#';
			if (keyboard[SCAN_4] && (repeat || !prevkeyboard[SCAN_4]))
				count='$';
			if (keyboard[SCAN_5] && (repeat || !prevkeyboard[SCAN_5]))
				count='%';
			if (keyboard[SCAN_6] && (repeat || !prevkeyboard[SCAN_6]))
				count='^';
			if (keyboard[SCAN_7] && (repeat || !prevkeyboard[SCAN_7]))
				count='&';
			if (keyboard[SCAN_8] && (repeat || !prevkeyboard[SCAN_8]))
				count='*';
			if (keyboard[SCAN_9] && (repeat || !prevkeyboard[SCAN_9]))
				count='(';
			if (keyboard[SCAN_FOWARD_SLASH] && (repeat || !prevkeyboard[SCAN_FOWARD_SLASH]))
				count='?';
			if (keyboard[SCAN_SEMI] && (repeat || !prevkeyboard[SCAN_SEMI]))
				count=':';
			if (keyboard[SCAN_MINUS] && (repeat || !prevkeyboard[SCAN_MINUS]))
				count='_';
			if (keyboard[SCAN_EQUALS] && (repeat || !prevkeyboard[SCAN_EQUALS]))
				count='+';
			if (keyboard[SCAN_PERIOD] && (repeat || !prevkeyboard[SCAN_PERIOD]))
				count='>';
			if (keyboard[SCAN_COMMA] && (repeat || !prevkeyboard[SCAN_COMMA]))
				count='<';
			if (keyboard[SCAN_BACK_SLASH] && (repeat || !prevkeyboard[SCAN_BACK_SLASH]))
				count='|';
			if (keyboard[SCAN_APOS] && (repeat || !prevkeyboard[SCAN_APOS]))
				count=34;
      }
    }
	if (keyboard[SCAN_NUMDEL] && (repeat || !prevkeyboard[SCAN_NUMDEL]))
		count=9;
	if (keyboard[SCAN_DELETE] && (repeat || !prevkeyboard[SCAN_DELETE]))
		count=9;
	if (keyboard[SCAN_BKSP] && (repeat || !prevkeyboard[SCAN_BKSP]))
		count=10;
	if ((keyboard[SCAN_ENTER] && !prevkeyboard[SCAN_ENTER]) || (keyboard[SCAN_ESC] && !prevkeyboard[SCAN_ESC]))
		count=11;
	if (keyboard[SCAN_TAB] && !prevkeyboard[SCAN_TAB]) 
		count=12;
	
	if (keyboard[SCAN_INSERT] && (repeat || !prevkeyboard[SCAN_INSERT]))
		menuinputinsert^=1;
	if (keyboard[SCAN_HOME] && (repeat || !prevkeyboard[SCAN_HOME]))
    {
		menuinputcursorpos=0;
		if (!keyboard[SCAN_SHIFT])
			menuinputselectpos=menuinputcursorpos;
    }
	if (keyboard[SCAN_END] && (repeat || !prevkeyboard[SCAN_END]))
    {
		menuinputcursorpos=strlen(menuinput);
		if (!keyboard[SCAN_SHIFT])
			menuinputselectpos=menuinputcursorpos;
    }
  if (keyboard[SCAN_LEFT] && (repeat || !prevkeyboard[SCAN_LEFT]))
    {
    if (menuinputcursorpos>0)
      menuinputcursorpos--;
		if (!keyboard[SCAN_SHIFT])
			menuinputselectpos=menuinputcursorpos;
    }
  if (keyboard[SCAN_RIGHT] && (repeat || !prevkeyboard[SCAN_RIGHT]))
    {
    if (menuinputcursorpos<strlen(menuinput))
      menuinputcursorpos++;
		if (!keyboard[SCAN_SHIFT])
			menuinputselectpos=menuinputcursorpos;
    }

  if (menuinputselectpos<0)
    menuinputselectpos=0;
  if (menuinputselectpos>strlen(menuinput))
    menuinputselectpos=strlen(menuinput);
  if (menuinputcursorpos<0)
    menuinputcursorpos=0;
  if (menuinputcursorpos>strlen(menuinput))
    menuinputcursorpos=strlen(menuinput);

	return(count);
  }

void addmenuinputchar(int charinput)
  {
	int count;
	
	if (menuinputcursorpos>=192)
		return;
	
	if (!menuinputinsert)
    {
		count=192;
		while (count>menuinputcursorpos)
      {
			menuinput[count]=menuinput[count-1];
			count--;
      }
    }
	menuinput[menuinputcursorpos]=charinput;
	menuinputcursorpos++;
	menuinputselectpos=menuinputcursorpos;
  }

int deleteselectedtext(void)
  {
	int count,count2;
	int textdeleted;
  int cursortemp;
	
	count2=0;
	textdeleted=0;
  cursortemp=menuinputcursorpos;
	for (count=0;count<192;count++)
    {
    if ((count>=menuinputselectpos && count<menuinputcursorpos) ||
        (count>=menuinputcursorpos && count<menuinputselectpos))
      {
      if (cursortemp>count)
        cursortemp=count;
			textdeleted=1;
      }
		else
      {
      menuinputtemp[count2]=menuinput[count];
			count2++;
      }
    }
	menuinputtemp[count2]=0;
  strcpy(menuinput,menuinputtemp);

  menuinputcursorpos=cursortemp;

  if (menuinputcursorpos>strlen(menuinput))
    menuinputcursorpos=strlen(menuinput);
	menuinputselectpos=menuinputcursorpos;
	
	return(textdeleted);
  }

