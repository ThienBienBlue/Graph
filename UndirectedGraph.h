//
// Created by Thien on 12/30/2019.
//

#ifndef GRAPH_UNDIRECTEDGRAPH_H
#define GRAPH_UNDIRECTEDGRAPH_H


#include "Graph.h"

class UndirectedGraph: public Graph {
public:
    UndirectedGraph();

    virtual void
    add_edge(int a, int b, int weight);

    virtual bool
    update_edge(int a, int b, int val);

    virtual bool
    increase_edge(int a, int b, int val);

    virtual const void
    summary();

    std::vector<std::tuple<int, int, int>>  // <node, node, weight>
    prims_algorithm();

private:
    virtual std::pair<bool, std::vector<int>>
    topological_sort() {};
};


#endif //GRAPH_UNDIRECTEDGRAPH_H
