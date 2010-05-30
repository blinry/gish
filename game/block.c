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

void saveblock(int blocknum)
  {
  int count;
  int changeddir;
  char filename[13]="blck000.blk";

  changeddir=chdir("block");

  filename[4]=48+(blocknum/100)%10;
  filename[5]=48+(blocknum/10)%10;
  filename[6]=48+blocknum%10;

  if ((fp=fopen(filename,"wb"))!=NULL)
    {
    fwrite2(&block[blocknum].numoflines,4,1,fp);
    for (count=0;count<block[blocknum].numoflines;count++)
      fwrite2(block[blocknum].line[count],4,8,fp);

    fclose(fp);
    }

  if (changeddir==0)
    chdir("..");
  }

void loadblock(int blocknum)
  {
  int count;
  int changeddir;
  char filename[13]="blck000.blk";

  changeddir=chdir("block");

  filename[4]=48+(blocknum/100)%10;
  filename[5]=48+(blocknum/10)%10;
  filename[6]=48+blocknum%10;

  block[blocknum].numoflines=0;
  /*
  if ((fp=fopen(filename,"rb"))!=NULL)
    {
    fread2(&block[blocknum].numoflines,4,1,fp);
    for (count=0;count<block[blocknum].numoflines;count++)
      {
      fread2(block[blocknum].line[count],4,8,fp);
      if (block[blocknum].line[count][4]==0.0f)
        block[blocknum].line[count][4]=1.0f;
      block[blocknum].friction=block[blocknum].line[count][4];
      if (blocknum==160)
        block[blocknum].breakpoint=0.125f*0.25f;
      if (blocknum==161)
        block[blocknum].breakpoint=0.125f*0.5f;
      if (blocknum==162)
        block[blocknum].breakpoint=0.125f;
      if (blocknum==163)
        block[blocknum].breakpoint=0.25f;
      if (blocknum==164)
        block[blocknum].breakpoint=0.5f;
      if (blocknum==165)
        block[blocknum].breakpoint=1.0f;
      if (blocknum==166)
        block[blocknum].breakpoint=2.0f;
      if (blocknum==167)
        block[blocknum].breakpoint=0.125f*0.5f;
      block[blocknum].middamage=0;
      block[blocknum].foredamage=0;
      block[blocknum].density=0.0f;
      block[blocknum].drag=0.0f;
      block[blocknum].animation=0;
      }

    fclose(fp);
    }
  */

  block[blocknum].numoflines=4;
  count=0;
  block[blocknum].line[count][0]=0.0f;
  block[blocknum].line[count][1]=1.0f;
  block[blocknum].line[count][2]=1.0f;
  block[blocknum].line[count][3]=1.0f;
  count=1;
  block[blocknum].line[count][0]=1.0f;
  block[blocknum].line[count][1]=1.0f;
  block[blocknum].line[count][2]=1.0f;
  block[blocknum].line[count][3]=0.0f;
  count=2;
  block[blocknum].line[count][0]=1.0f;
  block[blocknum].line[count][1]=0.0f;
  block[blocknum].line[count][2]=0.0f;
  block[blocknum].line[count][3]=0.0f;
  count=3;
  block[blocknum].line[count][0]=0.0f;
  block[blocknum].line[count][1]=0.0f;
  block[blocknum].line[count][2]=0.0f;
  block[blocknum].line[count][3]=1.0f;

  block[blocknum].friction=1.0f;
  block[blocknum].breakpoint=0.0f;
  block[blocknum].middamage=0;
  block[blocknum].foredamage=0;
  block[blocknum].density=0.0f;
  block[blocknum].drag=0.0f;
  block[blocknum].animation=0;

  setupblockflags(blocknum);

  if (changeddir==0)
    chdir("..");
  }

void setupblockflags(int blocknum)
  {
  int count;

  block[blocknum].flags=0;
  for (count=0;count<block[blocknum].numoflines;count++)
    {
    if (block[blocknum].line[count][0]==0.0f)
    if (block[blocknum].line[count][1]==1.0f)
    if (block[blocknum].line[count][2]==1.0f)
    if (block[blocknum].line[count][3]==1.0f)
      block[blocknum].flags|=1;
    
    if (block[blocknum].line[count][0]==1.0f)
    if (block[blocknum].line[count][1]==1.0f)
    if (block[blocknum].line[count][2]==1.0f)
    if (block[blocknum].line[count][3]==0.0f)
      block[blocknum].flags|=2;
    
    if (block[blocknum].line[count][0]==1.0f)
    if (block[blocknum].line[count][1]==0.0f)
    if (block[blocknum].line[count][2]==0.0f)
    if (block[blocknum].line[count][3]==0.0f)
      block[blocknum].flags|=4;
    
    if (block[blocknum].line[count][0]==0.0f)
    if (block[blocknum].line[count][1]==0.0f)
    if (block[blocknum].line[count][2]==0.0f)
    if (block[blocknum].line[count][3]==1.0f)
      block[blocknum].flags|=8;
    }
  }

void setupblockalpha(int blocknum)
  {
  int count,count2;
  float x,y;
  int yline;
  int xleft,xright;
  int xleftadd,xrightadd;
  int xstart,xend;
  int vertleft,vertright;
  int vertleftnext,vertrightnext;
  int yend;

  numofpolygontemps=0;

  for (count=0;count<block[blocknum].numoflines;count++)
    {
    x=block[blocknum].line[count][0];
    y=block[blocknum].line[count][1];
    y=1.0f-y;

    for (count2=0;count2<numofpolygontemps;count2++)
    if (x==polygontemp[count2].vertex[polygontemp[count2].numofverts-1][0])
    if (y==polygontemp[count2].vertex[polygontemp[count2].numofverts-1][1])
      {
      x=block[blocknum].line[count][2];
      y=block[blocknum].line[count][3];
      y=1.0f-y;

      polygontemp[count2].vertex[polygontemp[count2].numofverts][0]=x;
      polygontemp[count2].vertex[polygontemp[count2].numofverts][1]=y;
      polygontemp[count2].numofverts++;

      goto createpolybypass;
      }

    polygontemp[numofpolygontemps].numofverts=0;

    polygontemp[numofpolygontemps].vertex[polygontemp[numofpolygontemps].numofverts][0]=x;
    polygontemp[numofpolygontemps].vertex[polygontemp[numofpolygontemps].numofverts][1]=y;
    polygontemp[numofpolygontemps].numofverts++;

    x=block[blocknum].line[count][2];
    y=block[blocknum].line[count][3];
    y=1.0f-y;

    polygontemp[numofpolygontemps].vertex[polygontemp[numofpolygontemps].numofverts][0]=x;
    polygontemp[numofpolygontemps].vertex[polygontemp[numofpolygontemps].numofverts][1]=y;
    polygontemp[numofpolygontemps].numofverts++;
    numofpolygontemps++;

    createpolybypass:;
    }

  for (count2=0;count2<numofpolygontemps;count2++)
    polygontemp[count2].numofverts--;

  for (count2=0;count2<numofpolygontemps;count2++)
  for (count=0;count<polygontemp[count2].numofverts;count++)
    {
    polygontemp[count2].ivertex[count][0]=polygontemp[count2].vertex[count][0]*(texture[blocknum].sizex+0);
    polygontemp[count2].ivertex[count][1]=polygontemp[count2].vertex[count][1]*(texture[blocknum].sizey+0);
    }


  for (count2=0;count2<numofpolygontemps;count2++)
  if (polygontemp[count2].numofverts>2)
    {
    yline=polygontemp[count2].ivertex[0][1];
    xleft=polygontemp[count2].ivertex[0][0];
    xright=polygontemp[count2].ivertex[0][0];
    vertleft=0;
    vertright=0;

    for (count=1;count<polygontemp[count2].numofverts;count++)
      {
      if (yline>polygontemp[count2].ivertex[count][1] || (yline==polygontemp[count2].ivertex[count][1] && xleft>polygontemp[count2].ivertex[count][0]))
        {
        yline=polygontemp[count2].ivertex[count][1];
        xleft=polygontemp[count2].ivertex[count][0];
        xright=polygontemp[count2].ivertex[count][0];
        vertleft=count;
        vertright=count;
        }
      }

    if (yline<0)
      yline=0;

    yend=polygontemp[count2].ivertex[0][1];
    for (count=1;count<polygontemp[count2].numofverts;count++)
      if (yend<polygontemp[count2].ivertex[count][1])
        yend=polygontemp[count2].ivertex[count][1];

    xleft<<=16;
    xright<<=16;

    if (vertleft>0)
      vertleftnext=vertleft-1;
    else
      vertleftnext=polygontemp[count2].numofverts-1;

    xleftadd=(polygontemp[count2].ivertex[vertleftnext][0]<<16)-xleft;
    if ((polygontemp[count2].ivertex[vertleftnext][1]-yline)>0)
      xleftadd/=(polygontemp[count2].ivertex[vertleftnext][1]-yline);

    vertrightnext=(vertright+1)%polygontemp[count2].numofverts;

    xrightadd=(polygontemp[count2].ivertex[vertrightnext][0]<<16)-xright;
    if ((polygontemp[count2].ivertex[vertrightnext][1]-yline)>0)
      xrightadd/=(polygontemp[count2].ivertex[vertrightnext][1]-yline);

    while (yline<yend && yline<texture[blocknum].sizey)
      {
      xleft+=xleftadd;
      xright+=xrightadd;

      if (yline==polygontemp[count2].ivertex[vertleftnext][1])
        {
        vertleft=vertleftnext;

        if (vertleft>0)
          vertleftnext=vertleft-1;
        else
          vertleftnext=polygontemp[count2].numofverts-1;

        xleftadd=(polygontemp[count2].ivertex[vertleftnext][0]<<16)-xleft;
        if ((polygontemp[count2].ivertex[vertleftnext][1]-yline)>0)
          xleftadd/=(polygontemp[count2].ivertex[vertleftnext][1]-yline);
        }
      if (yline==polygontemp[count2].ivertex[vertrightnext][1])
        {
        vertright=vertrightnext;

        vertrightnext=(vertright+1)%polygontemp[count2].numofverts;
    
        xrightadd=(polygontemp[count2].ivertex[vertrightnext][0]<<16)-xright;
        if ((polygontemp[count2].ivertex[vertrightnext][1]-yline)>0)
          xrightadd/=(polygontemp[count2].ivertex[vertrightnext][1]-yline);
        }

      xstart=xleft>>16;
      if (xstart<0)
        xstart=0;
      if (xstart>texture[blocknum].sizex-1)
        xstart=texture[blocknum].sizex-1;
      xend=xright>>16;
      if (xend<0)
        xend=0;
      if (xend>texture[blocknum].sizex)
        xend=texture[blocknum].sizex;

      while (xstart<xend)
        {
        if (!bigendian)
          texture[blocknum].rgba[0][yline*texture[blocknum].sizex+xstart]|=0xFF000000;
        else
          texture[blocknum].rgba[0][yline*texture[blocknum].sizex+xstart]|=0x000000FF;
        xstart++;
        }
      yline++;
      }
    }
  }
