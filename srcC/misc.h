#ifndef MISC_H
#define MISC_H

#include "helper.h"
#include "lagrange.h"
#include "graph.h"

int nodeIndex(int node, IntArray nodes);

DoubleArray pressuresDFS(LinkArray tree, LinkArray graph, IntArray nodes,
    bool* checked, int node, DoubleArray flows, DoubleArray p);

DoubleArray pressures(LinkArray graph, LinkArray tree, LinkArray chords, DoubleArray loopFlows, IntArray nodes, int root);

double sumLoopPressureDrops(LinkArray loop, LinkArray graph, DoubleArray direction, DoubleArray pressureDrops);

double loopPressureDiff(LinkArray loopM, LinkArray* loops, int loopsSize, double x);

#endif // MISC_H
