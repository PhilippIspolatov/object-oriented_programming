#include "canvasworks.h"
#include "render.h"


sCanvasPoint CanvasPoint(int fromX, int fromY)
{
	sCanvasPoint pt;
	pt.x = fromX;
	pt.y = fromY;
	return pt;
}


void DrawLine(sCanvasContainer *canvas, sCanvasPoint &from, sCanvasPoint &to)
{
    canvas->pb->addLine(from.x, -from.y,  to.x, -to.y,QPen(Qt::red));
}
