#pragma once

#include "render.h"
#include "conversions.h"
#include "fileworks.h"

enum eChangeAction {caInit, caLoad, caSave, caScale, caRotate, caSetRot, caShift, caDraw, caDelete};

typedef struct uChangeData
{
    sMove move;
    double scale;
    sCanvasContainer *canvas;
    char *filename;
}uChangeData;

eCodeFile Apply(eChangeAction action, uChangeData *data);
