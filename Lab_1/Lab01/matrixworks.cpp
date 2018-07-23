#include <math.h>
#include "matrixworks.h"

#define ZERO 0
#define ONE 1


double *MultVectorXMatrix(double *V, double *M, int d)
{
	d++;
	double *res = new double[d];
	for (int i = 0; i < d; i++)
	{
		double s = 0;
		for (int j = 0; j < d; j++)
		{
			s += V[j] * M[j*d + i];
		}
		res[i] = s;
	}
	return res;
}


double *MultMatrixXMatrix(double *M1, double *M2, int d)
{
	d++;
	double *res = new double[d*d];
	for (int i = 0; i < d; i++)
	{

		for (int j = 0; j < d; j++)
		{
			double s = 0;
			for (int k = 0; k < d; k++)
			{
				s += M1[i*d + k] * M2[k*d + j];
			}
			res[i*d + j] = s;
		}
	}
	return res;
}


double *Get3DRotateXMatrix(double ang)
{
	double *M = new double[16];
	if (!M)
		return nullptr;
	
    M[0] = ONE;
    M[1] = ZERO;
    M[2] = ZERO;
    M[3] = ZERO;

    M[4] = ZERO;
	M[5] = cos(ang);
	M[6] = -sin(ang);
    M[7] = ZERO;

    M[8] = ZERO;
	M[9] = sin(ang);
	M[10] = cos(ang);
    M[11] = ZERO;

    M[12] = ZERO;
    M[13] = ZERO;
    M[14] = ZERO;
    M[15] = ONE;
	return M;
}


double *Get3DRotateYMatrix(double ang)
{
	double *M = new double[16];
	if (!M)
		return nullptr;
	
	M[0] = cos(ang);
    M[1] = ZERO;
	M[2] = sin(ang);
    M[3] = ZERO;

    M[4] = ZERO;
    M[5] = ONE;
    M[6] = ZERO;
    M[7] = ZERO;

	M[8] = -sin(ang);
    M[9] = ZERO;
	M[10] = cos(ang);
    M[11] = ZERO;

    M[12] = ZERO;
    M[13] = ZERO;
    M[14] = ZERO;
    M[15] = ONE;
	return M;
}


double *Get3DRotateZMatrix(double ang)
{
	double *M = new double[16];
	if (!M)
		return nullptr;
	
	M[0] = cos(ang);
	M[1] = -sin(ang);
    M[2] = ZERO;
    M[3] = ZERO;

	M[4] = sin(ang);
	M[5] = cos(ang);
    M[6] = ZERO;
    M[7] = ZERO;

    M[8] = ZERO;
    M[9] = ZERO;
    M[10] = ONE;
    M[11] = ZERO;

    M[12] = ZERO;
    M[13] = ZERO;
    M[14] = ZERO;
    M[15] = ONE;
	return M;
}


double *Get3DShiftMatrix(double dx, double dy, double dz)
{
	double *M = new double[16];
	if (!M)
		return nullptr;
	
    M[0] = ONE;
    M[1] = ZERO;
    M[2] = ZERO;
    M[3] = ZERO;

    M[4] = ZERO;
    M[5] = ONE;
    M[6] = ZERO;
    M[7] = ZERO;

    M[8] = ZERO;
    M[9] = ZERO;
    M[10] = ONE;
    M[11] = ZERO;

	M[12] = dx;
	M[13] = dy;
	M[14] = dz;
    M[15] = ONE;
	return M;
} 


double *Get3DScaleMatrix(double scale)
{
	double *M = new double[16];
	if (!M)
		return nullptr;
	
	M[0] = scale;
    M[1] = ZERO;
    M[2] = ZERO;
    M[3] = ZERO;

    M[4] = ZERO;
	M[5] = scale;
    M[6] = ZERO;
    M[7] = ZERO;

    M[8] = ZERO;
    M[9] = ZERO;
	M[10] = scale;
    M[11] = ZERO;

    M[12] = ZERO;
    M[13] = ZERO;
    M[14] = ZERO;
    M[15] = ONE;
	return M;
}
