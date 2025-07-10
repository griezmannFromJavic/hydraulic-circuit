/*======================================== TODO ========================================*\

Real links parser, Lagrange polynomials, and graph logic are implemented.

Solver is yet to be implemented.

Graph must be connected with only one link between two nodes (simple).

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
	printf("real graph:           ");
	printLinkArray(realLinks);

	int bcCount;
    BoundaryCondition* BCs = boundaryParser(&bcCount);
    printf("boundary conditions:  ");
    printBoundaryConditions(BCs, bcCount);

    LinkArray ficticiousLinks = fictitiousTree(BCs, bcCount);
	printf("ficticious links:     ");
	printLinkArray(ficticiousLinks);

	LinkArray graph = mergeGraphs(realLinks, ficticiousLinks);
	printf("complete graph:       ");
	printLinkArray(graph);

	LinkArray tree = generateTree(graph, 0);
	printf("tree:                 ");
	printLinkArray(tree);

	LinkArray chords = nonTreeLinks(graph, tree);
	printf("chords:               ");
	printLinkArray(chords);

	IntArray nodes = extractNodes(graph);
	printf("nodes:                ");
	printIntArray(nodes);

    DoubleArray loopFlows;
    // double assumed[] = {10.2, 5.0, 1.0, 20.0, -15.0};
    double* assumed = calloc(chords.size, sizeof(double)); // initial guess = zero vector
    loopFlows.data = assumed;
    loopFlows.size = chords.size;
    DoubleArray flows = linkFlows(loopFlows, chords, tree, graph);
    printf("flows:                ");
    printDoubleArray(flows);

    DoubleArray dps = pressureDrops(flows, graph);
    printf("pressure drops:       ");
    printDoubleArray(dps);

    DoubleArray p = pressures(graph, tree, chords, loopFlows, nodes, 0);

    printf("pressures:            ");
    printDoubleArray(p);






    // generating loops with cooresponding direction vectors
    DoubleArray* directionVectors = malloc(chords.size * sizeof(DoubleArray));
    LinkArray* loops = malloc(chords.size * sizeof(LinkArray));
    DoubleArray errors;
    errors.size = chords.size;
    errors.data = malloc(chords.size * sizeof(double));

    for (int i = 0; i < chords.size; i++) {
       	DoubleArray direction;
        direction.size = 0;
        LinkArray path = findTreePath(tree, chords.data[i], &direction);
        printf("path from chord %d:    ", i);
        printLinkArray(path);



        loops[i] = path;
        directionVectors[i] = direction;
        errors.data[i] = sumLoopPressureDrops(path, direction, graph, flows);
    }

    printf("pressure errors of a given loop:     ");
    printDoubleArray(errors);


	return 0;
}
