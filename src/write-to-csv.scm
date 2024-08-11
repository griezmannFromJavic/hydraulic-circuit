(define (string-join lst delim)
	(if (null? lst)
		""                                 	
		(if (null? (cdr lst))                 
			(car lst)                         
			(string-append (car lst) delim    
	(string-join (cdr lst) delim)))))

(define (list->csv lst)
	"Function to convert a list to a CSV-formatted string"
 	(let ((rows (map (lambda (row) (map format-csv-field row)) lst)))
    (string-join (map (lambda (row) (string-join row ",")) rows); Join each row with a comma
	"\n")))


(define (format-csv-field field)
	"Convert non-string variables to string"
	(if (string? field)
		field
		(number->string field)))


(define (write-csv-file filename lst)
"Function to write CSV data to a file"
	(call-with-output-file filename
		(lambda (port)
		(display (list->csv lst) port))))

;; Example usage:
;(define points '((1 10) (2 2) (3 3) (4 7) (6 5) (10 1)))
;(define xs (linspace 1 10 101))
;(define ys (map (lagrange-polynomial points) xs))
;(write-csv-file "lagrange-data.csv" (list (map exact->inexact xs) (map exact->inexact ys)))

