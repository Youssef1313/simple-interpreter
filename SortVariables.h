#ifndef SIMPLE_INTERPRETER_SORTVARIABLES_H
#define SIMPLE_INTERPRETER_SORTVARIABLES_H

#include <string>
#include "Evaluation/Value.h"
#include <unordered_map>
#include "Collections/Heap.h"
#include "Collections/BST.h"

void sortVariables(const unordered_map<string, Value> &map);

void sortVariables(const unordered_map<string, Value>&map) {
    Heap<string, Value> heap(map.size());
    BST<string, Value> bst;

    for (const auto& variable : map) {
        heap.put(variable.first, variable.second);
        bst.put(variable.first, variable.second);
    }

    heap.sort();
    bst.inOrder();

    heap.print();
}

#endif //SIMPLE_INTERPRETER_SORTVARIABLES_H
