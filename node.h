#ifndef NODE_H
#define NODE_H

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <cmath>

using namespace std;

template<typename T>
class BTree;

template<typename T>
class Node {
protected:
    unsigned int size;
    vector<unsigned int> keys;
    vector<Node<T> *> childs;
    unsigned int digri;
    bool isLeaf;


public:
    Node(unsigned int digri, bool isLeaf = true) : size(0), isLeaf(isLeaf), digri(digri) {
        keys.resize(digri - 1);
        childs.resize(digri);
    }

    bool search(int key) {
        int i = 0;
        while (i < size && keys[i] < key) i++;
        if (keys[i] == key) return true;
        if (isLeaf) return false;
        return childs[i]->search(key);
    }


    void insertNonFull(int k) {
        int i = size - 1;
        if (isLeaf) {
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k;
            size++;
        } else {
            while (i > 0 && keys[i] > k) i--;

            if (childs[i + 1]->size == digri - 1) {//if full
                split(i + 1, childs[i + 1]);
                if (keys[i + 1] < k) i++;
            }

            childs[i + 1]->insertNonFull(k);
        }
    }

    void split(int i, Node *toSplit) {
        auto newNode = new Node(toSplit->digri, toSplit->isLeaf);
        int dummy = static_cast<int>(floor((digri - 1) / 2));
        newNode->size = dummy-1;

        for (int j = 0; j < newNode->size; ++j) newNode->keys[i] = toSplit->keys[dummy + i + 1];

        if (!toSplit->isLeaf)
            for (int j = 0; j <= newNode->size; ++j)
                newNode->childs[i] = toSplit->childs[dummy + i + 1];

        toSplit->size = dummy;

        for (int j = size + 1; j > i + 1; --j) childs[i] = childs[i - 1];

        childs[i + 1] = newNode;

        for (int j = size; j > i; --j) keys[i] = keys[i - 1];

        keys[i] = toSplit->keys[dummy];
        size++;

    }

    void recorrerNodo() {
        int i;
        for (i = 0; i < size; ++i) {
            if (!isLeaf) {
                childs[i]->recorrerNodo();
                cout << keys[i] << " ";
            }
            else cout << keys[i] << " ";
        }
        if (!isLeaf) childs[i]->recorrerNodo();

    }

    friend class BTree<T>;

};

#endif