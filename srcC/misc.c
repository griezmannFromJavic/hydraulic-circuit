/*================================== ABOUT ==================================*\

Miscalenious procedures that might and might not be used in the final version.

\*===========================================================================*/

/*
#include "misc.h"
#include "solver.h"
#include "helper.h"
#include "graph.h"
#include "lagrange.h"


DoubleArray pressuresDFS(LinkArray tree, LinkArray graph, IntArray nodes,
                         bool* checked, int node, DoubleArray flows, DoubleArray p) {

	for (int l = 0; l < tree.size; l++) {
		Link link = tree.data[l];
		if (link.inletNode == node && !checked[nodeIndex(link.outletNode, nodes)]) {
		    if (link.type == 'r') {
		        p.data[nodeIndex(link.outletNode, nodes)] =
			    p.data[nodeIndex(link.inletNode, nodes)] +
			    lagrangePolynomial(link.lData, flows.data[linkIndex(link, graph)]);
		    } else if (link.type == 'p') {
		        p.data[nodeIndex(link.outletNode, nodes)] =
			    p.data[nodeIndex(link.inletNode, nodes)] +
			    link.bcValue;
		    }

			checked[nodeIndex(link.outletNode, nodes)] = true;
			pressuresDFS(tree, graph, nodes, checked, link.outletNode, flows, p);
		}
		if (link.outletNode == node && !checked[nodeIndex(link.inletNode, nodes)]) {
		    if (link.type == 'r') {
			    p.data[nodeIndex(link.inletNode, nodes)] =
			    p.data[nodeIndex(link.outletNode, nodes)] -
			    lagrangePolynomial(link.lData, flows.data[linkIndex(link, graph)]);
		    } else if (link.type == 'p') {
		        p.data[nodeIndex(link.outletNode, nodes)] =
			    p.data[nodeIndex(link.inletNode, nodes)] -
			    link.bcValue;
		    }

			checked[nodeIndex(link.inletNode, nodes)] = true;
			pressuresDFS(tree, graph, nodes, checked, link.inletNode, flows, p);
		}
	}
	return p;
}

// to be moved in "helper.c" or later in "postprocessor.c"
// not necessary for solver.
DoubleArray pressures(LinkArray graph, LinkArray tree, LinkArray chords, DoubleArray loopFlows, IntArray nodes, int root) {
	DoubleArray flows = linkFlows(loopFlows, chords, tree, graph);
	DoubleArray p;
	p.size = nodes.size;
	p.data = malloc(p.size * sizeof(double));
    bool* checked = calloc(nodes.size, sizeof(bool));

    checked[nodeIndex(root, nodes)] = true;

	return pressuresDFS(tree, graph, nodes, checked, root, flows, p);
}

double sumLoopPressureDrops(LinkArray loop, LinkArray graph, DoubleArray direction, DoubleArray pressureDrops) {
    double result = 0;
    for (int i = 0; i < loop.size; i++) {
        int ind = linkIndex(loop.data[i], graph);
        result += pressureDrops.data[ind] * direction.data[i];
    }
    return result;
}

int nodeIndex(int node, IntArray nodes) {
	int index;
	for (index = 0; index < nodes.size; index++) {
		if (nodes.data[index] == node) return index;
	}
	printf("ERROR: Node %d not in given nodes array!", node);
	return -1;
}

*/
