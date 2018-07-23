#include "model_loadparts.h"
#include "fileworks.h"

void ClearPointsList(sPointsList *p)
{
	if (!p)
		return;
	delete p->pointsArray;
	p->pointsArray = nullptr;
	p->count = 0;
}


void ClearEdgesList(sEdgesList *e)
{
	if (!e)
		return;
	delete e->edgesArray;
	e->edgesArray = nullptr;
	e->count = 0;
}


eCodeFile LoadPoints(sPointsList *points, FILE *fl)
{
	eCodeFile res = cfFine;

	for (int i = 0;  (i < points->count) && (res == cfFine);  i++)
	{
        res = LoadSinglePoint(&(points->pointsArray[i]), fl);
	}
	return res;
}

eCodeFile SavePoints(sPointsList points, FILE *fl)
{
    eCodeFile res = cfFine;
    res = SaveCount(fl, points.count);

    for (int i = 0; (i < points.count) && (res == cfFine);  i++)
        res = SaveSinglePoint(fl, points.pointsArray[i]);
    return res;
}

eCodeFile LoadEdges(sEdgesList *edges, FILE *fl)
{
	eCodeFile res = cfFine;

	for (int i = 0;  (i < edges->count) && (res == cfFine);  i++)
	{
        res = LoadSingleEdge(&(edges->edgesArray[i]), fl);
	}
	return res;
}

eCodeFile SaveEdges(sEdgesList edges, FILE *fl)
{
    eCodeFile res = cfFine;
    res = SaveCount(fl, edges.count);

    for (int i = 0; (i < edges.count) && (res == cfFine);  i++)
        res = SaveSingleEdge(fl, edges.edgesArray[i]);

    return res;
}


eAllocError AllocPointsList(sPointsList *points)
{
	points->pointsArray = new sPoint3d[points->count];

	if (!points->pointsArray)
		return aeOutOfMemory;

	return aeFine;
}


eAllocError AllocEdgesList(sEdgesList *edges)
{
	edges->edgesArray = new sEdge[edges->count];

	if (!edges->edgesArray)
		return aeOutOfMemory;

	return aeFine;
}


eCodeFile TryLoadPoints(sPointsList *points, FILE *fl)
{	
    eCodeFile res = LoadCount(points->count, fl);
    if (res == cfFine)
    {
            //return res;

        if (AllocPointsList(points) == aeOutOfMemory)
            res =  cfOutOfMemory;

        res = LoadPoints(points, fl);

        if (res != cfFine)
            ClearPointsList(points);
    }

	return res;
}

eCodeFile TryLoadEdges(sEdgesList *edges, FILE *fl)
{
    eCodeFile res = LoadCount(edges->count, fl);
    if (res == cfFine)
    {
            //return res;

        if (AllocEdgesList(edges) == aeOutOfMemory)
            res =  cfOutOfMemory;

        res = LoadEdges(edges, fl);

        if (res != cfFine)
            ClearEdgesList(edges);
    }

	return res;
}
