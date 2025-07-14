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


double dPdX(LinkArray loopM, LinkArray loopN, double x) {
    //partial derivative of loop M pressure drop with respect to loop flow N at value x
    double result = 0;
    for (int m = 0; m < loopM.size; m++) {
        Link currM = loopM.data[m];
        for (int n = 0; n < loopN.size; n++) {
            Link currN = loopN.data[n];
            if (currM.inletNode == currN.inletNode && currM.outletNode == currN.outletNode) {
                result += lagrangeDerivative(currM.lData, x);
            }
            if (currM.inletNode == currN.outletNode && currM.outletNode == currN.inletNode) {
                result -= lagrangeDerivative(currM.lData, x);
            }
        }
    }
}

double loopPressureDrop(LinkArray loop, LinkArray graph, DoubleArray flows) {
    double dp = 0;
    for (int i = 0; i < loop.size; i++) {
        Link loopLink = loop.data[i];
        for (int j = 0; j < graph.size; j++) {
            Link graphLink = graph.data[j];
                if (loopLink.inletNode == graphLink.inletNode && loopLink.outletNode == graphLink.outletNode) {
                    dp += lagrangePolynomial(loopLink.lData, flows.data[j]);
                    break;
                }
                if (loopLink.inletNode == graphLink.outletNode && loopLink.outletNode == graphLink.inletNode) {
                    dp -= lagrangePolynomial(loopLink.lData, flows.data[j]);
                    break;
                }
        }
    }
    return dp;
}

void matrixSystemInputs(LinkArray* loops, DoubleArray* directions, DoubleArray guess, int size, DoubleMatrix* A, DoubleArray* b) {
    A->data = malloc(size * sizeof(double*));
    A->rows = size;
    A->cols = size;
    b->data = malloc(size * sizeof(double));
    b->size = size;
    for (int i = 0; i < size; i++) {
        // b->data =
        for (int j = 0; j < size; j++) {
            A->data[i][j] = dPdX(loops[i], loops[j], guess.data[i]);
        }

    }
}







double manhattan(DoubleArray error) {
    double res = 0;
    for (int i = 0; i < error.size; i++) {
        res += error.data[i] * error.data[i];
    }
    return res;
}
