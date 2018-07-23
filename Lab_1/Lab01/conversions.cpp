
#include "conversions.h"
#include "canvasworks.h"
#include "matrixworks.h"
#include "fileworks.h"

#include <QDebug>

void deleteFewMatr(double *matr1, double *matr2, double *matr3) {
    delete matr1;
    delete matr2;
    delete matr3;
}

double *getRotateMatr(sRenderData *data) {
    double *RotateZMatrix = Get3DRotateZMatrix(data->fz);
    if (!RotateZMatrix)
        return nullptr;

    double *RotateYMatrix = Get3DRotateYMatrix(data->fy);
    if (!RotateYMatrix) {
        delete RotateZMatrix;
        return nullptr;
    }

    double *RotateXMatrix = Get3DRotateXMatrix(data->fx);
    if (!RotateXMatrix) {
        delete RotateYMatrix;
        delete RotateZMatrix;
        return nullptr;
    }

    double *tmp = MultMatrixXMatrix(RotateZMatrix, RotateYMatrix, 3);
    if (!tmp) deleteFewMatr(RotateXMatrix, RotateYMatrix, RotateZMatrix);

    double *result = MultMatrixXMatrix(tmp, RotateXMatrix, 3);
    if (!result) {
        delete tmp;
        deleteFewMatr(RotateXMatrix, RotateYMatrix, RotateZMatrix);
    }

    return result;
}

double *GetConversionMatrix(sRenderData *data)
{
    double *ShiftMatrix = Get3DShiftMatrix(data->dx, data->dy, data->dz);
    if (!ShiftMatrix)
        return nullptr;

    double *allRotMatr = getRotateMatr(data);
    if (!allRotMatr) {
        delete ShiftMatrix;
        return nullptr;
    }

    double *ScaleMatrix = Get3DScaleMatrix(data->M);
    if (!ScaleMatrix) {
        delete ShiftMatrix;
        delete allRotMatr;
		return nullptr;
	}

    double *tmp = MultMatrixXMatrix(ShiftMatrix, allRotMatr, 3);
    if (!tmp) {
        deleteFewMatr(ShiftMatrix, tmp, allRotMatr);
    }

    double *result = MultMatrixXMatrix(tmp, ScaleMatrix, 3);
    if (!result) {
        deleteFewMatr(ShiftMatrix, allRotMatr, ScaleMatrix);
        delete tmp;
		return nullptr;
	}

    deleteFewMatr(ShiftMatrix, allRotMatr, ScaleMatrix);
    delete tmp;

    return result;
}


sCanvasPoint* ConvertSinglePoint(sPoint3d *p, double *ConvMatrix)
{
    double *pVector = new double[4];
    if (!pVector)
		return nullptr;
	
	pVector[0] = p->x;
	pVector[1] = p->y;
	pVector[2] = p->z;
	pVector[3] = 1;

	double *conversion = MultVectorXMatrix(pVector, ConvMatrix, 3);

    delete [] pVector;

	if (!conversion) return nullptr;

	sCanvasPoint *res = new sCanvasPoint;
	if (!res)
	{
		delete conversion;
		return nullptr;
	}

	res->x = (int) conversion[0];
	res->y = (int) conversion[1];
	delete conversion;

	return res;
}

sConvertedPoints* AllocateConvertedPoints(int count)
{
	sConvertedPoints *conv = new sConvertedPoints;
	if (!conv) return nullptr;

    int *Xs = new int [count];
	if (!Xs)
	{
		delete conv;
		return nullptr;
	}
    int *Ys = new int [count];
	if (!Ys)
	{
		delete conv;
        delete [] Xs;
		return nullptr;
	}

	conv->count = count;
	conv->Xs = Xs;
	conv->Ys = Ys;
	return conv;
}


sConvertedPoints* ConvertPoints(sPointsList *points, sRenderData *params)
{
    sConvertedPoints *conv = AllocateConvertedPoints(points->count);

	if (!conv) return nullptr;

    double *ConvMatrix = GetConversionMatrix(params);
	if (!ConvMatrix)
	{
		delete conv;
		return nullptr;
	}

	for (int i=0; i<points->count; i++)
	{
		sCanvasPoint *point = ConvertSinglePoint(points->pointsArray + i, ConvMatrix);
		conv->Xs[i] = point->x;
		conv->Ys[i] = point->y;
		delete point;
	}

	delete ConvMatrix;

	return conv;
}

void ClearConvertedPoints(sConvertedPoints *converted)
{
	delete converted->Xs;
	delete converted->Ys;
	delete converted;
}
