/*================================== ABOUT ==================================*\

Miscalanious helper functions

\*===========================================================================*/

#include "helper.h"


double* extractColumn(double** points, int pointsSize, int column) {
    double* result = malloc(pointsSize * sizeof(double));
    for (int i = 0; i < pointsSize; i++) {
        result[i] = points[i][column];
    }
    return result;
}


bool member(int element, IntArray arr) {
    for (int i = 0; i < arr.size; i++) {
        if (element == arr.data[i]) return true;
    }
    return false;
}

bool memberInRange(int element, int* arr, int range) {
    for (int i = 0; i < range; i++) {
        if (element == arr[i]) return true;
    }
    return false;
}

void printIntArray(IntArray x) {
    printf("[");
    int i;
    for (i = 0; i < x.size - 1; i++) {
        printf("%d, ", x.data[i]);
    }
    printf("%d]\n", x.data[i]);
}

IntArray setIntersection(IntArray s1, IntArray s2) {
    IntArray intersection;
    int* iData = malloc(s1.size * sizeof(int));
    int iSize = 0;
    
    for (int i = 0; i < s1.size; i++) {
        if (member(s1.data[i], s2)) iData[iSize++] = s1.data[i];
    }
    
    intersection.size = iSize;
    intersection.data = iData;
    return intersection;
}

IntArray setDifference(IntArray s1, IntArray s2) {
    IntArray intersection;
    int* iData = malloc(s1.size * sizeof(int));
    int iSize = 0;
    
    for (int i = 0; i < s1.size; i++) {
        if (!member(s1.data[i], s2)) iData[iSize++] = s1.data[i];
    }
    
    intersection.size = iSize;
    intersection.data = iData;
    return intersection;
}



