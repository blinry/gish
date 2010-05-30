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

void loadtextfile(char *filename)
  {
  int temp;

  parser.textsize=0;

  if ((fp=fopen(filename,"rb"))!=NULL)
    {
    temp=fgetc(fp);
    while (temp!=EOF)
      {
      parser.text[parser.textsize]=temp;
      parser.textsize++;
      temp=fgetc(fp);
      }
    parser.text[parser.textsize]=0;

    fclose(fp);
    }

  parser.textloc=0;
  }

void resetparser(void)
  {
  parser.textloc=0;
  }

int findstring(char *str)
  {
  while (parser.textloc<parser.textsize && !checkstring(str))
    parser.textloc++;

  parser.textloc+=strlen(str);

  if (parser.textloc<parser.textsize)
    return(1);
  return(0);
  }

int checkstring(char *str)
  {
  int count;

  count=0;
  while (parser.textloc+count<parser.textsize && str[count]!=0 && str[count]==parser.text[parser.textloc+count])
    count++;

  if (str[count]==0)
    return(1);
  return(0);
  }

int getint(void)
  {
  int count;
  int temp;

  while (parser.textloc<parser.textsize && (parser.text[parser.textloc]<48 || parser.text[parser.textloc]>57) && parser.text[parser.textloc]!='-')
    parser.textloc++;

  count=0;
  while (parser.textloc<parser.textsize && count<255 && ((parser.text[parser.textloc]>=48 && parser.text[parser.textloc]<=57) || parser.text[parser.textloc]=='-'))
    {
    parser.numtemp[count]=parser.text[parser.textloc];
    parser.textloc++;
    count++;
    }
  parser.numtemp[count]=0;
  sscanf(parser.numtemp,"%d",&temp);

  return(temp);
  }

float getfloat(void)
  {
  int count;
  float temp;

  while (parser.textloc<parser.textsize && (parser.text[parser.textloc]<48 || parser.text[parser.textloc]>57) && parser.text[parser.textloc]!='-' && parser.text[parser.textloc]!='.')
    parser.textloc++;

  count=0;
  while (parser.textloc<parser.textsize && count<255 && ((parser.text[parser.textloc]>=48 && parser.text[parser.textloc]<=57) || parser.text[parser.textloc]=='-' || parser.text[parser.textloc]=='.'))
    {
    parser.numtemp[count]=parser.text[parser.textloc];
    parser.textloc++;
    count++;
    }
  parser.numtemp[count]=0;
  sscanf(parser.numtemp,"%f",&temp);

  return(temp);
  }

void getstring(char *str,int size)
  {
  int count;

  count=0;
  while (parser.textloc<parser.textsize && count<size-1 && parser.text[parser.textloc]!=13 && parser.text[parser.textloc]!=10)
    {
    str[count]=parser.text[parser.textloc];
    parser.textloc++;
    count++;
    }
  str[count]=0;
  }

