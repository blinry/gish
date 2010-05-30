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

void setupaudio(void)
  {
  int count;
  ALsizei size,freq;
  ALenum format;
  ALvoid *data;
  ALboolean loop;
  int changeddir;

  aldevice=alcOpenDevice(NULL);
  if (aldevice!=NULL)
    {
    alcontext=alcCreateContext(aldevice,NULL);
    if (alcontext!=NULL)
      {
      alcMakeContextCurrent(alcontext);
      soundenabled=1;
      }
    }

  if (!soundenabled)
    return;

  for (count=0;count<2;count++)
    alGenBuffers(1,&oggbuffer[count]);
  for (count=0;count<30;count++)
    alGenBuffers(1,&soundbuffer[count]);

  changeddir=chdir("sound");

  loadwav(0,"blockbreak.wav");
  loadwav(1,"rockhit.wav");
  loadwav(2,"fleshhit.wav");
  loadwav(3,"ropebreak.wav");
  loadwav(4,"chainbreak.wav");
  loadwav(5,"gishhit.wav");
  loadwav(6,"rockfriction.wav");
  loadwav(7,"squish.wav");
  loadwav(8,"secrets1.wav");
  loadwav(9,"secrets2.wav");
  loadwav(10,"amber.wav");
  loadwav(11,"nibattack.wav");
  loadwav(12,"visattack.wav");
  loadwav(13,"bobattack.wav");
  loadwav(14,"switch.wav");
  loadwav(15,"points.wav");
  loadwav(16,"gishhurt.wav");
  loadwav(17,"splash.wav");
  loadwav(18,"lava.wav");
  loadwav(19,"necksnap.wav");
  loadwav(20,"tarball.wav");

  if (changeddir==0)
    chdir("..");

#ifndef DEMO
  changeddir=chdir("data");

  loadwav(21,"cubemap.dat");
  loadwav(22,"specular.dat");
  loadwav(23,"stencil.dat");
  loadwav(24,"pixel.dat");

  if (changeddir==0)
    chdir("..");
#endif

  alGenSources(1,&oggsource);

  for (count=0;count<12;count++)
    alGenSources(1,&sound[count].alname);

  //alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
  }

int updateogg(void)
  {
  int processed;
  int buffernum;
  int active;

  if (!soundenabled)
    return(1);
  if (!option.music)
    return(1);

  active=1;

  alGetSourcei(oggsource,AL_BUFFERS_PROCESSED,&processed);

  while (processed>0)
    {
    alSourceUnqueueBuffers(oggsource,1,&buffernum);

    active=streamogg(buffernum);

    if (active)
      alSourceQueueBuffers(oggsource,1,&buffernum);

    processed--;
    }
  if (!active)
    {
    game.songnum=-1;
    /*
    if (level.gametype<10)
      {
      game.songnum++;
      if (game.songnum>3)
        game.songnum=0;
      }
    */
    }
  return(active);
  }

int streamogg(int buffernum)
  {
  int size;
  int section;
  int result;
  int count;
  char temp;

  size=0;
  while (size<OGGBUFFERSIZE)
    {
    result=ov_read(&oggstream[0],oggdata+size,OGGBUFFERSIZE-size,0,2,1,&section);

    if (result>0)
      size+=result;
    else
      goto streamoggbypass;
    }
  streamoggbypass:;

  if (size==0)
    return(0);

  if (bigendian)
  for (count=0;count<size/2;count++)
    {
    temp=oggdata[count*2];
    oggdata[count*2]=oggdata[count*2+1];
    oggdata[count*2+1]=temp;
    }

  alBufferData(buffernum,oggformat,oggdata,size,vorbisinfo->rate);

  return(1);
  }

void shutdownaudio(void)
  {
  alcontext=alcGetCurrentContext();
  aldevice=alcGetContextsDevice(alcontext);
  alcMakeContextCurrent(NULL);
  alcDestroyContext(alcontext);
  alcCloseDevice(aldevice);

  //ov_clear(&oggstream[0]);
  }

void loadwav(int buffernum,char *filename)
  {
  int count;
  SDL_AudioSpec wavspec;
  unsigned int wavlength;
  unsigned char *wavbuffer;
  unsigned char temp;
  ALenum format;

  if (SDL_LoadWAV(filename,&wavspec,&wavbuffer,&wavlength))
    {
    if (wavspec.channels==1)
      {
      if (wavspec.format==AUDIO_U8 || wavspec.format==AUDIO_S8)
        format=AL_FORMAT_MONO8;
      else
        format=AL_FORMAT_MONO16;

      if (bigendian)
      if (format==AL_FORMAT_MONO16)
        {
        for (count=0;count<wavlength/2;count++)
          {
          temp=wavbuffer[count*2+0];
          wavbuffer[count*2+0]=wavbuffer[count*2+1];
          wavbuffer[count*2+1]=temp;
          }
        }

      alBufferData(soundbuffer[buffernum],format,wavbuffer,wavlength,wavspec.freq);
      bufferloaded[buffernum]=1;
      }
    SDL_FreeWAV(wavbuffer);
    }
  }

