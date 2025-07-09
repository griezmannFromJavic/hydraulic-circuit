#ifndef GRAPH_H
#define GRAPH_H

#include "lagrange.h"
#include "helper.h"



typedef struct Link {
    char* name;
	int inletNode;
	int outletNode;
	char type;
	double bcValue;
	struct LagrangeData lData;
} Link;

typedef struct {
    Link* data;
    int size;
} LinkArray;

Link fillLink(char* name, int inlet, int outlet, char type, struct LagrangeData lData);

bool isSameLink(Link a, Link b);

IntArray extractNodes(LinkArray links);

IntArray adjacent(int node, LinkArray links);

Link findLink(int node1, int node2, LinkArray graph);

int linkIndex(Link link, LinkArray graph);

LinkArray generateTree(LinkArray graph, int root);

LinkArray nonTreeLinks(LinkArray graph, LinkArray tree);

//LinkArray treePathDFS(LinkArray tree, bool* passed, int finish, int curr, LinkArray path);
LinkArray treePathDFS(LinkArray tree, bool* passed, int finish, int curr, LinkArray path, DoubleArray* direction);

//LinkArray findTreePath(LinkArray tree, Link chord);
LinkArray findTreePath(LinkArray tree, Link chord, DoubleArray* direction);

void printLinkArray(LinkArray x);

LinkArray mergeGraphs(LinkArray g1, LinkArray g2);

LinkArray fictitiousTree(BoundaryCondition* bc, int count);


#endif // GRAPH_H
