/*======================================== TODO ========================================*\

Real links parser, Lagrange polynomials, and graph logic are implemented.

Graph must be connected with only one link between two nodes (simple graph).

Memory needs freeing in some functions: treePathDFS() and findTreePath()

SINCE ONE PRESSURE BOUNDARY CONDITION MUST BE DEFINED, THAT LINK WILL BE CHOSEN FOR TREE TRAVERSAL.
upper idea must be implemented

\*======================================================================================*/



#include "parser.h"
// #include "lagrange.h" // used mostly in "graph.c" and "solver.c"
#include "graph.h"
#include "helper.h"
#include "solver.h"

#include <stdio.h>


int main() {
    char input[] = "inputsTutorial";
	LinkArray realLinks = realGraphParser(input);
	// printf("real graph:           ");
	// printLinkArray(realLinks);

	int bcCount;
    BoundaryCondition* BCs = boundaryParser(&bcCount);
    // printf("boundary conditions:  ");
    // printBoundaryConditions(BCs, bcCount);

    LinkArray ficticiousLinks = fictitiousTree(BCs, bcCount);
	// printf("ficticious links:     ");
	// printLinkArray(ficticiousLinks);

	LinkArray graph = mergeGraphs(realLinks, ficticiousLinks);
	// printf("complete graph:       ");
	// printLinkArray(graph);

	LinkArray tree = generateTree(graph, 0);
	// printf("tree:                 ");
	// printLinkArray(tree);

	LinkArray chords = nonTreeLinks(graph, tree);
	// printf("chords:               ");
	// printLinkArray(chords);

	IntArray nodes = extractNodes(graph);
	// printf("nodes:                ");
	// printIntArray(nodes);





	return 0;
}
