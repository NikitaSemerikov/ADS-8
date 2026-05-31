// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "bst.h"

static bool isLatinLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
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

        if (isLatinLetter(static_cast<char>(ch))) {
            char lower = static_cast<char>(std::tolower(ch));
            word.push_back(lower);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> vec;
    tree.getFreqList(vec);

    std::sort(vec.begin(), vec.end(),
              [](const std::pair<std::string, int>& a,
                 const std::pair<std::string, int>& b) {
                  if (a.second != b.second) return a.second > b.second;
                  return a.first < b.first;
              });

    std::ofstream out("result/freq.txt");

    for (const auto& p : vec) {
        std::cout << p.first << " " << p.second << "\n";
        out << p.first << " " << p.second << "\n";
    }
}
