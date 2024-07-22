(define (remove-member elem lst)
	(cond
		((null? lst) '()) 
		((equal? elem (car lst)) (remove-member elem (cdr lst))) 
		(else (cons (car lst) (remove-member elem (cdr lst))))
		))

(define (remove-nth-element lst n)
  (if (= n 0) 
      (cdr lst)
      (append (list (car lst)) (remove-nth-element (cdr lst) (- n 1)))))

(define (filter pred lst)
	(cond
		((null? lst) '())
		((pred (car lst)) (cons (car lst) (filter pred (cdr lst))))
		(else (filter pred (cdr lst)))
		))


(define (remove-duplicates lst)
	(cond ((null? lst) '())
    	((null? (cdr lst)) lst)
        (else (cons (car lst)
                    (remove-duplicates
                    	(filter (lambda (x) (not (= (car lst) x))) (cdr lst))
                    	)))))

(define (get-corresponding-element element list1 list2)error: Your local changes to the following files would be overwritten by merge:
"takes an element from the first list, along with two lists, and returns the element from the second list located at the same index as the given element in the first list."
	(if (or (null? list1) (null? list2)) '()
		(if (equal? element (car list1)) (car list2)
		(get-corresponding-element element (cdr list1) (cdr list2)))))

(define (set-difference s1 s2)
	(cond (
		(null? s1) '())
		((not (member (car s1) s2)) (cons (car s1) (set-difference (cdr s1) s2)))
		(else (set-difference (cdr s1) s2))
		))
     
(define (subset? s1 s2)
"Is s1 subset of s2?"
	(and (list? s1)
		 (list? s2)
		 (null? (set-difference s1 s2))
		 ))

;; i made a mess here
;; this function is not allowing for the arbitrary naming of nodes
(define incidence-matrix
	(lambda (i j)
		(cond ((= i (list-ref outlet-nodes j)) -1)
			  ((= i (list-ref inlet-nodes j)) 1)
			  (#t 0)
			  )))


(define (apply-f-to-the-list-of-functions f functions)
	(lambda (x) (apply f (map (lambda (func) (func x)) functions)))
	)
		
(define (sum-list-of-functions functions)
	(apply-f-to-the-list-of-functions + functions)
	)
	
(define (multiply-list-of-functions functions)
	(apply-f-to-the-list-of-functions * functions)
	)

(define (divide-two-functions dividend divisor)
	(lambda (x) (/ (dividend x) (divisor x)))
	)
	
(define (multiply-function-with-number number function)
	(lambda (x) (* number ((lambda (func) (func x)) function)))
	)


(define (linspace start end num-points)
	(let* (
		(first-n-natural-numbers (lambda (n)
			(let loop ((count 0) (result '()))
				(if (= count n)
					(reverse result)
					(loop (+ count 1) (cons count result))))))
		(linspace-from-0-to-1
			(map (lambda (x) (/ x (- num-points 1))) (first-n-natural-numbers num-points)))
		(scaled-linspace
			(map (lambda (x) (* x (- end start))) linspace-from-0-to-1)))
		(map (lambda (x) (+ start x)) scaled-linspace)))



(define (matrix-multiplication a b)
"Returns AxB if where A is described as (a i j).
No is-matrix? procedure is performed."
	(list))
	
