; at this moment it is nither dfs or bfs but something in between
; BUG! creates loops

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
		(if (null? unvisited-neighbours)
			(reverse tree)
			(begin
				(set! visited (cons node visited))
				(set! tree
					(cons (list node (car unvisited-neighbours)) tree)
					)

		(display "visited: ")
		(display visited)
		(newline) (newline)		
		(display "unvisited neighbours: ")
		(display unvisited-neighbours)
		(newline) (newline)
		(display "tree: ")
		(display tree)
		(newline) (newline)
		(display "-----------------------------------")
		(newline) (newline)

			(map dfs unvisited-neighbours)
			))))
			
	(dfs initial-node)
	))
