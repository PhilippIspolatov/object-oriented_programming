
#include "actions.h"
#include "render.h"	
#include "conversions.h"
#include "matrixworks.h"

void ChangeScale(sRenderData *renderdata, double scale)
{
	renderdata->M = scale;
}


void ChangeRotation(sRenderData *renderdata, sMove move)
{
	renderdata->fx += move.dx;
	renderdata->fy += move.dy;
	renderdata->fz += move.dz;
}


void SetRotation(sRenderData *renderdata, sMove move)
{
	renderdata->fx = move.dx;
	renderdata->fy = move.dy;
	renderdata->fz = move.dz;
}


void ChangeShift(sRenderData *renderdata, sMove move)
{
	renderdata->dx += move.dx;
	renderdata->dy += move.dy;
	renderdata->dz += move.dz;
}

void InitializeRenderData(sRenderData *renderdata)
{
    renderdata->fx = 0;
    renderdata->fy = 0;
    renderdata->fz = 0;
    renderdata->dx = 0;
    renderdata->dy = 0;
    renderdata->dz = 0;
    renderdata->M = 1;
}
