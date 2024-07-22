(define (neighbours node adj-list) (cadr (assoc node adj-list)))

(define (tree-neighbours node tree)
  "Tree neighbours, subset of neighbours."
  (display tree) (newline)
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
                  ;(display tree) (newline)
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
                  

(define tree0 (dfs-tree adjacency-list-undirected 0))
;(display links) (newline) (display tree0) (newline)


(define (chords tree) ;global variable "links" inside function!!! Rename links to *links*, do the same wit all global variables. Mainly with ones from system.scm.
  (set-difference
   (set-difference links (map reverse tree))
   tree)
  )

(define chords0 (chords tree0))


(define tree-loop (lambda (chord tree)
                    (letrec (
                             (start (cadr chord))
                             (finish (car chord))
                             (unvisited-neighbours
                              (lambda (node)
                                (set-difference (tree-neighbours node tree) (visited))
                                ))
                             (dfs
                              (lambda (node visited)
                                (if (equal? node finish)
                                    visited
                                    (map
                                     (lambda (x) (dfs x (cons node visited)))
                                       (unvisited-neighbours node))
                                       )))
                                )
                      (display finish) (newline)
                              (dfs start '())
                              )))

(display (tree-loop (car chords0) tree0))


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
