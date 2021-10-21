#ifndef BST_H
#define BST_H

#include <iostream>
#include "queue.h"
using namespace std;

template<class Type>
class BST;

template<class Type>
class Node {
    Node<Type> *parent;
    Node<Type> *left;
    Node<Type> *right;
    Type value;

    friend class BST<Type>;
    Node(Type value) {
        parent = NULL;
        left = NULL;
        right = NULL;
        this->value = value;
    }
public:
    Type getValue() {
        return value;
    }
    Node<Type>* getLeft() {
        return left;
    }
    Node<Type>* getRight() {
        return right;
    }
    Node<Type>* getParent() {
        return parent;
    }
};

template <class Type>
class BST {  ///equal elements placed on right branch
    Node<Type>* root;
public:
    BST() {
        root = NULL;
    }
    void addNode(Type value) {
        if(root == NULL) {
            root = new Node<Type>(value);
            return;
        }
        Node<Type>* newly = new Node<Type>(value);
        Node<Type>* it = root;
        while(true) {
            if(newly->value < it->value) {
                if(it->left == NULL) {
                    it->left = newly;
                    newly->parent = it;
                    break;
                }
                it = it->left;
            }
            else {
                if(it->right == NULL) {
                    it->right = newly;
                    newly->parent = it;
                    break;
                }
                it = it->right;
            }
        }
    }
    bool findNode(Type value) {
        return (getNode(value, root) != NULL);
    }
private:
    Node<Type>* getNode(Type value, Node<Type>*start) {
        Node<Type> *found = start;
        while(found != NULL) {
            if(value < found->value) found = found->left;
            else if(found->value < value) found = found->right;
            else break;
        }
        return found;
    }
public:
    int countNode(Type value) {
        Node<Type>* start = root;
        int count = 0;
        while(true) {
            start = getNode(value, start);
            if(start == NULL)  break;
            count++;
            start = start->right;
        }
        return count;
    }
    void printTree() {
        if(root == NULL) {
            cout << "Tree empty." << endl;
            return;
        }
        Queue<Node<Type>*> q;
        Node<Type>* temp;
        cout << "Root -> " << root->value << endl;
        q.enq(root);
        while(!q.isEmpty()) {
            temp = q.deq();
            if(temp != NULL) {
                cout << "Children of " << temp->value << ": ";
                if(temp->left != NULL) {
                    cout << "left -> " << temp->left->value;
                    q.enq(temp->left);
                    if(temp->right != NULL) {
                        cout << ", ";
                    }
                }
                if(temp->right != NULL) {
                    cout << "right -> " << temp->right->value;
                    q.enq(temp->right);
                }
                cout << endl;
            }
        }
    }
    void printInOrder() {  ///prints as if sorted
        inOrder(root);
        cout << endl;
    }
    void printPreOrder() {
        preOrder(root);
        cout << endl;
    }
    void printPostOrder() {
        postOrder(root);
        cout << endl;
    }
private:
    void inOrder(Node<Type>* start) {
        if(start != NULL) {
            inOrder(start->left);
            cout << start->value << " ";
            inOrder(start->right);
        }
    }
    void preOrder(Node<Type>* start) {
        if(start != NULL) {
            cout << start->value << " ";
            preOrder(start->left);
            preOrder(start->right);
        }
    }
    void postOrder(Node<Type>* start) {
        if(start != NULL) {
            postOrder(start->left);
            postOrder(start->right);
            cout << start->value << " ";
        }
    }
public:
    Type getMinimum() {
        if(root == NULL) {
            cout << "Tree empty! Returning garbage..." << endl;
            return Type();
        }
        Node<Type>* it = root;
        while(it->left != NULL) {
            it = it->left;
        }
        return it->value;
    }
    Type getMaximum() {
        if(root == NULL) {
            cout << "Tree empty! Returning garbage..." << endl;
            return Type();
        }
        Node<Type>* it = root;
        while(it->right != NULL) {
            it = it->right;
        }
        return it->value;
    }
    Type getPrev(Type value) {
        Node<Type>* it = getNode(value, root);
        if(it == NULL) {
            cout << "Given value not found. Returning garbage..." << endl;
            return Type();
        }
        return prev(it);
    }
    Type getNext(Type value) {
        Node<Type>* it = getNode(value, root);
        if(it == NULL) {
            cout << "Given value not found. Returning garbage..." << endl;
            return Type();
        }
        return next(it);
    }
private:
    Type prev(Node<Type>* start) {
        Node<Type>* it = start;
        if(it->left != NULL) {
            it = it->left;
            while(it->right != NULL) {
                it = it->right;
            }
        }
        else {
            while(it->parent != NULL && it->parent->left == it) {
                it = it->parent;
            }
            if(it->parent == NULL) {
                cout << "Previous doesn't exist. Given value is minimum. Returning minimum..." << endl;
                return start->value;
            }
            it = it->parent;
        }
        if(it->value == start->value)
            return prev(it);
        else
            return it->value;
    }
    Type next(Node<Type>* start) {
        Node<Type>* it = start;
        if(it->right != NULL) {
            it = it->right;
            while(it->left != NULL) {
                it = it->left;
            }
        }
        else {
            while(it->parent != NULL && it->parent->right == it) {
                it = it->parent;
            }
            if(it->parent == NULL) {
                cout << "Next doesn't exist. Given value is maximum. Returning maximum..." << endl;
                return start->value;
            }
            it = it->parent;
        }
        if(it->value == start->value)
            return next(it);
        else
            return it->value;
    }
public:
    void deleteNode(Type value) {
        Node<Type>* it = getNode(value, root);
        if(it == NULL) {
            cout << "Value not found. Nothing to delete..." << endl;
            return;
        }
        if(it->left == NULL) {
            transplant(it,it->right);
        }
        else if(it->right == NULL) {
            transplant(it,it->left);
        }
        else {
            Node<Type>* next = nextBelow(it);
            if(it->right != next) {
                transplant(next, next->right);
                next->right = it->right;
                next->right->parent = next;
            }
            transplant(it, next);
            next->left = it->left;
            next->left->parent = next;
        }
        delete it;
    }
private:
    void transplant(Node<Type>* old, Node<Type>* newly) {
        if(newly != NULL) {
            newly->parent = old->parent;
        }
        if(old->parent == NULL) {
            root = newly;
        }
        else if(old->parent->left == old) {
            old->parent->left = newly;
        }
        else if(old->parent->right == old) {
            old->parent->right = newly;
        }
        else  cout << "FATAL ERROR!" << endl;
    }
    Node<Type>* nextBelow(Node<Type>* it) {
        if(it->right == NULL)  cout << "FATAL ERROR!" << endl;
        it = it->right;
        while(it->left != NULL) {
            it = it->left;
        }
        return it;
    }
public:
    void clear() {
        clearFrom(root);
        root = NULL;
    }
private:
    void clearFrom(Node<Type>* from) {
        if(from == NULL)  return;
        clearFrom(from->left);
        clearFrom(from->right);
        delete from;
    }
};

#endif // BST_H
