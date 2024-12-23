// Implementing union find data structure using disjoint subset

// Using both union by rank and path compression

<template typename T>
class disjoint_subset {
    private:
        struct Node {
            T data;
            Node* parent;
            std::size_t rank;
        };

        Node *data;

    public:
        disjoint_subset(const T &data) {
            data = new Node{data, nullptr, 0};
        }

        disjoint_subset(const T &data, const T &parent_data) {
            data = new Node{data, nullptr, 0};
            Node *parent_node = new Node{parent_data, nullptr, 1};

            data->parent = parent_node;
        }

        T find(const T &data) {
            if (data->parent != nullptr) {
                // Path compression
                data->parent = find(data->parent);
                return data->parent;
            }
            return data;
        }

        void union_set(const T &A, const T &B) {
            T x = find(A);
            T y = find(B);

            // Union by rank

            if (x->rank < y->rank) {
                x->parent = y;
            } else if (x->rank > y->rank) {
                y->parent = x;
            } else {
                y->parent = x;
                ++x->rank;
            }
        }
};