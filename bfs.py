from collections import deque

def bfs(adj_list, initial_node):
    visited = {node: False for node in adj_list}
    parent = {node: None for node in adj_list}
    queue = deque([initial_node])
    visited[initial_node] = True

    while queue:
        current_node = queue.popleft()
        for neighbor in adj_list[current_node]:
            if not visited[neighbor]:
                visited[neighbor] = True
                parent[neighbor] = current_node
                queue.append(neighbor)

    return parent

# Example usage:
adj_list = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

initial_node = 'A'
tree = bfs(adj_list, initial_node)
print(tree)

