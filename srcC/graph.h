#ifndef GRAPH_H
#define GRAPH_H

#include "lagrange.h"
#include "helper.h"



typedef struct Link {
    char* name;
	int inletNode;
	int outletNode;
	struct LagrangeData lData;
} Link;

typedef struct {
    Link* data;
    int size;
} LinkArray;

Link fillLink(char* name, int inlet, int outlet, struct LagrangeData lData);

IntArray extractNodes(LinkArray links);

IntArray adjacent(IntArray nodes, int node, LinkArray links);

LinkArray generateTree(LinkArray graph, int root);

void printLinkArray(LinkArray x);


#endif // GRAPH_H