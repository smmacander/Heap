#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "BHeap.cpp"

int main(){
    string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
	int B[10] = {10,9,8,7,6,5,4,3,2,1};
    BHeap<string,int> X(A,B,10);
}