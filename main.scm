(load "functions.scm")
(load "solver-constants.scm")
(load "system.scm")
(load "lagrange-polynomial.scm")
(load "write-to-csv.scm")
(load "matrix-generator.scm")
(load "dfs.scm")

(define working-points (map cadr system))
(define pressure-characteristics (map lagrange-interpolation working-points))


(define points '((1 10) (2 2) (3 3) (4 7) (6 5) (10 1)))
(define xs (linspace 0 10 101))
(map (lagrange-interpolation points) xs)
