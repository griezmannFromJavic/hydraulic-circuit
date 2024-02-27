(define (incidence-matrix graph)
	(lambda (node link)
	(let (
		(owner (car (list-ref system link)))
		(neighbour (cadr (list-ref system link)))
		)
	(cond
		((equal? neighbour link) 1)
		((equal? owner link) -1)
		(#t 0)
		))))

;; example usage
;; ((incidence-matrix system) 1 0)


