#include <iostream>
using namespace std;

template<class keytype, class valuetype>
struct BHeapNode{
    public:
        BHeapNode<keytype, valuetype> *parent, *sibling, *child;
        int degree;
        keytype key;
        valuetype value;
        BHeapNode(keytype k, valuetype v, BHeapNode<keytype, valuetype> * p = nullptr){
            key = k;
            value = v;
            parent = p; 
            sibling = child = nullptr;
            degree = 0;
        };
        void addChild(BHeapNode<keytype, valuetype>* childNode){
            if(childNode){
                childNode->sibling = nullptr;
                if(child){
                    BHeapNode<keytype, valuetype> *temp = child;
                    while(temp->sibling) temp = temp->sibling;
                    temp->sibling = childNode;
                }
                else child = childNode;
                degree++;
                childNode->parent = this;
            }
        }
};

template<class keytype, class valuetype>
class BHeap{
    public:
        friend class BHeapNode<keytype, valuetype>;
        BHeap(); //Default Constructor. The Heap should be empty
        BHeap(keytype k[], valuetype V[], int s); //For this constructor theheap should be built using the arrays K and V containing s items of keytype and valuetype.  The heap should be constructed using repeated insertion
        void insert(keytype k, valuetype v); //Inserts the key k and value v pair into the heap.
        void printKey(); //Writes the keys stored in the heap, printing the smallest binomial tree first.  When printing a binomial tree, print the size of tree first and then use a modified preorder traversal of the tree.  See the example below.
    private:
        keytype key;
        valuetype value;
        BHeapNode<keytype, valuetype> *sibling, *child, *parent;
        int size;
        BHeapNode<keytype, valuetype> * unionHeap(BHeapNode<keytype, valuetype> *heapA, BHeapNode<keytype, valuetype> *heapB); 
        BHeapNode<keytype, valuetype> * mergeHeap(BHeapNode<keytype, valuetype> *heapA, BHeapNode<keytype, valuetype> *heapB);
        int degree(BHeapNode<keytype, valuetype> *heap);
        BHeapNode<keytype, valuetype> *head;
};

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap(){
    head = 0;
}

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap(keytype k[], valuetype V[], int s){
    head = 0;
    for(int i = 0; i < s; i++){
        insert(k[i], V[i]);
    }
};

template<class keytype, class valuetype>
void BHeap<keytype, valuetype>::insert(keytype k, valuetype v){
    BHeapNode<keytype, valuetype> *p = head? head->parent: nullptr;
    BHeapNode<keytype, valuetype> *singleton = new BHeapNode<keytype, valuetype>(k, v);
    head = unionHeap(singleton, head);
}

template<class keytype, class valuetype>
void BHeap<keytype, valuetype>::printKey(){
    
}

/////////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////////
template<class keytype, class valuetype>
BHeapNode<keytype, valuetype>* BHeap<keytype, valuetype>::unionHeap(BHeapNode<keytype, valuetype>* heapA, BHeapNode<keytype, valuetype>* heapB){
    BHeapNode<keytype, valuetype>* heapU = mergeHeap(heapA, heapB);
    if(heapU){
        BHeapNode<keytype, valuetype> *cur = heapU, *prev = nullptr, *next = nullptr;
        int degreeA, degreeB;
        while(cur && cur->sibling){
            next = cur->sibling;
            degreeA = cur->degree;
            degreeB = next->degree;
            if((degreeA == degreeB) && (degreeA != degree(next->sibling))){
                if(cur->key < next->key){
                    cur->sibling = next->sibling;
                    cur->addChild(next);
                    prev = cur;
                    cur = cur->sibling;
                }
                else{
                    if(prev) prev->sibling = next;
                    else heapU = next;
                    next->addChild(cur);
                    prev = next;
                    cur = next->sibling;
                }
            }
            else{
                if(!prev) heapU = cur;
                prev = cur;
                cur = next;
            }
        }
    }
    return heapU;
}

template<class keytype, class valuetype>
BHeapNode<keytype, valuetype>* BHeap<keytype, valuetype>::mergeHeap(BHeapNode<keytype, valuetype>* heapA, BHeapNode<keytype, valuetype>* heapB){
    BHeapNode<keytype, valuetype> *heapM = nullptr;
    if(heapA || heapB){
        if(heapA && !heapB) heapM = heapA;
        else if(!heapA && !heapB) heapM = heapB;
        else{
            BHeapNode<keytype, valuetype> *temp = nullptr, *next = nullptr, *prev = nullptr, *cur = nullptr;
            if(heapA->degree > heapB->degree){
                heapM = heapB;
                next = heapA;
            }
            else{
                heapM = heapA;
                next = heapB;
            }
            cur = heapM;
            while((cur) && (next) && (cur != next)){
                if(cur->degree <= next->degree){
                    if(cur->sibling){
                        temp = cur->sibling;
                        cur->sibling = next;
                        prev = cur;
                        cur = next;
                        next = temp;
                    }
                    else{
                        cur->sibling = next;
                        cur = next;
                    }
                }
                else{
                    if(prev) prev->sibling = next;
                    else heapM = next;
                    temp = next->sibling;
                    next->sibling = cur;
                    prev = next;
                    next = temp;
                }
            }
        }
    }
    return heapM;
}

template<class keytype, class valuetype>
int BHeap<keytype, valuetype>::degree(BHeapNode<keytype, valuetype> *heap){
    if(!heap) return -1;
    int i = 0;
    BHeapNode<keytype, valuetype> *child = heap->child;
    while(child){
        i++;
        child = child->sibling;
    }
    return i;
}
