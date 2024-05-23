(define (basis-factor point other-point) ; returns function of x
	(lambda (x) (/ (- x (car other-point)) (- (car point) (car other-point))))
	)
	
(define (list-of-factors point) ; returns list of functions of x
	(map (lambda (p) (basis-factor point p)) (remove (lambda (p) (equal? point p)) points))
	)

(define (basis-polynomial point) ; returns function of x
		(multiply-list-of-functions (list-of-factors point))
	)

(define (lagrange-interpolation points)	; returns function of x
	(sum-list-of-functions (map multiply-function-with-number (map cadr points) (map basis-polynomial points)))
	)



;; add error message if 2 x's are the same



; EXAMPLE USAGE:
;(define points '((1 10) (2 2) (3 3) (4 7) (6 5) (10 1)))
;(define xs (linspace 0 10 101))
;(map (lagrange-interpolation points) xs)
