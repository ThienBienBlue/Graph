//
// Created by Thien on 12/30/2019.
//

#include <iostream>
#include "UndirectedGraph.h"

UndirectedGraph::UndirectedGraph()
    : Graph()
{}

void
UndirectedGraph::add_edge(int a, int b, int weight) {
    Graph::add_edge(a, b, weight);
    Graph::add_edge(b, a, weight);
}

bool
UndirectedGraph::update_edge(int a, int b, int val) {
    Graph::update_edge_by_nodes(a, b, val);
    Graph::update_edge_by_nodes(b, a, val);
}

bool
UndirectedGraph::increase_edge(int a, int b, int val) {
    if (Graph::has_vertex(a) && Graph::has_vertex(b)) {
        int old_weight = Graph::has_edge(a, b);
        Graph::update_edge_by_nodes(a, b, val + old_weight);
        Graph::update_edge(b, a, val + old_weight);
        return true;
    }
    return false;
}

const void
UndirectedGraph::summary() {
    std::cout << "The graph has " << Graph::get_vertices() << " vertices.\n";
    std::cout << "The graph has " << Graph::get_edges() / 2 << " edges.\n";
    std::cout << "The summation of weight over all edges is " << Graph::get_edge_weights() / 2
              << ".\n";
}

std::vector<std::tuple<int, int, int>>
UndirectedGraph::prims_algorithm() {
    if (Graph::m_adj_matrix.size() == 0) {
        return std::vector<std::tuple<int, int, int>>();
    }

    std::vector<std::tuple<int, int, int>> return_me;

}
