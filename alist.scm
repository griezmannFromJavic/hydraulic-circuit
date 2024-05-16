;; associacion list function definitions

(define (lookup key alist)
  (cond ((null? alist) #f) ; If the alist is empty, key is not found
        ((equal? key (caar alist)) (cadar alist)) ; If the key matches the first element of the first pair, return the value
        (else (lookup key (cdr alist))))) ; Otherwise, recursively search the rest of the alist

(define (insert key value alist)
  (cons (cons key value) alist)) ; Add a new key-value pair to the beginning of the alist

(define (update key value alist)
  (cond ((null? alist) (error "Key not found")) ; If the alist is empty, key is not found
        ((equal? key (caar alist)) ; If the key matches the first element of the first pair, update the value
         (cons (cons key value) (cdr alist)))
        (else (cons (car alist) (update key value (cdr alist)))))) ; Otherwise, recursively search the rest of the alist

(define my-alist '((key1 . value1) (key2 . value2) (key3 . value3)))

(display (lookup 'key2 my-alist)) ; Output: value2
(newline)

(define new-alist (insert 'key4 'value4 my-alist))
(display new-alist) ; Output: ((key4 . value4) (key1 . value1) (key2 . value2) (key3 . value3))
(newline)

(define updated-alist (update 'key2 'new-value2 my-alist))
(display updated-alist) ; Output: ((key1 . value1) (key2 . new-value2) (key3 . value3))
(newline)

