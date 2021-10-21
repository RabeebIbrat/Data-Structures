#include <iostream>
#include "linked_list.h"
#include "queue.h"
using namespace std;
#define INFINITY 100000

class intLL {
    //friend class LinkedList<intLL>;
    friend class BinomeHeap;

    int level;
    int* value;
    LinkedList<intLL>* children;
public:  ///modification needed
    intLL() {
        clear();
    }
private:
    intLL(int number) {
        set(number);
    }
    void clear() {
        value = NULL;
        children = NULL;
        level = 0;
    }
    void set(int number) {
        value = new int(number);
        children = new LinkedList<intLL>;
        level = 1;
    }
    void cutPaste(intLL &rhs) {
        level = rhs.level;
        value = rhs.value;
        children = rhs.children;
        rhs.clear();
    }
    /*friend ostream& operator<<(ostream& os, const intLL& out) {
        if(out.value == NULL)  os << "&";
        else os << *(out.value);
    }*/
};

class BinomeHeap {
    intLL** tree;
    int size;
public:
    BinomeHeap(int capacity = 30) {
        tree = new intLL*[capacity];
        size = capacity;
        for(int i = 0; i < capacity; i++) {
            tree[i] = new intLL();
        }
    }
private:
    bool mergeTrees(intLL *lhs, intLL *rhs) {  ///equal trees merged into lhs
                                               ///return value: Is tree level increased?
        if(lhs->value == NULL) {
            lhs->cutPaste(*rhs);
            return false;
        }
        else if(rhs->value == NULL){
            return false;
        }
        else if(*(lhs->value) < *(rhs->value)){
            lhs->children->pushFront(*rhs);
            lhs->level++;
            rhs->clear();
            return true;
        }
        else {
            rhs->children->pushFront(*lhs);
            rhs->level++;
            lhs->clear();

            lhs->cutPaste(*rhs);
            return true;
        }
    }
public:
    void unionOf(BinomeHeap &rhs) {
        if(size != rhs.size) {
            cout << "Error: Cannot merge. Incompatible heaps." << endl;
            return;
        }
        intLL* carry = new intLL();
        for(int i = 0; i < size; i++) {
            bool bigger = mergeTrees(this->tree[i], rhs.tree[i]);
            if(bigger) {
                intLL* temp = tree[i];
                tree[i] = carry;
                carry = temp;
            }
            else {
                bigger = mergeTrees(this->tree[i], carry);
                if(bigger) {
                    intLL* temp = tree[i];
                    tree[i] = carry;
                    carry = temp;
                }
            }
        }
        if(carry->value != NULL) {
            cout << "Error: Heap overflown. Elements lost." << endl;
        }
    }
    void insert(int number) {
        BinomeHeap temp(size);
        temp.tree[0]->set(number);
        unionOf(temp);
    }
private:
    intLL *locateMin() {
        intLL *locate = NULL;
        for(int i = 0; i < size; i++) {
            if(tree[i]->value == NULL)  continue;
            if(locate == NULL || *(tree[i]->value) < *(locate->value)) {
                locate = tree[i];
            }
        }
        return locate;
    }
public:
    int findMin() {
        intLL *small = locateMin();
        if(small == NULL) {
            cout << "Heap empty. Minimum not found. Returning -inf" << endl;
            return -INFINITY;
        }
        return *(small->value);
    }
    int extractMin() {
        intLL *root = locateMin();
        if(root == NULL) {
            cout << "Heap empty. Minimum not found. Returning -inf" << endl;
            return -INFINITY;
        }
        int small = *(root->value);
        BinomeHeap spare(size);
        LinkedList<intLL> &feeder = *(root->children);
        intLL now;
        while(!feeder.isEmpty()) {
            now = feeder.popFront();
            spare.tree[now.level - 1]->cutPaste(now);
        }
        root->clear();
        unionOf(spare);
        return small;
    }
private:
    void printTree(int index) {
        if(index < 0 || index >= size) {
            cout << "Error in printTree: Tree index out of bound." << endl;
            return;
        }
        cout << "-----Tree " << index+1 << " -----" << endl << endl;
        int level = tree[index]->level;
        Queue<intLL> leveller;
        Queue<intLL> leveller2;
        leveller.enq(*tree[index]);
        leveller.enq(*(new intLL()));
        intLL now;
        for(int i = 1; i <= level; i++) {
            cout << "L-" << i << ": ";
            while(!leveller.isEmpty()) {
                now = leveller.deq();
                if(now.value == NULL) {
                    cout << "\b ; ";
                }
                else {
                    cout << *(now.value) << ",";
                    for(Linker<intLL> *it = now.children->getHead()->getNext(); it != now.children->getTail(); it = it->getNext()) {
                        leveller2.enq(it->getValue());
                    }
                    leveller2.enq(*(new intLL()));
                }
            }
            while(!leveller2.isEmpty()) {
                leveller.enq(leveller2.deq());
            }
            cout << endl;
        }
        cout << endl;
    }
public:
    void print() {
        cout << endl;
        for(int i = 0; i < size; i++)  printTree(i);
    }
};

int main() {
    BinomeHeap *h[3];
    int treeNum;
    //cout << "Enter number of trees in heap: ";
    //cin >> treeNum;
    treeNum = 5;
    for(int i = 0; i < 3; i++) {
        h[i] = new BinomeHeap(treeNum);
    }
    while(true) {
        int hNum;
        cout << "Select heap number(1~3) or 4 to exit." << endl;
        cin >> hNum;
        if(hNum <= 0 || hNum > 4) {
            cout << "Invalid choice." << endl;
            continue;
        }
        if(hNum == 4)  break;
        hNum--;

        int choice;
        cout << "1.Find-min 2.Extract-min 3.Insert 4.Union 5.Print 6.Back" << endl;
        cin >> choice;
        if(choice == 1) {
            cout << h[hNum]->findMin() << endl;
        }
        else if(choice == 2) {
            cout << h[hNum]->extractMin() << endl;
        }
        else if(choice == 3) {
            int value;
            cin >> value;
            h[hNum]->insert(value);
        }
        else if(choice == 4) {
            int hNum2;
            cin >> hNum2;
            if(hNum2 <= 0 || hNum2 > 3) {
                cout << "Invalid heap number." << endl;
                continue;
            }
            hNum2--;
            h[hNum]->unionOf(*h[hNum2]);
        }
        else if(choice == 5) {
            h[hNum]->print();
        }
        else if(choice == 6) {
            continue;
        }
        else {
            cout << "Invalid choice." << endl;
            continue;
        }
    }
}
