#pragma once

#include <QGraphicsScene>
#include "model.h"
#include "conversions.h"
#include "matrixworks.h"


typedef struct sCanvasContainer
{
    QGraphicsScene *pb;
}sCanvasContainer;


eCodeFile DrawModel(sModel *mdl, sCanvasContainer *canvas, sRenderData *params);
