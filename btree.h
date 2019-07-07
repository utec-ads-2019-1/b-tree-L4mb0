#ifndef BTREE_H
#define BTREE_H

#include "node.h"


template<typename T>
class BTree {
private:
    Node<T> *root;
    unsigned int degree;

public:
    BTree(unsigned int degree) {
        this->degree = degree;
        this->root = nullptr;
    };

    T search(int k) {
        if (!root) return false;
        return root->search(k);
    }

    bool insert(int k) {
        if (search(k)) return false;
        if (!root) {
            root = new Node<T>(degree, true);
            root->keys[0] = k;
            root->size = 1;
        } else {
            if (root->size == 2*degree - 1){ //if full
                auto newRoot = new Node<T>(degree, false);
                newRoot->childs[0] = root;
                newRoot->split(0, root);

                int i = 0;
                if (newRoot->keys[0] < k)
                    i++;
                newRoot->childs[i]->insertNonFull(k);

                root = newRoot;
            }
            else  root->insertNonFull(k);
        }
        return true;
    }

    void remove(int k) {
        // TODO
    }

    void printChicha() {
        if (root) root->recorrerNodo();
        cout << endl;
    }

    /*~BTree();*/
};

#endif