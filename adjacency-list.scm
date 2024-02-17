; The direction of edges is inferred from the order of vertices in the adjacency list.
; If vertex A has an edge to vertex B, then B will be listed in the adjacency list of A.
; If vertex A does not have an edge to vertex B, then B will not be present in the adjacency list of A.
; format: (starting-node (target-node-1 target-node-2) (link-1 link-2))

(define adjacency-list '(
(0 (1 2 4) (3 4 1))
(1 (3 4) (8 5))
(2 (3 5) (9 7))
(3 (4 5) (10 11))
(4 (5) (6))
(5 (0) (2))
))
