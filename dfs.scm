(define (dfs-init graph initial-node)
"returns list of tree links"
(define tree '())
(define visited '())
	(define (dfs node)
	"operation for one node"
	
	(display "node")
	(display node)
	(newline)
	
		(define neighbours (cadr (assoc node adjacency-list-undirected)))
		(define unvisited-neighbours (set-difference neighbours visited))
		
		(display "unvisited-neighbours")
		(display unvisited-neighbours)
		(newline)
		
		(set! visited (cons node visited))
		
		(display "visited")
		(display visited)
		(newline)
		
		(set! tree
			(append tree
				(map (lambda (neighbour) (list node neighbour)) unvisited-neighbours)
				))

		(if (null? unvisited-neighbours)
;;		(if (= (length visited) num-nodes) ; ne radi, samo drugačije 
			tree
			(map dfs unvisited-neighbours)
			))
	(dfs initial-node))
