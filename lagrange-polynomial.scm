(define (lagrange-interpolation points)	; returns function of x
	(define (basis-factor point other-point) ; should return function of x
		(lambda (x) (/ (- x (car other-point)) (- (car point) (car other-point)))))  
	(define (list-of-factors point) ; returns list of functions of x
		(map (lambda (p) (basis-factor point p)) (remove (lambda (p) (equal? point p)) points)))
	(define (multiply-list-of-functions functions)
		(lambda (x)
			(apply * (map (lambda (func) (func x)) functions))))
	(multiply-list-of-functions (list-of-factors point))
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

(define points '((1 2) (3 4) (5 6)))
(define point '(3 4))
(define xs (linspace -10 10 1000))
(define ys (map (lagrange-interpolation points) xs))


(call-with-output-file "output.txt"
	(lambda (output-port)
		(display xs output-port)
		(display ys output-port)
	))

