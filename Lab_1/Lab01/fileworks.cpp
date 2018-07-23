#include <stdio.h>
#include "fileworks.h"

eCodeFile LoadCount(int &n, FILE *fl)
{
	int count;
    eCodeFile res = cfFine;

	if (fscanf(fl, "%d", &count) != 1)
        res =  cfCorrupted;

	
	n = count;
    return res;
}


eCodeFile LoadSinglePoint(sPoint3d *point, FILE *fl)
{
    eCodeFile res = cfFine;
	if (fscanf(fl, "%lf %lf %lf", &point->x, &point->y, &point->z) != 3)
        res =  cfCorrupted;
	
    return res;
}


eCodeFile LoadSingleEdge(sEdge *edge, FILE *fl)
{
    eCodeFile res = cfFine;
	if (fscanf(fl, "%d %d", &edge->from, &edge->to) != 2)
        res =  cfCorrupted;
    edge->from -= 1;
    edge->to -= 1;
	
    return res;
}


eCodeFile SaveCount(FILE *fl, int n)
{
    fprintf(fl, "%d\n", n);
    return cfFine;
}


eCodeFile SaveSinglePoint(FILE *fl, sPoint3d point)
{
    fprintf(fl, "%lf %lf %lf\n", point.x, point.y, point.z);
    return cfFine;
}


eCodeFile SaveSingleEdge(FILE *fl, sEdge edge)
{
    fprintf(fl, "%d %d\n", edge.from + 1, edge.to + 1);
    return cfFine;
}

