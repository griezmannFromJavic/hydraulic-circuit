(define (dfs-tree adj-list initial-node)
	(letrec (
		(neighbours (lambda (node) (cadr (assoc node adj-list))))
		(dfs (lambda (node visited tree)
			(let ((new-visited (cons node visited)))
				(fold-right
					(lambda (neighbor result)
						(let ((result-tree (car result))
							(result-visited (cdr result)))
							(if (member neighbor result-visited)
								result
								(let ((dfs-result (dfs neighbor result-visited (cons (list node neighbor) result-tree))))
									(cons (car dfs-result) (cdr dfs-result))))))
					(cons tree new-visited)
					(neighbours node)))))
		)
		(reverse (car (dfs initial-node '() '())))
	))

(define tree (dfs-tree adjacency-list-undirected 0))

(define chords (set-difference
	(set-difference links (map reverse tree))
	tree)
	)
	
#|
(define loop (lambda (chord tree)
	(let (
		(
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


