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

void edittextures(void)
  {
  int count,count2;
  int texturenum;
  float vec[3];

  loadtilesettemp();

  textureedit.texturenum=-1;

  resetmenuitems();

  while (!menuitem[0].active && !windowinfo.shutdown)
    {
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    numofmenuitems=0;
    createmenuitem(TXT_EXIT,0,0,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_HOTKEY,SCAN_ESC);

    createmenuitem(TXT_LOAD_TILESET,0,464,16,1.0f,1.0f,1.0f,1.0f);

    createmenuitem(TXT_LEVEL_NAME"     ",(640|TEXT_END),448,16,1.0f,1.0f,1.0f,1.0f);
    setmenuitem(MO_STRINGINPUT,textureedit.filename);
    setmenuitem(MO_HOTKEY,SCAN_ENTER);

    checksystemmessages();
    checkkeyboard();
    checkmouse();
    checkmenuitems();

    setuptextdisplay();

    for (count=0;count<32;count++)
      {
      glBindTexture(GL_TEXTURE_2D,texture[count+textureedit.pagenum*32].glname);

      glBegin(GL_QUADS);

      vec[0]=(count&7)*64+4;
      vec[1]=16+4+(count>>3)*64;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=(count&7)*64+60;
      vec[1]=16+4+(count>>3)*64;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=(count&7)*64+60;
      vec[1]=16+60+(count>>3)*64;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=(count&7)*64+4;
      vec[1]=16+60+(count>>3)*64;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      glEnd();
      }
    for (count=0;count<16;count++)
      {
      glBindTexture(GL_TEXTURE_2D,texture[1792+count+textureedit.tilepagenum*16].glname);

      glBegin(GL_QUADS);

      vec[0]=(count&7)*64+4;
      vec[1]=320+4+(count>>3)*64;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=(count&7)*64+60;
      vec[1]=320+4+(count>>3)*64;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=(count&7)*64+60;
      vec[1]=320+60+(count>>3)*64;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=(count&7)*64+4;
      vec[1]=320+60+(count>>3)*64;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      glEnd();
      }

    if (textureedit.texturenum!=-1)
      {
      glBindTexture(GL_TEXTURE_2D,texture[textureedit.texturenum].glname);

      glBegin(GL_QUADS);

      vec[0]=mouse.x-28;
      vec[1]=mouse.y-28;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(0.0f,0.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=mouse.x+28;
      vec[1]=mouse.y-28;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(1.0f,0.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=mouse.x+28;
      vec[1]=mouse.y+28;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(1.0f,1.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      vec[0]=mouse.x-28;
      vec[1]=mouse.y+28;
      convertscreenvertex(vec,640,480);
      glTexCoord2f(0.0f,1.0f);
      glVertex3f(vec[0],vec[1],-1.0f);

      glEnd();
      }

    drawtext(TXT_TILESET":/i",0,292,16,1.0f,1.0f,1.0f,1.0f,textureedit.tileset);

    drawmenuitems();

    drawmousecursor(768+font.cursornum,mouse.x,mouse.y,16,1.0f,1.0f,1.0f,1.0f);

    SDL_GL_SwapBuffers();

    if (keyboard[SCAN_LFT_BRACKET] && !prevkeyboard[SCAN_LFT_BRACKET])
    if (textureedit.tileset>0)
      {
      textureedit.tileset--;
      loadtilesettemp();
      }
    if (keyboard[SCAN_RGT_BRACKET] && !prevkeyboard[SCAN_RGT_BRACKET])
    if (textureedit.tileset<7)
      {
      textureedit.tileset++;
      loadtilesettemp();
      }

    if (keyboard[SCAN_Q] && !prevkeyboard[SCAN_Q])
    if (textureedit.pagenum<7)
      textureedit.pagenum++;
    if (keyboard[SCAN_Z] && !prevkeyboard[SCAN_Z])
    if (textureedit.pagenum>0)
      textureedit.pagenum--;
    if (keyboard[SCAN_W] && !prevkeyboard[SCAN_W])
    if (textureedit.tilepagenum<15)
      textureedit.tilepagenum++;
    if (keyboard[SCAN_X] && !prevkeyboard[SCAN_X])
    if (textureedit.tilepagenum>0)
      textureedit.tilepagenum--;

    if (mouse.lmb && !prevmouse.lmb)
      {
      textureedit.texturenum=-1;

      for (count=0;count<32;count++)
      if (mouse.x>=(count&7)*64+4 && mouse.x<(count&7)*64+60)
      if (mouse.y>=16+4+(count>>3)*64 && mouse.y<16+60+(count>>3)*64)
        textureedit.texturenum=count+textureedit.pagenum*32;

      for (count=0;count<16;count++)
      if (mouse.x>=(count&7)*64+4 && mouse.x<(count&7)*64+60)
      if (mouse.y>=320+4+(count>>3)*64 && mouse.y<320+60+(count>>3)*64)
        textureedit.texturenum=1792+count+textureedit.tilepagenum*16;
      }
    if (!mouse.lmb && prevmouse.lmb)
      {
      texturenum=-1;

      for (count=0;count<32;count++)
      if (mouse.x>=(count&7)*64+4 && mouse.x<(count&7)*64+60)
      if (mouse.y>=16+4+(count>>3)*64 && mouse.y<16+60+(count>>3)*64)
        texturenum=count+textureedit.pagenum*32;

      for (count=0;count<16;count++)
      if (mouse.x>=(count&7)*64+4 && mouse.x<(count&7)*64+60)
      if (mouse.y>=320+4+(count>>3)*64 && mouse.y<320+60+(count>>3)*64)
        texturenum=1792+count+textureedit.tilepagenum*16;

      if (textureedit.texturenum!=-1)
      if (texturenum!=-1)
      if (texturenum!=textureedit.texturenum)
      if (texturenum<256)
        copytexture(texturenum,textureedit.texturenum);

      if (texturenum<256)
        editor.blocknum=texturenum;

      textureedit.texturenum=-1;
      }
    if (menuitem[1].active)
      {
      loadleveltiles(textureedit.filename);

      menuitem[1].active=0;
      }
    }

  resetmenuitems();
  }

void copytexture(int texturenum,int oldtexturenum)
  {
  int mipmaplevel;
  int count,count2;
  /*
  if (!glIsTexture(texture[texturenum].glname))
    glGenTextures(1,&texture[texturenum].glname);

  glBindTexture(GL_TEXTURE_2D,texture[texturenum].glname);
  */
  texture[texturenum].sizex=texture[oldtexturenum].sizex;
  texture[texturenum].sizey=texture[oldtexturenum].sizey;
  texture[texturenum].mipmaplevels=texture[oldtexturenum].mipmaplevels;
  texture[texturenum].format=texture[oldtexturenum].format;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=texture[oldtexturenum].wraps;
  texture[texturenum].wrapt=texture[oldtexturenum].wrapt;
  texture[texturenum].magfilter=texture[oldtexturenum].magfilter;
  texture[texturenum].minfilter=texture[oldtexturenum].minfilter;

  for (mipmaplevel=0;mipmaplevel<texture[texturenum].mipmaplevels;mipmaplevel++)
    {
    free(texture[texturenum].rgba[mipmaplevel]);
    texture[texturenum].rgba[mipmaplevel]=(unsigned int *) malloc((texture[texturenum].sizex>>mipmaplevel)*(texture[texturenum].sizey>>mipmaplevel)*4);

    for (count=0;count<(texture[texturenum].sizey>>mipmaplevel);count++)
    for (count2=0;count2<(texture[texturenum].sizex>>mipmaplevel);count2++)
      texture[texturenum].rgba[mipmaplevel][count*(texture[texturenum].sizex>>mipmaplevel)+count2]=texture[oldtexturenum].rgba[mipmaplevel][count*(texture[oldtexturenum].sizex>>mipmaplevel)+count2];
    }

  setuptexture(texturenum);
  }

void loadtilesettemp(void)
  {
  int count;
  int changeddir;
  char texfilename[13]="text000.tga";

  changeddir=1;

  if (textureedit.tileset==0)
    changeddir=chdir("tile01");
  if (textureedit.tileset==1)
    changeddir=chdir("tile02");
  if (textureedit.tileset==2)
    changeddir=chdir("tile03");
  if (textureedit.tileset==3)
    changeddir=chdir("tile04");
  if (textureedit.tileset==4)
    changeddir=chdir("tile05");
  if (textureedit.tileset==5)
    changeddir=chdir("tile06");
  if (textureedit.tileset==6)
    changeddir=chdir("tile07");
  if (textureedit.tileset==7)
    changeddir=chdir("tile08");

  for (count=0;count<256;count++)
    {
    texfilename[4]=48+(count/100)%10;
    texfilename[5]=48+(count/10)%10;
    texfilename[6]=48+count%10;
    if (game.levelnum!=6)
      loadtexturetga(count+1792,texfilename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
    else
      loadtexturetga(count+1792,texfilename,0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_NEAREST,GL_NEAREST);
    }

  if (changeddir==0)
    chdir("..");
  }

void loadleveltiles(char *filename)
  {
  int count,count2;
  int changeddir;
  int version;
  unsigned int x,y;

  x=0x17AF2E03;
  changeddir=chdir("level");

  if ((fp=fopen(filename,"rb"))!=NULL)
    {
    fread2(&version,4,1,fp);

    if (version==9)
      {
      fread2(cryptdata,1,32,fp);
      fread2(cryptdata,4,1,fp);
      fread2(cryptdata,4,1,fp);
      fread2(cryptdata,4,1,fp);
      fread2(cryptdata,4,64*4,fp);

      fread2(cryptdata,1,256*256,fp);

      fread2(cryptdata,1,256*256,fp);

      fread2(cryptdata,1,256*256,fp);

      fread2(cryptdata,4,3,fp);
      fread2(cryptdata,4,12,fp);

      fread2(&count2,4,1,fp);
      if (count2<0 || count2>=256)
        {
        fclose(fp);
        if (changeddir==0)
          chdir("..");
        return;
        }

      for (count=0;count<count2;count++)
        {
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,3,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,2,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,3,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        }
      fread2(&count2,4,1,fp);
      if (count2<0 || count2>=1024)
        {
        fclose(fp);
        if (changeddir==0)
          chdir("..");
        return;
        }
      for (count=0;count<count2;count++)
        {
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        }
      for (count=1;count<251;count++)
        {
        fread2(&texture[count].sizex,4,1,fp);
        if (texture[count].sizex<0 || texture[count].sizex>=1024)
          {
          fclose(fp);
          if (changeddir==0)
            chdir("..");
          return;
          }
        if (texture[count].sizex!=0)
          {
          fread2(&texture[count].sizey,4,1,fp);
          fread2(&texture[count].magfilter,4,1,fp);
          fread2(&texture[count].minfilter,4,1,fp);
          free(texture[count].rgba[0]);
          texture[count].rgba[0]=(unsigned int *) malloc(texture[count].sizex*texture[count].sizey*4);
          fread(texture[count].rgba[0],4,texture[count].sizex*texture[count].sizey,fp);
          memcpy(cryptdata,texture[count].rgba[0],4*texture[count].sizex*texture[count].sizey);
          decryptdata(x,4*texture[count].sizex*texture[count].sizey/4);
          memcpy(texture[count].rgba[0],cryptdata,4*texture[count].sizex*texture[count].sizey);

          texture[count].mipmaplevels=1;
          texture[count].format=GL_RGBA;
          texture[count].alphamap=0;
          texture[count].normalmap=0;
          texture[count].glossmap=0;
          texture[count].wraps=GL_CLAMP_TO_EDGE;
          texture[count].wrapt=GL_CLAMP_TO_EDGE;
          texture[count].magfilter=GL_LINEAR;
          texture[count].minfilter=GL_LINEAR;

          if ((texture[count].sizex&(texture[count].sizex-1))==0)
          if ((texture[count].sizey&(texture[count].sizey-1))==0)
            setuptexture(count);
          }
  
        fread2(&block[count].numoflines,4,1,fp);
        if (block[count].numoflines<0 || block[count].numoflines>=64)
          {
          fclose(fp);
          if (changeddir==0)
            chdir("..");
          return;
          }
        for (count2=0;count2<block[count].numoflines;count2++)
          fread2(block[count].line[count2],4,8,fp);
        fread2(&block[count].friction,4,1,fp);
        fread2(&block[count].breakpoint,4,1,fp);
        fread2(&block[count].middamage,4,1,fp);
        fread2(&block[count].foredamage,4,1,fp);
        fread2(&block[count].density,4,1,fp);
        fread2(&block[count].drag,4,1,fp);
        fread2(&block[count].animation,4,1,fp);
        fread2(&block[count].animationspeed,4,1,fp);
        }
      }

    if (version==10)
      {
      fread2(cryptdata,1,32,fp);
      fread2(cryptdata,4,1,fp);
      fread2(cryptdata,4,1,fp);
      fread2(cryptdata,4,1,fp);
      fread2(cryptdata,4,64*4,fp);

      fread2(cryptdata,1,256*256,fp);

      fread2(cryptdata,1,256*256,fp);

      fread2(cryptdata,1,256*256,fp);

      fread2(cryptdata,4,3,fp);
      fread2(cryptdata,4,12,fp);

      fread2(&count2,4,1,fp);
      if (count2<0 || count2>=256)
        {
        fclose(fp);
        if (changeddir==0)
          chdir("..");
        return;
        }

      for (count=0;count<count2;count++)
        {
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,3,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,2,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,3,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        }
      fread2(&count2,4,1,fp);
      if (count2<0 || count2>=1024)
        {
        fclose(fp);
        if (changeddir==0)
          chdir("..");
        return;
        }
      for (count=0;count<count2;count++)
        {
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        fread2(cryptdata,4,1,fp);
        }
      for (count=1;count<251;count++)
        {
        fread2(&texture[count].sizex,4,1,fp);
        if (texture[count].sizex<0 || texture[count].sizex>=1024)
          {
          fclose(fp);
          if (changeddir==0)
            chdir("..");
          return;
          }
        if (texture[count].sizex!=0)
          {
          fread2(&texture[count].sizey,4,1,fp);
          fread2(&texture[count].magfilter,4,1,fp);
          fread2(&texture[count].minfilter,4,1,fp);
          free(texture[count].rgba[0]);
          texture[count].rgba[0]=(unsigned int *) malloc(texture[count].sizex*texture[count].sizey*4);
          fread(texture[count].rgba[0],4,texture[count].sizex*texture[count].sizey,fp);

          texture[count].mipmaplevels=1;
          texture[count].format=GL_RGBA;
          texture[count].alphamap=0;
          texture[count].normalmap=0;
          texture[count].glossmap=0;
          texture[count].wraps=GL_CLAMP_TO_EDGE;
          texture[count].wrapt=GL_CLAMP_TO_EDGE;
          texture[count].magfilter=GL_LINEAR;
          texture[count].minfilter=GL_LINEAR;

          if ((texture[count].sizex&(texture[count].sizex-1))==0)
          if ((texture[count].sizey&(texture[count].sizey-1))==0)
            setuptexture(count);
          }
  
        fread2(&block[count].numoflines,4,1,fp);
        if (block[count].numoflines<0 || block[count].numoflines>=64)
          {
          fclose(fp);
          if (changeddir==0)
            chdir("..");
          return;
          }
        for (count2=0;count2<block[count].numoflines;count2++)
          fread2(block[count].line[count2],4,8,fp);
        fread2(&block[count].friction,4,1,fp);
        fread2(&block[count].breakpoint,4,1,fp);
        fread2(&block[count].middamage,4,1,fp);
        fread2(&block[count].foredamage,4,1,fp);
        fread2(&block[count].density,4,1,fp);
        fread2(&block[count].drag,4,1,fp);
        fread2(&block[count].animation,4,1,fp);
        fread2(&block[count].animationspeed,4,1,fp);
        }
      }

    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");

  loadtexturetga(251,"oneup.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexturetga(252,"tarball.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexturetga(253,"amber1.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexturetga(254,"amber2.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  loadtexturetga(255,"amber3.tga",0,GL_CLAMP_TO_EDGE,GL_CLAMP_TO_EDGE,GL_LINEAR,GL_LINEAR);
  }
