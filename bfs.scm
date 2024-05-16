(define (bfs adj-list initial-node)
	(define (neighbours node) (cadr (assoc node adj-list)))
	(do (
		(tree '() tree)
		(queue (list initial-node) ????)
		(current-node (car queue) (car queue))
		) ; bindings 
		
		((equal (length tree) (- num-nodes 1)) tree) ;clause
		
		(for-each 
			
			
		
		

