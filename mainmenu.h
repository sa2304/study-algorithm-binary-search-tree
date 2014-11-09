#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bstree.h"
using namespace std;

#define CLEAR_SCREEN() system("cls")
#define PAUSE() system("pause")


class MainMenu
{
    /* Пункты меню */
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

    /* Заголовки пунктов меню */
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

    /* Дерево */
    BSTree<int, int> _tree_for_menu_test;


    void _paintMenu();

    void _menuActionAddNode();
    void _menuActionRemoveNode();
    void _menuActionPrintAllNodes();
    void _menuActionPrintNodesCount();
    void _menuActionTestIsTreeEmpty();
    void _menuActionFindData();
    void _menuActionClearTree();
    void _menuActionGetNodeMaxDepth();
    void _menuActionDumpTreeStructure();

public:
    MainMenu();

    void run();
};

#endif // MAINMENU_H
