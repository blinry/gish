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

#ifdef WINDOZE
void getcputime(__int64 *ptime)
  {
  __asm
    {
    rdtsc
    mov esi,ptime
    mov dword ptr [esi],eax
    mov dword ptr 4[esi],edx
    }
  }
#endif

void resettimer(int timernum)
  {
  timer[timernum].totaltime=0;
  }

void starttimer(int timernum)
  {
#ifdef WINDOZE
  getcputime(&timer[timernum].starttime);
#endif
  }

void stoptimer(int timernum)
  {
#ifdef WINDOZE
  getcputime(&timetemp);

  timer[timernum].totaltime+=(timetemp-timer[timernum].starttime);
#endif
  }
