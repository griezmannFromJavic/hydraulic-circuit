#|
PYTHON IMPLEMENTATION

graph = {
  '5' : ['3','7'],
  '3' : ['2', '4'],
  '7' : ['8'],
  '2' : [],
  '4' : ['8'],
  '8' : []
}

visited = set() # Set to keep track of visited nodes of graph.

def dfs(visited, graph, node):  #function for dfs 
    if node not in visited:
        print ("v: ", node)
        visited.add(node)
        for neighbour in graph[node]:
            print("n: ", neighbour)
            dfs(visited, graph, neighbour)

# Driver Code
print("Following is the Depth-First Search")
dfs(visited, graph, '5')
|#

; python inspired

(define (dfs visited graph node)
	(let* (
		(neighbours (cadr (assoc node adjacency-list-undirected)))
		(unvisited-neighbours (set-difference neighbours visited))
		)
	(if (not (member node visited))
		(set! visited (cons node visited))
		(reverse visited) ; return valjda
		)
		(display visited)
		(newline)
		(map (lambda (neighbour) (dfs visited graph neighbour)) unvisited-neighbours)
		))

;(dfs '() system 1)








; old code
#|
(define (dfs-init graph initial-node)
(let  (
      (tree '())
      (visited '())
      )
  (define (dfs node)
		(let* (
              (neighbours (cadr (assoc node adjacency-list-undirected)))
              (unvisited-neighbours (set-difference neighbours visited))
              ) 
		(if (null? unvisited-neighbours)
			(reverse tree)
			(begin
				(set! visited (cons node visited))
				(display "tree before cons: ")
				(display tree)
				(newline) (newline)
				(set! tree
					(cons (list node (car unvisited-neighbours)) tree) ; tu je greška zašto car?
					)

		(display "visited: ")
		(display visited)
		(newline) (newline)		
		(display "unvisited neighbours: ")
		(display unvisited-neighbours)
		(newline) (newline)
		(display "tree after cons: ")
		(display tree)
		(newline) (newline)
		(display "-----------------------------------")
		(newline) (newline)

			(map dfs unvisited-neighbours)
			))))
			
	(dfs initial-node)
	))
|#
