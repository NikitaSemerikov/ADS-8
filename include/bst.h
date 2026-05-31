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
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& k)
            : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* addNode(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }
        if (value < node->key) {
            node->left = addNode(node->left, value);
        } else if (value > node->key) {
            node->right = addNode(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }

    int searchNode(Node* node, const T& value) const {
        if (!node) return 0;
        if (value == node->key) return node->count;
        if (value < node->key) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }

    int depthNode(Node* node) const {
        if (!node) return -1;  // высота пустого дерева
        int dl = depthNode(node->left);
        int dr = depthNode(node->right);
        return (dl > dr ? dl : dr) + 1;
    }

    void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        inorder(node->left, out);
        out.emplace_back(node->key, node->count);
        inorder(node->right, out);
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

    void insert(const T& value) { root = addNode(root, value); }

    int search(const T& value) const { return searchNode(root, value); }

    int depth() const { return depthNode(root); }

    void getFreqList(std::vector<std::pair<T, int>>& out) const {
        inorder(root, out);
    }
};

#endif  // INCLUDE_BST_H_
