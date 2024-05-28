(define (basis-factor point other-point) ; returns function of x
	(display point) (display other-point) (newline)
	(lambda (x) (/ (- x (car other-point)) (- (car point) (car other-point))))
	)
	
(define (list-of-factors point points) ; returns list of functions of x
	(map (lambda (p) (basis-factor point p)) (remove-member point points))
	)

(define (basis-polynomial point points) ; returns function of x
	(multiply-list-of-functions (list-of-factors point points))
	)

(define (lagrange-polynomial points)
"Implements Lagrange interpolation to produce polynomial that passes through all points."
	(sum-list-of-functions
		(map multiply-function-with-number
			(map cadr points) (map (lambda (p) (basis-polynomial p points)) points)))
	)

;; add error message if 2 x's are the same

; EXAMPLE USAGE:
;(define points '((1 10) (2 2) (3 3) (4 7) (6 5) (10 1)))
;(define xs (list 0 1 2 3 4 5 6 7 8 9))
;(map (lagrange-polynomial points) xs)

(define (basis-factor-derivation point other-point)
	(/ (- (cadr other-point) (cadr point)) (car other-point) (car point))
	)

(define (list-of-derivatives point points) ; returns list of derivatives of a linear function
	(map (lambda (p) (basis-factor-derivation point p)) (remove-member point points))
	)

; Creating a Lagrange polynomial derivative function that will later be used to create Lagrange polynomial integral from 0 to x:
; Step 1: create a derivative of a basis factor (done)
; Step 2: create a derivative of a basis polynomial using product rule
; 			(f1 * f2 * ... * fn)' = f1' * f2 * ... * fn + f1 * f2' * ... * fn + ... + f1 * f2 * ... * fn'"
; Step 3: create a derivative of the whole Lagrange polynomial


(define (basis-polynomial-derivative-nth-summand point points n)
	(multiply-function-with-number
		(list-ref (list-of-derivatives point points) n)
		(multiply-list-of-functions (remove-nth-element (list-of-factors point points) n))
		))


