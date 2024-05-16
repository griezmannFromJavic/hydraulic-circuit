(define (dfs-init graph initial-node)
  (define (neighbours node) (cadr (assoc node adjacency-list-undirected)))
  
  (define (dfs parent child tree visited)
    (define (unvisited-neighbours node) (set-difference (neighbours node) visited))
    
    (define new-tree (cons (list parent child) tree))
    (define new-visited (cons child visited))
    
    (if (null? (unvisited-neighbours child))
        (reverse new-tree)
        (begin
          (display "visited: ") (display new-visited) (newline) (newline)
          (display "unvisited neighbours: ") (display (unvisited-neighbours child)) (newline) (newline)
          (display "tree: ") (display tree) (newline) (newline)
          (display "new tree: ") (display new-tree) (newline) (newline)
          (display "-----------------------------------") (newline) (newline)
          (map (lambda (x) (dfs child x new-tree new-visited)) (unvisited-neighbours child))
          )))

  ; Initiating DFS from each unvisited node
  (let loop ((nodes (map car graph)) (tree '()) (visited '()))
    (cond
      ((null? nodes) tree)
      ((memq (car nodes) visited) (loop (cdr nodes) tree visited)) ; Skip visited nodes
      (else (loop (cdr nodes) (dfs #f (car nodes) tree visited) (cons (car nodes) visited))))))


