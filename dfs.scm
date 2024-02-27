(define (dfs-init graph initial-node)
"returns list of tree links"
(define tree '())
(define visited '(inital-node))
	(define (dfs node)
	;;(display node)
	"operation for one node"
		(define neighbours (cadr (assoc node adjacency-list-undirected)))
		(define unvisited-neighbours (set-difference neighbours visited))
		(set! visited (list node visited))
		(set! tree
			(append tree
				(map (lambda (neighbour) (list node neighbour)) unvisited-neighbours)
				))
		(if (null? unvisited-neighbours)
			tree
			(map dfs unvisited-neighbours)
			))
	tree)

;; (cadr (assoc 4 adjacency-list-undirected)) ; radi

