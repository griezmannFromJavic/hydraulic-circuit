
/*================================== ABOUT ==================================*\

Network topology definition and related functions.

\*===========================================================================*/


#include "graph.h"
#include "helper.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// #include <math.h>



void printLinkArray(LinkArray x) {
	for(int i = 0; i < x.size; i++) {
		//int a = x.data[i].inletNode;
        //int b = x.data[i].outletNode;
		//printf("[%d, %d] ", a, b);
		printf("%s ", x.data[i].name);
	}
	printf("\n");
}


Link fillLink(char* name, int inlet, int outlet, struct LagrangeData lData) {
    struct Link d;
    d.name = name;
    d.inletNode = inlet;
    d.outletNode = outlet;
    d.lData = lData;

    return d;
}



IntArray extractNodes(LinkArray links) {
    IntArray nodes;
    int count = 0;
    int capacity = 16;
    int* tempNodes = malloc(capacity * sizeof(int));

    for (int i = 0; i < links.size; i++) {
        int a = links.data[i].inletNode;
        int b = links.data[i].outletNode;

        if (!memberInRange(a, tempNodes, count))
            tempNodes[count++] = a;
        if (!memberInRange(b, tempNodes, count))
            tempNodes[count++] = b;
    }

        if (count >= capacity) {
            capacity *= 2;
            tempNodes = realloc(tempNodes, capacity * sizeof(int));
        }

    nodes.data = tempNodes;
    nodes.size = count;

    return nodes;
}

IntArray adjacent(IntArray nodes, int node, LinkArray links) {
    IntArray adjList;
    int count = 0;
    int a;
    int b;

    int* temp = malloc((links.size + 1) * sizeof(int)); // max num of nodes of a connected graph given number of links. i guess?

    for (int i = 0; i < links.size; i++) {
        a = links.data[i].inletNode;
        b = links.data[i].outletNode;
        if (node == a) temp[count++] = b;
        if (node == b) temp[count++] = a;
    }
    adjList.size = count;
    adjList.data = temp;

    return adjList;
}


Link findLink(int node1, int node2, LinkArray graph) {
    for (int i = 0; i < graph.size; i++) {
        Link curr = graph.data[i];
        int a = curr.inletNode;
        int b = curr.outletNode;
        if ((a == node1 && b == node2) || (a == node2 && b == node1)) return curr;
    }
    printf("ERROR: Link with nodes [%d, %d] does not exist in a graph.", node1, node2);
    Link uninitLink;
    exit(EXIT_FAILURE);
}


void dfs(LinkArray graph, LinkArray* tree, IntArray nodes, IntArray* visited, int current) {
    if (member(current, *visited)) return;
    visited->data[visited->size++] = current;

    IntArray neighbours = adjacent(nodes, current, graph);

    for (int i = 0; i < neighbours.size; i++) {
        int next = neighbours.data[i];
        if (!member(next, *visited)) {
            Link l = findLink(current, next, graph);
            tree->data[tree->size++] = l;
            dfs(graph, tree, nodes, visited, next);
        }

    }

    free(neighbours.data);
}


LinkArray generateTree(LinkArray graph, int root) {
    LinkArray tree;
    tree.data = malloc((graph.size + 1) * sizeof(Link)); // size of spanning tree
    tree.size = 0;

    IntArray visited;
    visited.data = malloc((graph.size + 1) * sizeof(int));
    visited.size = 0;

    IntArray nodes = extractNodes(graph);

    dfs(graph, &tree, nodes, &visited, root);

    free(nodes.data);
    return tree;
}
