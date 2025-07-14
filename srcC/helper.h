#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct {
    int* data;
    int size;
} IntArray;

typedef struct {
    double* data;
    int size;
} DoubleArray;

typedef struct {
    double** data;
    int rows;
    int cols;
} DoubleMatrix;

typedef struct {
    int node;
    char type;
    double value;
} BoundaryCondition;


double* extractColumn(double** points, int pointsSize, int column);

bool member(int element, IntArray arr);

bool memberInRange(int element, int* arr, int range);

void printIntArray(IntArray x);

void printDoubleArray(DoubleArray x);

double sumDoubleArray(DoubleArray x);

void printBoundaryConditions(BoundaryCondition* BCs, int bcCount);

bool neighbours(
    int** adjList, int* adjListSizes,
    int* nodes, int nodesSize,
    int node1, int node2
    );

IntArray setIntersection(IntArray s1, IntArray s2);

IntArray setDifference(IntArray s1, IntArray s2);

void printAdjList(int* nodes, int nodesSize, int** adjList, int* adjListSizes);

int firstSetPressureNode(int bcCount, BoundaryCondition* BCs);

#endif // HELPER_H
