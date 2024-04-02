(define (bfs graph initial-node)
	(define (neighbours node) (cadr (assoc node adjacency-list-undirected)))
	(define tree (list))
	(define visited (list initial-node))
	(define (unvisited-neighbours node) (set-difference (neighbours node) visited))
	(do (
		(queue (list initial-node) (remove-duplicates (apply append (map neighbours (neighbours node)))))
		())
    )

