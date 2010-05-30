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

void loadconfig(void)
  {
  int count,count2;
  char tempstr[32];

  config.resolutionx=800;
  config.resolutiony=600;
  config.bitsperpixel=32;
  config.depthbits=24;
  config.stencilbits=8;
  config.fullscreen=0;
  config.sound=1;
  config.music=1;
  config.joystick=1;

  option.sound=1;
  option.music=1;
  option.soundvolume=1.0f;
  option.musicvolume=1.0f;

  control[0].key[0]=SCAN_LEFT;
  control[0].key[1]=SCAN_RIGHT;
  control[0].key[2]=SCAN_DOWN;
  control[0].key[3]=SCAN_UP;
  control[0].key[4]=SCAN_A;
  control[0].key[5]=SCAN_SPACE;
  control[0].key[6]=SCAN_S;
  control[0].key[7]=SCAN_D;
  control[0].joysticknum=0;
  control[0].axis[0]=0;
  control[0].axis[1]=1;
  for (count=0;count<4;count++)
    control[0].button[count]=-1;
  for (count=0;count<4;count++)
    control[0].button[count+4]=count;
  control[0].button[8]=5;

  control[1].joysticknum=-1;
  control[1].axis[0]=0;
  control[1].axis[1]=1;
  for (count=0;count<4;count++)
    control[1].button[count]=-1;
  for (count=0;count<4;count++)
    control[1].button[count+4]=count;

  control[2].joysticknum=-1;
  control[2].axis[0]=0;
  control[2].axis[1]=1;
  for (count=0;count<4;count++)
    control[2].button[count]=-1;
  for (count=0;count<4;count++)
    control[2].button[count+4]=count;

  control[3].joysticknum=-1;
  control[3].axis[0]=0;
  control[3].axis[1]=1;
  for (count=0;count<4;count++)
    control[3].button[count]=-1;
  for (count=0;count<4;count++)
    control[3].button[count+4]=count;

  loadtextfile("config.txt");
  optionreadint(&config.resolutionx,"screenwidth=");
  optionreadint(&config.resolutiony,"screenheight=");
  optionreadint(&config.bitsperpixel,"bitsperpixel=");
  optionreadint(&config.depthbits,"depthbits=");
  optionreadint(&config.stencilbits,"stencilbits=");
  optionreadint(&config.fullscreen,"fullscreen=");
  optionreadint(&config.sound,"sound=");
  optionreadint(&config.music,"music=");
  optionreadint(&config.joystick,"joystick=");

  optionreadint(&option.sound,"soundon=");
  optionreadint(&option.music,"musicon=");
  count=-1;
  optionreadint(&count,"soundvolume=");
  if (count!=-1)
    option.soundvolume=(float)count/100.0f;
  count=-1;
  optionreadint(&count,"musicvolume=");
  if (count!=-1)
    option.musicvolume=(float)count/100.0f;

  for (count=0;count<4;count++)
    {
    for (count2=0;count2<16;count2++)
      {
      sprintf(tempstr,"player%dkey%d=",count+1,count2+1);
      optionreadint(&control[count].key[count2],tempstr);
      }

    sprintf(tempstr,"player%djoysticknum=",count+1);
    optionreadint(&control[count].joysticknum,tempstr);

    for (count2=0;count2<4;count2++)
      {
      sprintf(tempstr,"player%daxis%d=",count+1,count2+1);
      optionreadint(&control[count].axis[count2],tempstr);
      }
    for (count2=0;count2<16;count2++)
      {
      sprintf(tempstr,"player%dbutton%d=",count+1,count2+1);
      optionreadint(&control[count].button[count2],tempstr);
      }
    }

  windowinfo.resolutionx=config.resolutionx;
  windowinfo.resolutiony=config.resolutiony;
  windowinfo.bitsperpixel=config.bitsperpixel;
  windowinfo.depthbits=config.depthbits;
  windowinfo.stencilbits=config.stencilbits;
  windowinfo.fullscreen=config.fullscreen;
  }

void saveconfig(void)
  {
  int count,count2;
  char tempstr[32];

  config.resolutionx=windowinfo.resolutionx;
  config.resolutiony=windowinfo.resolutiony;
  config.bitsperpixel=windowinfo.bitsperpixel;
  config.depthbits=windowinfo.depthbits;
  config.stencilbits=windowinfo.stencilbits;
  config.fullscreen=windowinfo.fullscreen;

  if ((fp=fopen("config.txt","wb"))==NULL)
    return;

  optionwriteint(&config.resolutionx,"screenwidth=");
  optionwriteint(&config.resolutiony,"screenheight=");
  optionwriteint(&config.bitsperpixel,"bitsperpixel=");
  optionwriteint(&config.depthbits,"depthbits=");
  optionwriteint(&config.stencilbits,"stencilbits=");
  optionwriteint(&config.fullscreen,"fullscreen=");
  optionwriteint(&config.sound,"sound=");
  optionwriteint(&config.music,"music=");
  optionwriteint(&config.joystick,"joystick=");

  optionwriteint(&option.sound,"soundon=");
  optionwriteint(&option.music,"musicon=");
  count=option.soundvolume*100.0f;
  optionwriteint(&count,"soundvolume=");
  count=option.musicvolume*100.0f;
  optionwriteint(&count,"musicvolume=");

  for (count=0;count<4;count++)
    {
    for (count2=0;count2<16;count2++)
      {
      sprintf(tempstr,"player%dkey%d=",count+1,count2+1);
      optionwriteint(&control[count].key[count2],tempstr);
      }

    sprintf(tempstr,"player%djoysticknum=",count+1);
    optionwriteint(&control[count].joysticknum,tempstr);

    for (count2=0;count2<4;count2++)
      {
      sprintf(tempstr,"player%daxis%d=",count+1,count2+1);
      optionwriteint(&control[count].axis[count2],tempstr);
      }
    for (count2=0;count2<16;count2++)
      {
      sprintf(tempstr,"player%dbutton%d=",count+1,count2+1);
      optionwriteint(&control[count].button[count2],tempstr);
      }
    }

  fclose(fp);
  }

void notsupportedmenu(void)
  {
  int count;
  char *glvendor;
  char *glrenderer;
  char *glversion;
  char *ext;

  glvendor=(char *) glGetString(GL_VENDOR);
  glrenderer=(char *) glGetString(GL_RENDERER);
  glversion=(char *) glGetString(GL_VERSION);
  ext=(char *) glGetString(GL_EXTENSIONS);

  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem("Exit",8,8,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);
    count=352;
    createmenuitem("NVIDIA Drivers",(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;
    createmenuitem("ATI Drivers",(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;
    createmenuitem("Intel Drivers",(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkmenuitems();

    setuptextdisplay();

    count=224;
    drawtext("Multitexture required",(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;
    count+=16;
    drawtext("Make sure you have the",(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;
    drawtext("latest video card drivers",(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;
    drawtext("for your computer",(320|TEXT_CENTER),count,16,1.0f,1.0f,1.0f,1.0f);
    count+=16;

    count=432;
    drawtext("GL_VERSION: /s",8,count,12,1.0f,1.0f,1.0f,1.0f,glversion);
    count+=12;
    drawtext("GL_VENDOR: /s",8,count,12,1.0f,1.0f,1.0f,1.0f,glvendor);
    count+=12;
    drawtext("GL_RENDERER: /s",8,count,12,1.0f,1.0f,1.0f,1.0f,glrenderer);
    count+=12;

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (menuitem[1].active)
      {
      launchwebpage("www.nvidia.com/content/drivers/drivers.asp");
      menuitem[1].active=0;
      }
    if (menuitem[2].active)
      {
      launchwebpage("ati.amd.com/support/driver.html");
      menuitem[2].active=0;
      }
    if (menuitem[3].active)
      {
      launchwebpage("downloadcenter.intel.com");
      menuitem[3].active=0;
      }
    }

  resetmenuitems();

  if ((fp=fopen("glreport.txt","wb"))==NULL)
    return;

  fprintf(fp,"%s\r\n",glversion);
  fprintf(fp,"%s\r\n",glvendor);
  fprintf(fp,"%s\r\n",glrenderer);
  fprintf(fp,"%s\r\n",ext);
  }

void optionreadint(int *ptr,char *str)
  {
  if (findstring(str))
    *ptr=getint();

  parser.textloc=0;
  }

void optionwriteint(int *ptr,char *str)
  {
  fprintf(fp,"%s%d\r\n",str,*ptr);
  }

void optionreadstring(char *ptr,char *str,int size)
  {
  if (findstring(str))
    getstring(ptr,size);

  parser.textloc=0;
  }

void optionwritestring(char *ptr,char *str,int size)
  {
  fprintf(fp,"%s%s\r\n",str,ptr);
  }

