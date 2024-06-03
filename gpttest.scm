(define (listc-helper prev lista listb fun1 fun2)
  (if (or (null? lista) (null? listb))
      '()
      (let ((current (fun2 prev (car lista) (car listb))))
        (cons current
              (listc-helper current (cdr lista) (cdr listb) fun1 fun2)))))

(define (listc lista listb fun1 fun2)
  (if (or (null? lista) (null? listb))
      '()
      (let ((first (fun1 (car lista) (cdr listb))))
        (cons first
              (listc-helper first (cdr lista) (cdr listb) fun1 fun2)))))

; Example usage:
(define (fun1 a b) (list a b))
(define (fun2 prev a b) (list a b prev))

(define lista '(a b c d))
(define listb '(1 2 3 4))

(define test (listc lista listb fun1 fun2))

