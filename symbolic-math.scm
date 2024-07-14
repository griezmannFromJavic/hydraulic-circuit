;; Returns an expression that evaluates to derivative of an expression
;; Each (sub-)expression must take at most two arguments.
;;     (SERIOUS PRACTICAL PROBLEM)
;; Possible expressions are number, variable, sum, and multiplication.
;; Inspired by SICP page 199.

;; The variables are symbols. They are identified by the primitive predicate symbol?
(define (variable? x) (symbol? x))

;; Two variables are the same if the symbols representing them are eq?:
(define (same-variable? v1 v2)
	(and (variable? v1) (variable? v2) (eq? v1 v2)))
	
;; Sums and products are constructed as lists:
(define (make-sum lst) (cons '+ lst))
(define (make-product lst) (cons '* lst))
(define (make-sub lst) (cons '- lst))
(define (make-div lst) (cons '/ ))

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

;; Returns an expression that evaluates to derivative of an expression
(define (deriv exp var)
	(cond
		((number? exp) 0)
		((variable? exp) (if (same-variable? exp var) 1 0))
		((sum? exp) (make-sum (cdr exp)))
		((product? exp)
			(make-sum
				(make-product (multiplier exp) (deriv (multiplicand exp) var))
				(make-product (deriv (multiplier exp) var) (multiplicand exp))
				))
		(else (error "unknown expression type: DERIV" exp))
			))


#|
----------------------------
Now I implement symbolic version of the polynomials already programmed in
lagrange-polynomial.scm
----------------------------
|#

(define (x p) (car p)) ; must not use 'x as var!!
(define (y p) (cadr p))

(define (bsis-fctor p1 p2 var)
	(make-div (make-diff var (var (x p2))) (make diff (x p1) (x p2)))
	)

(define (bsis-polyn p1 ps)
	(cons '* 19))
	




