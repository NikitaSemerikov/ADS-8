// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>

template <typename T>
class BST {
private:
    struct Node {
        T key;
        int freq;
        Node* left;
        Node* right;

        explicit Node(const T& k)
            : key(k), freq(1), left(nullptr), right(nullptr) {
        }
    };

    Node* root;

    void insert(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value < node->key) {
            insert(node->left, value);
        }
        else if (value > node->key) {
            insert(node->right, value);
        }
        else {
            node->freq++;
        }
    }

    Node* searchNode(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value < node->key) return searchNode(node->left, value);
        if (value > node->key) return searchNode(node->right, value);
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int dl = depth(node->left);
        int dr = depth(node->right);
        return 1 + (dl > dr ? dl : dr);
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        collect(node->left, out);
        out.push_back({ node->key, node->freq });
        collect(node->right, out);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& value) { insert(root, value); }

    bool search(const T& value) const {
        return searchNode(root, value) != nullptr;
    }

    int depth() const { return depth(root); }

    std::vector<std::pair<T, int>> toVector() const {
        std::vector<std::pair<T, int>> v;
        collect(root, v);
        return v;
    }
};

#endif  // INCLUDE_BST_H_
