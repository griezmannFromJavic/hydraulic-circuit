/*================================== ABOUT ==================================*\

All functions and structures related to the Lagrange polynomial representation
of flow(pressure drop) in a link.

\*===========================================================================*/

#include "lagrange.h"
#include "helper.h"

// #include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-12


double* barycentricWeights(double* xs, int xsSize) {
    double* weights = malloc(xsSize * sizeof(double));
    for (int i = 0; i < xsSize; i++) {
        weights[i] = 1.0;
        for (int j = 0; j < xsSize; j++) {
            if (i != j)
                weights[i] /= (xs[i] - xs[j]);
        }
    }
    return weights;
}

double** compute_differentiation_matrix(struct LagrangeData d) {
    const double* x = d.xs;
    const double* w = d.weights;
    int n = d.pointsSize;

    double** D = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        D[i] = calloc(n + 1, sizeof(double));
    }

    // fill off-diagonal entries
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                D[i][j] = (w[j] / w[i]) / (x[i] - x[j]);
            }
        }
    }

    // fill diagonal entries
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += D[i][j];
        }
        D[i][i] = -sum;
    }
    return D;
}

double lagrangePolynomial(struct LagrangeData d, double xEval) {
    double* x = d.xs;
    double* y = d.ys;
    double* w = d.weights;
    int n = d.pointsSize;

    double num = 0.0;
    double den = 0.0;

    for (int i = 0; i < n; i++) {
        if (fabs(xEval - x[i]) < EPSILON) {
            return y[i];
        }
        double temp = w[i] / (xEval - x[i]);
        num += temp * y[i];
        den += temp;
    }
    return num / den;
}

double lagrangeDerivative(struct LagrangeData d, double xEval) {
    int n = d.pointsSize;
    double* x = d.xs;
    double* y = d.ys;
    double* w = d.weights;
    double** D = d.differentiationMatrix;

    // Check if xEval coincides with any node
    for (int i = 0; i < n; i++) {
        if (fabs(xEval - x[i]) < EPSILON) {
            // Compute derivative at node x[i] using differentiation matrix row i
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += D[i][j] * y[j];
            }
            return sum;
        }
    }

    // General barycentric derivative formula (xEval not on a node)
    double num = 0.0;
    double den = 0.0;
    double s = 0.0;

    for (int i = 0; i < n; i++) {
        double diff = xEval - x[i];
        double temp = w[i] / diff;
        num += temp * y[i];
        den += temp;
        s += temp * y[i] / diff;
    }

    return (s * den - num * num) / (den * den);
}


struct LagrangeData fillLagrangeData(double** points, int pointsSize) {
    struct LagrangeData d;
    d.pointsSize = pointsSize;
    d.points = points;
    d.xs = extractColumn(d.points, d.pointsSize, 0);
    d.ys = extractColumn(d.points, d.pointsSize, 1);
    d.weights = barycentricWeights(d.xs, d.pointsSize);
    d.differentiationMatrix = compute_differentiation_matrix(d);

    return d;
}
