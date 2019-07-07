#include <iostream>

#include "btree.h"
#include "node.h"

using namespace std;

int main(int argc, char *argv[]) {
    int degree = 3;
    auto t = new BTree<int>(degree);
    t->insert(10);
    t->insert(20);
    t->insert(5);
    t->insert(6);
    t->insert(12);
    t->insert(30);
    t->insert(7);
    t->insert(17);/**/
    /*t->insert(1);
    t->insert(4);
    t->insert(6);
    t->insert(8);
    t->insert(12);
    t->insert(0);
    t->insert(3);
    t->insert(14);
    t->insert(7);
    t->insert(5);
    t->insert(11);
    t->insert(10);/**/
    t->printChicha();

    return EXIT_SUCCESS;
}