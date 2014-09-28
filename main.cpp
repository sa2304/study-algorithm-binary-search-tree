#include <iostream>

#include "testbstree.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    TestBSTree test;
    test.testInsert();
    test.testRemove();
    test.testCount();
    test.testClear();

    system("pause");

    return 0;
}

