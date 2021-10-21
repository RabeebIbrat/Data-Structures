#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include "linked_list.h"
using namespace std;

template <class Type>
class Stack {
    Type none;
public:
    LinkedList<Type>* store;
    Stack(Type noval = Type()) {
        none = noval;
        store = new LinkedList<Type>(noval);
    }
    ///copy functions
    Stack(const Stack& rhs) {
        store = new LinkedList<Type>(rhs.store);
        none = store->getNone();
    }
    operator=(const Stack& rhs) {
        delete store;
        store = new LinkedList<Type>(rhs.store);
        none = store->getNone();
    }
    ///basic functions
    void push(Type value) {
        store->pushFront(value);
    }
    Type pop() {
        if(store->isEmpty()) {
            cout << "Stack empty." << endl;
            return store->getNone();
        }
        return store->popFront();
    }
    Type top() {
        if(store->isEmpty()) {
            cout << "Stack empty." << endl;
            return store->getNone();
        }
        return store->getFront();
    }
    bool isEmpty() {
        return store->isEmpty();
    }
    void clear() {
        store->clear();
    }
    int getSize() {
        store->getSize();
    }
    void print(string pre = "", string post = ") ") {
        store->print(pre, post);
    }
    ///linked-list derived functions
    ///check linked_list.h ; use store
    ///destructor
    ~Stack() {
        delete store;
    }
};

#endif // STACK_H
