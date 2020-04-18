#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include "Heap.cpp"
#include "BHeap.cpp"

using namespace std;

void func(Heap<int, int> x)
{
    x.printKey(); // should print contents properly
    return;
}

void func(Heap<char, char> x)
{
    x.printKey(); // should print contents properly
    return;
}

void func(Heap<string, string> x)
{
    x.printKey(); // should print contents properly
    return;
}

int main()
{
    srand(time(0));

    cout << "TESTING HEAPS!" << endl;
    cout << "BEGINNING WITH INTEGERS" << endl;
    cout << "TESTING BUILDHEAP (bottom up!): " << endl;

    int buildHeapKeys[] = {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int buildHeapValues[] = {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    Heap<int, int> x(buildHeapKeys, buildHeapValues, 31);

    x = x;

    cout << "INSIDE FUNCTION" << endl;
    func(x); // should print first line of below printKey
    cout << "DONE WITH FUNCTION" << endl;
    
    for (int i = 0; i < 31; i++)
    {
        x.printKey();
        cout << x.peekKey() << endl;
        cout << x.peekValue() << endl;
        cout << x.extractMin() << endl << endl;
    }

    // peekKey, peekValue & extractMin should each print the same value, counting up from 1 to 31

    // printKey should look as follows for each iteration (with peekKey peekVal & extractMin in between)
    /*
    * 1 9 2 13 10 5 3 15 14 11 21 7 6 4 17 16 24 28 23 12 22 27 30 8 20 26 19 31 18 25 29
    * 2 9 3 13 10 5 4 15 14 11 21 7 6 18 17 16 24 28 23 12 22 27 30 8 20 26 19 31 29 25
    * 3 9 4 13 10 5 17 15 14 11 21 7 6 18 25 16 24 28 23 12 22 27 30 8 20 26 19 31 29
    * 4 9 5 13 10 6 17 15 14 11 21 7 19 18 25 16 24 28 23 12 22 27 30 8 20 26 29 31
    * 5 9 6 13 10 7 17 15 14 11 21 8 19 18 25 16 24 28 23 12 22 27 30 31 20 26 29
    * 6 9 7 13 10 8 17 15 14 11 21 20 19 18 25 16 24 28 23 12 22 27 30 31 29 26
    * 7 9 8 13 10 19 17 15 14 11 21 20 26 18 25 16 24 28 23 12 22 27 30 31 29
    * 8 9 17 13 10 19 18 15 14 11 21 20 26 29 25 16 24 28 23 12 22 27 30 31
    * 9 10 17 13 11 19 18 15 14 12 21 20 26 29 25 16 24 28 23 31 22 27 30
    * 10 11 17 13 12 19 18 15 14 22 21 20 26 29 25 16 24 28 23 31 30 27
    * 11 12 17 13 21 19 18 15 14 22 27 20 26 29 25 16 24 28 23 31 30
    * 12 13 17 14 21 19 18 15 23 22 27 20 26 29 25 16 24 28 30 31
    * 13 14 17 15 21 19 18 16 23 22 27 20 26 29 25 31 24 28 30
    * 14 15 17 16 21 19 18 24 23 22 27 20 26 29 25 31 30 28
    * 15 16 17 23 21 19 18 24 28 22 27 20 26 29 25 31 30
    * 16 21 17 23 22 19 18 24 28 30 27 20 26 29 25 31
    * 17 21 18 23 22 19 25 24 28 30 27 20 26 29 31
    * 18 21 19 23 22 20 25 24 28 30 27 31 26 29
    * 19 21 20 23 22 26 25 24 28 30 27 31 29
    * 20 21 25 23 22 26 29 24 28 30 27 31
    * 21 22 25 23 27 26 29 24 28 30 31
    * 22 23 25 24 27 26 29 31 28 30
    * 23 24 25 28 27 26 29 31 30
    * 24 27 25 28 30 26 29 31
    * 25 27 26 28 30 31 29
    * 26 27 29 28 30 31
    * 27 28 29 31 30
    * 28 30 29 31
    * 29 30 31
    * 30 31
    * 31
    */

   cout << endl << endl << endl << "BEGINNING RANDOM TESTS..." << endl << endl << endl;

    Heap<int, int> y;

    int arraySize = (rand() % 20) + 20; // generates a random array size between 20 and 40, adjust as necessary to debug
    int max = 0;
    int min = 2000;

    int keys[arraySize];
    int values[arraySize];

    cout << "ARRAY SIZE: " << arraySize << endl;

    for (int i = 0; i < arraySize; i++)
    {
        int randomKey = rand() % 100;
        int randomValue = randomKey;

        if (randomKey > max) { max = randomKey; }
        if (randomKey < min) { min = randomKey; }

        cout << "INSERTING KEY: " << randomKey << endl;
        cout << "INSERTING VALUE: " << randomValue << endl << endl;
        // uncomment these if u want to debug with the visualizer

        keys[i] = randomKey;
        values[i] = randomValue;

        y.insert(randomKey, randomValue);
    }

    Heap<int, int> z(keys, values, arraySize);

    cout << "MIN VALUE INSERTED: " << min << endl;
    cout << "MAX VALUE INSERTED: " << max << endl;

    for (int i = 0; i < arraySize; i++)
    {
        y.printKey();
        z.printKey();
        cout << y.peekKey() << endl;
        cout << y.peekValue() << endl;
        cout << y.extractMin() << endl;
        cout << z.peekKey() << endl;
        cout << z.peekValue() << endl;
        cout << z.extractMin() << endl << endl;
    }

    // first 2 lines are printKeys with each heap, min val at root
    // note the printKeys should not be identical each time. bottom up method builds a different heap than repeated inserts
    // next 6 lines should print the root 6 times in a row. Each iteration will build ascendingly from min value inserted to max value inserted

    cout << endl << endl << endl << "BEGINNING LARGE TESTS..." << endl << endl << endl;
    Heap <int, int> a;
    arraySize = 10000000;
    max = 0;
    min = 10000001;

    clock_t start = clock();
    for (int i = 0; i < 10000000; i++)
    {
        int randomKey = rand() % 100000;
        int randomValue = randomKey;

        if (randomKey > max) { max = randomKey; }
        if (randomKey < min) { min = randomKey; }

        a.insert(randomKey, randomValue);
        cout << "completed " << i << " inserts" << endl;
    }
    cout << "COMPLETED 10,000,000 INSERTS IN: " << (( clock() - start ) / (double) CLOCKS_PER_SEC) << " SECONDS." << endl << endl << endl << endl;
    // mine finished at around 2 seconds flat on average. not sure if thats good? let me know what you guys are getting 


    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------------

    return 0;
}