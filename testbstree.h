#ifndef TESTBSTREE_H
#define TESTBSTREE_H

#include "bstree.h"
#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;

/** Класс представляет собой набор автоматизированных тестов для методов класса BSTree
 *
 */

class TestBSTree
{
public:
    TestBSTree();

    // Тестировщики методов класса BSTree
    bool testInsert();
    bool testRemove();
    bool testCount();
    bool testClear();
    bool testIterator();
    bool testMaxDepth();


private:

    //-------------------------------------------------------------------------
    void _notifyTestFailed(std::string info = "") {
        cout << "!FAILED!";
        if (!info.empty()) {
            cout << "Info: " << info;
        }
        cout << endl;
    }

    //-------------------------------------------------------------------------
    void _testPassed() {
        cout << "Ok!" << endl;
    }



};

#endif // TESTBSTREE_H
