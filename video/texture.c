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

#include "../config.h"

#include "../video/opengl.h"

#if defined(LINUX) || defined(MAC)
  #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include <assert.h>

#include "../video/texture.h"
#include "../game/debug.h"
#include "../sdl/endian.h"
#include "../sdl/file.h"

unsigned int *lastrgba = NULL;
int lastfullwidth, lastfullheight;
char lastfilename[256] = "";
_texture texture[2048];
_tgaheader tgaheader;

/*
 * This should handle a variety common PNG formats 
 * most importantly 8bit palletized with alpha channel
 */
int loadtexturepng(char *filename, void **rgba, int *width, int *height)
{
	FILE *fp;
	int load_status;
	
	if((fp = fopen(filename, "rb")) == NULL)
	{
		if(debug_texture_load) fprintf(stderr, "Texture Load Failed: %s\n", filename);
		load_status = -1;
	}
	else
	{
		unsigned char header[8];
		fread(header, 1, 8, fp);
		if(png_sig_cmp(header, 0, 8))
		{
			if(debug_texture_load) fprintf(stderr, "PNG file not recognized: %s\n", filename);
			load_status = -2;
		}
		else
		{
			png_structp png_ptr;
			png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			if (png_ptr)
			{
				png_infop info_ptr;
				if (info_ptr = png_create_info_struct(png_ptr))
				{
					if(setjmp(png_jmpbuf(png_ptr)))
					{
						if(debug_texture_load) fprintf(stderr, "Error during init_io for %s\n", filename);
						load_status = -3;
					}
					else
					{
						int number_passes;
						png_init_io(png_ptr, fp);
						png_set_sig_bytes(png_ptr, 8);
						png_read_info(png_ptr, info_ptr);

						/* expand paletted colors into true rgb */
						if (info_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
							png_set_expand(png_ptr);

						/* expand grayscale images to the full 8 bits */
						if (info_ptr->color_type == PNG_COLOR_TYPE_GRAY && info_ptr->bit_depth < 8)
							png_set_expand(png_ptr);

						/* expand images with transparency to full alpha channels */
						if (info_ptr->valid & PNG_INFO_tRNS)
							png_set_expand(png_ptr);

						/* tell libpng to strip 16 bit depth files down to 8 bits */
						if (info_ptr->bit_depth == 16)
							png_set_strip_16(png_ptr);

						/* fill upto 4 byte RGBA - we always want an alpha channel*/
						if (info_ptr->bit_depth == 8 && info_ptr->color_type != PNG_COLOR_TYPE_RGB_ALPHA)
							png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);

						// XXX: is this required? we're not handling interlaced PNGs ...
						if (info_ptr->interlace_type)
							number_passes = png_set_interlace_handling(png_ptr);
						else
							number_passes = 1;

						png_start_read_image(png_ptr);
						//png_read_update_info(png_ptr, info_ptr);

						if(setjmp(png_jmpbuf(png_ptr)))
						{
							if(debug_texture_load) fprintf(stderr, "Error during read_image for %s\n", filename);
							load_status = -4;
						}
						else
						{
							int w, h, y;
							w = info_ptr->width;
							h = info_ptr->height;
							*width = w;
							*height = h;
							*rgba = (unsigned int *) malloc(w*h*4);
							memset(*rgba, 0, w*h*4);
							for(y = 0; y < h; y++)
								png_read_row(png_ptr, ((png_bytep)*rgba + (w*4*y)), NULL);
							load_status = 0;
						}
					}
					png_read_end(png_ptr, info_ptr);
					png_destroy_read_struct(&png_ptr, &info_ptr, (png_infop*)0);
				}
				free(info_ptr);
			}
			free(png_ptr);
		}
		fclose(fp);
	}
	return load_status;
}

int loadtexturetga(char *filename, void **rgba, int *width, int *height)
  {
	bool isAlpha = FALSE;
  int count,count2;
  int red,green,blue,alpha;
  unsigned char origin;
  FILE *fp;

  if ((fp=fopen(filename,"rb"))==NULL)
    {
    if (debug_texture_load) printf("Texture \"%s\" failed: fopen error\n",filename);
    return -1;
    }

  fseek(fp,2,SEEK_CUR);
  fread2(&tgaheader.imagetypecode,1,1,fp);
  if (tgaheader.imagetypecode!=2 && tgaheader.imagetypecode!=3)
    {
    if (debug_texture_load) printf("Texture \"%s\" failed: bad format\n",filename);
    fclose(fp);
    return -2;
    }

  fseek(fp,9,SEEK_CUR);
  fread2(&tgaheader.imagewidth,2,1,fp);
  fread2(&tgaheader.imageheight,2,1,fp);
  fread2(&tgaheader.pixeldepth,1,1,fp);
  fread2(&origin,1,1,fp);
  origin=(origin>>4)&3;

  isAlpha = FALSE;

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
      isAlpha = TRUE;

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

  //if ((tgaheader.imagewidth&(tgaheader.imagewidth-1))!=0)
  //  return -3;
  //if ((tgaheader.imageheight&(tgaheader.imageheight-1))!=0)
  //  return -4;

  *width = tgaheader.imagewidth;
  *height = tgaheader.imageheight;

  *rgba = (unsigned int *) malloc((*width) * (*height) * 4);

  memcpy(*rgba,tgaheader.imagedata, (*width) * (*height) * 4);

  return 0;
  }

int loadtexturefile(char *filename, void **rgba, int *width, int *height)
{
	int changeddir;
	int result;
	char *extension = filename + strlen(filename);
	while(*extension != '.' && extension != filename) { extension--; }

	if (extension == filename) extension = NULL;

	changeddir=chdir("texture");
	if (strcmp(extension, ".tga") == 0)
		result = loadtexturetga(filename, rgba, width, height);
	else
	{
		if (extension == NULL)
			printf("WARNING: No extension found in filename '%s'. Defaulting to png format.", filename);
		else if (strcmp(extension, ".png") != 0)
			printf("WARNING: Extension '%s' in filename '%s' not recognized. Defaulting to png format.", extension, filename);

		result = loadtexturepng(filename, rgba, width, height);
	}
	if (changeddir==0)
		chdir("..");
	return result;
}
int loadtexture(int texturenum,char *filename,int mipmap,int wraps,int wrapt,int magfilter,int minfilter)
{
	int result;

	if (debug_texture_load) printf("Loading \"%s\" into #%i...\n", filename, texturenum);

	if (texture[texturenum].rgba[0])
	{
		free(texture[texturenum].rgba[0]);
		texture[texturenum].rgba[0] = NULL;
	}
	result = loadtexturefile(filename, &(texture[texturenum].rgba[0]), &(texture[texturenum].sizex), &(texture[texturenum].sizey));

	texture[texturenum].mipmaplevels=1;
	texture[texturenum].format=GL_RGBA;
	texture[texturenum].alphamap=1;
	texture[texturenum].normalmap=0;
	texture[texturenum].glossmap=0;
	texture[texturenum].wraps=wraps;
	texture[texturenum].wrapt=wrapt;
	texture[texturenum].magfilter=magfilter;
	texture[texturenum].minfilter=minfilter;

	if (mipmap) {
		generatemipmap(texturenum);
	}
	setuptexture(texturenum);

	memset(texture[texturenum].filename, 0, 256);
	strcpy(texture[texturenum].filename,filename);

	return result;
}
void loadtexturepartial(int texturenum,char *filename,int startx,int starty,int sizex,int sizey)
{
	int result;
	unsigned int *fullrgba;
	int fullwidth, fullheight;
	int x, y;

	if (debug_texture_load) printf("Loading \"%s\" partially into #%i...\n", filename, texturenum);

	if (texture[texturenum].rgba[0])
	{
		free(texture[texturenum].rgba[0]);
		texture[texturenum].rgba[0] = NULL;
	}

	if (strcmp(lastfilename, filename) == 0)
	{
		fullrgba = lastrgba;
		fullwidth = lastfullwidth;
		fullheight = lastfullheight;
	}
	else
	{
		result = loadtexturefile(filename, &fullrgba, &fullwidth, &fullheight);

		if (result != 0)
			return;

		if (lastrgba)
			free(lastrgba);

		strcpy(lastfilename, filename);
		lastrgba = fullrgba;
		lastfullwidth = fullwidth;
		lastfullheight = fullheight;
	}

	texture[texturenum].rgba[0] = (unsigned int *)malloc(sizex*sizey*4);

	memset(texture[texturenum].rgba[0], 128, sizex*sizey*4);
	{
		int maxy = min(fullheight, starty+sizey)-starty;
		for (y = 0; y < maxy; y++)
		{
			int maxx = min(fullwidth, startx+sizex)-startx;
			for (x = 0; x < maxx; x++)
			{
				texture[texturenum].rgba[0][x + y * sizex]=fullrgba[(startx+x) + (starty+y) * fullwidth];
			}
		}
	}

	texture[texturenum].sizex = sizex;
	texture[texturenum].sizey = sizey;
	texture[texturenum].mipmaplevels=1;
	texture[texturenum].format=GL_RGBA;
	texture[texturenum].alphamap=1;
	texture[texturenum].normalmap=0;
	texture[texturenum].glossmap=0;
	texture[texturenum].wraps=GL_CLAMP;
	texture[texturenum].wrapt=GL_CLAMP;
	texture[texturenum].magfilter=GL_NEAREST;
	texture[texturenum].minfilter=GL_NEAREST;
	texture[texturenum].filename[0] = 0;
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
