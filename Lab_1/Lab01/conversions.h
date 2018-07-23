#pragma once

#include "model_loadparts.h"

typedef struct sMove
{
	double dx;
	double dy;
	double dz;
}sMove;


typedef struct sRenderData
{
    double fx, fy, fz;
    double dx, dy, dz;
    double M;
}sRenderData;

typedef struct sConvertedPoints
{
    int count;
    int *Xs;
    int *Ys;
}sConvertedPoints;

sConvertedPoints* ConvertPoints(sPointsList *points, sRenderData *params);

void ClearConvertedPoints(sConvertedPoints *converted);
