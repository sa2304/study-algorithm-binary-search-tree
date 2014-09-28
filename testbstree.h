#ifndef TESTBSTREE_H
#define TESTBSTREE_H

#include "bstree.h"
#include <iostream>

using namespace std;

/** Класс представляет собой набор автоматизированных тестов для методов класса BSTree
 *
 */

class TestBSTree
{
public:
    TestBSTree();

    bool testInsert();
    bool testRemove();
    bool testCount();
    bool testClear();
    bool testArrayOperator();

private:

    void _notifyTestFailed(std::string info = "") {
        cout << "!FAILED!";
        if (!info.empty()) {
            cout << "Info: " << info;
        }
        cout << endl;
    }

    void _testPassed() {
        cout << "Ok!" << endl;
    }
};

#endif // TESTBSTREE_H
