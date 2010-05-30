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

void soundsimulation(float position[3],float orientation[3][3])
  {
  int count;
  int state;
  float vec[3];
  float alorientation[6];
  float intersectpoint[3];
  float normal[3];
  float scale;

  if (!soundenabled)
    return;
  if (!option.sound)
    return;

  alListenerfv(AL_POSITION,position);
  zerovector(vec);
  alListenerfv(AL_VELOCITY,vec);
  scalevector(alorientation,orientation[2],-1.0f);
  copyvector(alorientation+3,orientation[1]);
  alListenerfv(AL_ORIENTATION,alorientation);

  if (game.currentsongnum!=-1)
    {
    if (game.exit!=0)
      scale=0.3f-(float)(100-game.exitdelay)*0.003f;
    else
      scale=0.3f;

    alSourcef(oggsource,AL_GAIN,scale*option.musicvolume);
    }
  else
    alSourceStop(oggsource);

  count=0;
  while (count<numofsounds)
    {
    updateogg();

    alGetSourcei(sound[count].alname,AL_SOURCE_STATE,&state);
    while (count<numofsounds && sound[count].delay==0 && state!=AL_PLAYING && !sound[count].looping)
      {
      deletesound(count);
      alGetSourcei(sound[count].alname,AL_SOURCE_STATE,&state);
      }
    count++;
    }
  }

void playsound(int buffernum,float position[3],float velocity[3],float volume,int looping,float pitch,int objectnum,int objectsoundnum)
  {
  int count,count2;
  float vec[3];
  float intersectpoint[3];
  float normal[3];
  float scale;

  if (!soundenabled)
    return;

  if (!option.sound)
    return;

  if (numofsounds>=12)
    return;

  if (game.oldschool==2)
    {
    if (buffernum==5)
      buffernum=21;
    if (buffernum==10)
      buffernum=23;
    if (buffernum<21)
      return;
    }

  if (objectnum!=-1)
  if (object[objectnum].soundnum[objectsoundnum]!=-1)
    return;

  if (!bufferloaded[buffernum])
    return;

  count2=0;
  for (count=0;count<numofsounds;count++)
    {
    if (sound[count].buffernum==buffernum)
      count2++;
    }

  //if (buffernum==0)
  if (buffernum!=10 && buffernum!=15)
  if (count2>=2)
    return;

  if (game.oldschool==2)
  if (count2>=1)
    return;

  if (volume<0.0f)
    volume=0.0f;
  if (volume>1.0f)
    volume=1.0f;
  if (pitch<0.0f)
    pitch=0.0f;
  if (pitch>1.0f)
    pitch=1.0f;

  volume*=option.soundvolume;

  sound[numofsounds].buffernum=buffernum;
  sound[numofsounds].objectnum=-1;
  sound[numofsounds].looping=looping;
  sound[numofsounds].pitchshift=0;
  alSourcei(sound[numofsounds].alname,AL_BUFFER,soundbuffer[buffernum]);
  alSourcei(sound[numofsounds].alname,AL_LOOPING,looping);
  alSourcefv(sound[numofsounds].alname,AL_POSITION,position);
  if (velocity!=NULL)
    scalevector(vec,velocity,PHYSICSCYCLE);
  else
    zerovector(vec);
  alSourcefv(sound[numofsounds].alname,AL_VELOCITY,vec);
  alSourcef(sound[numofsounds].alname,AL_REFERENCE_DISTANCE,5.0f);
  alSourcef(sound[numofsounds].alname,AL_PITCH,pitch);

  alSourcef(sound[numofsounds].alname,AL_GAIN,volume);

  alSourcePlay(sound[numofsounds].alname);

  updateogg();

  sound[numofsounds].objectnum=objectnum;
  object[objectnum].soundnum[objectsoundnum]=numofsounds;

  numofsounds++;
  }

void deletesound(int soundnum)
  {
  int count,count2;
  ALuint alnametemp;

  if (!soundenabled)
    return;

  if (soundnum<0)
    return;
  if (soundnum>=numofsounds)
    return;

  if (sound[soundnum].objectnum!=-1)
  for (count=0;count<4;count++)
  if (object[sound[soundnum].objectnum].soundnum[count]==soundnum)
    object[sound[soundnum].objectnum].soundnum[count]=-1;

  numofsounds--;

  alSourceStop(sound[soundnum].alname);

  if (soundnum==numofsounds)
    return;

  alnametemp=sound[soundnum].alname;
  memcpy(&sound[soundnum],&sound[numofsounds],sizeof(sound[soundnum]));
  sound[numofsounds].alname=alnametemp;

  if (sound[numofsounds].objectnum!=-1)
  for (count=0;count<4;count++)
  if (object[sound[numofsounds].objectnum].soundnum[count]==numofsounds)
    object[sound[numofsounds].objectnum].soundnum[count]=soundnum;
  }
