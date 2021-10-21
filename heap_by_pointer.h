#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
using namespace std;

template<class Type>
class MinHeap;

template<class Type>
class Trash {
    int id;
    int sign;
    friend class MinHeap<Type>;
public:
    Type entry;
    Trash() {
        id = 0;
        sign = 0;
    }
    Trash(const Type& value) {
        entry = value;
        id = 0;
        sign = 0;
    }
};

template<class Type>
class MinHeap {
    Trash<Type> **a;
    int capacity;
    int size;
    int sign;
    static int count;

    void swap(int i, int j) {
        Trash<Type>* temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        a[i]->id = i;
        a[j]->id = j;
    }
    int siftUp(int i) {
        while(i > 1) {
            if(a[i]->entry < a[i/2]->entry) {
                swap(i/2,i);
                i /= 2;
            }
            else break;
        }
        return i;
    }
    int siftDown(int i) {
        while(2*i < size) {
            if(a[2*i]->entry < a[2*i+1]->entry) {
                if(a[2*i]->entry < a[i]->entry) {
                    swap(2*i,i);
                    i *= 2;
                }
                else break;
            }
            else {
                if(a[2*i+1]->entry < a[i]->entry) {
                    swap(2*i+1,i);
                    (i *= 2)++;
                }
                else break;
            }
        }
        if(2*i == size) {
            if(a[2*i]->entry < a[i]->entry) {
                swap(i,2*i);
                i *= 2;
            }
        }
        return i;
    }
public:
    MinHeap(int capacity = 100, Type garbage = Type()) {  ///Type() must be defined
        sign = ++count;
        this->capacity = capacity;
        a = new Trash<Type>*[capacity+1];
        size = 0;
        a[0] = new Trash<Type>(garbage);
    }
    void throwIn(Trash<Type>* element) {
        if(size == capacity) {
            cout << "Heap full!" << endl;
            return;
        }
        a[++size] = element;
        element->id = size;
        element->sign = sign;
        siftUp(size);
    }
    Trash<Type>* pickUp() {  ///CAUTION: delete pointer must be done outside of heap
        if(size == 0) {
            cout << "Heap empty! Returning garbage...";
            return a[0];
        }
        Trash<Type>* min = a[1];
        swap(1, size);
        a[size]->id = 0;
        a[size]->sign = 0;
        size--;
        siftDown(1);
        return min;
    }
    void adjust(Trash<Type> thing) {
        if(thing.id == 0) {
            cout << "Item not in any heap." << endl;
        }
        else if(thing.sign != sign) {
            cout << "Item not in this heap." << endl;
        }
        else {
            siftDown(siftUp(thing.id));
        }
    }
    void adjust(Trash<Type>* thing) {
        adjust(*thing);
    }
    Trash<Type>* getMin() {
        if(size == 0) {
            cout << "Heap empty! Returning garbage...";
            return a[0];
        }
        return a[1];
    }
    int getSize() {
        return size;
    }
    bool isEmpty() {
        return (size == 0);
    }
    void clear() {  ///CAUTION: Clears addresses only. Data must be manually cleared.
        delete a;
    }
    void print(string pre = "", string post = "\n") {  ///Type::print() must be defined
        for(int i = 1; i <= size; i++) {
            cout << pre;
            a[i]->entry.print();
            cout << post;
        }
    }
    ~MinHeap() {
        delete a;
    }
};
template<class Type>
int MinHeap<Type>::count = 0;

#endif // HEAP_H
