#include "parser.h"
#include "lagrange.h"
#include "graph.h"
#include "helper.h"

#include <stdio.h>

/*======================================== TODO ========================================*\

Real links parser, Lagrange polynomials, and graph logic are implemented.

Solver is yet to be implemented.

Now implementing DFS for creating a spanning tree.

\*======================================================================================*/



int main() {

	LinkArray realLinks = realLinksParser();

	IntArray nodes = extractNodes(realLinks);

	// printLinkArray(realLinks);

	LinkArray tree = generateTree(realLinks, 4);

	printLinkArray(tree);

	return 0;
}
