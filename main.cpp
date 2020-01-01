#include <iostream>
#include "Graph.h"
#include "KeyValHeap.h"
#include "UndirectedGraph.h"

bool test_graph() {
    Graph graph;
    graph.add_edge('r', 'o', 1);
    graph.add_edge('o', 'w', 1);
    graph.add_edge('w', 'l', 1);
    graph.add_edge('l', 'e', 1);
    graph.add_edge('e', 't', 1);

    std::vector<std::vector<char>> additional_edges = {
            {'r', 't'}, {'r', 'l'}, {'o', 'l'},
            {'o', 'e'}, {'w', 't'}
    };
    for (auto &tuple : additional_edges) {
        graph.add_edge(tuple[0], tuple[1], 1);
    }

    graph.summary();
    graph.print_graph();

    auto rowlet = graph.topological_sort();
    if (rowlet.first) {
        std::cout << "The topological sort for this graph is:\n";
        for (auto i : rowlet.second) {
            std::cout << (char)i;
        } std::cout << '\n';
    }
    else {
        std::cout << "you fucked up on the rowlet.\n";
    }

    graph.add_edge('t', 'l', 420);
    auto row_let = graph.topological_sort();
    if (!row_let.first) {
        for (char c : row_let.second) {
            std::cout << (char)c;
        } std::cout << '\n';
    }

    graph.summary();

    std::vector<int> digits = {1, 3, 2, 4};
    auto digit_permutations = Graph::get_permutations(digits);
    for (auto &p : digit_permutations) {
        std::cout << "[ ";
        for (auto &v : p) {
            std::cout << v << " ";
        }
        std::cout << "]\n";
    }

    return true;
}

bool test_heap() {
    std::vector<int> digits = {1, 3, 5, 6, 8, 4, 2, 0, 9, 7};
    KeyValHeap heap;
    for (auto i : digits) {
        heap.add_key_val(i, i);
    }

    heap.summary();
    std::vector<int> sorted_digits;
    sorted_digits.reserve(10);
    while (!heap.empty()) {
        sorted_digits.push_back(heap.pop().second);
    }
    std::cout << "[ ";
    for (auto d : sorted_digits) {
        std::cout << d << ' ';
    } std::cout << "]";

    return true;
}

bool test_deikstra() {
    Graph g;
    char nodes[] = {'A', 'B', 'C', 'D', 'E'};
    for (auto c : nodes)
        g.add_node(c);

    g.add_edge('A', 'B', 3);
    g.add_edge('B', 'A', 3);

    g.add_edge('A', 'C', 1);
    g.add_edge('C', 'A', 1);

    g.add_edge('B', 'C', 7);
    g.add_edge('C', 'B', 7);

    g.add_edge('C', 'D', 2);
    g.add_edge('D', 'C', 2);

    g.add_edge('B', 'D', 5);
    g.add_edge('D', 'B', 5);

    g.add_edge('B', 'E', 1);
    g.add_edge('E', 'B', 1);

    g.add_edge('D', 'E', 7);
    g.add_edge('E', 'D', 7);

    auto dei = g.deikstra('C');
    std::cout << "[";
    for (auto &d : dei) {
        std::cout << "[" << (char)d.first << ", " << d.second << "], ";
    }
    std::cout << "]\n";

    g.summary();

    return true;
}

bool test_UndirectedGraph() {
    UndirectedGraph g;
    Graph t;

    char nodes[] = {'A', 'B', 'C', 'D', 'E'};
    for (auto c : nodes)
        g.add_node(c);

    g.add_edge('B', 'A', 3);

    g.add_edge('C', 'A', 1);

    g.add_edge('C', 'B', 7);

    g.add_edge('D', 'C', 2);

    g.add_edge('D', 'B', 5);

    g.add_edge('E', 'B', 1);

    g.add_edge('E', 'D', 7);

    auto dei = g.deikstra('C');
    std::cout << "[";
    for (auto &d : dei) {
        std::cout << "[" << (char)d.first << ", " << d.second << "], ";
    }
    std::cout << "]\n";

    g.summary();
    g.print_graph();

    return true;
}

int main() {
    test_graph();
    test_deikstra();
    test_UndirectedGraph();

    return 0;
}
