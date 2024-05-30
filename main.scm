(load "functions.scm")
(load "solver-constants.scm")
(load "system.scm")
(load "lagrange-polynomial.scm")
(load "write-to-csv.scm")
(load "matrix-generator.scm")
(load "dfs.scm")

(define working-points (map cadr system))
(define pressure-characteristics (map lagrange-polynomial working-points)) ; ??


(define points '((1 10) (2 2) (3 3) (4 7) (6 5) (10 1)))
(define xs (linspace 1 10 101))
;(define xs (list 0 1 2 3 4 5 6 7 8 9 10))
(define ys (map (lagrange-polynomial points) xs))

(write-csv-file "lagrange-data.csv" (list (map exact->inexact xs) (map exact->inexact ys)))

