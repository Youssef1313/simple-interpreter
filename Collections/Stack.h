/*
 * we implemented this stack before knowing
 * that we can use stl stack,
 * therefore it isn't used.
 */

#ifndef SIMPLE_INTERPRETER_STACK_H
#define SIMPLE_INTERPRETER_STACK_H
#include <stdlib.h>

template<typename T>
struct Node {
    T data;
    Node *next;
};

template<typename T>
class Stack {
private:
    Node<T> *top;
public:
    Stack() {
        top = NULL;
    }

    void push(T v) {
        Node<T> *temp = new Node<T>;
        temp->data = v;
        temp->next = top;
        top = temp;
    }

    T peek() {
        return top->data;
    }

    void pop() {
        Node<T> *temp = top;
        top = top->next;
        delete temp;
    }

    bool isEmpty() {
        return top == NULL;
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }
};

#endif //SIMPLE_INTERPRETER_STACK_H
