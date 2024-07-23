; contains information about network: the nodes of a given link and the points of a pressure characteristics
; ((outlet-node inlet-node) ((x1 y1) (x2 y2) ... (xn yn))

(define *system* '(
	((0 4) ((0 4.1) (1 3) (2 0))) 
	((5 0) ((0 0) (1 1) (2 4)))
	((0 1) ((0 0) (1 1.5) (2 4)))
	((0 2) ((0 10) (1 0) (2 10)))
	((1 4) ((0 10) (1 8) (2 0)))
	((4 5) ((0 0) (2/3 10) (4/3 1) (2 9)))
	((2 5) ((0 0) (1 1) (2 4) (0.5 7) (1.5 0)))
	((1 3) ((0 0) (1 1.7) (2 4)))
	((2 3) ((0 0) (2 8)))
	((3 4) ((0 0) (1 2) (3 9.2)))
	((3 5) ((0 0) (1 1) (2 4))) 
	))

(define *links* (map car *system*))


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
