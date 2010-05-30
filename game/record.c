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

void recordframe(void)
  {
  int count,count2;
  int changeddir;
  char filename[16]="gish0000.bmp";
  short bmpheader[27]={19778,4150,14,0,0,54,0,40,0,480,0,272,0,1,24,0,0,4096,14,0,0,0,0,0,0,0};
  int red,green,blue;
  unsigned char bytetemp;
  short shorttemp;
  int inttemp;

  glReadBuffer(GL_BACK);
  glReadPixels(0,0,windowinfo.resolutionx,windowinfo.resolutiony,GL_RGBA,GL_UNSIGNED_BYTE,screenshotbuffer);

  filename[4]=48+(movie.framenum/1000)%10;
  filename[5]=48+(movie.framenum/100)%10;
  filename[6]=48+(movie.framenum/10)%10;
  filename[7]=48+movie.framenum%10;

  changeddir=chdir("movie");

  if((fp=fopen(filename,"wb"))!=NULL)
    {
    /*
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
    */
    fwrite(bmpheader,27,2,fp);

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

  if (changeddir==0)
    chdir("..");

  movie.framenum++;
  }
