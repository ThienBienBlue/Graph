//
// Created by Thien on 12/27/2019.
//

#include <iostream>
#include "Graph.h"
#include "KeyValHeap.h"
#include <queue>

//--------------------
// Public functions.
//--------------------

Graph::Graph()
    : m_vertices(0), m_edges(0), m_edge_weights(0)
{}

void
Graph::add_node(int val) {
    if (!has_vertex(val)) {
        m_vals.push_back(val);
        m_val_to_index[val] = m_vertices;
        m_adj_matrix.emplace_back(m_vertices);
        for (auto &row: m_adj_matrix) {
            row.push_back(0);
        }
        m_vertices++;
    }
}

void
Graph::add_edge(int a, int b, int weight) {
    if (!has_vertex(a)) {
        add_node(a);
    }
    if (!has_vertex(b)) {
        add_node(b);
    }

    int row = m_val_to_index[a];
    int col = m_val_to_index[b];
    update_edge_by_index(row, col, weight);
}

bool
Graph::update_edge(int a, int b, int val) {
    if (has_edge(a, b)) {
        int row = m_val_to_index[a];
        int col = m_val_to_index[b];
        update_edge_by_index(row, col, val);
        return true;
    }
    return false;
}

bool
Graph::increase_edge(int a, int b, int val) {
    if (has_edge(a, b)) {
         int row = m_val_to_index[a];
         int col = m_val_to_index[b];
         int new_val = val + m_adj_matrix[row][col];
         update_edge_by_index(row, col, new_val);
         return true;
    }
    return false;
}

std::pair<bool, std::vector<int>>
Graph::topological_sort() {
    std::vector<int> ts;
    ts.reserve(m_vertices);

    std::vector<int> indegrees(m_vertices);
    std::queue<int> q;
    for (int i = 0; i < m_vertices; i++) {
        int indegree = 0;
        for (int j = 0; j < m_vertices; j++) {
            indegree += m_adj_matrix[j][i];
        }

        indegrees[i] = indegree;
        if (indegree == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int source = q.front();
        ts.push_back(m_vals[source]);
        q.pop();

        for (int outgoing = 0; outgoing < m_vertices; outgoing++) {
            int in = indegrees[outgoing];
            if (in > 0) {
                in += -1 * m_adj_matrix[source][outgoing];
                if (in == 0) {
                    q.push(outgoing);
                }
                indegrees[outgoing] = in;
            }
        }
    }

    int remainder = 0;
    for (auto val : indegrees) {
        remainder += val;
    }

    return std::pair<bool, std::vector<int>>(!(bool)remainder, ts);
}

std::vector<std::pair<int, int>>
Graph::deikstra(int source) {
    std::vector<int> shortest_path(m_vertices, INT32_MAX);

    // Set up the key-value heap.
    int source_index = m_val_to_index[source];
    KeyValHeap heap;
    heap.add_key_val(source_index, 0);
    for (int i = 0; i < m_vertices; i++) {
        if (i != source_index) {
            heap.add_key_val(i, INT32_MAX);
        }
    }

    while(!heap.empty()) {
        auto top_node = heap.pop();
        int path_to_node = top_node.first;
        int node_index = top_node.second;
        shortest_path[top_node.second] = path_to_node;

        for (int node = 0; node < m_vertices; node++) {
            int edge = m_adj_matrix[node_index][node];
            if (edge) {
                shortest_path[node] = std::min(shortest_path[node],
                        path_to_node + edge);
                heap.update_key(node, shortest_path[node]);
            }
        }
    }

    std::vector<std::pair<int, int>> return_me;
    return_me.reserve(m_vertices);
    for (int i = 0; i < m_vertices; i++) {
        return_me.emplace_back(std::pair<int, int> (m_vals[i], shortest_path[i]));
    }

    return return_me;
}

const void
Graph::print_graph() {
    for (auto &val : m_vals) {
        std::cout << val << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < m_vertices; i++) {
        std::cout << "Node: " << m_vals[i] << "    | [ ";
        for (int j = 0; j < m_vertices; j++) {
            std::cout << m_adj_matrix[i][j] << ", ";
        }
        std::cout << " ]\n";
    }
}

const void
Graph::summary() {
    std::cout << "The graph has " << m_vertices << " vertices.\n";
    std::cout << "The graph has " << m_edges << " edges.\n";
    std::cout << "The summation of weight over all edges is " << m_edge_weights
        << ".\n";
}

//---------------------
// Static functions.
//---------------------

std::vector<std::vector<int>>
Graph::get_permutations(std::vector<int> &vector) {
    int size = vector.size();
    std::vector<std::vector<int>> permutations;

    if (size == 0) {
        return permutations;
    }

    Graph g;
    std::vector<int> ways_to_go;
    for (int val : vector) {
        g.add_node(val);
        int index = g.m_val_to_index[val];
        if (index >= ways_to_go.size()) {
            ways_to_go.push_back(0);
        }
        ways_to_go[index]++;
    }

    for (int i = 0; i < g.m_vertices; i++) {
        for (int j = 0; j < g.m_vertices; j++) {
            g.update_edge_by_index(i, j, 1);
        }
    }

    std::vector<int> permutation;
    permutation.reserve(size);

    for (int index = 0; index < g.m_vertices; index++) {
        g.permute(permutations, ways_to_go, permutation, index, size);
    }

    return permutations;
}

//----------------------
// Protected Functions.
//----------------------

const bool
Graph::has_vertex(int val) {
    auto vertex_reference = m_val_to_index.find(val);
    return vertex_reference != m_val_to_index.end();
}

const int
Graph::has_edge(int a, int b) {
    auto row = m_val_to_index.find(a);
    auto col = m_val_to_index.find(b);

    int edge_exists = 0;
    if (row != m_val_to_index.end() && col != m_val_to_index.end()) {
        edge_exists = m_adj_matrix[row->second][col->second];
    }
    return edge_exists;
}

const int
Graph::get_vertices() {
    return m_vertices;
}

const int
Graph::get_edges() {
    return m_edges;
}

const int
Graph::get_edge_weights() {
    return m_edge_weights;
}

void
Graph::update_edge_by_nodes(int a, int b, int val) {
    int row = m_val_to_index[a];
    int col = m_val_to_index[b];
    update_edge_by_index(row, col, val);
}


//-----------------------
// Private Functions.
//-----------------------

void
Graph::update_edge_by_index(int row, int col, int val) {
    int weight = m_adj_matrix[row][col];
    m_edge_weights += -weight;
    m_edge_weights += val;

    if (weight != 0) {
        m_edges--;
    }

    if (val != 0) {
        m_edges++;
    }

    m_adj_matrix[row][col] = val;
}

void
Graph::permute(std::vector<std::vector<int>> &return_me,
               std::vector<int> &ways_to_go,
               std::vector<int> &permutation,
               int index, const int size)
{
    if (ways_to_go[index] > 0) {
        ways_to_go[index]--;
        permutation.push_back(m_vals[index]);

        if (permutation.size() == size) {
            return_me.push_back(permutation);
        }
        else {
            for (int next = 0; next < m_vertices; next++) {
                if (m_adj_matrix[index][next]) {
                    permute(return_me, ways_to_go, permutation,
                            next, size);
                }
            }
        }

        permutation.pop_back();
        ways_to_go[index]++;
    }
}