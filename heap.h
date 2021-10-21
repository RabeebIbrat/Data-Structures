#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
using namespace std;

template <class Type>
class MinHeap {
    Type *a;
    int capacity;
    int size;
    void swap(int i, int j) {
        Type temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
public:
    MinHeap(int capacity = 100) {
        this->capacity = capacity;
        a = new Type[capacity+1];
        size = 0;
    }
    void throwIn(Type element) {
        if(size == capacity) {
            cout << "Heap full!" << endl;
            return;
        }
        a[++size] = element;
        for(int i = size; i > 1; i/=2) {
            if(a[i/2] < a[i])  break;
            swap(i/2,i);
        }
    }
    Type pickUp() {
        if(size == 0) {
            cout << "Heap empty! Returning garbage...";
            return a[0];
        }
        Type min = a[1];
        a[1] = a[size--];
        int i = 1;
        while(2*i < size) {
            if(a[2*i] < a[2*i+1]) {
                if(a[2*i] < a[i]) {
                    swap(2*i,i);
                    i *= 2;
                }
                else break;
            }
            else {
                if(a[2*i+1] < a[i]) {
                    swap(2*i+1,i);
                    (i *= 2)++;
                }
                else break;
            }
        }
        if(2*i == size) {
            if(a[2*i] < a[i])
                swap(i,2*i);
        }
        return min;
    }
    Type getMin() {
        return a[1];
    }
    int getSize() {
        return size;
    }
    bool isEmpty() {
        return (size == 0);
    }
    void clear() {
        size = 0;
    }
    void print(string pre = "", string post = ", ") { ///must overload operator<<(ostream&, const Type&)
        for(int i = 1; i <= size; i++) {
            cout << pre << a[i] << post;
        }
    }
    ~MinHeap() {
        delete a;
    }
};

#endif // HEAP_H
