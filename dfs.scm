(define (dfs-init graph initial-node)
(let  (
      (tree '())
      (visited '())
      )
  (define (dfs node)
		(let* (
              (neighbours (cadr (assoc node adjacency-list-undirected)))
              (unvisited-neighbours (set-difference neighbours visited))
              )
		(set! visited (cons node visited))
		(set! tree
			(append tree
				(map (lambda (neighbour) (list node neighbour)) unvisited-neighbours)
				))
		(if (null? unvisited-neighbours)
			tree
			(dfs (car unvisited-neighbours))
			)))  
	(dfs initial-node)))
