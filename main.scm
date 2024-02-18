(load "solver-constants.scm")
(load "system.scm")
(load "functions.scm")
(load "lagrange-polynomial.scm")
(load "write-to-csv.scm")


(define points '((0 10) (3 9) (10 0) (4 7)))
(define xs (linspace 1 10 101))
(define ys (map (lagrange-interpolation points) xs))
(write-csv-file "lagrange-data.csv" (list (map exact->inexact xs) (map exact->inexact ys)))
