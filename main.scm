(load "solver-constants.scm")
(load "system.scm")
(load "functions.scm")
(load "lagrange-polynomial.scm")
(load "write-to-csv.scm")

#|
(display "all-nodes: ") 
(newline)
(display all-nodes)
(newline)
(display "adjacency list for directed graph: ")
(newline)
(display (adjacency-list system #t))
(newline)
(display "adjacency list for undirected graph: ")
(newline)
(display (adjacency-list system #f))
|#

(define points '((1 2) (3 7) (5 6) (7 12)))
; (define point '(5 6)) ;; treba radit bez ovog
(define xs (linspace -10 10 1001))
(define ys (map (lagrange-interpolation points) xs))

(write-csv-file "lagrange-data.csv" (list (map exact->inexact xs) (map exact->inexact ys)))
