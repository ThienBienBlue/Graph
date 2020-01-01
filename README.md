# Graph
Mathematical Graph, G(V, E), implementation in C++.

In my algorithms class at University, there were many subjects learned on paper. Some were more easily translated to code (i.e Knapsack,
Longest Increasing Subsequence), but others, mainly graph based algorithms, are not as simple to translate to code.

Here we will explore ways to represent graphs, and ways to implement the many graph algorithms, and give a purpose for using a graph
algorithm to solve a problem.

# Class: (Directed) Graph
A graph is represented as an adjacency matrix `m_adj_matrix`, which is represented as a 2D square vector of ints. Adding a vertex to 
the graph would increase `m_adj_matrix` by a row and a column. Indexing into the matrix at a certain row and column represents the 
weight from the vertex represented by index row, to the vertex represented by index column.

The adjacency matrix knows nothing about the value attached to any nodes, only it's corresponding index, so we rectify this with an 
array `m_vals` to map: index -> val of node. There is also a corresponding mapping: val -> index in a `m_val_to_index` unordered map.
The Graph class's API should allow users to interact with vertices through the vertex's value, and edges through the two vertices of 
the edge. Indices of the matrix representation as well as the matrix, val -> node, node -> val should be hidden to the user.

add_node(int val): O(|V|)\n
Adds a node to Graph based on the node's value. All nodes are unique by design, there cannot exist two nodes with the same value.
Updates `m_adj_matrix` by adding a row and column, as well as `m_vals` and `m_val_to_index`.

add_edge(int a, int b, int weight): O(|V|)\n
Indexes into `m_adj_matrix` and updates the value at row `a`, column `b`. If either vertex `a` or `b` does not exist, create it by
calling add_node.

update_edge(int a, int b, int weight): O(1)\n
Updates the weight of an already existing edge by updating `m_adj_matrix[a][b]`.

topological_sort(): O(|V|^2)\n
Runs topological sort and returns <True, TS> where TS is the sort. If there is no existing topological sort, returns <False, TS>.
An initial scan of the adjacency matrix gets all the indegrees of every vertex, and puts all vertices with indegree=0 into a queue.
Then continuously dequeue a vertex from the queue, update all indegrees of the other vertices and add to queue if applicable. Do a 
final indegree scan to ensure that each vertex has an indegree of 0.

deikstra(int source): O(|V|^2 * lg(|V|))\n
Runs Deikstra's shortest path (one-to-all) on Graph. DOES NOT check for negative weights. Initialises a min-heap that maps: node -> 
shortest path, and fills all values with INT_MAX. Then updates the source node to have a shortest path of 0. Continuously pop items 
off the heap, look at all the vertices that the current node connects to, and update their shortest path if needed on the heap.

get_permutations(std::vector<int> &vector): O(n!)\n
Returns all the permutations that can be created from `vector`. There is a simple way to do this, involving sorting, recursion, and 
proper swapping of items around, but this can also be treated as a Graph problem. Take all items in `vector`, toss it into a graph 
where all items have an edge to all other items, and keep count of the number of times each item appears. Then run Hamiltonian 
paths, starting from every unique item.

# TODO
Split Graph into Graph and AdjMatrix, where AdjMatrix is a base class that takes the data members of Graph into its protected 
section. From there create Graph and DGraph as derived classes from AdjMatrix. Graphs and Directed Graphs can have similar 
implementations on the surface, but are mathematically different objects. Spanning Trees are well defined in Graphs, but not 
Directed Graphs; vice-versa with topological-sort and Bellman-Ford.
