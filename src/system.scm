; contains information about network: the nodes of a given link and the points of a pressure characteristics
; ((outlet-node inlet-node) ((x1 y1) (x2 y2) ... (xn yn))

(define *system* '( ; this approach is currently being disregarded
	((0 4) '(+ x 1)) 
	((5 0) '(+ x 2))
	((0 1) '(/ x 3))
	((0 2) 100)
	((1 4) 100)
	((4 5) 100)
	((2 5) 100)
	((1 3) 100)
	((2 3) 100)
	((3 4) 100)
	((3 5) 100)
	))

(define *links* (map car *system*))
(define pressures (map cadr *system*))

(define *outlet-nodes* (map car *links*))
(define *inlet-nodes* (map cadr *links*))
(define *num-links* (length *links*))
(define *all-nodes* (remove-duplicates (append *inlet-nodes* *outlet-nodes*)))
(define *num-nodes* (length *all-nodes*))

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
					*all-nodes*)
				(reverse neighbours)))

(define *adjacency-list-directed* (adjacency-list *links* #t))
(define *adjacency-list-undirected* (adjacency-list *links* #f))
