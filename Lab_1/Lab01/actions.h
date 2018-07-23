#pragma once

#include "render.h"

void ChangeScale(sRenderData *renderdata, double scale);

void ChangeRotation(sRenderData *renderdata, sMove move);

void SetRotation(sRenderData *renderdata, sMove move);

void ChangeShift(sRenderData *renderdata, sMove move);

void InitializeRenderData(sRenderData *renderdata);
