#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include "linked_list.h"
using namespace std;

template <class Type>
class Queue {
    Type none;
public:
    LinkedList<Type>* store;
    Queue(Type noval = Type()) {
        none = noval;
        store = new LinkedList<Type>(noval);
    }
    ///copy functions
    Queue(const Queue& rhs) {
        store = new LinkedList<Type>(rhs.store);
        none = store->getNone();
    }
    void operator=(const Queue& rhs) {
        delete store;
        store = new LinkedList<Type>(rhs.store);
        none = store->getNone();
    }
    ///basic functions
    void enq(Type value) {
        store->pushBack(value);
    }
    Type deq() {
        if(store->isEmpty()) {
            cout << "Queue empty." << endl;
            return store->getNone();
        }
        return store->popFront();
    }
    Type front() {
        if(store->isEmpty()) {
            cout << "Queue empty." << endl;
            return store->getNone();
        }
        return store->getFront();
    }
    Type back() {
        if(store->isEmpty()) {
            cout << "Queue empty." << endl;
            return store->getNone();
        }
        return store->getBack();
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
    void print(string pre = "", string post = " <- ") {
        store->print(pre, post);
    }
    ///linked-list derived functions
    ///check linked_list.h ; use store
    ///destructor
    ~Queue() {
        delete store;
    }
};

#endif // QUEUE_H
