#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "graph.h"
#include "lagrange.h"

void removeExcess(char* line);
Link parseLink(char* line, FILE* file);
LagrangeData parsePoints(FILE* file);
Link* parseLinks(FILE* file, int* linkCount);
LinkArray realLinksParser();

#endif // PARSER_H
