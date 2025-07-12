/*======================================== TODO ========================================*\

PSEUDOCODE FOR NEWTONS SOLVER

while (not_converged) {
    compute_F(x, F);         // Evaluate F(x)
    compute_Jacobian(x, J);  // Evaluate Jacobian matrix at x
    solve_linear_system(J, delta_x, -F); // Solve J * dx = -F
    x = x + delta_x;
}


NOW WORKING ON:

The tree is generated form the ficticious "0" node, all other pressures are calculated from that tree.
The guess vector will be loop flows.
Matrix system must be constructed such that all BCs are satisfied.

Pressure boundary condition will be imposed, the residual check will be compared to the
calculated chord pressure drop and the current iteration dp.

Loop flows may be calculated without solving apsolute pressures. Apsolute pressures will be
calculated after the solver returns solution.

newton-rapson breaks on gradient == 0. in that case reset the estimation to 0 or offset it slightly

\*======================================================================================*/

#include "solver.h"
#include "helper.h"
#include "graph.h"
#include "lagrange.h"

// #include <lapacke.h>


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


DoubleArray linkFlows(DoubleArray loopFlows, LinkArray chords, LinkArray tree, LinkArray graph) { // trouble with direction[i] being 0
	DoubleArray result;
	result.size = graph.size;
	result.data = calloc(graph.size, sizeof(double)); // init to 0
	DoubleArray direction;


	LinkArray path;

	for (int loop = 0; loop < chords.size; loop++) {
		path = findTreePath(tree, chords.data[loop], &direction);
		for (int l = 0; l < path.size; l++) {
			Link pathLink = path.data[l];
			for (int i = 0; i < graph.size; i++) {
				Link graphLink = graph.data[i];
				if (isSameLink(graphLink, pathLink)) {
					result.data[i] += loopFlows.data[loop] * direction.data[l];   // add loop flow to link flow
				}
			}
		}
	}
	return result;
}


DoubleArray pressureDrops(DoubleArray flows, LinkArray graph) {
	// might be redundant, existing tree could be used to define node pressures
	DoubleArray result;
	result.data = malloc(flows.size * sizeof(double));
	result.size = flows.size;

	for (int i = 0; i < flows.size; i++) {
		double flow = flows.data[i];
		LagrangeData d = graph.data[i].lData;
		char type = graph.data[i].type;
		if (type == 'r') {
		    result.data[i] = lagrangePolynomial(d, flow);
		} else if (type == 'p') {
		    result.data[i] = graph.data[i].bcValue;
		}
	}
	return result;
}



// IMPLEMENTING FOR SOLVER
void pressureDropsAndGradients(DoubleArray flows, LinkArray graph, DoubleArray* dps, DoubleArray* DdpPerDx) {
	// WORKING
	dps->data = malloc(flows.size * sizeof(double));
	DdpPerDx->data = malloc(flows.size * sizeof(double));
	dps->size = flows.size;
	DdpPerDx->size = flows.size;

	for (int i = 0; i < flows.size; i++) {
		double flow = flows.data[i];
		LagrangeData d = graph.data[i].lData;
		if (graph.data[i].type == 'r') {
		    dps->data[i] = lagrangePolynomial(d, flow);
			DdpPerDx->data[i] = lagrangeDerivative(d, flow);
		} else if (graph.data[i].type == 'p') {
		    dps->data[i] = graph.data[i].bcValue;
			DdpPerDx ->data[i] = 0; // possibly dangerous edge case. might couse division by zero in some functions
		}
	}
}

bool isChecked(int node, IntArray nodes, bool* checked) {
	for (int i = 0; i < nodes.size; i++) {
		if (nodes.data[i] == node) {
			return checked[i];
		}
	}
	printf("ERROR: Node not in nodes array!");
	return false;
}

int nodeIndex(int node, IntArray nodes) {
	int index;
	for (index = 0; index < nodes.size; index++) {
		if (nodes.data[index] == node) return index;
	}
	printf("ERROR: Node %d not in given nodes array!", node);
	return -1;
}


double sumLoopPressureDrops(LinkArray loop, LinkArray graph, DoubleArray direction, DoubleArray pressureDrops) {
    double result = 0;
    for (int i = 0; i < loop.size; i++) {
        int ind = linkIndex(loop.data[i], graph);
        result += pressureDrops.data[ind] * direction.data[i];
    }
    return result;
}








double manhattan(DoubleArray error) {
    double res = 0;
    for (int i = 0; i < error.size; i++) {
        res += error.data[i] * error.data[i];
    }
    return res;
}
