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
};

template<class k, class v>
class BST {
private:
    struct Node<k, v> *root;

public:
    BST() {
        root = NULL;
    }

    void insert(k key, v value) {
        root = insert(root, key, value);
    }

    void inOrder() {
        inOrder(root);
    }

private:
    Node<k, v> *insert(struct Node<k, v> *root, k key, v value) {
        Node<k, v> *node = newNode(key, value);
        if (root == NULL) {
            root = node;
        } else if (root->key > key)
            root->left = insert(root->left, key, value);
        else {
            root->right = insert(root->right, key, value);
        }
        return root;
    }

    struct Node<k, v> *newNode(k key, v value) {
        struct Node<k, v> *node = new Node<k, v>;
        node->key = key;
        node->value = value;
        node->right = NULL;
        node->left = NULL;
        return node;
    }

    void inOrder(struct Node<k, v> *root) {
        if (root == NULL)
            return;
        inOrder(root->left);
        std::cout << "Key : " << root->key << " Value : " << root->value << std::endl;
        inOrder(root->right);
    }
};


#endif //SIMPLE_INTERPRETER_BST_H
