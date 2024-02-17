; contains informatin about network
; (outlet-node inlet-node)

(define system '(
(0 4)
(5 0)
(0 1)
(0 2)
(1 4)
(4 5)
(2 5)
(1 3)
(2 3)
(3 4)
(3 5)
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
						(set! neighbours (append neighbours (list node node-neighbour)))))
					all-nodes)
				neighbours))

(define adjacency-list-directed (adjacency-list system #t))
(define adjacency-list-undirected (adjacency-list system #f))
