#ifndef SIMPLE_INTERPRETER_HEAP_H
#define SIMPLE_INTERPRETER_HEAP_H

#include <iostream>
#include <vector>

using namespace std;

template<class k, class v>
struct HeapNode {
    k key;
    v value;
    HeapNode(k key, v value) : key(key), value(value) {}
};

template<class k, class v>
class Heap {
private:
    vector<struct HeapNode<k, v> *> arr;
    int index = -1;

    void bubbleUp() {
        int i = index;
        while (i > 0 && !isValidParent(getParent(i))) {
            swap(i, getParent(i));
            i = getParent(i);
        }
    }

    void swap(int i, int largest) {
        v tempv = (v) arr[i]->value;
        k tempk = (k) arr[i]->key;
        arr[i]->value = (v) arr[largest]->value;
        arr[i]->key = (k) arr[largest]->key;
        arr[largest]->value = (v) tempv;
        arr[largest]->key = (k) tempk;
    }

    void bubbleDown(int i) {
        while (i <= index && !isValidParent(i)) {
            int larger = largeChild(i);
            swap(i, larger);
            i = larger;
        }
    }

    void extractMin() {
        if (index == -1)
            throw "empty heap";
        swap(0, index--);
        bubbleDown(0);
    }

    int getParent(int i) {
        return (i - 1) / 2;
    }

    int getLeft(int i) {
        return i * 2 + 1;
    }

    int getRight(int i) {
        return i * 2 + 2;
    }

    bool isEmpty() {
        return index < 0;
    }

    bool hasLeft(int i) {
        return getLeft(i) <= index;
    }

    bool hasRight(int i) {
        return getRight(i) <= index;
    }
    /*
     * this function get node index,
     * then check if node need to be bubbled up.
     */
    bool isValidParent(int i) {
        if (!hasLeft(i))
            return true;
        if (!hasRight(i))
            return (v) arr[i]->value > (v) arr[getLeft(i)]->value;
        return (v) arr[i]->value >= (v) arr[getLeft(i)]->value && (v) arr[i]->value >= (v) arr[getRight(i)]->value;
    }

    int largeChild(int i) {
        if (!hasLeft(i))
            return i;
        if (!hasRight(i))
            return getLeft(i);
        return (v) arr[getLeft(i)]->value > (v) arr[getRight(i)]->value ? getLeft(i) : getRight(i);
    }

public:
    Heap() {}
    Heap(int size) {
        arr.reserve(size);
    }

    void put(k key, v value) {
        arr.push_back(new HeapNode<k, v>(key, value));
        index++;
        bubbleUp();
    }

    void sort() {
        for (int i = arr.size(); i; --i) extractMin();
    }

    void print(){
        cout << "sorted by value :" << endl; /// assuming it is sorted
        for(unsigned int i = 0; i < arr.size(); ++i)
            cout << "Key : " << (k) arr[i]->key << " Value : " << (v) arr[i]->value << endl;
        cout << endl << endl;
    }
    
};


#endif //SIMPLE_INTERPRETER_HEAP_H

