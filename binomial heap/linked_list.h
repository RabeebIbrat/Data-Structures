#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
using namespace std;

template <class Type>
class LinkedList;

template <class Type>
class Linker {
    Type value;
    Linker<Type> *prev;
    Linker<Type> *next;
    int sign;

    friend class LinkedList<Type>;
    Linker(int sign, Type value) {
        prev = NULL;
        next = NULL;
        this->sign = sign;
        this->value = value;
    }
public:
    const Type& getValue() {
        return value;
    }
    Linker<Type>* getPrev() {
        if(prev == NULL) {
            cout << "Error in Linker: Previous doesn't exist.";
            return this;
        }
        return prev;
    }
    Linker<Type>* getNext() {
        if(next == NULL) {
            cout << "Error in Linker: Next doesn't exist.";
            return this;
        }
        return next;
    }
    Linker<Type>* plus(int num) {
        Linker<Type> *temp = this;
        while(num-- && temp->next != NULL) {
            temp = temp->next;
        }
        return temp;
    }
    Linker<Type>* minus(int num) {
        Linker<Type> *temp = this;
        while(num-- && temp->prev != NULL) {
            temp = temp->prev;
        }
        return temp;
    }
};

template <class Type>
class LinkedList {
    Linker<Type> *head;
    Linker<Type> *tail;
    Type none;
    int size;
    int sign;
    static int count;
    ///constructor commons
    void basicConstruct(Type noval) {
        sign = ++count;
        size = 0;
        none = noval;
        head = new Linker<Type>(sign, none);
        tail = new Linker<Type>(sign, none);
        head->next = tail;
        tail->prev = head;
    }
    void ptr2ptrWrite(Type *a, Type *b) {
        if(a > b) {
            cout << "Error in LinkedList: Invalid pair of pointers for writing." << endl;
            return;
        }
        for(Type *it = a; it != b; it++) {
            pushBack(*it);
        }
        size = b-a;
    }
public:
    ///constructors
    LinkedList(Type noval = Type()) {
        basicConstruct(noval);
    }
    LinkedList(Type *a, Type *b, Type noval = Type()) {
        basicConstruct(noval);
        ptr2ptrWrite(a,b);
    }
    LinkedList(Type *a, int len, Type noval = Type()) {
        basicConstruct(noval);
        ptr2ptrWrite(a, a+len);
    }
    ///copy functions
    LinkedList(const LinkedList& rhs) {
        basicConstruct(rhs.none);
        for(Linker<Type> *it = rhs.head->next; it != rhs.tail; it = it->next) {
            pushBack(it->value);
        }
    }
    void operator=(const LinkedList &rhs) {
        clear();
        none = rhs.none;
        head.value = none;
        tail.value = none;
        for(Linker<Type> *it = rhs.head->next; it != rhs.tail; it = it->next) {
            pushBack(it->value);
        }
    }
    ///basic push-pop
    void pushFront(Type value) {
        insert(head->getNext(), value);
    }
    void pushBack(Type value) {
        insert(tail, value);
    }
    Type getFront() {
        if(head->next == tail) {
            cout << "Error in LinkedList: List empty." << endl;
        }
        return head->next->value;
    }
    Type getBack() {
        if(tail->prev == head) {
            cout << "Error in LinkedList: List empty." << endl;
        }
        return tail->prev->value;
    }
    Type popFront() {
        if(head->next == tail) {
            cout << "Error in LinkedList: List empty." << endl;
            return none;
        }
        Type retval = head->next->value;
        deletes(head->next);
        return retval;
    }
    Type popBack() {
        if(tail->prev == head) {
            cout << "Error in LinkedList: List empty." << endl;
        }
        Type retval = tail->prev->value;
        deletes(tail->prev);
        size--;
        return retval;
    }
    ///basic pointers for iteration
    Linker<Type>* getHead() {
        return head;
    }
    Linker<Type>* getTail() {
        return tail;
    }
    Linker<Type>* goTo(int index) {  ///1-indexing
        if(index < 1) {
            cout << "Error in LinkedList: Index does not exist." << endl;
            return head;
        }
        if(index > size) {
            cout << "Error in LinkedList: Index does not exist." << endl;
            return tail;
        }
        return head->plus(index);
    }
    ///pointer-based modifiers
    Linker<Type>* deletes(Linker<Type>* local) {
        if(local->sign != sign) {
            cout << "Error in LinkedList: Signatures mismatch." << endl;
            return local;
        }
        if(local == head || local == tail) {
            cout << "Error in LinkedList: Cannot delete head/tail." << endl;
            return local;
        }
        Linker<Type>* left = local->prev;
        Linker<Type>* right = local->next;
        delete local;
        left->next = right;
        right->prev = left;
        size--;
        return right;
    }
    Linker<Type>* insert(Linker<Type>* local, Type value) {
        if(local->sign != sign) {
            cout << "Error in LinkedList: Signatures mismatch." << endl;
            return local;
        }
        Linker<Type>* left = local->prev;
        Linker<Type>* newly = new Linker<Type>(sign, value);
        left->next = newly;
        newly->next = local;
        local->prev = newly;
        newly->prev = left;
        size++;
        return newly;
    }
    Linker<Type>* changeTo(Linker<Type>* local, Type value) {
        deletes(local);
        insert(local, value);
    }
    ///list properties
    bool isEmpty() {
        return (head->next == tail);
    }
    int getSize() {
        return size;
    }
    Type getNone() {
        return none;
    }
    void getInArray(Type *a) {
        for(Linker<Type> *it = head->next; it != tail; it = it->next, a++) {
            a = it->value;
        }
    }
    void print(string pre = "", string post = " -> ") {
        for(Linker<Type> *it = head->next; it != tail; it = it->next) {
            cout << pre << it->value << post;
        }
        cout << endl;
    }
    ///special functions
    void clear() {
        while(!isEmpty()) {
            popFront();
        }
        size = 0;
    }
    void reverse() {  ///O(n) for iterator compatibility
        int a[size];
        for(int i = 0; i < size; i++) {
            a[i] = popFront();
        }
        for(int i = 0; i < size; i++) {
            pushFront(a[i]);
        }
    }
    static int objectCount() {
        return count;
    }
    ///destructor
    ~LinkedList() {
        clear();
        delete head;
        delete tail;
    }
};
template<class Type>
int LinkedList<Type>::count = 0;

#endif // LINKED_LIST_H
