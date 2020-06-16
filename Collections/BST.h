#ifndef SIMPLE_INTERPRETER_BST_H
#define SIMPLE_INTERPRETER_BST_H

#include <iostream>
#include <string.h>

template<class k, class v>
struct Node {
    k key;
    v value;
    Node *left;
    Node *right;

    Node(k key, v value) : key(key), value(value) {
        this->right = this->left = NULL;
    }
};

template<class k, class v>
class BST {
private:
    struct Node<k, v> *root;

public:
    BST() {
        root = NULL;
    }

    void put(k key, v value) {
        root = insert(root, key, value);
    }

    void inOrder(QString *result) {
        inOrder(root, result);
    }

private:
    Node<k, v> *insert(struct Node<k, v> *root, k key, v value) {
        auto *node = new Node<k, v>(key, value);
        if (root == NULL) {
            root = node;
        } else if (root->key > key)
            root->left = insert(root->left, key, value);
        else {
            root->right = insert(root->right, key, value);
        }
        return root;
    }

    void inOrder(struct Node<k, v> *root, QString *result) {
        if (root == NULL) return;
        inOrder(root->left, result);
        result->append(((string)root->key).c_str()).append(" = ").append(root->value.toString().c_str()).append('\n');
        inOrder(root->right, result);
    }
};


#endif //SIMPLE_INTERPRETER_BST_H
