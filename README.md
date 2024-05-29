# Hydraulic Circuit Solver

This program is mostly based on the work by [M. A. Hall](https://onlinelibrary.wiley.com/doi/abs/10.1002/net.3230060204).

The program takes as input a list containing two pieces of information about inlet nodes: their inflow and outflow nodes, and the pressure-flow characteristic points. The output is the stationary pressure-flow state of a given system[^1].

The program then calculates the (n-1)-degree polynomial for a given set of n points[^2] using Lagrange interpolation. The polynomial function and its integral, both necessary for the algorithm to work, are calculated analytically, ensuring speed and precision for further programs based on this one.

An arbitrary tree in a graph is constructed using a depth-first search (DFS) recursive algorithm.

The incidence matrix B and the fundamental circuit matrix G are both represented as functions of their row and column inputs.

[^1]: Users must ensure the uniqueness of the solution. The authors assumed that the pressure-flow functions used are monotonic and increasing and proved the uniqueness of the solution with that assumption. However, the general polynomial allowed for user input does not always satisfy those conditions. [My Master's thesis](https://zir.nsk.hr/islandora/object/fsb%3A9362) partially covers hydraulic instabilities caused by the multiple solutions to the pressure-flow equation (N-curve). Reader interested in the subject who does not read Croatian is encouraged to explore literature cited in that work. 

[^2]: The degree can be smaller if you decide to overdetermine the polynomial. Overdetermination does not cause bugs.

