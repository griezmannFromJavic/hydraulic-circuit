(load "functions.scm")
(load "solver-constants.scm")
(load "system.scm")
(load "lagrange-polynomial.scm")
(load "write-to-csv.scm")
(load "matrix-generator.scm")
(load "dfs.scm")


;(define points '((1 10) (2 2) (3 3) (4 7) (6 5) (10 1)))
;(define xs (linspace 0 10 101))
;(define ys (map (lagrange-interpolation points) xs))
;(write-csv-file "lagrange-data.csv" (list (map exact->inexact xs) (map exact->inexact ys)))

;(display adjacency-list-undirected)
;(newline) (newline)
;(dfs-init adjacency-list-undirected 3)

