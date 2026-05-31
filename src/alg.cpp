// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

static bool isLatinLetter(char c) {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z');
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!\n";
        return;
    }

    std::string word;
    while (true) {
        int ch = file.get();
        if (!file) break;

        if (isLatinLetter(ch)) {
            word.push_back(static_cast<char>(std::tolower(ch)));
        }
        else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto vec = tree.toVector();

    std::sort(vec.begin(), vec.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });

    std::ofstream out("result/freq.txt");

    for (const auto& p : vec) {
        std::cout << p.first << " " << p.second << "\n";
        out << p.first << " " << p.second << "\n";
    }

    out.close();
}
