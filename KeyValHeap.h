//
// Created by Thien on 12/29/2019.
//

#ifndef GRAPH_KEYVALHEAP_H
#define GRAPH_KEYVALHEAP_H

#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>

class KeyValHeap {
public:
    KeyValHeap()
    {};

    void
    add_key_val(int key, int val) {
        int index = m_heap.size();
        m_key_to_index[key] = index;
        m_heap.emplace_back(std::pair<int, int>(val, key));
        update_index(index);
    }

    std::pair<int, int>
    pop() {
        auto top = m_heap[0];
        swap(0, m_heap.size() - 1);
        m_heap.pop_back();
        m_key_to_index.erase(m_key_to_index.find(top.second));
        trickle_down();
        return top;
    }

    void
    update_key(int key, int val) {
        if (m_key_to_index.find(key) != m_key_to_index.end()) {
            int index = m_key_to_index[key];
            m_heap[index].first = val;
            update_index(index);
        }
    }

    const bool
    empty() {
        return m_heap.size() == 0;
    }

    const void
    summary() {
        std::cout << "[ ";
        for (auto d : m_heap) {
            std::cout << d.second << ' ';
        }
        std::cout << "]";
    }

private:
    std::vector<std::pair<int, int>> m_heap;  // <val, key>
    std::unordered_map<int, int> m_key_to_index;  // key -> index.

    void
    swap(int a, int b) {
        auto a_node = m_heap[a];
        auto b_node = m_heap[b];

        m_heap[a] = b_node;
        m_heap[b] = a_node;

        m_key_to_index[a_node.second] = b;
        m_key_to_index[b_node.second] = a;
    }

    static int
    parent(int index) {
        return (index - 1) / 2;
    }

    static int
    left_child(int index) {
        return 2 * index + 1;
    }

    static int
    right_child(int index) {
        return 2 * index + 2;
    }

    std::pair<int, int>
    min_child(int index) {
        auto min_child = std::pair<int, int>(-1, -1);
        bool left = left_child(index) < m_heap.size();
        bool right = right_child(index) < m_heap.size();
        if (left && right) {
            min_child = std::min(
                    std::pair<int, int> (m_heap[left_child(index)].first, left_child(index)),
                    std::pair<int, int> (m_heap[right_child(index)].first, right_child(index)),
                    [](const std::pair<int, int> &a, const std::pair<int, int> &b) -> bool {
                        return a.first < b.first;
                    });
        }
        else if (left) {
            min_child = std::pair<int, int> (m_heap[left_child(index)].first, left_child(index));
        }
        else if (right) {
            min_child = std::pair<int, int> (m_heap[right_child(index)].first, right_child(index));
        }
        return min_child;
    }

    void
    update_index(int index) {
        int index_val = m_heap[index].first;
        int parent_val = m_heap[parent(index)].first;
        while (index_val < parent_val) {
            swap(index, parent(index));
            index = parent(index);
            parent_val = m_heap[parent(index)].first;
        }
    }

    void
    trickle_down() {
        int index = 0;
        const int index_val = m_heap[index].first;
        auto index_min_child = min_child(index);
        while (index_min_child.second != -1 && index_min_child.first < index_val) {
            swap(index, index_min_child.second);
            index = index_min_child.second;
            index_min_child = min_child(index);
        }
    }
};

#endif //GRAPH_KEYVALHEAP_H
