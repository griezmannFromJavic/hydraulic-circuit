(load "functions.scm")
(load "solver-constants.scm")
(load "system.scm")
(load "lagrange-polynomial.scm")
(load "write-to-csv.scm")
(load "matrix-generator.scm")
(load "dfs.scm")

(define working-points (map cadr system))
(define pressure-characteristics (map lagrange-polynomial working-points))

(define flows (linspace 0 2 101))
(define pressures0 (map (car pressure-characteristics) flows))
(define pressures1 (map (cadr pressure-characteristics) flows))
(define pressures2 (map (caddr pressure-characteristics) flows))

(define pressures (map (lambda (f) (map f flows)) pressure-characteristics))

(write-csv-file "lagrange-data.csv"
	(map (lambda (lst) (map exact->inexact lst))
		(cons flows pressures)
		))
