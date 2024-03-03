; contains informatin about network
; (outlet-node inlet-node)

#|
(define system (list
(list 0 4) ; first links
(list 5 0) ; second link
(list 0 1)
(list 0 2)
(list 1 4)
(list 4 5)
(list 2 5)
(list 1 3)
(list 2 3)
(list 3 4)
(list 3 5) ; n'th link
))
|#


; system to test dfs algorithm
(define system (list
(list 1 2)
(list 1 3) 
(list 2 4)
(list 2 5)
(list 3 6)
(list 4 5)
))


(define outlet-nodes (map car system))
(define inlet-nodes (map cadr system))
(define num-links (length system))

(define (remove-duplicates lst)
  (cond ((null? lst) '())
        ((null? (cdr lst)) lst)
        (else (cons (car lst)
                    (remove-duplicates
                    	(filter (lambda (x) (not (= (car lst) x))) (cdr lst))
                    	)))))
                    	
(define all-nodes (remove-duplicates (append inlet-nodes outlet-nodes)))
(define num-nodes (length all-nodes))

(define (adjacency-list graph is-directed?)
	"Creates adjacency list from graph description.
	Loops over all-nodes and appends neighbors to neighbors list using graph list
	Can create both directed and not-directed adjacency list."
	(let ((neighbours '()))
		(for-each
			(lambda (node)
				(let ((node-neighbour '()))
					(for-each
						(lambda (link)
							(cond
								((equal? node (car link)) (set! node-neighbour (append node-neighbour (list (cadr link)))))
								((and (not is-directed?) (equal? node (cadr link))) (set! node-neighbour (append node-neighbour (list (car link)))))
								))
							graph)
						(set! neighbours (cons (list node node-neighbour) neighbours))))
					all-nodes)
				(reverse neighbours)))

(define adjacency-list-directed (adjacency-list system #t))
(define adjacency-list-undirected (adjacency-list system #f))
