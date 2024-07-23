# Hydraulic Circuit Solver

This program is inspired by the [M. A. Hall's](https://onlinelibrary.wiley.com/doi/abs/10.1002/net.3230060204) work.
I personally believe you should pay the distributor for the authors work because the science funding is known for its meritocratic nature.
You should not download the work from the pirate distributors like [Z-library](https://z-lib.io/) (where the paper can be found) or [Anna's Archive](https://annas-archive.org/) because knowledge should be payed for!
If one tries to download the paper for free from the pirated site and fails, he or she will find no luck in contacting me at my personal [e-mail address](j.krtolacic@gmail.com),
as I already made my views on the illegal distribution clear!

When searching for the algorithm on the subject the menitoned algorithm stands out as mathematically most elegant.
Unfortunatley, authors gave themselves the freedom of doing most of the job analitically (thus the elegance), so the praticallity of writing the peace of software that can solve serious problems is missing out. In their example they are using the pressure-drop function $f$ with regard to flow $x$ $f(x)=r*x^2$ so the definite integral is simple to calculate analitically $g(x)=r* x^3 /3$ for $x\geq 0$ and $g(x)=r* x^3 /3$ for $x \less 0$. Since I wanted to avoid making the user integrading his own pressure-drop definite integrals I wanted the user to input just the points of the pressure charachteristics and make lagrange polynomial do the rest, symbolic polynomial integration is still quite the challange for my poor coding skills.
Thus, I decided to discart the M. A. Hall's algorithm alltogether and program something more familliar: segregated iterative solver.

The two spaces to be solved are the node pressure vector (scalar vector length X where X is the number of the nodes), and loop flow space, (the scalar vector length Y where Y is the number of independent loops), the loop flows can be transformed to link flows using fundamental circuit matrix transformation.


<!---
The authors do not provide us with the code they are mentioning in the paper, but from the context of the paper it can be deducted that their code is not very flexible, it would seem that every new system must be described by hand (much such codes can be found on github, written by good mathematicians with poor programming skills, Matlab seems to be their programming language of choice).

This code is made to be flexible and user friendly, user must provide only the necessary information about the system and the software will do the rest (like calculating the analytic definite integral of a polynomial).

The program takes as input a list containing two pieces of information about inlet nodes: their inflow and outflow nodes, and the pressure-flow characteristic points. The output is the stationary pressure-flow state of a given system[^1].
The authors only mention the dp-x functions representing trošila (valves, pipe bends, wires, resistors...), the ones whose pressure drop is zero with flow being zero.
The izvori (pumps or batteries) are not mentioned.
I have no idea how simple description of such elements will effect the uniqueness of the solution, but they can be implemeted in the code.
The electric machine is especially interesting in this regard since it can behave as a generator, a motor and a brake (PROVJERI).
TREBA IMPLEMENTIRAT VERZIJU S KOMPLEKSNIM BROJEVIMA DA SE MOGU ANALIZIRAT IZMJENIČNE MREŽE.
The solver solves for stationary state, so making AC network solver required mere implementation of complex number calculus.

The program then calculates the (n-1)-degree polynomial for a given set of n points[^2] using Lagrange interpolation.
The polynomial function and its integral, both necessary for the algorithm to work, are calculated analytically, ensuring speed and precision for further programs based on this one.

An arbitrary tree in a graph is constructed using a depth-first search (DFS) recursive algorithm.

The incidence matrix B and the fundamental circuit matrix G are both represented as functions of their row and column inputs.


;QUESTIONABLE, SEE incidence-matrix "functions.scm"@54.7
Scheme allows great flexibility in naming the nodes and links.
Links need not be named at all, if the user wants, he can add comment next to the link he is describing (see example system).

## Comments on some part of the algorithm

Author has written the paper in a very concise manner, with the assumption of the readers familiarity with the mathematical and physical underlings of the calculated phenomena.
This text is written from a more modest point of view by a person whose mathematical knowledge is far closer to the average Joe's.

Upon examination of the flow conservation equation Bx=0 its nature becomes intuitive.
First we check the dimensionality,
the transformation B transforms the n-dimensional flow vector (where n is the number of links)
to the m-dimensional node source-of-mass-flow vector, taken to be zero in all nodes.
The mass sources (and sinks, having negative sign) representing the systems boundary are eliminated by connecting the fictional node 0 to all the nodes.
The solver solves for stationary state, so no accumulation of mass in the system is allowed, this condition ensures zero sum inflow on the constant-pressure and constant-flow nodes, which, in turn, ensures no mass source of the fictitious link 0, connected to all constant-pressure and constant-flow nodes.
That is the reasoning behind introducing the fictitious node 0, creating a network of sourceless nodes, poorly explained in the original work.
The usage of incidence matrix B in the 
-->



----------------------------------------------------------------------
[^1]: Users must ensure the uniqueness of the solution. The authors assumed that the pressure-flow functions used are monotonic and increasing and proved the uniqueness of the solution with that assumption. However, the general polynomial allowed for user input does not always satisfy those conditions. [My Master's thesis](https://zir.nsk.hr/islandora/object/fsb%3A9362) partially covers hydraulic instabilities caused by the multiple solutions to the pressure-flow equation (N-curve). Reader interested in the subject who does not read Croatian is encouraged to explore literature cited in that work. 

[^2]: The degree can be smaller if you decide to overdetermine the polynomial, it does not cause bugs.
The example of overdetermination of the polynomial would be describing a line with three colinear points.



