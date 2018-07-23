#pragma once

#include <stdio.h>

typedef struct sEdge
{
    int from, to;
}sEdge;

typedef struct sPoint3d
{
    double x, y, z;
}sPoint3d;

enum eCodeFile {cfFine, cfNotFound, cfCorrupted, cfOutOfMemory, cfUnknownAction};


eCodeFile LoadCount(int &n, FILE *fl);
//eCodeFile LoadEdgesCount(int &n, FILE *fl);
eCodeFile LoadSinglePoint(sPoint3d *point, FILE *fl);
eCodeFile LoadSingleEdge(sEdge *edge, FILE *fl);

eCodeFile SaveCount(FILE *fl, int n);
eCodeFile SaveSinglePoint(FILE *fl, sPoint3d point);
eCodeFile SaveSingleEdge(FILE *fl, sEdge edge);
