(define (display-matrix matrix)
"Display the elements of a matrix."
	(let (
		(num-rows (length matrix))
		(num-cols (length (car matrix)))
		)
    (do ((i 0 (+ i 1)))
    	((= i num-rows))
		(do ((j 0 (+ j 1)))
			((= j num-cols))
			(display (list-ref (list-ref matrix i) j))
			(display " "))
      	(newline)
      	)))
