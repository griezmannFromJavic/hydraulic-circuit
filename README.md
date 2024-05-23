# Hydraulic circuit

## Introduction

This work is based mostly on the work by [M. A. Hall](https://onlinelibrary.wiley.com/doi/abs/10.1002/net.3230060204)

The program takes for an input the list containing two information about inlet nodes: its inflow and outflow node, and the pressure-flow characteristics points.
The program then calculates the `(n-1)`-degree polynomial for given `n` points [^1] using Lagrange interpolation.

[^1]: The degree can be smaller if you decide to overdetermine the polynomial. Overdetermination does not cause bugs.




