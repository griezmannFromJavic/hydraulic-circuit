(load "solver-constants.scm")
(load "system.scm")
(load "functions.scm")
(load "lagrange-polynomial.scm")
(load "write-to-csv.scm")


(define points '((1 10) (2 9) (3 8) (4 7) (5 -4) (6 5)))
(define xs (linspace 0 10 101))
(define ys (map (lagrange-interpolation points) xs))
(write-csv-file "lagrange-data.csv" (list (map exact->inexact xs) (map exact->inexact ys)))
