(define (get-corresponding-element element list1 list2)
	"takes an element from the first list, along with two lists, and returns the element from the second list located at the same index as the given element in the first list."
	(if (or (null? list1) (null? list2)) '()
		(if (equal? element (car list1)) (car list2)
		(get-corresponding-element element (cdr list1) (cdr list2)))))

(define (set-difference s1 s2)
	(cond ((null? s1) '())
		   ((not (member (car s1) s2)) (cons (car s1) (set-difference (cdr s1) s2)))
	(else (set-difference (cdr s1) s2))))
     
(define (subset? s1 s2)
	"Is s1 subset of s2?"
	(and (list? s1)
		 (list? s2)
		 (null? (remove-duplicates (set-difference s1 s2)))))

(define (incidence-matrix system)
	"Creates incidence matrix from system descriprion."
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
				
(define (set-difference set-a set-b)
  (cond ((null? set-a) '())  ; If set-a is empty, return an empty set
        ((memv (car set-a) set-b)  ; If the first element of set-a is in set-b
         (set-difference (cdr set-a) set-b))  ; Skip the element and continue with the rest of set-a
        (else  ; If the first element of set-a is not in set-b
         (cons (car set-a)  ; Include the element in the result
               (set-difference (cdr set-a) set-b)))))  ; Continue with the rest of set-a

(define (apply-f-to-the-list-of-functions f functions)
	(lambda (x) (apply f (map (lambda (func) (func x)) functions))))
