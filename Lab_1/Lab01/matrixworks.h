#pragma once


double *MultVectorXMatrix(double *V, double *M, int d);

double *MultMatrixXMatrix(double *M1, double *M2, int d);

double *Get3DRotateXMatrix(double ang);

double *Get3DRotateYMatrix(double ang);

double *Get3DRotateZMatrix(double ang);

double *Get3DShiftMatrix(double dx, double dy, double dz);

double *Get3DScaleMatrix(double scale);
