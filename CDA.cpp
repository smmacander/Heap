#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<class elmtype>
int randomPartition(elmtype arr[], int l, int r);  //Standard partition process of QuickSort(). It considers the last element as pivot and moves all smaller element to left of it and greater elements to right 
template<class elmtype>
int kthSmallest(elmtype arr[], int l, int r, int k); //This function returns k'th smallest element in arr[l..r] using QuickSort based method. ASSUMPTION: ELEMENTS IN ARR[] ARE DISTINCT 

template<class elmtype>
class CDA{
    public:
        CDA(); //Default Constructor. The array should be of capacity 1, size 0 and ordered is false.
        CDA(int s); //For this constructor the array should be of capacity and size s with ordered = false
        CDA<elmtype>& operator=(CDA<elmtype>& other);  //overloaded assignment operator
        //CDA(const CDA<elmtype>& other); //copy assignment operator
        elmtype& operator[](int i); //Traditional [] operator. Should print a message if i is out of bounds and return a reference to value of type elmtype stored in the class for this purpose.
        //~CDA(); //destructor
        void AddEnd(elmtype v); //Increases the size of the array by 1 and stores vat the end of the array. Should double the capacity when the new element doesn't fit.  If ordered is true, check to be sure that the array is still in order. 
        void AddFront(elmtype v); //Increases the size of the array by 1 and stores vat the beginning of the array. Should double the capacity when the new element doesn't fit. The new element should be the item returned at index 0.  If ordered is true, check to be sure that the array is still in order.
        void DelEnd(); //reduces the size of the array by 1 at the end. Should shrink the capacity when only 25% of the array is in use after the delete. The capacity should never go below 1.
        void DelFront(); //reduces the size of the array by 1 at the beginning of the array. Should shrink the capacity when only 25% of the array is in use after the delete. The capacity should never go below 1.
        int Length(); //returns the size of the array
        int Capacity(); //returns the size of the array
        bool Ordered(); //returns the status of the ordered flag
        int SetOrdered(); //Check to see if the array is in order.  Set the order flag appropriately.  Return 1 if the array was ordered and -1 otherwise.
        elmtype Select(int k); //returns the kthsmallest element in the array.  If ordered is true then return the item at index k-1.  Otherwise use the quickselect algorithm. Quickselect should choose a random partition element.
        void InsertionSort(); //Performs insertion sort on the array.  Sets ordered to true.
        void QuickSort(); //Sorts the values in the array using the quick sort algorithm.  This should pick the partition value using the median of three technique.  Set ordered to true.Should also make use of insertion sort to improve performance.
        void CountingSort(int m); //Sorts the values in the array using counting sort, where the values in the array are in the range 0...m.  Set ordered to true.  You may assume that all values in the array are integers in the range 0...m.
        int Search(elmtype e); //If ordered is true, perform a binary searchof the array looking for the item e.  Otherwise perform linear search.  Returns the index of the item if found or -1 otherwise.
        void swap(CDA<elmtype> arr, int left, int right); 
    private:
        elmtype *array;
        int back;
        int capacity;
        int front;
        bool ordered;
        int size;
        void DoubleArraySize();
        int medianof3(CDA<elmtype> arr, int low, int high);       
};

template<class elmtype>
CDA<elmtype>::CDA(){
    capacity = 1;
    size = 0;
    front = 0;
    back = 0;
    array = new elmtype[capacity];
    ordered = false;
}

template<class elmtype>
CDA<elmtype>::CDA(int s){
    capacity = s;
    size = s;
    front = 0;
    back = s-1;
    array = new elmtype[capacity];
    ordered = false;
}

template <class elmtype>
CDA<elmtype>& CDA<elmtype>::operator=(CDA<elmtype>& other){
    if(this != &other){ 
        capacity = other.capacity;
        size = other.size;
        front = other.front;
        back = other.back;
        ordered = other.ordered;
        delete []array;
        array = new elmtype[capacity];
        for(int i = 0; i < capacity; i++){
           array[i] = other.array[i];
        }
    }
    return *this;
}

/*template<class elmtype>
CDA<elmtype>::CDA(const CDA &other){ 
    capacity = other.capacity;
    size = other.size;
    front = other.front;
    back = other.back;
    ordered = other.ordered;
    delete []array;
    array = new elmtype[capacity];
    for(int i = 0; i < capacity; i++){
        array[i] = other.array[i];
    }    
}*/

template<class elmtype>
elmtype& CDA<elmtype>::operator[](int i){
    if(i > size){
        cout << "Out of bounds!" << endl;
        exit;
    }
    return *(array + ((front + i) % (capacity)));
}

/*template<class elmtype> 
CDA<elmtype>::~CDA(){
    front = 0;
    back = 0;
    size = 0;
    capacity = 1;
    ordered = false;
    delete []array;
}*/

template<class elmtype>
void CDA<elmtype>::AddEnd(elmtype v){
    if(size == capacity){
        DoubleArraySize();
    }
    if(back == capacity - 1){
        back = 0;
        *(array + (back % capacity)) = v;
        size++;
        if((ordered == true) && (*(array + back) < *(array + (capacity - 1)))){
            ordered = false;
        }
    }
    else{
        back++;
        *(array + (back % capacity)) = v;
        size++;
        if((ordered == true) && (*(array + back) < *(array + (back - 1)))){
            ordered = false;
        }
    }
}

template<class elmtype>
void CDA<elmtype>::AddFront(elmtype v){
    if(size == capacity){
        DoubleArraySize();
    }
    if(front == 0){
        front = capacity - 1;
        *(array + (front % capacity)) = v;
        size++;
        if((ordered == true) && (*(array + front) > *(array + (capacity - 1)))){
            ordered = false;
        }
    }
    else{
        front--;
        *(array + (front % capacity)) = v;
        size++;
        if((ordered == true) && (*(array + front) > *(array + (front + 1)))){
            ordered = false;
        }
    }
}

template<class elmtype>
void CDA<elmtype>::DelEnd(){
    if(capacity > 1){
        back--;
        size--;
        if(capacity < size/4){
            elmtype* newArray;
            newArray = new elmtype[size];
            for(int i = 0; i < size; i++){
                *(newArray + i) = *(array + ((front + i) % (capacity)));
            }
            std::swap(array, newArray);
            capacity /= 2;
            front = 0;
            back = size - 1;
        }
    }
}

template<class elmtype>
void CDA<elmtype>::DelFront(){
    if(capacity > 1){
        front++;
        size--;
        if(capacity < size/4){
            elmtype* newArray;
            newArray = new elmtype[size];
            for(int i = 0; i < size; i++){
                *(newArray + i) = *(array + ((front + i) % (capacity)));
            }
            std::swap(array, newArray);
            capacity /= 2;
            front = 0;
            back = size - 1;
        }
    }
}

template<class elmtype>
int CDA<elmtype>::Length(){
    return size;
}

template<class elmtype>
int CDA<elmtype>::Capacity(){
    return capacity;
}

template<class elmtype>
bool CDA<elmtype>::Ordered(){
    return ordered;
}

template<class elmtype>
int CDA<elmtype>::SetOrdered(){
    elmtype current;
    elmtype currentPlusOne;
    for(int i = 0; i < size - 1; i++){
        current = *(array + ((front + i)%capacity));
        currentPlusOne = *(array + (front + i + 1)%capacity);
        if(current > currentPlusOne){
            ordered = false;
            return -1;
        }
    }
    ordered = true;
    return 1;
}

template<class elmtype>
elmtype CDA<elmtype>::Select(int k){
    if(ordered == true){
        return this->operator[](k-1);
    }
    else{
        CDA<elmtype> temp = *this;
        return kthSmallest(temp, 0, size - 1, k);
    }
}

template<class elmtype>
void CDA<elmtype>::InsertionSort(){
    insertionSortHelper(*this, size);
    ordered = true;
}

template<class elmtype>
void CDA<elmtype>::QuickSort(){
    quickSortHelper(*this, 0, size - 1);
    ordered = true;
}

template<class elmtype>
void CDA<elmtype>::CountingSort(int m){
    countingSortHelper(*this, m);
    ordered = true;
}

template<class elmtype>
int CDA<elmtype>::Search(elmtype e){
    if(ordered == true){
        CDA <elmtype> temp = *this;
        return binarySearch(temp, 0, size - 1, e);
    }
    else{
        CDA <elmtype> temp = *this;
        return linearSearch(temp, size, e);
    }
}

template<class elmtype>
void swap(CDA<elmtype> arr, int left, int right){
    elmtype temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
}

template<class elmtype>
int medianof3(CDA<elmtype> arr, int left, int right){
    int mid = (left + right)/2;
    if(arr[right] < arr[left]) swap(arr, left, right);
    if(arr[mid] < arr[left]) swap(arr, mid, left);
    if(arr[right] < arr[mid]) swap(arr, right, mid);
    return mid;
}

template<class elmtype>
void CDA<elmtype>::DoubleArraySize(){
    capacity *= 2;
    elmtype* temp = new elmtype[capacity];
    int oldArrayCounter = front;
    int newArrayCounter = 0;

    bool loop = true;

    while(loop){
        if(oldArrayCounter == size) oldArrayCounter = 0;
        temp[newArrayCounter] = array[oldArrayCounter];
        if(oldArrayCounter == back) loop = false;
        oldArrayCounter++;
        newArrayCounter++;
    }
    delete[] array;
    array = temp;
    front = 0;
    back = size - 1;
}

//HELPER FUNCTIONS BELOW/////////////////////////////////////////////////////////////////////////////////
template<class elmtype>
int kthSmallest(CDA<elmtype> array, int l, int r, int k){
    int pos = randomPartition(array, l, r); 
  
    // If position is same as k 
    if (pos-l == k-1) 
        return array[pos]; 
    if (pos-l > k-1)  // If position is more, recur for left subarray 
        return kthSmallest(array, l, pos-1, k); 
  
    // Else recur for right subarray 
    return kthSmallest(array, pos+1, r, k-pos+l-1); 
}

template<class elmtype>
int partition(CDA<elmtype> array, int l, int r) 
{ 
    int x = array[r], i = l; 
    for (int j = l; j <= r - 1; j++) 
    { 
        if (array[j] <= x) 
        { 
            swap(array, i, j); 
            i++; 
        } 
    } 
    swap(array, i, r); 
    return i; 
} 

template<class elmtype>
int randomPartition(CDA<elmtype> array, int l, int r){
    int n = r-l+1; 
    int pivot = rand() % n; 
    swap(array, l + pivot, r); 
    return partition(array, l, r); 
}

template<class elmtype>
int binarySearch(CDA<elmtype> array, int l, int r, elmtype x){
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        if (array[mid] == x) 
            return mid; 
  
        if (array[mid] > x) 
            return binarySearch(array, l, mid - 1, x); 
  
        return binarySearch(array, mid + 1, r, x); 
    } 
    return -1; 
}

template<class elmtype>
int linearSearch(CDA<elmtype> array, int n, elmtype x){
    int i; 
    for (i = 0; i < n; i++){
        if (array[i] == x) 
            return i; 
    }
    return -1; 
}

template<class elmtype>
void insertionSortHelper(CDA<elmtype> array, int n)  
{  
    elmtype key;
    int i, j; 
    for (i = 1; i < n; i++){  
        key = array[i];  
        j = i - 1; 
        while (j >= 0 && array[j] > key) 
        {  
            array[j + 1] = array[j];  
            j = j - 1;  
        }  
        array[j + 1] = key;  
    }  
}  

template<class elmtype>
void quickSortHelper(CDA<elmtype> array, int low, int high){
    int size = (high + 1) - low;
    if(size < 1){
        insertionSortHelper(array, size);
    }
    else{
        int pivot = medianof3(array, low, high);
        int pi = partition(array, low, high);
        quickSortHelper(array, low, pi - 1);
        quickSortHelper(array, pi + 1, high);
    }
}

template<class elmtype>
void countingSortHelper(CDA<elmtype> array, int m){

    int range = m; 
      
    vector<int> count(range), output(array.Length()); 
    for(int i = 0; i < array.Length(); i++) 
        count[array[i]]++; 
          
    for(int i = 1; i < count.size(); i++) 
           count[i] += count[i-1]; 
    
    for(int i = array.Length()-1; i >= 0; i--) 
    {  
         output[count[array[i]] -1 ] = array[i];  
              count[array[i]]--;  
    } 
      
    for(int i=0; i < array.Length(); i++) 
            array[i] = output[i]; 
}    

