(define (neighbours node adj-list) (cadr (assoc node adj-list)))

(define (tree-neighbours node tree)
  "Tree neighbours, subset of neighbours."
  (cond
   ((null? tree) '())
   ((equal? (car (car tree)) node)
    (cons (cadr (car tree)) (tree-neighbours node (cdr tree)))
    )
   ((equal? (cadr (car tree)) node)
    (cons (car (car tree)) (tree-neighbours node (cdr tree)))
    )
   (else (tree-neighbours node (cdr tree)))
   ))

(define (dfs-tree adj-list initial-node)
  "Creates a spanning tree in a graph using DFS. Tree is subset of links"
  (letrec (
           (dfs (lambda (node visited tree)
                  (fold-right
                   (lambda (neighbor result)
                     (let (
                           (result-tree (car result))
                           (result-visited (cdr result))
                           )
                       (if (member neighbor result-visited)
                           result
                           (dfs neighbor result-visited (cons (list node neighbor) result-tree)))))
                   (cons tree (cons node visited))
                   (neighbours node adj-list)
                   ))))
    (reverse (car (dfs initial-node '() '()))) ; THIS WORKS
    ;(dfs initial-node '() '()) ; ONLY FOR TESTING
    ))

#|
(define (NEW-dfs-tree adj-list initial-node)
  (letrec (
           (dfs (lambda (node visited tree)
                  (let (
                        (unvisited-neighbours (set-difference (neighbours node adj-list) (visited)))
                        )
                  (if (null? unvisited-neighbours)
                      tree
                      (fold-right (lambda ()
                  )))

                (dfs initial-node '() '())
|#
                  

(define *tree* (dfs-tree *adjacency-list-undirected* 0))


(define (chords tree)
  (set-difference
   (set-difference *links* (map reverse tree))
   tree)
  )

(define *chords* (chords *tree*))


(define tree-loop (lambda (chord tree)
                    (letrec (
                             (start (cadr chord))
                             (finish (car chord))
                             (dfs
                              (lambda (node visited)
                                (let (
                                      (unvisited-neighbours
                                       (lambda (node)
                                         (set-difference (tree-neighbours node tree) visited)
                                         ))
                                      )
                                  (if (equal? node finish)
                                      visited
                                      (begin
                                      ;(pretty-print visited)
                                      (map
                                       (lambda (x) (dfs x (cons node visited)))
                                       (unvisited-neighbours node))
                                       )
                                      ))))
                             )
                      (dfs start '())
                      )))

(define *tree-loops* (map (lambda (chord) (tree-loop chord *tree*)) *chords*))

;(pretty-print *chords*) (newline) (pretty-print *tree-loops*) (newline)
(pretty-print '(0 4)) (newline) (pretty-print (tree-loop '(0 4) *tree*)) (newline)


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

#|
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
|#

;; example usage
;; (define example-tree (dfs-init system 0))
;; ((fundamental-circuit-matrix system example-tree) 1 0)

; defining FUNDAMENTAL CIRCUIT MATRIX
