(define (neighbours node adj-list) (cadr (assoc node adj-list)))

(define (tree-neighbours node tree)
	(cond
		((null? tree) '())
		((equal? (car (car tree)) node)
			(cons (cadr (car tree)) (tree-neighbours (cdr tree) node))
			)
		((equal? (cadr (car tree)) node)
			(cons (car (car tree)) (tree-neighbours (cdr tree) node))
			)
		(else (tree-neighbours (cdr tree) node))
		))

(define (dfs-tree adj-list initial-node)
"Creates a spanning tree in a graph using DFS. Tree is subset of links"
	(letrec (
		(dfs (lambda (node visited tree)
			(let
				((new-visited (cons node visited)))
				(fold-right
					(lambda (neighbor result)
						(let (
							(result-tree (car result))
							(result-visited (cdr result))
								)
							(if (member neighbor result-visited)
								result
								(let (
									(dfs-result (dfs neighbor result-visited (cons (list node neighbor) result-tree)))
									)
									(cons (car dfs-result) (cdr dfs-result))
									))))
					(cons tree new-visited)
					(neighbours node adj-list))
					)))
		)
		;(reverse (car (dfs initial-node '() '()))) ; THIS WORKS
		(dfs initial-node '() '()) ; ONLY FOR TESTING
	))

(define tree0 (dfs-tree adjacency-list-undirected 0))
(display links) (newline) (display tree0) (newline)

#|
(define (chords tree) ;global variable "links" inside function!!!
	(set-difference
		(set-difference links (map reverse tree))
			tree)
		)
	
(define chords0 (chords tree0))


(define tree-loop (lambda (chord tree)
	(letrec (
		(start (car chord))
		(finish (cadr chord))
		(visited (lambda () (cons node visited)))
		(unvisited-neighbour
			(lambda ()
				(car (set-difference (tree-neighbours tree node) visited))
				))
		(dfs
			(lambda (node neighbour visited tree)
				(if (equal? (cdr loop-link) finish)
				visited
				(dfs (neighbour (unvisited-neighbour neighbour) (cons neighbour visited) tree))
				)))
			)
		(dfs start tree)
		)))
		
(display (tree-loop (car chords0) tree0))
|#

; defining INCIDENCE MATRIX
(define (incidence-matrix graph)
	(lambda (node link)
	(let (
		(owner (car (list-ref system link)))
		(neighbour (cadr (list-ref system link)))
		)
	(cond
		((equal? neighbour link) 1)
		((equal? owner link) -1)
		(else 0)
		))))

;; example usage
;; ((incidence-matrix system) 1 0)

(define (fundamental-circuit-matrix graph tree)
  (lambda (node link)
    (letrec (
          ; loops
          ; loop-currents
          )
    (cond ((member (list owner neighbour) tree) 1)
          ((member (list neighbour owner) tree) -1)
          (else 0)
          ))))

;; example usage
;; (define example-tree (dfs-init system 0))
;; ((fundamental-circuit-matrix system example-tree) 1 0)

; defining FUNDAMENTAL CIRCUIT MATRIX


