#pragma once
#include "render.h"

typedef struct sCanvasPoint
{
    int x;
    int y;
} sCanvasPoint;

sCanvasPoint CanvasPoint(int fromX, int fromY);

void DrawLine(sCanvasContainer *canvas,sCanvasPoint &from, sCanvasPoint &to);
