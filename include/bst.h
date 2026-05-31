// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
    struct Node {
        T key;
        int freq;
        Node* left;
        Node* right;

        explicit Node(const T& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insertNode(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value < node->key) {
            insertNode(node->left, value);
        } else if (value > node->key) {
            insertNode(node->right, value);
        } else {
            node->freq++;
        }
    }

    Node* searchNode(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value < node->key) return searchNode(node->left, value);
        if (value > node->key) return searchNode(node->right, value);
        return node;
    }

    int depthNode(Node* node) const {
        if (!node) return 0;
        int dl = depthNode(node->left);
        int dr = depthNode(node->right);
        return 1 + (dl > dr ? dl : dr);
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        collect(node->left, out);
        out.emplace_back(node->key, node->freq);
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

    void insert(const T& value) { insertNode(root, value); }

    bool search(const T& value) const {
        return searchNode(root, value) != nullptr;
    }

    int depth() const { return depthNode(root); }

    std::vector<std::pair<T, int>> toVector() const {
        std::vector<std::pair<T, int>> v;
        collect(root, v);
        return v;
    }
};

#endif  // INCLUDE_BST_H_
