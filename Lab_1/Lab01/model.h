#pragma once


#include <stdio.h>

#include "model_loadparts.h"

typedef struct sModel
{
    sPointsList points;
    sEdgesList edges;
}sModel;


enum eFileAction {faLoad, faSave};


sModel* InitializeModel();

eCodeFile FileProcess(sModel *&mdl, char *filename, eFileAction action);

void ClearModel(sModel *mdl);
