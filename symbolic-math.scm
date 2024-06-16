;; Returns an expression that evaluates to derivative of an expresison
;; Each (sub-)expression must take at most two arguments.
;; Possible expressions are number, variable, sum, and multiplication.
;; Basically copied from SICP page 199.

(define (deriv exp var)
	(cond
		((number? exp) 0)
		((variable? exp) (if (same-variable? exp var) 1 0))
		((sum? exp) (make-sum (deriv (addend exp) var)
			(deriv (augend exp) var)))
		((product? exp)
			(make-sum
				(make-product (multiplier exp)
					(deriv (multiplicand exp) var))
				(make-product (deriv (multiplier exp) var)
					(multiplicand exp))))
		(else (error "unknown expression type: DERIV" exp))
			))

;; The variables are symbols. They are identified by the primitive predicate symbol?
(define (variable? x) (symbol? x))

;; Two variables are the same if the symbols representing them are eq?:
(define (same-variable? v1 v2)
	(and (variable? v1) (variable? v2) (eq? v1 v2)))
	
;; Sums and products are constructed as lists:
(define (make-sum a1 a2) (list '+ a1 a2))
(define (make-product m1 m2) (list '* m1 m2))

;; A sum is a list whose first element is the symbol +:
(define (sum? x) (and (pair? x) (eq? (car x) '+)))

;; The addend is the second item of the sum list:
(define (addend s) (cadr s))

;; The augend is the third item of the sum list:
(define (augend s) (caddr s))

;; A product is a list whose first element is the symbol *:
(define (product? x) (and (pair? x) (eq? (car x) '*)))

;; The multiplier is the second item of the product list:
(define (multiplier p) (cadr p))

;; The multiplicand is the third item of the product list:
(define (multiplicand p) (caddr p))




