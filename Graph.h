//
// Created by Thien on 12/27/2019.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H


#include <string>
#include <vector>
#include <unordered_map>

class Graph {
public:
    Graph();

    void
    add_node(int val);

    virtual void
    add_edge(int a, int b, int weight);

    virtual bool
    increase_edge(int a, int b, int val);

    virtual bool
    update_edge(int a, int b, int val);

    virtual std::pair<bool, std::vector<int>>
    topological_sort();

    std::vector<std::pair<int, int>>
    deikstra(int source);

    const void
    print_graph();

    virtual const void
    summary();

    static std::vector<std::vector<int>>
    get_permutations(std::vector<int> &vector);

protected:
    std::vector<std::vector<int>> m_adj_matrix;
    std::unordered_map<int, int> m_val_to_index;
    std::vector<int> m_vals;

    int m_vertices;
    int m_edges;
    int m_edge_weights;

    const int
    get_edges();

    const int
    get_vertices();

    const int
    get_edge_weights();

    void
    update_edge_by_nodes(int a, int b, int val);

    const bool
    has_vertex(int val);

    const int
    has_edge(int a, int b);

private:
    void
    permute(std::vector<std::vector<int>> &return_me,
            std::vector<int> &ways_to_go,
            std::vector<int> &permutation,
            int index, const int size);

    void
    update_edge_by_index(int row, int col, int val);
};


#endif //GRAPH_GRAPH_H
