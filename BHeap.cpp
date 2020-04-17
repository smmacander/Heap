#include <iostream>
#include <list>
using namespace std;

template<class keytype, class valuetype>
struct Node{
    Node<keytype, valuetype> *child, *parent, *sibling;
    int degree;
    keytype key;
    valuetype value;    
};

template<class keytype, class valuetype>
Node<keytype, valuetype>* newNode(keytype key, valuetype value){ 
    Node<keytype, valuetype> *temp = new Node<keytype, valuetype>; 
    temp->key = key; 
    temp->value = value;
    temp->degree = 0; 
    temp->child = temp->parent = temp->sibling = NULL; 
    return temp; 
}

template<class keytype, class valuetype>
class BHeap{
    public:
        BHeap(); //Default Constructor. The Heap should be empty
        BHeap(keytype k[], valuetype V[], int s); //For this constructor theheap should be built using the arrays K and V containing s items of keytype and valuetype.  The heap should be constructed using repeated insertion
        keytype extractMin(); //Removes the minimum key in the heap and returns the key.
        void insert(keytype k, valuetype v); //Inserts the key k and value v pair into the heap.
        void printKey(); //Writes the keys stored in the heap, printing the smallest binomial tree first.  When printing a binomial tree, print the size of tree first and then use a modified preorder traversal of the tree.  See the example below.
    private:
        list<Node<keytype, valuetype>*> _head;
        list<Node<keytype,valuetype>*> insertHelper(keytype k, valuetype v);
        list<Node<keytype,valuetype>*> insertATreeInHeap(list<Node<keytype, valuetype>*> _heap, Node<keytype, valuetype> *tree);
        list<Node<keytype,valuetype>*> unionBinomialHeap(list<Node<keytype, valuetype>*> l1, list<Node<keytype, valuetype>*> l2);
        list<Node<keytype, valuetype>*> adjust(list<Node<keytype, valuetype>*> _heap);
        Node<keytype, valuetype>* mergeBinomialTrees(Node<keytype, valuetype> *b1, Node<keytype, valuetype> *b2);
        void printTree(Node<keytype, valuetype>* h);
        void printHeap(list<Node<keytype, valuetype>*> _heap);
};

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap(){
    NULL;
}

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap(keytype k[], valuetype V[], int s){
    for(int i = 0; i < s; i++){
        cout << "Inserting: " << k[i] << endl;
        insert(k[i], V[i]);
    }
};

template<class keytype, class valuetype>
void BHeap<keytype, valuetype>::insert(keytype k, valuetype v){
    _head = insertHelper(k, v);
}

template<class keytype, class valuetype>
void BHeap<keytype, valuetype>::printKey(){
    printHeap(_head);
}

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
template<class keytype, class valuetype>
list<Node<keytype,valuetype>*> BHeap<keytype, valuetype>::insertHelper(keytype k, valuetype v){
    Node<keytype, valuetype> *temp = newNode(k, v); 
    return insertATreeInHeap(_head,temp); 
}

template <class keytype, class valuetype>
list<Node<keytype,valuetype>*> BHeap<keytype, valuetype>::insertATreeInHeap(list<Node<keytype,valuetype>*> _heap, Node<keytype, valuetype> *tree){
    cout << "inserting a tree " << tree->key << " into the heap" << endl;
    list<Node<keytype,valuetype>*> temp;
    temp.push_back(tree);
    temp = unionBinomialHeap(_heap, temp);
    return adjust(temp);
}

template<class keytype, class valuetype>
Node<keytype, valuetype>* BHeap<keytype, valuetype>::mergeBinomialTrees(Node<keytype, valuetype> *b1, Node<keytype, valuetype> *b2){
    if(b1->key > b2->key) swap(b1, b2);
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

template <class keytype, class valuetype>
list<Node<keytype,valuetype>*> BHeap<keytype, valuetype>::unionBinomialHeap(list<Node<keytype, valuetype>*> l1, list<Node<keytype, valuetype>*> l2){
    list<Node<keytype,valuetype>*> _new;
    typename list<Node<keytype,valuetype>*>::iterator it = l1.begin();
    typename list<Node<keytype, valuetype>*>::iterator ot = l2.begin();
    while(it!=l1.end() && ot!=l2.end()){
        if((*it)->degree <= (*ot)->degree){
            _new.push_back(*it);
            it++;
        }
        else{
            _new.push_back(*ot);
            ot++;
        }
    }
    while(it != l1.end()){
        _new.push_back(*it);
        it++;
    }
    while(ot != l2.end()){
        _new.push_back(*ot);
        ot++;
    }
    return _new;
}

template<class keytype, class valuetype>
list<Node<keytype, valuetype>*> BHeap<keytype, valuetype>::adjust(list<Node<keytype, valuetype>*> _heap){
    if(_heap.size() <= 1) return _heap;
    list<Node<keytype, valuetype>*> new_heap;
    typename list<Node<keytype,valuetype>*>::iterator it1, it2, it3;
    it1 = it1 = it3 = _heap.begin();
    if(_heap.size() == 2){
        it2 = it1;
        it2++;
        it3 = _heap.end();
    }
    else{
        it2++;
        it3=it2;
        it3++;
    }
    while(it1 != _heap.end()){
        if(it2 == _heap.end()) it1++;
        else if((*it1)->degree < (*it2)->degree){
            it1++;
            it2++;
            if(it3!=_heap.end()) it3++;
        }
        else if((it3!=_heap.end()) && ((*it1)->degree == (*it2)->degree) && ((*it1)->degree == (*it3)->degree)){
            it1++;
            it2++;
            it3++;
        }
        else if((*it1)->degree == (*it2)->degree){
            Node<keytype, valuetype> *temp;
            *it1 = mergeBinomialTrees(*it1, *it2);
            it2 = _heap.erase(it2);
            if(it3 != _heap.end()) it3++;
        }
    }
    return _heap;
}

template<class keytype, class valuetype>
void printTree(Node<keytype, valuetype> *h){
    while(h){
        cout << h->data << " ";
        printTree(h->child);
        h = h->sibling;
    }
}

template<class keytype, class valuetype>
void printHeap(list<Node<keytype, valuetype>*> _heap){
    typename list<Node<keytype, valuetype>*>::iterator it;
    it = _heap.begin();
    while(it != _heap.end()){
        cout << "B" << (*it)->degree << endl;
        printTree(*it);
        it++;
    }
}