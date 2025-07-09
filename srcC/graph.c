
/*================================== ABOUT ==================================*\

Network topology definition and related functions.

\*===========================================================================*/


#include "graph.h"
#include "parser.h"
#include "helper.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



void printLinkArray(LinkArray x) {
	for(int i = 0; i < x.size; i++) {
		//int a = x.data[i].inletNode;
        //int b = x.data[i].outletNode;
		//printf("[%d, %d] ", a, b);
		printf("%s ", x.data[i].name);
	}
	printf("\n");
}


Link fillLink(char* name, int inlet, int outlet, char type, struct LagrangeData lData) {
    struct Link d;
    d.name = name;
    d.inletNode = inlet;
    d.outletNode = outlet;
    d.type = type;
    d.lData = lData;

    return d;
}

bool isSameLink(Link a, Link b) { // program is limited to "simple" graphs
    return (
        a.inletNode == b.inletNode &&
        a.outletNode == b.outletNode
        );
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

IntArray adjacent(int node, LinkArray links) {
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
    exit(EXIT_FAILURE);
}

int linkIndex(Link link, LinkArray graph) {
    for (int i = 0; i < graph.size; i++) {
        if (isSameLink(link, graph.data[i])) return i;
    }
    printf("ERROR: Link %s does not exist in graph.", link.name);
    return -1;
}



void treeDFS(LinkArray graph, LinkArray* tree, IntArray nodes, IntArray* visited, int current) {
    if (member(current, *visited)) return;
    visited->data[visited->size++] = current;

    IntArray neighbours = adjacent(current, graph);

    for (int i = 0; i < neighbours.size; i++) {
        int next = neighbours.data[i];
        if (!member(next, *visited)) {
            Link l = findLink(current, next, graph);
            tree->data[tree->size++] = l;
            treeDFS(graph, tree, nodes, visited, next);
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

    treeDFS(graph, &tree, nodes, &visited, root);

    free(nodes.data);
    return tree;
}

// original treePathDFS() did not keep track on the direction of the loop
// which semes to be necessary
/*
LinkArray treePathDFS(LinkArray tree, bool* passed, int finish, int curr, LinkArray path) {
    if (curr == finish) {
        return path;
    }
    bool* newPassed = malloc(tree.size * sizeof(bool));
    memcpy(newPassed, passed, tree.size * sizeof(bool));
    for (int i = 0; i < tree.size; i++) {
        if (!passed[i] && tree.data[i].inletNode == curr) {
            newPassed[i] = true;
            path.data[path.size++] = tree.data[i];
            LinkArray temp = treePathDFS(tree, newPassed, finish, tree.data[i].outletNode, path);
            free(newPassed);
            return temp;
        } else if (!passed[i] && tree.data[i].outletNode == curr) {
            newPassed[i] = true;
            path.data[path.size++] = tree.data[i];
            LinkArray temp = treePathDFS(tree, newPassed, finish, tree.data[i].inletNode, path);
            free(newPassed);
            return temp;
        }
    }
}

LinkArray findTreePath(LinkArray tree, Link chord) {
    LinkArray path;
    path.data[0] = chord;
    path.size = 1;
    int finish = chord.inletNode;
    int curr = chord.outletNode;
    bool* passed = calloc(tree.size, sizeof(bool)); // init to all false
    for (int i = 0; i < tree.size; i++) {
        if (isSameLink(tree.data[i], chord)) {
            passed[i] = true;
            break;
        }
    }

    return treePathDFS(tree, passed, finish, curr, path);
}
*/

/*
LinkArray treePathDFS(LinkArray tree, bool* passed, int finish, int curr, LinkArray path, DoubleArray* direction) {
    printf("%d\n", curr);
    if (curr == finish) {
        return path;
    }
    bool* newPassed = malloc(tree.size * sizeof(bool));
    memcpy(newPassed, passed, tree.size * sizeof(bool));

    for (int i = 0; i < tree.size; i++) {
        if (!passed[i] && tree.data[i].inletNode == curr) {
            newPassed[i] = true;
            direction->data[path.size] = +1.0;
            path.data[path.size++] = tree.data[i];
            direction->size = path.size;
            return treePathDFS(tree, newPassed, finish, tree.data[i].outletNode, path, direction);
        } else if (!passed[i] && tree.data[i].outletNode == curr) {
            newPassed[i] = true;
            direction->data[path.size] = -1.0;
            path.data[path.size++] = tree.data[i];
            direction->size = path.size;
            return treePathDFS(tree, newPassed, finish, tree.data[i].inletNode, path, direction);
        }
    }
}
*/

LinkArray treePathDFS(LinkArray tree, bool* passed, int finish, int curr, LinkArray path, DoubleArray* direction) {
    bool* newPassed = malloc(tree.size * sizeof(bool));
    memcpy(newPassed, passed, tree.size * sizeof(bool));

    for (int i = 0; i < tree.size; i++) {
        if (!passed[i] && tree.data[i].inletNode == curr) {
            newPassed[i] = true;
            direction->data[path.size] = +1.0;
            path.data[path.size++] = tree.data[i];
            direction->size = path.size;
            treePathDFS(tree, newPassed, finish, tree.data[i].outletNode, path, direction);
        } else if (!passed[i] && tree.data[i].outletNode == curr) {
            newPassed[i] = true;
            direction->data[path.size] = -1.0;
            path.data[path.size++] = tree.data[i];
            direction->size = path.size;
            treePathDFS(tree, newPassed, finish, tree.data[i].inletNode, path, direction);
        }
    }
    return path;
}

LinkArray findTreePath(LinkArray tree, Link chord, DoubleArray* direction) {
    LinkArray path;
    //printf("%d\n", tree.size);
    path.data = malloc(tree.size * sizeof(Link));
    path.size = 1;
    path.data[0] = chord;

    direction->data = malloc(tree.size * sizeof(double));
    direction->size = 1;
    direction->data[0] = +1.0;

    bool* passed = calloc(tree.size, sizeof(bool)); // init to all false
    int finish = chord.inletNode;
    int curr = chord.outletNode;

    for (int i = 0; i < tree.size; i++) { // add chord to passed
        if (isSameLink(tree.data[i], chord)) {
            passed[i] = true;
            break;
        }
    }

    return treePathDFS(tree, passed, finish, curr, path, direction);
}




// working on the code above

LinkArray nonTreeLinks(LinkArray graph, LinkArray tree) {
    //comparing links by nodes
    LinkArray chords;
    int count = 0;
    chords.data = malloc(graph.size * sizeof(Link));
    for (int i = 0; i < graph.size; i++) {
        Link curr = graph.data[i];
        bool linkInTree = false;
        for (int j = 0; j < tree.size; j++) {
            Link temp = tree.data[j];
            if (isSameLink(curr, temp)) {
                linkInTree = true;
                break;
            }
        }
        if (!linkInTree) {
            chords.data[count++] = curr;
        }
    }
    chords.size = count;
    return chords;
}


LinkArray mergeGraphs(LinkArray g1, LinkArray g2) {
    LinkArray merged;
    merged.size = g1.size + g2.size;
    merged.data = malloc(merged.size * sizeof(Link));
    Link* temp = merged.data;
    memcpy(temp, g1.data, g1.size * sizeof(Link));
    temp += g1.size;
    memcpy(temp, g2.data, g2.size * sizeof(Link));
    return merged;
}



LinkArray fictitiousTree(BoundaryCondition* bc, int count) {
    LinkArray fa;
    fa.size = count;
    fa.data = malloc(count * sizeof(Link));

    Link l;
    for (int i = 0; i < count; i++) {
        char nameBuffer[16];
        snprintf(nameBuffer, sizeof(nameBuffer), "bc%c%d", bc[i].type, bc[i].node);

        l.name = strdup(nameBuffer);
        l.inletNode = 0;
        l.outletNode = bc[i].node;
        l.type = bc[i].type;
        l.bcValue = bc[i].value;

        fa.data[i] = l;
    }

    return fa;
}
