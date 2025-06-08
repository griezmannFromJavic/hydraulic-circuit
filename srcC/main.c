/*======================================== TODO ========================================*\

Real links parser, Lagrange polynomials, and graph logic are implemented.

Solver is yet to be implemented.

Graph must be connected with only one link between two nodes (simple).

Memory needs freeing in som functions: treePathDFS() and findTreePath()

\*======================================================================================*/



#include "parser.h"
#include "lagrange.h"
#include "graph.h"
#include "helper.h"
#include "solver.h"

#include <stdio.h>


int main() {
	LinkArray realLinks = realGraphParser();
	printf("graph:                ");
	printLinkArray(realLinks);
	
	int bcCount;
    BoundaryCondition* BCs = boundaryParser(&bcCount);
    printf("boundary conditions:  ");
    printBoundaryConditions(BCs, bcCount);
    
    LinkArray ficticiousLinks = fictitiousTree(BCs, bcCount);
	printf("ficticious test:      ");
	printLinkArray(ficticiousLinks);
    
    //int firstP = firstSetPressureNode(bcCount, BCs);
	
	LinkArray graph = mergeGraphs(realLinks, ficticiousLinks);
	
	LinkArray tree = generateTree(graph, 0);
	printf("tree:                 ");
	printLinkArray(tree);
	
	LinkArray chords = nonTreeLinks(graph, tree);
	printf("chords:               ");
	printLinkArray(chords);
	
	IntArray nodes = extractNodes(graph);
	printf("nodes:                ");
	printIntArray(nodes);
	
	
	DoubleArray* direction0 = malloc(sizeof(DoubleArray));
	direction0->size = 0;
    LinkArray path0 = findTreePath(tree, chords.data[0], direction0);
	printf("path from chord 0:    ");
    printLinkArray(path0);
    
    printf("path directions:      ");
    printDoubleArray(*direction0);
    

    
    DoubleArray loopFlows;
    double a[] = {10.0, 5.0, 1.0};
    loopFlows.data = a;
    loopFlows.size = 3;
    DoubleArray flows = linkFlows(loopFlows, chords, tree, graph);
    printf("flows:                ");
    printDoubleArray(flows);
    
    DoubleArray dps = pressureDrops(flows, graph);
    printf("pressure drops:       ");
    printDoubleArray(dps);
    
    
    DoubleArray p = pressures(graph, tree, chords, loopFlows, nodes);
    
    printf("pressures:            ");
    printDoubleArray(p);
    
    
	return 0;
}


