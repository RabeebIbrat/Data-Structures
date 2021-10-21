#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <iostream>
using namespace std;

template<class Type>
class SetLinker {
    SetLinker<Type>* head;
    SetLinker<Type>* next;
    int size;
public:
    Type value;
    SetLinker() {  ///aka makeSet()
        size = 1;
        head = this;
        next = NULL;
    }
    SetLinker<Type>* getHead() {  ///aka findSet()
        return head;
    }
    SetLinker<Type>* getNext() {
        return next;
    }
    int getSize() {
        return head->size;
    }
    void unionOf(SetLinker<Type>& other) {
        if(head == other.head)  return;
        if(head->size > other.head->size) {
            unite(other);
        }
        else {
            other.unite(*this);
        }
    }
private:
    void unite(SetLinker<Type>& small) {
        head->size += small.head->size;
        small.head->size = 0;
        SetLinker<Type>* ender = head->next;
        head->next = small.head;
        SetLinker<Type>* iter = small.head;
        while(true) {
            iter->head = head;
            if(iter->next == NULL) {
                iter->next = ender;
                break;
            }
            iter = iter->next;
        }
    }
public:
    void printSet(char separate = ',') {
        cout << "{";
        SetLinker<Type>* it = head;
        while(it != NULL) {
            cout << it->value << separate << " ";
            it = it->next;
        }
        cout << "\b\b}";
    }
};

template <class Type>
void unionOf(SetLinker<Type>& one, SetLinker<Type>& other) {
    one.unionOf(other);
}

#endif // DISJOINT_SET_H
