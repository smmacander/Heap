#include <iostream>
#include "CDA.cpp"
using namespace std;

template<class keytype, class valuetype>
class Heap{
    public:
        Heap(); //Default constructor. The Heap should be empty.
        Heap(keytype k[], valuetype  V[], int s); //For this constructor the heap should be built using the arrays K and V containing s items of keytype and valuetype.  The heap should be constructed using the O(n) bottom up heap building method.
        ~Heap(); //Destructor for the class
        Heap<keytype, valuetype>& operator=(Heap<keytype, valuetype>& other); //copy assignment operator
        Heap(Heap<keytype, valuetype>& other); //copy constructor
        keytype peekKey(); //Returns the minimum key in the heap without modifiying the heap.
        valuetype peekValue(); //Returns the value associated with the minimum key in the heap without modifiying the heap.
        keytype extractMin(); //Removes the minimum key in the heap and returns the key.
        void insert(keytype k, valuetype v); //Inserts the key k and value v pair into the heap. 
        void printKey();
    private:
        CDA<keytype> keyArray;
        CDA<valuetype> valueArray;
        int heapsize;
        int Parent(int i);
        int Left(int i);
        int Right(int i);
        void MinHeapify(CDA<keytype> A, CDA<valuetype> B, int i);
        void BuildMinHeap(CDA<keytype> A, CDA<valuetype> B);
        void HeapDecreaseKey(CDA<keytype> A, CDA<valuetype> B, int i, keytype key, valuetype value);
        void deleteAll();
};

template<class keytype, class valuetype>
Heap<keytype, valuetype>::Heap(){
    heapsize = 0;
}

template<class keytype, class valuetype>
Heap<keytype, valuetype>::Heap(keytype k[], valuetype  V[], int s){
    for(int i = 0; i < s; i++){
        keyArray.AddEnd(k[i]);
        valueArray.AddEnd(V[i]);
    }
    BuildMinHeap(keyArray, valueArray);
    heapsize = keyArray.Length();
}

template<class keytype, class valuetype>
Heap<keytype, valuetype>::~Heap(){
    for(int i = 0; i <= heapsize; i++){
        keyArray.DelEnd();
        valueArray.DelEnd();
    } 
    heapsize = 0;
}

template<class keytype, class valuetype>
Heap<keytype, valuetype>& Heap<keytype, valuetype>::operator=(Heap<keytype, valuetype>& other){
    //if(other != *this){
        keyArray = other.keyArray;
        valueArray = other.valueArray;
        heapsize = other.heapsize;
    //}
    return *this;
}

template<class keytype, class valuetype>
Heap<keytype, valuetype>::Heap(Heap<keytype, valuetype>& other){
    keyArray = other.keyArray;
    valueArray = other.valueArray;
    heapsize = other.heapsize;
}

template<class keytype, class valuetype>
keytype Heap<keytype, valuetype>::peekKey(){
    return keyArray[0];
}

template<class keytype, class valuetype>
valuetype Heap<keytype, valuetype>::peekValue(){
    return valueArray[0];
}

template<class keytype, class valuetype>
keytype Heap<keytype, valuetype>::extractMin(){
    keytype minKey = keyArray[0];
    keyArray[0] = keyArray[heapsize-1];
    keytype minValue = valueArray[0];
    valueArray[0] = valueArray[heapsize-1];
    heapsize--;
    MinHeapify(keyArray, valueArray, 0);
    keyArray.DelEnd();
    valueArray.DelEnd();
    return minKey;
}

template<class keytype, class valuetype>
void Heap<keytype, valuetype>::insert(keytype k, valuetype v){
    heapsize+=1;
    keyArray.AddEnd(k);
    valueArray.AddEnd(v);
    for(int i = (keyArray.Length()/2 + 1); i >= 0; i--){
        MinHeapify(keyArray, valueArray, i);
    }
}

template<class keytype, class valuetype>
void Heap<keytype, valuetype>::printKey(){
    for(int i = 0; i < heapsize; i++){
        cout << keyArray[i] << " ";
    }
    cout << endl;
}

///////////////////////
///Private Functions///
///////////////////////

template<class keytype, class valuetype>
int Heap<keytype, valuetype>::Parent(int i){
    return i/2;
}

template<class keytype, class valuetype>
int Heap<keytype, valuetype>::Left(int i){
    return 2*i;
}

template<class keytype, class valuetype>
int Heap<keytype, valuetype>::Right(int i){
    return 2*i+1;
}

template<class keytype, class valuetype>
void Heap<keytype, valuetype>::MinHeapify(CDA<keytype> A, CDA<valuetype> B, int i){
    int l = Left(i + 1) - 1;
    int r = Right(i + 1) - 1;
    int min;
    if((l <= heapsize - 1) && (A[l] < A[i])) min = l;
    else min = i;
    if((r <= heapsize - 1) && (A[r] < A[min])) min = r;
    if(min != i){
        keytype tempKey = A[i];
        A[i] = A[min];
        A[min] = tempKey;
        valuetype tempValue = B[i];
        B[i] = B[min];
        B[min] = tempValue;
        MinHeapify(A, B, min);
    }
}

template<class keytype, class valuetype>
void Heap<keytype, valuetype>::BuildMinHeap(CDA<keytype> A, CDA<valuetype> B){
    heapsize = A.Length();
    for(int i = (A.Length()/2 + 1); i>=0; i--){
        MinHeapify(A, B, i);
    }
}
