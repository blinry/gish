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

void checkmusic(void)
  {
  int count,count2;
  int queued;
  float vec[3];

  if (!soundenabled)
    return;
  if (!config.sound)
    return;
  if (!option.sound)
    return;

  if (!option.music)
    game.songnum=-1;

  if (game.songnum>8)
    game.songnum=0;

#ifdef DEMO
  if (game.songnum>0 && game.songnum<8)
    game.songnum=0;
#endif

  if (game.songnum!=game.currentsongnum)
    {
    if (game.currentsongnum!=-1)
      {
      alSourceStop(oggsource);

      alGetSourcei(oggsource,AL_BUFFERS_QUEUED,&queued);

      while (queued>0)
        {
        alSourceUnqueueBuffers(oggsource,1,&count);

        queued--;
        }

      ov_clear(&oggstream[0]);
      }

    if (game.songnum!=-1)
      {
      vorbiscallbacks.read_func=vorbisread;
      vorbiscallbacks.seek_func=vorbisseek;
      vorbiscallbacks.close_func=vorbisclose;
      vorbiscallbacks.tell_func=vorbistell;

      oggmemoryfile[game.songnum].dataread=0;
      if (ov_open_callbacks(&oggmemoryfile[game.songnum],&oggstream[0],NULL,0,vorbiscallbacks)>=0)
        {
        vorbisinfo=ov_info(&oggstream[0],-1);

        if (vorbisinfo->channels==1)
          oggformat=AL_FORMAT_MONO16;
        else
          oggformat=AL_FORMAT_STEREO16;

        streamogg(oggbuffer[0]);
        streamogg(oggbuffer[1]);

        alSourceQueueBuffers(oggsource,2,oggbuffer);

        vec[0]=0.0f;
        vec[1]=0.0f;
        vec[2]=0.0f;

        alSource3f(oggsource,AL_POSITION,vec[0],vec[1],vec[2]);
        alSource3f(oggsource,AL_VELOCITY,0.0f,0.0f,0.0f);
        alSourcef(oggsource,AL_REFERENCE_DISTANCE,10.0f);
        alSourcef(oggsource,AL_GAIN,0.3f*option.musicvolume);
        alSourcei(oggsource,AL_SOURCE_RELATIVE,AL_TRUE);

        alSourcePlay(oggsource);

        updateogg();

        alSourcePlay(oggsource);

        game.currentsongnum=game.songnum;
        }
      else
        game.currentsongnum=-1;
      }
    else
      {
      game.currentsongnum=game.songnum;
      }
    }

  if (game.currentsongnum!=-1)
    {
    alGetSourcei(oggsource,AL_SOURCE_STATE,&count);
    if (count!=AL_PLAYING)
      alSourcePlay(oggsource);
    }
  }

void loadoggs(void)
  {
  int count;
  int oggnum;
  int changeddir;

  changeddir=chdir("music");

  oggnum=0;
  if ((fp=fopen("sewer.ogg","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }

#ifndef DEMO
  oggnum=1;
  if ((fp=fopen("cave.ogg","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }
  oggnum=2;
  if ((fp=fopen("hell.ogg","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }
  oggnum=3;
  if ((fp=fopen("egypt.ogg","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }
  oggnum=4;
  if ((fp=fopen("church.ogg","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }
  oggnum=5;
  if ((fp=fopen("boss.ogg","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");

  changeddir=chdir("data");

  oggnum=6;
  if ((fp=fopen("async.dat","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");

  changeddir=chdir("music");

  oggnum=7;
  if ((fp=fopen("versus.ogg","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }
#endif

  oggnum=8;
  if ((fp=fopen("intro.ogg","rb"))!=NULL)
    {
    fseek(fp,0,SEEK_END);
    oggmemoryfile[oggnum].datasize=ftell(fp);
    oggmemoryfile[oggnum].dataread=0;
    oggmemoryfile[oggnum].data=(char *) malloc(oggmemoryfile[oggnum].datasize);

    fseek(fp,0,SEEK_SET);

    fread2(oggmemoryfile[oggnum].data,1,oggmemoryfile[oggnum].datasize,fp);

    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");
  }

size_t vorbisread(void *ptr,size_t bytesize,size_t sizetoread,void *datasource)
  {
  int actualsizetoread;
  int spacetoeof;
  struct OGGMEMORYFILE *vorbisdata;

  vorbisdata=(struct OGGMEMORYFILE *)datasource;

  spacetoeof=vorbisdata->datasize-vorbisdata->dataread;

  if (sizetoread*bytesize<spacetoeof)
    actualsizetoread=sizetoread*bytesize;
  else
    actualsizetoread=spacetoeof;

  if (actualsizetoread>0)
    {
    memcpy(ptr,(char *)vorbisdata->data+vorbisdata->dataread,actualsizetoread);
    vorbisdata->dataread+=actualsizetoread;
    }

  return(actualsizetoread);
  }

int vorbisseek(void *datasource,ogg_int64_t offset,int whence)
  {
  int spacetoeof;
  ogg_int64_t actualoffset;
  struct OGGMEMORYFILE *vorbisdata;

  vorbisdata=(struct OGGMEMORYFILE *)datasource;

  if (whence==SEEK_SET)
    {
    if (offset<vorbisdata->datasize)
      actualoffset=offset;
    else
      actualoffset=vorbisdata->datasize;
    vorbisdata->dataread=(int)actualoffset;
    }
  if (whence==SEEK_CUR)
    {
    spacetoeof=vorbisdata->datasize-vorbisdata->dataread;

    if (offset<spacetoeof)
      actualoffset=offset;
    else
      actualoffset=spacetoeof;
    vorbisdata->dataread+=(int)actualoffset;
    }
  if (whence==SEEK_END)
    {
    vorbisdata->dataread=vorbisdata->datasize+1;
    }
  return(0);
  }

int vorbisclose(void *datasource)
  {
  return(1);
  }

long vorbistell(void *datasource)
  {
  struct OGGMEMORYFILE *vorbisdata;

  vorbisdata=(struct OGGMEMORYFILE *)datasource;

  return(vorbisdata->dataread);
  }
