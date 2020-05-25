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

    void inOrder() {
        cout << "sorted by variable name" << endl;
        inOrder(root);
        cout << endl << endl;
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

    void inOrder(struct Node<k, v> *root) {
        if (root == NULL) return;
        inOrder(root->left);
        std::cout << "Key : " << root->key << " Value : " << root->value << std::endl;
        inOrder(root->right);
    }
};


#endif //SIMPLE_INTERPRETER_BST_H
