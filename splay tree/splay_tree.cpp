///Data() must be defined
//Data(const Data&) must be correctly defined
///Data.operator=(Data) must be correctly defined

///Key.operator=(Key) must be correctly defined
///Key.operator<(Key) must be defined.
///Duplicate key allowed. Goes to right branch.
#include <iostream>
#include <string>
#include "queue.h"
#include "linked_list.h"
#include <cstdlib>
using namespace std;

template<class Key, class Data>
class SplayTree;

template <class Key, class Data>
class Splayer {
public:
    Splayer<Key,Data> *parent;
    Splayer<Key,Data> *left;
    Splayer<Key,Data> *right;
    Key key;
    Data data;
    friend class SplayTree<Key,Data>;
    Splayer(Key key, Data value = Data()) {
        this->key = key;
        data = value;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
public:
    const Key& getKey() {
        if(this == NULL)
            cout << "Error in Linker: Can't get key from null pointer." << endl;
        return key;
    }
    Data getData() {
        if(this == NULL) {
            cout << "Error in Linker: Can't get data from null pointer." << endl;
            return Data();
        }
        return data;
    }
    void setData(const Data& value) {
        if(this == NULL) {
            cout << "Error in Linker: Can't set data to null pointer." << endl;
            return;
        }
        data = value;
    }
    Splayer<Key,Data> *getLeft() {
        if(this == NULL) {
            cout << "Error in Linker: Can't get left from null pointer." << endl;
            return NULL;
        }
        return left;
    }
    Splayer<Key,Data> *getRight() {
        if(this == NULL) {
            cout << "Error in Linker: Can't get right from null pointer." << endl;
            return NULL;
        }
        return right;
    }
    Splayer<Key,Data> *getParent() {
        if(this == NULL) {
            cout << "Error in Linker: Can't get parent from null pointer." << endl;
            return NULL;
        }
        return parent;
    }
};

template <class Data>
class BoolData {
public:
    bool truth;
    Data data;
    BoolData(const bool& truth, const Data& data) {
        this->truth = truth;
        this->data = data;
    }
};

template <class Key, class Data>
class SplayerPair {
public:
    Splayer<Key,Data> *one, *other;
    SplayerPair(Splayer<Key,Data> *first, Splayer<Key,Data> *second) {
        one = first, other = second;
    }
};

template <class Key, class Data>
class SplayTree {
    Splayer<Key,Data> *root;
public:
    SplayTree() {
        root = NULL;
    }
    SplayTree(Splayer<Key,Data>* rootAddress) {  ///pointing to an already made splay tree
        root = rootAddress;
    }
    Splayer<Key,Data>* getRoot() {
        return root;
    }
    Splayer<Key,Data>* locate(Key key) {
        if(root == NULL) {
            return NULL;
        }
        Splayer<Key,Data> *now = root;
        while(true) {
            if(key < now->key) {
                if(now->left == NULL)
                    break;
                else
                    now = now->left;
            }
            else if (now->key < key){
                if(now->right == NULL)
                    break;
                else
                    now = now->right;
            }
            else {
                break;
            }
        }
        return now;
    }
private:
    bool rotation(Splayer<Key,Data>* node) {  ///false => node is either root or NULL.
        if(node == NULL) {
            return false;
        }
        else if(node->parent == NULL) {
            return false;
        }

        Splayer<Key,Data> *parent = node->parent, *gParent = parent->parent, *child = node->left;
        bool pLinkLeft = false, gpLinkLeft = false;
        if(parent->left == node) {
            pLinkLeft = true;
            child = node->right;
        }
        node->parent = gParent;
        if(gParent != NULL) {
            if(gParent->left == parent) {
                gpLinkLeft = true;
            }
            if(gpLinkLeft) {
                gParent->left = node;
            }
            else {
                gParent->right = node;
            }
        }
        parent->parent = node;
        if(pLinkLeft) {
            node->right = parent;
            parent->left = child;
        }
        else {
            node->left = parent;
            parent->right = child;
        }
        if(child != NULL) {
            child->parent = parent;
        }
        if(node->parent == NULL) {
            root = node;
            return false;
        }
        return true;
    }
    bool partSplay(Splayer<Key,Data>* node) {  ///false => node is either root or NULL.
        if(node == NULL || node->parent == NULL || node->parent->parent == NULL) {
            return rotation(node);
        }
        Splayer<Key,Data> *parent = node->parent, *gParent = parent->parent;
        bool pLinkLeft = false, gpLinkLeft = false;
        if(parent->left == node) {
            pLinkLeft = true;
        }
        if(gParent->left == parent) {
            gpLinkLeft = true;
        }
        if(pLinkLeft == gpLinkLeft) {  ///zig-zig
            rotation(parent);
            return rotation(node);
        }
        else {  ///zig-zag
            rotation(node);
            return rotation(node);
        }
    }
public:
    void splay(Splayer<Key,Data>* node) {
        while(partSplay(node)){};
    }
    void splay(Key key) {
        Splayer<Key,Data>* node = locate(key);
        splay(node);
    }
    BoolData<Data> search(Key key) {  ///returns: "found?" and "Data"
        splay(key);
        if(root == NULL || root->key != key) {
            return BoolData<Data>(false, Data());
        }
        else {
            return BoolData<Data>(true, root->data);
        }
    }
    void insert(Key key, Data data = Data()) {
        Splayer<Key,Data>* addend = new Splayer<Key,Data>(key, data);
        if(root == NULL) {
            root = addend;
            return;
        }
        Splayer<Key,Data>* now = locate(key);
        if(key < now->key) {
            now->left = addend;
            addend->parent = now;
        }
        else if(now->key < key){
            now->right = addend;
            addend->parent = now;
        }
        else {
            Splayer<Key,Data> *child = now->right;
            now->right = addend;
            addend->right = child;
            if(child != NULL) {
                child->parent = addend;
            }
            addend->parent = now;
        }
        splay(addend);
    }
private:
    SplayerPair<Key,Data> deleteSplit(Key key) {  ///WARNING: This operation eliminates the root
        if (root == NULL) {
            cout << "Empty tree." << endl;
            return SplayerPair<Key,Data>(NULL, NULL);
        }
        splay(key);
        if(root->key != key) {
            cout << "Key doesn't exist." << endl;
            Splayer<Key,Data> *right = root->right;
            root->right = NULL;
            if(right != NULL) {
                right->parent = NULL;
            }
            return SplayerPair<Key,Data>(root, right);
        }
        else {
            Splayer<Key,Data> *left = root->left, *right = root->right;
            if(left != NULL) {
                left->parent = NULL;
            }
            if(right != NULL) {
                right->parent = NULL;
            }
            delete root;
            return SplayerPair<Key,Data>(left,right);
        }
    }
    void join(Splayer<Key,Data>* left, Splayer<Key,Data>* right) {  ///CAUTION: This operation reassigns the root
        if(right == NULL) {
            root = left;
            return;
        }
        Splayer<Key,Data>* now = right;
        while(now->left != NULL) {
            now = now->left;
        }
        splay(now);
        while(now->left != NULL) {
            now = now->left;
        }
        now->left = left;
        if(left != NULL) {
            left->parent = now;
        }
        root = now;
    }
public:
    void deletes(Key key) {
        SplayerPair<Key,Data> parts = deleteSplit(key);
        join(parts.one, parts.other);
    }
    void print(Splayer<Key,Data> *root, bool space = false) {
        if(root == NULL) {
            cout << "Tree empty." << endl;
            return;
        }
        string gap = space? " ":"";
        Queue<Splayer<Key,Data>*> q;
        cout << "Root: " << root->key << endl;
        q.enq(root);
        cout << "Hierarchy: " << endl;
        while(!q.isEmpty()) {
            Splayer<Key,Data>* now = q.deq();
            if(now->left == NULL) {
                cout << "NULL";
            }
            else {
                cout << now->left->key;
                q.enq(now->left);
            }
            cout << gap << "<-" << gap << now->key << gap << "->" << gap;
            if(now->right == NULL) {
                cout << "NULL";
            }
            else {
                cout << now->right->key;
                q.enq(now->right);
            }
            cout << " (Parent: ";
            if(now->parent == NULL) {
                cout << "NULL";
            }
            else {
                cout << now->parent->key;
            }
            cout << ")" << endl;
        }
        cout << endl;
    }
    void print(bool space = false) {
        print(root, space);
    }
    void clear(Splayer<Key,Data> *node) {  ///auto adjusts root
        if(node == NULL)  return;

        clear(node->left);
        clear(node->right);

        if(node->parent != NULL) {
            if(node->parent->left == node) {
                node->parent->left = NULL;
            }
            else {
                node->parent->right = NULL;
            }
        }
        else {
            root = NULL;
        }
        delete node;
    }
    void clear() {
        clear(root);
    }
    int getLevel(Splayer<Key,Data> *root) {
        if(root == NULL) {
            return 0;
        }
        Queue<Splayer<Key,Data>*> q1, q2;
        q1.enq(root);
        int level = 1;
        while(true) {
            while(!q1.isEmpty()) {
                Splayer<Key,Data> *now = q1.deq();
                if(now->left != NULL)  q2.enq(now->left);
                if(now->right != NULL)  q2.enq(now->right);
            }
            if(q2.isEmpty()) {
                break;
            }
            else {
                while(!q2.isEmpty()) {
                    q1.enq(q2.deq());
                }
                level++;
            }
        }
        return level;
    }
    int getLevel() {
        getLevel(root);
    }
private:
    void vPrintNodes(LinkedList<Splayer<Key,Data>*> &nodes, int brDepth) {
        if(nodes.isEmpty()) {
            cout << "Error in vPrintNodes: No nodes given." << endl;
            return;
        }
        ///root print
        if(nodes.getHead()->plus(2) == nodes.getTail()) {
            for(int d = 1; d < brDepth; d++) {
                cout << " ";
            }
            Linker<Splayer<Key,Data>*> *only = nodes.getHead()->getNext();
            if(only != NULL) {
                ///int custom
                if(only->getValue()->key >= 10) {
                    cout << "\b";
                }
                cout << only->getValue()->key;
            }
            cout << endl;
            return;
        }
        ///branch print
        for(int deflect = 1; deflect <= brDepth; deflect++) {
            for(int d = 1; d < 2*brDepth - deflect; d++) {
                cout << " ";
            }
            for(Linker<Splayer<Key,Data>*> *iter = nodes.getHead()->getNext(); iter != nodes.getTail(); iter = iter->plus(2)) {
                if(iter->getValue() != NULL) {
                    cout << "/";
                }
                else {
                    cout << " ";
                }
                for(int i = 1; i < deflect; i++) {
                    cout << "  ";
                }
                cout << " ";
                if(iter->getNext()->getValue() != NULL) {
                    cout << "\\";
                }
                else cout << " ";
                int midGap = 4*brDepth - 2*deflect;
                for(int i = 1; i < midGap; i++) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        ///node print
        bool reduce;  ///int custom
        for(int d = 1; d < brDepth; d++) {
            cout << " ";
        }
        for(Linker<Splayer<Key,Data>*> *iter = nodes.getHead()->getNext(); iter != nodes.getTail(); iter = iter->plus(2)) {
            if(iter->getValue() != NULL) {
                if(iter->getValue()->key >= 10) {  ///int custom
                    cout << "\b";
                }
                if(reduce) {  ///int custom
                    cout << "\b";
                }
                cout << iter->getValue()->key;
            }
            else {
                cout << " ";
            }
            for(int i = 1; i < brDepth; i++) {
                cout << "  ";
            }
            cout << " ";
            if(iter->getNext()->getValue() != NULL) {
                if(iter->getNext()->getValue()->key >= 10) {  ///int custom
                    reduce = true;
                }
                else {
                    reduce = false;
                }
                cout << iter->getNext()->getValue()->key;
            }
            else {
                cout << " ";
            }
            int midGap = 2*brDepth;
            for(int i = 1; i < midGap; i++) {
                cout << " ";
            }
        }
        cout << endl;
    }
public:
    void visualPrint(Splayer<Key,Data> *root, int lastDepth = 1) {
        if(root == NULL) {
            cout << "    [NULL]    " << endl << endl;
            return;
        }
        int level = getLevel(root);
        int brDepth = 1;  ///for level 1
        for(int i = 2; i <= level; i++) {
            brDepth *= 2;
        }
        Queue<Splayer<Key,Data>*> q1, q2;
        q1.enq(root);
        while(brDepth) {
            vPrintNodes(*q1.store, brDepth * lastDepth);
            while(!q1.isEmpty()) {
                Splayer<Key,Data> *now = q1.deq();
                if(now == NULL) {
                    q2.enq(NULL);
                    q2.enq(NULL);
                }
                else {
                    q2.enq(now->left);
                    q2.enq(now->right);
                }
            }
            while(!q2.isEmpty()) {
                q1.enq(q2.deq());
            }
            brDepth /= 2;
        }
        cout << endl;
    }
    void visualPrint(int lastDepth = 1) {
        visualPrint(root, lastDepth);
    }
};

int main() {
    bool dataIncl = false;
    /*while (true) {
        char check;
        cout << "Include data with key?(y/n) ";
        cin >> check;
        if(check == 'y') {
            dataIncl = true;
            break;
        }
        else if(check == 'n') {
            dataIncl = false;
            break;
        }
    }*/
    SplayTree<int,string> tree;
    int option, keyIn;
    string dataIn;
    Splayer<int,string> *iter;
    while(true) {
        cout << "1.Search 2.Insert 3.Delete 4.Splay 5.Print 6.Clear 7.Exit" << endl;
        cin >> option;
        if(option == 1) {
            cin >> keyIn;
            BoolData<string>output = tree.search(keyIn);
            if(output.truth) {
                cout << "Found." << endl;
                if(dataIncl) {
                    cout << output.data << endl;
                }
            }
            else {
                cout << "Not found." << endl;
            }
        }
        else if(option == 2) {
            cin >> keyIn;
            if(dataIncl) {
                cin >> dataIn;
                tree.insert(keyIn, dataIn);
            }
            else {
                tree.insert(keyIn);
            }
        }
        else if(option == 3) {
            cin >> keyIn;
            tree.deletes(keyIn);
        }
        else if(option == 4) {
            cin >> keyIn;
            tree.splay(keyIn);
        }
        else if(option == 5) {
            tree.visualPrint(2);
        }
        else if(option == 6) {
            tree.clear();
        }
        else if(option == 7) {
            break;
        }
        else {
            cout << "Invalid option." << endl;
        }
    }
}
