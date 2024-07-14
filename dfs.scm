(define (dfs-init adj-list initial-node)
	(letrec (
		(neighbours (lambda (node) (cadr (assoc node adj-list))))
		(dfs (lambda (node visited tree)
			(let ((new-visited (cons node visited)))
				(fold-right 
					(lambda (neighbor result)
						(let ((result-tree (car result))
							(result-visited (cdr result)))
							(if (memq neighbor result-visited)
								result
								(let ((dfs-result (dfs neighbor result-visited (cons (list node neighbor) result-tree))))
									(cons (car dfs-result) (cdr dfs-result))))))
					(cons tree new-visited)
					(neighbours node)))))
		)
		(car (dfs initial-node '() '()))
	))


; example usage:
#|
(display 
	((incidence-matrix links) 3 3)
)
(newline)
(define example-tree (dfs-init adjacency-list-undirected 3))
(display example-tree)
(newline)
(display
	((fundamental-circuit-matrix links example-tree) 3 3)
)
|#

