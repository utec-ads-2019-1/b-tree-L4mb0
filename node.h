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
    unsigned int totKeys;
    unsigned int size;
    vector<unsigned int> keys;
    vector<Node<T> *> childs;
    unsigned int digri;
    bool isLeaf;


public:

    Node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf)
    {
        keys.resize(size - 1);
        childs.resize(size);
        totKeys = 0;
        digri = ceil(size/2);
    }

    bool search(int key) {
        int i = 0;
        while (i < totKeys && keys[i] < key) i++;
        if (keys[i] == key) return true;
        if (isLeaf) return false;
        return childs[i]->search(key);
    }


    void insertNonFull(int k) {
        int i = totKeys - 1;
        if (isLeaf) {
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k;
            totKeys++;
        } else {
            while (i >= 0 && keys[i] > k) i--;

            if (childs[i + 1] -> totKeys == 2*digri - 1) {//if full
                split(i + 1, childs[i + 1]);
                if (keys[i + 1] < k) i++;
            }

            childs[i + 1]->insertNonFull(k);
        }
    }

    void split(int i, Node<T> *toSplit) {
        auto splitNode = new Node<T>(toSplit -> digri, toSplit -> isLeaf);
        splitNode -> totKeys = digri - 1;

        for(int j = 0; j < digri - 1; j++)
            splitNode -> keys[j] = toSplit -> keys[j + digri];

        if (!(toSplit -> isLeaf)){
            for(int j = 0; j < digri; j++)
                splitNode -> childs[j] = toSplit -> childs [j + digri];
        }

        toSplit -> totKeys = digri - 1;

        for(int j =  totKeys; j >= i + 1; j--)
            keys[j+1] = keys[j];

        keys[i] = toSplit -> keys[digri - 1];

        totKeys++;
    }

    void recorrerNodo() {
        int i;
        for (i = 0; i < totKeys; ++i) {
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