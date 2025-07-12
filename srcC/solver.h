#ifndef SOLVER_H
#define SOLVER_H

#include "helper.h"
#include "lagrange.h"
#include "graph.h"

#include <stdio.h>
#include <stdbool.h>


DoubleArray linkFlows(DoubleArray loopFlows, LinkArray chords, LinkArray tree, LinkArray graph);

DoubleArray pressureDrops(DoubleArray flows, LinkArray graph);

void pressureDropsAndGradients(DoubleArray flows, LinkArray graph, DoubleArray* dps, DoubleArray* DdpPerDx);

int nodeIndex(int node, IntArray nodes);

DoubleArray pressures(LinkArray graph, LinkArray tree, LinkArray chords, DoubleArray loopFlows, IntArray nodes, int root);

double sumLoopPressureDrops(LinkArray loop, LinkArray graph, DoubleArray direction, DoubleArray pressureDrops);

//DoubleArray residual(DoubleArray assumedLoopFlows, LinkArray graph, LinkArray chords, LinkArray tree);

double manhattan(DoubleArray error);


#endif // SOLVER_H
