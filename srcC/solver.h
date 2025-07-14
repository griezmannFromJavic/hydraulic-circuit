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

double dPdX(LinkArray loopM, LinkArray loopN, double x);

double manhattan(DoubleArray error);

#endif // SOLVER_H
