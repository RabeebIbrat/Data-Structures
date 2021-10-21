#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include<iostream>
using namespace std;

template<class Type>
class SetLinker {
    SetLinker<Type>* parent;
    int size;
    int rank;
public:
    Type value;
    SetLinker() {  ///aka makeSet()
        parent = NULL;
        size = 1;
        rank = 0;
    }
    SetLinker<Type>* getRoot() {  ///aka findSet()
        if(this->parent == NULL) {
            return this;
        }
        this->parent = this->parent->getRoot();
        return this->parent;
    }
    int getSize() {
        return getRoot()->size;
    }
    void unionOf(SetLinker<Type>& other) {
        SetLinker<Type> *root = getRoot(), *root2 = other.getRoot();
        if(root == root2)  return;
        if(root2->rank > root->rank) {
            root->parent = root2;
            root2->size += root->size;
            root->size = 0;
        }
        else {
            root2->parent = root;
            root->size += root2->size;
            root2->size = 0;
            if(root->rank == root2->rank) {
                root->rank++;
            }
        }
    }
public:
};

template <class Type>
void unionOf(SetLinker<Type>& one, SetLinker<Type>& other) {
    one.unionOf(other);
}

#endif // DISJOINT_SET_H
