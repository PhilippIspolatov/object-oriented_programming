#include "render.h"
#include "canvasworks.h"
#include "conversions.h"
#include <QDebug>

void DrawSingleEdge(sConvertedPoints *converted, sCanvasContainer *canvas, sEdge *edge)
{

    sCanvasPoint p1 = CanvasPoint(converted->Xs[edge->from],
            converted->Ys[edge->from]);
    sCanvasPoint p2 = CanvasPoint(converted->Xs[edge->to],
            converted->Ys[edge->to]);

    DrawLine(canvas,p1,p2);

}

void DrawEdges(sConvertedPoints *converted, sCanvasContainer *canvas, sEdgesList *links)
{
    for (int i = 0; i < links->count; i++)
        DrawSingleEdge(converted, canvas, &(links->edgesArray[i]));
}

void ClearCanvas(sCanvasContainer *canvas)
{
    canvas->pb->clear();
}


eCodeFile DrawModel(sModel *mdl, sCanvasContainer *canvas, sRenderData *params)
{
    eCodeFile res = cfFine;
    if (!mdl || !canvas || !params)
        res =  cfNotFound;

    sConvertedPoints *conv = ConvertPoints(&(mdl->points), params);
    if (!conv) res =  cfOutOfMemory;

    ClearCanvas(canvas);
    DrawEdges(conv, canvas, &(mdl->edges));
	ClearConvertedPoints(conv);

    return res;
}
