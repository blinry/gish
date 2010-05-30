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

void loadtexturetga(int texturenum,char *filename,int mipmap,int wraps,int wrapt,int magfilter,int minfilter)
  {
  int count,count2;
	int red,green,blue,alpha;
  int changeddir;
  unsigned char origin;

  changeddir=chdir("texture");

  if ((fp=fopen(filename,"rb"))==NULL)
    {
    if (debugit)
      printf("Texture Load Failed: %d\n",texturenum);

    if (changeddir==0)
      chdir("..");
    return;
    }

  fseek(fp,2,SEEK_CUR);
  fread2(&tgaheader.imagetypecode,1,1,fp);
  if (tgaheader.imagetypecode!=2 && tgaheader.imagetypecode!=3)
    {
    if (debugit)
      printf("Texture Bad Format: %d\n",texturenum);

    fclose(fp);

    if (changeddir==0)
      chdir("..");
    return;
    }

  fseek(fp,9,SEEK_CUR);
  fread2(&tgaheader.imagewidth,2,1,fp);
  fread2(&tgaheader.imageheight,2,1,fp);
  fread2(&tgaheader.pixeldepth,1,1,fp);
  fread2(&origin,1,1,fp);
  origin=(origin>>4)&3;

  texture[texturenum].isalpha=0;

  for (count=0;count<tgaheader.imageheight;count++)
  for (count2=0;count2<tgaheader.imagewidth;count2++)
    {
    blue=fgetc(fp);
    green=fgetc(fp);
    red=fgetc(fp);
    if (tgaheader.pixeldepth==32)
      alpha=fgetc(fp);
    else
      alpha=255;

    if (alpha!=255)
      texture[texturenum].isalpha=1;

    if (!bigendian)
      {
      if (origin==0)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==1)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==2)
        tgaheader.imagedata[count*tgaheader.imagewidth+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==3)
        tgaheader.imagedata[count*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      }
    else
      {
      if (origin==0)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+count2]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==1)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==2)
        tgaheader.imagedata[count*tgaheader.imagewidth+count2]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==3)
        tgaheader.imagedata[count*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      }
    }

  fclose(fp);

  if (changeddir==0)
    chdir("..");

  if ((tgaheader.imagewidth&(tgaheader.imagewidth-1))!=0)
    return;
  if ((tgaheader.imageheight&(tgaheader.imageheight-1))!=0)
    return;

  texture[texturenum].sizex=tgaheader.imagewidth;
  texture[texturenum].sizey=tgaheader.imageheight;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_RGBA;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=wraps;
  texture[texturenum].wrapt=wrapt;
  texture[texturenum].magfilter=magfilter;
  texture[texturenum].minfilter=minfilter;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  for (count=0;count<texture[texturenum].sizey;count++)
  for (count2=0;count2<texture[texturenum].sizex;count2++)
    {
    texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]=tgaheader.imagedata[count*tgaheader.imagewidth+count2];

    if (!bigendian)
      {
      if ((texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]>>24)!=255)
        texture[texturenum].alphamap=1;
      }
    else
      {
      if ((texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]&255)!=255)
        texture[texturenum].alphamap=1;
      }
    }

  if (mipmap)
    generatemipmap(texturenum);
  setuptexture(texturenum);
  }

void loadtexturetganodir(int texturenum,char *filename,int mipmap,int wraps,int wrapt,int magfilter,int minfilter)
  {
  int count,count2;
	int red,green,blue,alpha;
  unsigned char origin;

  if ((fp=fopen(filename,"rb"))==NULL)
    {
    if (debugit)
      printf("Texture Load Failed: %d\n",texturenum);

    return;
    }

  fseek(fp,2,SEEK_CUR);
  fread2(&tgaheader.imagetypecode,1,1,fp);
  if (tgaheader.imagetypecode!=2 && tgaheader.imagetypecode!=3)
    {
    if (debugit)
      printf("Texture Bad Format: %d\n",texturenum);

    fclose(fp);

    return;
    }

  fseek(fp,9,SEEK_CUR);
  fread2(&tgaheader.imagewidth,2,1,fp);
  fread2(&tgaheader.imageheight,2,1,fp);
  fread2(&tgaheader.pixeldepth,1,1,fp);
  fread2(&origin,1,1,fp);
  origin=(origin>>4)&3;

  texture[texturenum].isalpha=0;

  for (count=0;count<tgaheader.imageheight;count++)
  for (count2=0;count2<tgaheader.imagewidth;count2++)
    {
    blue=fgetc(fp);
    green=fgetc(fp);
    red=fgetc(fp);
    if (tgaheader.pixeldepth==32)
      alpha=fgetc(fp);
    else
      alpha=255;

    if (alpha!=255)
      texture[texturenum].isalpha=1;

    if (!bigendian)
      {
      if (origin==0)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==1)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==2)
        tgaheader.imagedata[count*tgaheader.imagewidth+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==3)
        tgaheader.imagedata[count*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      }
    else
      {
      if (origin==0)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+count2]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==1)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==2)
        tgaheader.imagedata[count*tgaheader.imagewidth+count2]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==3)
        tgaheader.imagedata[count*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      }
    }

  fclose(fp);

  if ((tgaheader.imagewidth&(tgaheader.imagewidth-1))!=0)
    return;
  if ((tgaheader.imageheight&(tgaheader.imageheight-1))!=0)
    return;

  texture[texturenum].sizex=tgaheader.imagewidth;
  texture[texturenum].sizey=tgaheader.imageheight;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_RGBA;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=wraps;
  texture[texturenum].wrapt=wrapt;
  texture[texturenum].magfilter=magfilter;
  texture[texturenum].minfilter=minfilter;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  for (count=0;count<texture[texturenum].sizey;count++)
  for (count2=0;count2<texture[texturenum].sizex;count2++)
    {
    texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]=tgaheader.imagedata[count*tgaheader.imagewidth+count2];
    if (!bigendian)
      {
      if ((texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]>>24)!=255)
        texture[texturenum].alphamap=1;
      }
    else
      {
      if ((texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]&255)!=255)
        texture[texturenum].alphamap=1;
      }
    }

  if (mipmap)
    generatemipmap(texturenum);
  setuptexture(texturenum);
  }

void loadtexturetgapartial(int texturenum,char *filename,int startx,int starty,int sizex,int sizey)
  {
  int count,count2;
	int red,green,blue,alpha;
  int changeddir;
  unsigned char origin;

  if (strcmp(lasttextureloaded,filename)!=0)
    {
    changeddir=chdir("texture");
  
    if ((fp=fopen(filename,"rb"))==NULL)
      {
      if (debugit)
        printf("Texture Load Failed: %d\n",texturenum);

      if (changeddir==0)
        chdir("..");
      return;
      }
  
    fseek(fp,2,SEEK_CUR);
    fread2(&tgaheader.imagetypecode,1,1,fp);
    if (tgaheader.imagetypecode!=2 && tgaheader.imagetypecode!=3)
      {
      if (debugit)
        printf("Texture Bad Format: %d\n",texturenum);
  
      fclose(fp);
  
      if (changeddir==0)
        chdir("..");
      return;
      }
  
    fseek(fp,9,SEEK_CUR);
    fread2(&tgaheader.imagewidth,2,1,fp);
    fread2(&tgaheader.imageheight,2,1,fp);
    fread2(&tgaheader.pixeldepth,1,1,fp);
    fread2(&origin,1,1,fp);
    origin=(origin>>4)&3;
  
    for (count=0;count<tgaheader.imageheight;count++)
    for (count2=0;count2<tgaheader.imagewidth;count2++)
      {
      blue=fgetc(fp);
      green=fgetc(fp);
      red=fgetc(fp);
      if (tgaheader.pixeldepth==32)
        alpha=fgetc(fp);
      else
        alpha=255;
  
    if (!bigendian)
      {
      if (origin==0)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==1)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==2)
        tgaheader.imagedata[count*tgaheader.imagewidth+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      if (origin==3)
        tgaheader.imagedata[count*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(alpha<<24)+(blue<<16)+(green<<8)+red;
      }
    else
      {
      if (origin==0)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+count2]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==1)
        tgaheader.imagedata[(tgaheader.imageheight-1-count)*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==2)
        tgaheader.imagedata[count*tgaheader.imagewidth+count2]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      if (origin==3)
        tgaheader.imagedata[count*tgaheader.imagewidth+(tgaheader.imagewidth-1-count2)]=(red<<24)+(green<<16)+(blue<<8)+alpha;
      }
    }
  
    fclose(fp);
  
    if (changeddir==0)
      chdir("..");

    strcpy(lasttextureloaded,filename);
    }

  texture[texturenum].sizex=sizex;
  texture[texturenum].sizey=sizey;
  texture[texturenum].mipmaplevels=1;
  texture[texturenum].format=GL_RGBA;
  texture[texturenum].alphamap=0;
  texture[texturenum].normalmap=0;
  texture[texturenum].glossmap=0;
  texture[texturenum].wraps=GL_CLAMP;
  texture[texturenum].wrapt=GL_CLAMP;
  texture[texturenum].magfilter=GL_NEAREST;
  texture[texturenum].minfilter=GL_NEAREST;

  free(texture[texturenum].rgba[0]);
  texture[texturenum].rgba[0]=(unsigned int *) malloc(texture[texturenum].sizex*texture[texturenum].sizey*4);

  for (count=0;count<texture[texturenum].sizey;count++)
  if (count<tgaheader.imageheight)
  for (count2=0;count2<texture[texturenum].sizex;count2++)
  if (count2<tgaheader.imagewidth)
    {
    texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]=tgaheader.imagedata[(starty+count)*tgaheader.imagewidth+(startx+count2)];
    if (!bigendian)
      {
      if ((texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]>>24)!=255)
        texture[texturenum].alphamap=1;
      }
    else
      {
      if ((texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]&255)!=255)
        texture[texturenum].alphamap=1;
      }
    }

  setuptexture(texturenum);
  }

void generatemipmap(int texturenum)
  {
  int count,count2,count3,count4;
  int mipmaplevel;
  int mipmaplevelmax;
  unsigned int red,green,blue,alpha,temp;

  if (texture[texturenum].format!=GL_RGBA)
    return;

  mipmaplevelmax=1;
  while ((texture[texturenum].sizex>>mipmaplevelmax)!=0)
    mipmaplevelmax++;

  texture[texturenum].mipmaplevels=mipmaplevelmax;

  for (mipmaplevel=1;mipmaplevel<mipmaplevelmax;mipmaplevel++)
    {
    free(texture[texturenum].rgba[mipmaplevel]);
    texture[texturenum].rgba[mipmaplevel]=(unsigned int *) malloc((texture[texturenum].sizex>>mipmaplevel)*(texture[texturenum].sizey>>mipmaplevel)*4);
    if (texture[texturenum].normalmap)
      {
      free(texture[texturenum].normal[mipmaplevel]);
      texture[texturenum].normal[mipmaplevel]=(unsigned int *) malloc((texture[texturenum].sizex>>mipmaplevel)*(texture[texturenum].sizey>>mipmaplevel)*4);
      }
    for (count=0;count<(texture[texturenum].sizey>>mipmaplevel);count++)
      for (count2=0;count2<(texture[texturenum].sizex>>mipmaplevel);count2++)
        {
        red=0;
        green=0;
        blue=0;
        alpha=0;
        for (count3=0;count3<2;count3++)
        for (count4=0;count4<2;count4++)
          {
          temp=texture[texturenum].rgba[mipmaplevel-1][(count*2+count3)*(texture[texturenum].sizex>>(mipmaplevel-1))+(count2*2+count4)];
          red+=temp&0xFF;
          green+=(temp>>8)&0xFF;
          blue+=(temp>>16)&0xFF;
          alpha+=(temp>>24)&0xFF;
          }

        red>>=2;
        green>>=2;
        blue>>=2;
        alpha>>=2;
        texture[texturenum].rgba[mipmaplevel][count*(texture[texturenum].sizex>>mipmaplevel)+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;

        if (texture[texturenum].normalmap)
          {
          red=0;
          green=0;
          blue=0;
          alpha=0;
          for (count3=0;count3<2;count3++)
          for (count4=0;count4<2;count4++)
            {
            temp=texture[texturenum].normal[mipmaplevel-1][(count*2+count3)*(texture[texturenum].sizex>>(mipmaplevel-1))+(count2*2+count4)];
            red+=temp&0xFF;
            green+=(temp>>8)&0xFF;
            blue+=(temp>>16)&0xFF;
            alpha+=(temp>>24)&0xFF;
            }
  
          red>>=2;
          green>>=2;
          blue>>=2;
          alpha>>=2;
          texture[texturenum].normal[mipmaplevel][count*(texture[texturenum].sizex>>mipmaplevel)+count2]=(alpha<<24)+(blue<<16)+(green<<8)+red;
          }
        }
    }
  }

void setuptexture(int texturenum)
  {
  int count,count2;

  glBindTexture(GL_TEXTURE_2D,texture[texturenum].glname);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,texture[texturenum].wraps);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,texture[texturenum].wrapt);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,texture[texturenum].magfilter);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,texture[texturenum].minfilter);

  texture[texturenum].isalpha=0;

  for (count=0;count<texture[texturenum].sizey;count++)
  for (count2=0;count2<texture[texturenum].sizex;count2++)
    {
    if (!bigendian)
      {
      if ((texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]>>24)!=255)
        {
        texture[texturenum].isalpha=1;
        texture[texturenum].alphamap=1;
        }
      }
    else
      {
      if ((texture[texturenum].rgba[0][count*texture[texturenum].sizex+count2]&255)!=255)
        {
        texture[texturenum].isalpha=1;
        texture[texturenum].alphamap=1;
        }
      }
    }

  for (count=0;count<texture[texturenum].mipmaplevels;count++)
    glTexImage2D(GL_TEXTURE_2D,count,texture[texturenum].format,(texture[texturenum].sizex>>count),(texture[texturenum].sizey>>count),
                 0,texture[texturenum].format,GL_UNSIGNED_BYTE,texture[texturenum].rgba[count]);

  if (texture[texturenum].normalmap)
    {
    glBindTexture(GL_TEXTURE_2D,texture[texturenum].glnamenormal);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,texture[texturenum].wraps);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,texture[texturenum].wrapt);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,texture[texturenum].magfilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,texture[texturenum].minfilter);

    for (count=0;count<texture[texturenum].mipmaplevels;count++)
      glTexImage2D(GL_TEXTURE_2D,count,GL_RGBA,(texture[texturenum].sizex>>count),(texture[texturenum].sizey>>count),
                   0,GL_RGBA,GL_UNSIGNED_BYTE,texture[texturenum].normal[count]);
    }
  if (texture[texturenum].glossmap)
    {
    glBindTexture(GL_TEXTURE_2D,texture[texturenum].glnamegloss);
  
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,texture[texturenum].wraps);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,texture[texturenum].wrapt);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,texture[texturenum].magfilter);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,texture[texturenum].minfilter);
  
    for (count=0;count<texture[texturenum].mipmaplevels;count++)
      glTexImage2D(GL_TEXTURE_2D,count,GL_ALPHA,(texture[texturenum].sizex>>count),(texture[texturenum].sizey>>count),
                   0,GL_ALPHA,GL_UNSIGNED_BYTE,texture[texturenum].gloss[count]);
    }
  }
