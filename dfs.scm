(define (dfs-init adj-list initial-node)
  (define (neighbours node) (cadr (assoc node adj-list)))

  (define (dfs node visited tree)
    (let ((new-visited (cons node visited)))
      (fold-right 
        (lambda (neighbor result)
          (let ((result-tree (car result))
                (result-visited (cdr result)))
            (if (memq neighbor result-visited)
                result
                (let ((dfs-result (dfs neighbor result-visited (cons (list node neighbor) result-tree))))
                  (cons (car dfs-result) (cdr dfs-result))))))
        (cons tree new-visited)
        (neighbours node))))

  (car (dfs initial-node '() '())))

; Example usage:
; Assuming graph is an association list like this:
(define graph '((1 (2 3))
                (2 (1 4 5))
                (3 (1 6 7))
                (4 (2 5))
                (5 (2 4))
                (6 (3 7))
                (7 (3 6))
                ))
(dfs-init graph 1)

