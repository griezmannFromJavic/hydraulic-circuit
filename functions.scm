(define (remove-member elem lst)
	(cond
		((null? lst) '()) ;; If the list is empty, return an empty list
		((equal? elem (car lst)) (remove-member elem (cdr lst))) ;; If the first element is the one to remove, skip it
		(else (cons (car lst) (remove-member elem (cdr lst)))) ;; Otherwise, include the first element and continue
		))

(define (remove-nth-element lst n)
  (if (= n 0) 
      (cdr lst)
      (append (list (car lst)) (remove-nth-element (cdr lst) (- n 1)))))

(define (filter pred lst)
	(cond
		((null? lst) '())                         ;; If the list is empty, return an empty list
		((pred (car lst)) (cons (car lst) (filter pred (cdr lst)))) ;; If the predicate is true for the first element include it in the result ;; 
		(else (filter pred (cdr lst)))            ;; Otherwise, skip it and process the rest
		))


(define (remove-duplicates lst)
  (cond ((null? lst) '())
        ((null? (cdr lst)) lst)
        (else (cons (car lst)
                    (remove-duplicates
                    	(filter (lambda (x) (not (= (car lst) x))) (cdr lst))
                    	)))))

(define (get-corresponding-element element list1 list2)
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
		 (null? (remove-duplicates (set-difference s1 s2)))))

(define (incidence-matrix system)
	"Creates incidence matrix from system description."
	(list-tabulate num-nodes
		(lambda (i)
			(list-tabulate num-links
				(lambda (j)
					(cond ((equal? i (list-ref outlet-nodes j)) -1)
						  ((equal? i (list-ref inlet-nodes j)) 1)
						  (#t 0)
						  ))))))

(define (display-matrix matrix)
  "Display the elements of a matrix."
  (let ((num-rows (length matrix))
        (num-cols (if (not (null? matrix)) (length (car matrix)) 0)))
    (do ((i 0 (+ i 1)))
        ((= i num-rows))
      (do ((j 0 (+ j 1)))
          ((= j num-cols))
        (display (list-ref (list-ref matrix i) j))
        (display " "))
      (newline))))

(define (apply-f-to-the-list-of-functions f functions)
	(lambda (x) (apply f (map (lambda (func) (func x)) functions)))
	)
		
(define (sum-list-of-functions functions)
	(apply-f-to-the-list-of-functions + functions)
	)
	
(define (multiply-list-of-functions functions)
	(apply-f-to-the-list-of-functions * functions)
	)
	
(define (multiply-function-with-number number function)
	(lambda (x) (* number ((lambda (func) (func x)) function)))
	)

(define (linspace start end num-points)
	(define (first-n-natural-numbers n)
		(define (helper count result)
			(if (= count n)
				(reverse result)
				(helper (+ count 1) (cons count result))))
			(helper 0 '()))
	(define linspace-from-0-to-1 (map (lambda (x) (/ x (- num-points 1))) (first-n-natural-numbers num-points)))
	(define scaled-linspace (map (lambda (x) (* x (- end start))) linspace-from-0-to-1))
	(map (lambda (x) (+ start x)) scaled-linspace)
	)
