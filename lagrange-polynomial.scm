(define (lagrange-interpolation points)	; returns function of x
	(define (basis-factor point other-point) ; should return function of x
		(lambda (x) (/ (- x (car other-point)) (- (car point) (car other-point)))))  
	(define (list-of-factors point) ; returns list of functions of x
		(map (lambda (p) (basis-factor point p)) (remove (lambda (p) (equal? point p)) points)))
	(define (apply-f-to-the-list-of-functions f functions)
		(lambda (x) (apply f (map (lambda (func) (func x)) functions))))
	(define (sum-list-of-functions functions)
		(apply-f-to-the-list-of-functions + functions))
	(define (multiply-list-of-functions functions)
		(apply-f-to-the-list-of-functions * functions))
	(define (multiply-function-with-number number function) ; radi
		(lambda (x) (* number ((lambda (func) (func x)) function))))
	(define (basis-polynomial point)
		(multiply-list-of-functions (list-of-factors point)))
	(map multiply-function-with-number ((map cadr points) (map basis-polynomial points)))
)
	
			

;; add error message if 2 x's are the same

(define (linspace start end num-points)
	(define (first-n-natural-numbers n)
		(define (helper count result)
			(if (= count n)
				(reverse result)
			(helper (+ count 1) (cons count result))))
		(helper 0 '()))
	(define linspace-from-0-to-1 (map (lambda (x) (/ x (- num-points 1))) (first-n-natural-numbers num-points)))
	(define scaled-linspace (map (lambda (x) (* x (- end start))) linspace-from-0-to-1))
	(map (lambda (x) (+ start x)) scaled-linspace))




(multiply-function-with-number 4 (lambda (x) (+ 1 x)))
