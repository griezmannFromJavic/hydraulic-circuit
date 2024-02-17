(define (string-join lst delim)
	(if (null? lst)
		""                                 	
		(if (null? (cdr lst))                 
			(car lst)                         
			(string-append (car lst) delim    
	(string-join (cdr lst) delim)))))

(define (list->csv lst)
	"Function to convert a list to a CSV-formatted string"
 	(define rows (map (lambda (row) (map format-csv-field row)) lst))
    (string-join (map (lambda (row) (string-join row ",")) rows); Join each row with a comma
	"\n"))


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
;; (define data '(("Name" "Age" "Country")
;;               ("Charlie" 28 "UK")))

;;(write-csv-file "output.csv" data)

