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

#include "../math/vector.h"

float xaxis[3]={ 1.0f,0.0f,0.0f };
float yaxis[3]={ 0.0f,1.0f,0.0f };
float zaxis[3]={ 0.0f,0.0f,1.0f };

void resetorientation(float orientation[3][3])
  {
  orientation[0][0]=1.0f;
  orientation[0][1]=0.0f;
  orientation[0][2]=0.0f;
  orientation[1][0]=0.0f;
  orientation[1][1]=1.0f;
  orientation[1][2]=0.0f;
  orientation[2][0]=0.0f;
  orientation[2][1]=0.0f;
  orientation[2][2]=1.0f;
  }

void rotateorientation(float orientation[3][3],float *rotationvector,float rotationangle)
  {
  int count;
  float pointtemp[3],cosnormal[3],sinnormal[3];
  float axisnormal[3];
  float vectorlengthvalue,dotproductvalue;

  normalizevector(axisnormal,rotationvector);

  if (fabs(rotationangle)<.003f)
    return;

  for (count=0;count<3;count++)
    {
    copyvector(pointtemp,orientation[count]);

    crossproduct(sinnormal,axisnormal,pointtemp);

    normalizevector(sinnormal,sinnormal);

    crossproduct(cosnormal,sinnormal,axisnormal);

    normalizevector(cosnormal,cosnormal);

    dotproductvalue=dotproduct(axisnormal,pointtemp);
    pointtemp[0]-=axisnormal[0]*dotproductvalue;
    pointtemp[1]-=axisnormal[1]*dotproductvalue;
    pointtemp[2]-=axisnormal[2]*dotproductvalue;
    vectorlengthvalue=vectorlength(pointtemp);

    orientation[count][0]=axisnormal[0]*dotproductvalue+cosnormal[0]*cos(rotationangle)*vectorlengthvalue+sinnormal[0]*sin(rotationangle)*vectorlengthvalue;
    orientation[count][1]=axisnormal[1]*dotproductvalue+cosnormal[1]*cos(rotationangle)*vectorlengthvalue+sinnormal[1]*sin(rotationangle)*vectorlengthvalue;
    orientation[count][2]=axisnormal[2]*dotproductvalue+cosnormal[2]*cos(rotationangle)*vectorlengthvalue+sinnormal[2]*sin(rotationangle)*vectorlengthvalue;

    normalizevector(orientation[count],orientation[count]);
    }
  }
