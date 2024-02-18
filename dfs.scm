; u razradi.
; ako nulta noda ima susidnu nodu koja nije u listi posjećenih dodaj taj link u listu stabla
; VARIJACIJA 2: dodaj u tree-links sve neposjećene node
; vraća listu s granama stabla

(define (dfs graph node)
	"Creates a tree from a directed graph using Depth-First Search (DFS)"
	(let ((adjacency-list-undirected (adjacency-list graph #f))
		  (adjacency-list-directed (adjacency-list graph #t))
		  (visited (list node))
		  (tree-links '()))
		 (if (null? (set-difference (neighbours node) (visited)))
		 	'tree-links ; možda treba bit '()
		 	(begin
		 		(set! visited (append visited neighbour))
				(set! tree-links (append tree-links '(node neighbour)))
		 		(map dfs graph (make-list (length (neighbours node)) graph)) (neighbours node))
)))


; verzija 2
(define (dfs graph node visited tree-links)
 	"Creates a tree from a directed graph using Depth-First Search (DFS)"
	(let ((adjacency-list-undirected (adjacency-list graph #f))
		  (adjacency-list-directed (adjacency-list graph #t)))
	(if (null? (set-difference (neighbours node) visited))
		tree-links
		(let ((neighbour (car (neighbours node))))
			  (dfs graph neighbour (cons neighbour visited)
			(cons `(,node ,neighbour) tree-links))))))
			
;; verzija 3

; function dfs(node):
;     // Mark the current node as visited
;     mark node as visited

;     // Process the current node
;     process node

;     // Recursively visit all adjacent nodes
;     for each child of node:
;         if child is not visited:
;             dfs(child)

#|
(define (dfs graph node)
	(let* ((adjacency-list-undirected (adjacency-list graph #f)) ; let* supports the sequenced binding of variables, where each initial value expression can use the previous bindings.
		;; (adjacency-list-directed (adjacency-list graph #t)) ;; vjerojatno mi ne treba u ovoj funkciji
		(visited '())
		(tree-links '())
		((dfs-recursive node)
			(append visited '(node)) ; ovo samo kreira listu, treba pozvat set! funkciju
			(append tree-links (get-corresponding-element node all-nodes )
			
|#
		


	
