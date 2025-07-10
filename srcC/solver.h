#ifndef SOLVER_H
#define SOLVER_H

#include "helper.h"
#include "lagrange.h"
#include "graph.h"

#include <stdio.h>
#include <stdbool.h>


DoubleArray linkFlows(DoubleArray loopFlows, LinkArray chords, LinkArray tree, LinkArray graph);

DoubleArray pressureDrops(DoubleArray flows, LinkArray graph);

int nodeIndex(int node, IntArray nodes);

DoubleArray pressures(LinkArray graph, LinkArray tree, LinkArray chords, DoubleArray loopFlows, IntArray nodes, int root);

double sumLoopPressureDrops(LinkArray loop, DoubleArray direction, LinkArray graph, DoubleArray flows);

#endif // SOLVER_H
