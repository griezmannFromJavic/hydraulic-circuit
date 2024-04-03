(define (bfs graph initial-node)
	(define (neighbours node) (cadr (assoc node adjacency-list-undirected)))
	(define (unvisited-neighbours node) (set-difference (neighbours node) visited))
	(do (
		(queue (list initial-node) (remove-duplicates (apply append (map neighbours (neighbours node)))))
		(visited (list initial-node) (nesto))
		(tree '() (nesto))
    		)
    	((null? queue) tree)
    	
