#ifndef TESTBSTREE_H
#define TESTBSTREE_H

#include "bstree.h"
#include <iostream>
#include <cstdlib>

#define CLEAR_SCREEN() system("cls")
#define PAUSE() system("pause")


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


    void runMainMenu();


private:
    /** Пункты тестового меню */
    enum MainMenuActions {
        ActionAddNode,
        ActionRemoveNode,
        ActionPrintAllNodes,
        ActionPrintNodesCount,
        ActionTestIsTreeEmpty,
        ActionFindData,
        ActionClearTree,
        ActionGetNodeMaxDepth,
        ActionDumpTreeStructure,
        ActionExit
    };

    // Заголовки пунктов тестового меню
    static const string MenuItemTitleActionAddNode;
    static const string MenuItemTitleActionRemoveNode;
    static const string MenuItemTitleActionPrintAllNodes;
    static const string MenuItemTitleActionPrintNodesCount;
    static const string MenuItemTitleActionTestIsTreeEmpty;
    static const string MenuItemTitleActionFindData;
    static const string MenuItemTitleActionClearTree;
    static const string MenuItemTitleActionGetNodeMaxDepth;
    static const string MenuItemTitleActionDumpTreeStructure;
    static const string MenuItemTitleActionExit;



    void _paintMainMenu();

    void _menuActionAddNode();
    void _menuActionRemoveNode();
    void _menuActionPrintAllNodes();
    void _menuActionPrintNodesCount();
    void _menuActionTestIsTreeEmpty();
    void _menuActionFindData();
    void _menuActionClearTree();
    void _menuActionGetNodeMaxDepth();
    void _menuActionDumpTreeStructure();

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


    BSTree<int, int> _tree_for_menu_test;
};

#endif // TESTBSTREE_H
