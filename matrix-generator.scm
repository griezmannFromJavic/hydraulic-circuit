(define (incidence-matrix graph)
	(lambda (node link)
	(let (
		(owner (car (list-ref system link)))
		(neighbour (cadr (list-ref system link)))
		)
	(cond
		((equal? neighbour link) 1)
		((equal? owner link) -1)
		(#t 0)
		))))

;; example usage
;; ((incidence-matrix system) 1 0)


(define (fundamental-circuit-matrix graph tree)
  (lambda (node link)
    (let (
          (owner (car (list-ref system link)))
          (neighbour (cadr (list-ref system link)))
          )
    (cond ((member (list owner neighbour) tree) 1)
          ((member (list neighbour owner) tree) -1)
          (else 0)
          ))))

;; example usage
;; (define example-tree (dfs-init system 0))
;; ((fundamental-circuit-matrix system example-tree) 1 0)
