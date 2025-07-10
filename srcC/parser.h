#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "helper.h"
#include "graph.h"
#include "lagrange.h"

void removeExcess(char* line);
Link parseLink(char* line, FILE* file);
LagrangeData parsePoints(FILE* file);
Link* parseLinks(FILE* file, int* linkCount);
LinkArray realGraphParser(char* input);
BoundaryCondition* boundaryParser(int* count);

#endif // PARSER_H
