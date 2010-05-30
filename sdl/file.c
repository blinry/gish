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

int comparestrings(const void *arg1,const void *arg2)
  {
  return(strcmp(arg1,arg2));
  }

int checkfilespec(char *filespec,char *filename)
  {
  int count,count2;
  int namesize;

  namesize=strlen(filename);

  count=0;
  count2=0;
  while (filespec[count]!=0 && filename[count2]!=0)
    {
    if (filespec[count]!=filename[count2] && filespec[count]!='*')
      return(0);

    if (filespec[count]==filename[count2])
      count++;
    else if (filespec[count]=='*' && filespec[count+1]==filename[count2])
      count+=2;
    count2++;
    }
  return(1);
  }

void listfiles(char *filespec,char filelist[1024][32],int directories)
  {
#ifdef WINDOZE
  int count,count2;
  int handle;
  struct _finddata_t fileinfo;

  handle=_findfirst(filespec,&fileinfo);

  count=0;
  count2=handle;
  while (count2!=-1 && count<1024)
    {
    if (!directories)
      {
      if ((fileinfo.attrib&_A_SUBDIR)==0)
        {
        strcpy(filelist[count],fileinfo.name);
        count++;
        }
      }
    else
      {
      if ((fileinfo.attrib&_A_SUBDIR)!=0)
      if (fileinfo.name[0]!='.')
        {
        strcpy(filelist[count],fileinfo.name);
        count++;
        }
      }
    count2=_findnext(handle,&fileinfo);
    }

  filelist[count][0]=0;

  _findclose(handle);

  qsort(filelist,count,32,comparestrings);
#endif

#ifdef DETLEF
  int count;
  struct dirent *dp;
  DIR *dfd;
  struct stat stbuf;

  dfd=opendir(".");

  count=0;
  if (dfd!=NULL)
    {
    while ((dp=readdir(dfd))!=NULL)
      {
      stat(dp->d_name,&stbuf);
      if (!directories)
        {
        if ((stbuf.st_mode&S_IFMT)!=S_IFDIR)
        if (dp->d_name[0]!='<')
        if (checkfilespec(filespec,dp->d_name))
          {
          strcpy(filelist[count],dp->d_name);
          count++;
          }
        }
      else
        {
        if ((stbuf.st_mode&S_IFMT)==S_IFDIR)
        if (dp->d_name[0]!='.')
        if (dp->d_name[0]!='<')
        if (checkfilespec(filespec,dp->d_name))
          { 
          strcpy(filelist[count],dp->d_name);
          count++;
          }
        }
      }
    }

  filelist[count][0]=0;

  closedir(dfd);

  qsort(filelist,count,32,comparestrings);
#endif
  }
/*
size_t fread2(void *ptr,size_t psize,size_t pnum,FILE *pfp)
  {
  int count;
  unsigned char *cptr;

#ifndef THINKSTUPID
  fread(ptr,psize,pnum,pfp);
#endif
#ifdef THINKSTUPID
  cptr=(unsigned char *) ptr;
  if (psize==1)
    {
    for (count=0;count<pnum;count++)
      cptr[count]=fgetc(fp);
    }
  if (psize==2)
    {
    for (count=0;count<pnum;count++)
      {
      cptr[count*2+1]=fgetc(fp);
      cptr[count*2]=fgetc(fp);
      }
    }
  if (psize==4)
    {
    for (count=0;count<pnum;count++)
      {
      cptr[count*4+3]=fgetc(fp);
      cptr[count*4+2]=fgetc(fp);
      cptr[count*4+1]=fgetc(fp);
      cptr[count*4]=fgetc(fp);
      }
    }
#endif
  }

size_t fwrite2(const void *ptr,size_t psize,size_t pnum,FILE *pfp)
  {
  int count;
  unsigned char *cptr;

#ifndef THINKSTUPID
  fwrite(ptr,psize,pnum,pfp);
#endif
#ifdef THINKSTUPID
  cptr=(unsigned char *) ptr;
  if (psize==1)
    {
    for (count=0;count<pnum;count++)
      fputc(cptr[count],fp);
    }
  if (psize==2)
    {
    for (count=0;count<pnum;count++)
      {
      fputc(cptr[count*2+1],fp);
      fputc(cptr[count*2],fp);
      }
    }
  if (psize==4)
    {
    for (count=0;count<pnum;count++)
      {
      fputc(cptr[count*4+3],fp);
      fputc(cptr[count*4+2],fp);
      fputc(cptr[count*4+1],fp);
      fputc(cptr[count*4],fp);
      }
    }
#endif
  }
*/

size_t freadswap(void *ptr,size_t psize,size_t pnum,FILE *pfp)
  {
  int count;
  unsigned char *cptr;

  cptr=(unsigned char *) ptr;
  if (psize==1)
    {
    for (count=0;count<pnum;count++)
      cptr[count]=fgetc(pfp);
    }
  else if (psize==2)
    {
    for (count=0;count<pnum;count++)
      {
      cptr[(count<<1)+1]=fgetc(pfp);
      cptr[(count<<1)]=fgetc(pfp);
      }
    }
  else if (psize==4)
    {
    for (count=0;count<pnum;count++)
      {
      cptr[(count<<2)+3]=fgetc(pfp);
      cptr[(count<<2)+2]=fgetc(pfp);
      cptr[(count<<2)+1]=fgetc(pfp);
      cptr[(count<<2)]=fgetc(pfp);
      }
    }

  return(pnum);
  }

size_t fwriteswap(const void *ptr,size_t psize,size_t pnum,FILE *pfp)
  {
  int count;
  unsigned char *cptr;

  cptr=(unsigned char *) ptr;
  if (psize==1)
    {
    for (count=0;count<pnum;count++)
      fputc(cptr[count],pfp);
    }
  else if (psize==2)
    {
    for (count=0;count<pnum;count++)
      {
      fputc(cptr[(count<<1)+1],pfp);
      fputc(cptr[(count<<1)],pfp);
      }
    }
  else if (psize==4)
    {
    for (count=0;count<pnum;count++)
      {
      fputc(cptr[(count<<2)+3],pfp);
      fputc(cptr[(count<<2)+2],pfp);
      fputc(cptr[(count<<2)+1],pfp);
      fputc(cptr[(count<<2)],pfp);
      }
    }

  return(pnum);
  }