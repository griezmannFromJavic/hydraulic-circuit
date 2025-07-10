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


\*======================================================================================*/

#include "solver.h"
#include "helper.h"
#include "graph.h"
#include "lagrange.h"


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

// WORKING

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

/*
DoubleArray pressuresDFS(LinkArray tree, LinkArray graph, IntArray nodes,
                         bool* checked, int node, DoubleArray flows, DoubleArray p) {
    // pointers to the inlet and outlet node indexes should be precalculated
    // SINCE ONE PRESSURE BOUNDARY CONDITION MUST BE DEFINED, THAT LINK WILL BE CHOSEN FOR TREE TRAVERSAL.

    bool allChecked = true;
    for (int i = 0; i < nodes.size; i++) {
        allChecked = allChecked && checked[i]; // break may be added
    }

	if (allChecked) return p;

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
			return pressuresDFS(tree, graph, nodes, checked, link.outletNode, flows, p);
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
			return pressuresDFS(tree, graph, nodes, checked, link.inletNode, flows, p);
		}
	}
}
*/

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


double sumLoopPressureDrops(LinkArray loop, DoubleArray direction, LinkArray graph, DoubleArray flows) {
    // returns 0 for zero loop flow which ought to be wrong
    double result = 0;
    for (int i = 0; i < loop.size; i++) {
        Link curr = loop.data[i];
        int ind = linkIndex(curr, graph);
        if (curr.type == 'r') {
            result += lagrangePolynomial(curr.lData, flows.data[ind]) * direction.data[ind];
        } else if (curr.type == 'p') {
            printf("BCVALUE: %f\n", curr.bcValue);
            result += curr.bcValue * direction.data[ind];
        } else {
            printf("\n    ERROR in sumLoopPressureDrops\n\n");
        }
        printf("%f:  ", result);

        printf("%s:  ", curr.name);
        printf("%f, %f\n", flows.data[ind], direction.data[ind]);
    }
    printf("____________\n");
    return result;
}
