#ifndef LAGRANGE_H
#define LAGRANGE_H

#include <stdbool.h>


typedef struct LagrangeData LagrangeData;
struct LagrangeData fillLagrangeData(double** points, int pointsSize);
double* extractXY(double** points, int pointsSize, bool extractingY);
double* barycentricWeights(double* xs, int xsSize);
double** compute_differentiation_matrix(struct LagrangeData d);
typedef double (*PolynomialFunc)(struct LagrangeData*, double);
double lagrangePolynomial(struct LagrangeData d, double xEval);
double lagrangeDerivative(struct LagrangeData d, double xEval);

struct LagrangeData {
    int pointsSize;
    double** points;
    double* xs;
    double* ys;
	double* weights;
	double** differentiationMatrix;
};


#endif // LAGRANGE_H
