#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct {
    int* data;
    int size;
} IntArray;


double* extractColumn(double** points, int pointsSize, int column);

bool member(int element, IntArray arr);

bool memberInRange(int element, int* arr, int range);

void printIntArray(IntArray x);

/*
bool neighbours(
    int** adjList, int* adjListSizes,
    int* nodes, int nodesSize,
    int node1, int node2
    );
*/

IntArray setIntersection(IntArray s1, IntArray s2);

IntArray setDifference(IntArray s1, IntArray s2);

void printAdjList(int* nodes, int nodesSize, int** adjList, int* adjListSizes);

#endif // HELPER_H
