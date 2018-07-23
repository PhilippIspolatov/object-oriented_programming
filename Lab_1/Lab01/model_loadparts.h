#pragma once

//#include "model.h"
#include "fileworks.h"

typedef struct sEdgesList
{
    int count;
    sEdge *edgesArray;
}sEdgesList;

typedef struct sPointsList
{
    int count;
    sPoint3d *pointsArray;
}sPointsList;

enum eAllocError {aeFine, aeOutOfMemory};


void ClearPointsList(sPointsList *p);

void ClearEdgesList(sEdgesList *e);

eCodeFile TryLoadPoints(sPointsList *pd, FILE *fl);

eCodeFile TryLoadEdges(sEdgesList *adj, FILE *fl);

eAllocError AllocPointsList(sPointsList *points);

eAllocError AllocEdgesLst(sEdgesList *edges);

eCodeFile SavePoints(sPointsList points, FILE *fl);

eCodeFile SaveEdges(sEdgesList edges, FILE *fl);
