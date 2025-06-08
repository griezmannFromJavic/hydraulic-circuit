/*======================================== TODO ========================================*\

PSEUDOCODE FOR NEWTONS SOLVER

while (not_converged) {
    compute_F(x, F);         // Evaluate F(x)
    compute_Jacobian(x, J);  // Evaluate Jacobian matrix at x
    solve_linear_system(J, delta_x, -F); // Solve J * dx = -F
    x = x + delta_x;
}


NOW WORKING ON:

The tree can be generated form the ficticious "0" node, all other pressures will be calculated from that tree.
The guess vector will be loop flows.
Matrix system must be constructed such that all BCs are satisfied.



\*======================================================================================*/

#include "solver.h"
#include "helper.h"
#include "graph.h"
#include "lagrange.h"


DoubleArray linkFlows(DoubleArray loopFlows, LinkArray chords, LinkArray tree, LinkArray graph) { // trouble with direction[i] being 0
	DoubleArray result;
	result.size = graph.size;
	result.data = calloc(result.size, sizeof(double)); // init to 0

	DoubleArray* direction = malloc(sizeof(DoubleArray));
	LinkArray path;

	for (int loop = 0; loop < chords.size; loop++) {
		path = findTreePath(tree, chords.data[loop], direction);
		for (int l = 0; l < path.size; l++) {
			Link pathLink = path.data[l];
			for (int i = 0; i < graph.size; i++) {
				Link graphLink = graph.data[i];
				if (isSameLink(graphLink, pathLink)) {
					result.data[i] += loopFlows.data[loop] * direction->data[l];   // add loop flow to link flow
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
		result.data[i] = lagrangePolynomial(d, flow);
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

DoubleArray pressuresDFS(LinkArray tree, LinkArray graph, IntArray nodes,
                         bool* checked, int node, DoubleArray flows, DoubleArray p) {
    printf("node: %d\n", node);
    
    bool allChecked = true;
    for (int i = 0; i < nodes.size; i++) {
        allChecked = allChecked && checked[i]; // break may be added
    }
    
	if (allChecked) return p;

	for (int l = 0; l < tree.size; l++) {
		Link link = tree.data[l];
		if (link.inletNode == node && !checked[nodeIndex(link.outletNode, nodes)]) {
			p.data[nodeIndex(link.outletNode, nodes)] =
			    p.data[nodeIndex(link.inletNode, nodes)] +
			    lagrangePolynomial(link.lData, flows.data[linkIndex(link, graph)]);
			checked[nodeIndex(link.outletNode, nodes)] = true;
			return pressuresDFS(tree, graph, nodes, checked, link.outletNode, flows, p);
		}
		if (link.outletNode == node && !checked[nodeIndex(link.inletNode, nodes)]) {
			p.data[nodeIndex(link.inletNode, nodes)] =
			    p.data[nodeIndex(link.outletNode, nodes)] -
			    lagrangePolynomial(link.lData, flows.data[linkIndex(link, graph)]);
			checked[nodeIndex(link.inletNode, nodes)] = true;
			return pressuresDFS(tree, graph, nodes, checked, link.inletNode, flows, p);
		}
	}
}


DoubleArray pressures(LinkArray graph, LinkArray tree, LinkArray chords, DoubleArray loopFlows, IntArray nodes) { // in progress
	DoubleArray flows = linkFlows(loopFlows, chords, tree, graph);
	DoubleArray p;
	p.size = nodes.size;
	p.data = malloc(p.size * sizeof(double));
    bool* checked = calloc(nodes.size, sizeof(bool));
    
    int root = tree.data[0].inletNode;
    checked[nodeIndex(root, nodes)] = true;
    
	return pressuresDFS(tree, graph, nodes, checked, root, flows, p);
}










