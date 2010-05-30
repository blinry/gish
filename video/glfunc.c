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

void setupperspectiveviewport(int viewportx,int viewporty,int viewportwidth,int viewportheight,float nearplane,float farplane)
  {
  float heightwidthratio;

  heightwidthratio=(float)viewportheight/(float)viewportwidth;

  viewporty=font.sizey-(viewporty+viewportheight);
  viewportx=viewportx*windowinfo.resolutionx/font.sizex;
  viewportwidth=viewportwidth*windowinfo.resolutionx/font.sizex;
  viewporty=viewporty*windowinfo.resolutiony/font.sizey;
  viewportheight=viewportheight*windowinfo.resolutiony/font.sizey;
  glViewport(viewportx,viewporty,viewportwidth,viewportheight);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0*nearplane,1.0*nearplane,-heightwidthratio*nearplane,heightwidthratio*nearplane,nearplane,farplane);

  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  }

void setuporthoviewport(int viewportx,int viewporty,int viewportwidth,int viewportheight,float width,float height,float length)
  {
  viewporty=font.sizey-(viewporty+viewportheight);
  viewportx=viewportx*windowinfo.resolutionx/font.sizex;
  viewportwidth=viewportwidth*windowinfo.resolutionx/font.sizex;
  viewporty=viewporty*windowinfo.resolutiony/font.sizey;
  viewportheight=viewportheight*windowinfo.resolutiony/font.sizey;
  glViewport(viewportx,viewporty,viewportwidth,viewportheight);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-width,width,-height,height,-length,length);

  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  }

void setupviewpoint(float *position,float orientation[3][3])
  {
  float m[4][4];

  glMatrixMode(GL_MODELVIEW);

  if (orientation!=NULL)
    {
    m[0][0]=orientation[0][0];
    m[1][0]=orientation[0][1];
    m[2][0]=orientation[0][2];
    m[3][0]=0;
    m[0][1]=orientation[1][0];
    m[1][1]=orientation[1][1];
    m[2][1]=orientation[1][2];
    m[3][1]=0;
    m[0][2]=orientation[2][0];
    m[1][2]=orientation[2][1];
    m[2][2]=orientation[2][2];
    m[3][2]=0;
    m[0][3]=0;
    m[1][3]=0;
    m[2][3]=0;
    m[3][3]=1;
    glMultMatrixf((float *)m);
    }
  if (position!=NULL)
    glTranslatef(-position[0],-position[1],-position[2]);
  }

void setupobjectrender(float *position,float orientation[3][3])
  {
  float m[4][4];

  glMatrixMode(GL_MODELVIEW);

  if (position!=NULL)
    glTranslatef(position[0],position[1],position[2]);
  if (orientation!=NULL)
    {
    m[0][0]=orientation[0][0];
    m[0][1]=orientation[0][1];
    m[0][2]=orientation[0][2];
    m[0][3]=0;
    m[1][0]=orientation[1][0];
    m[1][1]=orientation[1][1];
    m[1][2]=orientation[1][2];
    m[1][3]=0;
    m[2][0]=orientation[2][0];
    m[2][1]=orientation[2][1];
    m[2][2]=orientation[2][2];
    m[2][3]=0;
    m[3][0]=0;
    m[3][1]=0;
    m[3][2]=0;
    m[3][3]=1;

    glMultMatrixf((float *)m);
    }
  }

void screenshot(void)
  {
  int count,count2;
  char filename[16]="scsht000.tga";
  int red,green,blue;
  unsigned char bytetemp;
  short shorttemp;
  int inttemp;

  glReadBuffer(GL_BACK);
  glReadPixels(0,0,windowinfo.resolutionx,windowinfo.resolutiony,GL_RGBA,GL_UNSIGNED_BYTE,screenshotbuffer);

  count=0;

  while ((fp=fopen(filename,"rb"))!=NULL && count<1000) 
    {
    count++;
    filename[5]=48+count/100;
    filename[6]=48+(count/10)%10;
    filename[7]=48+count%10;
    fclose(fp);
    }

  if((fp=fopen(filename,"wb"))!=NULL)
    {
    bytetemp=0;
    fwrite(&bytetemp,1,1,fp);
    bytetemp=0;
    fwrite(&bytetemp,1,1,fp);
    bytetemp=2;
    fwrite(&bytetemp,1,1,fp);

    shorttemp=0;
    fwrite(&shorttemp,2,1,fp);
    shorttemp=0;
    fwrite(&shorttemp,2,1,fp);
    bytetemp=0;
    fwrite(&bytetemp,1,1,fp);
    shorttemp=0;
    fwrite(&shorttemp,2,1,fp);
    shorttemp=0;
    fwrite(&shorttemp,2,1,fp);

    shorttemp=windowinfo.resolutionx;
    fwrite(&shorttemp,2,1,fp);
    shorttemp=windowinfo.resolutiony;
    fwrite(&shorttemp,2,1,fp);
    bytetemp=24;
    fwrite(&bytetemp,1,1,fp);
    bytetemp=0;
    fwrite(&bytetemp,1,1,fp);

    for (count=0;count<windowinfo.resolutiony;count++)
      {
      for (count2=0;count2<windowinfo.resolutionx;count2++)
        {
        red=screenshotbuffer[count*windowinfo.resolutionx+count2]&0xFF;
        green=(screenshotbuffer[count*windowinfo.resolutionx+count2]>>8)&0xFF;
        blue=(screenshotbuffer[count*windowinfo.resolutionx+count2]>>16)&0xFF;
        fputc(blue,fp); 
        fputc(green,fp); 
        fputc(red,fp); 
        }
      }
    fclose(fp);
    }
  }
