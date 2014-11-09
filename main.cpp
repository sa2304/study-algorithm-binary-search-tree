#include <iostream>

#include "mainmenu.h"
#include "testbstree.h"
using namespace std;





void testAll();

static BSTree<int, int> tree;

//-----------------------------------------------------------------------------
int main()
{
    MainMenu main_menu;
    main_menu.run();
    PAUSE();

    return 0;
}


//-----------------------------------------------------------------------------
void testAll() {
    cout << "Hello World!" << endl;

    TestBSTree test;
    test.testInsert();
    test.testRemove();
    test.testCount();
    test.testClear();
    test.testIterator();
    test.testMaxDepth();

    BSTree<int, string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");
    tree.insert(5, "five");
    tree.insert(6, "six");
    tree.insert(7, "seven");
    tree.insert(8, "eight");
    tree.insert(9, "nine");
    tree.print();
}
