#include "mainmenu.h"

// Инициализация констант класса
const string MainMenu::MenuItemTitleActionAddNode = "Add Node";
const string MainMenu::MenuItemTitleActionRemoveNode = "Remove Node";
const string MainMenu::MenuItemTitleActionPrintAllNodes = "Print All Nodes";
const string MainMenu::MenuItemTitleActionPrintNodesCount = "Print Nodes Count";
const string MainMenu::MenuItemTitleActionTestIsTreeEmpty = "Test If Tree Is Empty";
const string MainMenu::MenuItemTitleActionFindData = "Find Data By Key";
const string MainMenu::MenuItemTitleActionClearTree = "Clear Tree";
const string MainMenu::MenuItemTitleActionGetNodeMaxDepth = "Find Deepest Node";
const string MainMenu::MenuItemTitleActionDumpTreeStructure = "Dump Tree Structure";
const string MainMenu::MenuItemTitleActionExit = "Exit";

//-----------------------------------------------------------------------------
MainMenu::MainMenu() {
}

//-----------------------------------------------------------------------------
void MainMenu::run() {
    char chbuff;
    int menuitem;
    while (true) {
        // Вывести пункты тестового меню
        _paintMenu();

        // Ожидать, пока пользователь выберет пункт меню
        cout << endl << "Enter menu item number and hit <Enter>: ";
        chbuff = getchar();

        menuitem = atoi(&chbuff);
        /* Отнимаем 1 от номера пункта меню, чтобы получить значение из перечисления
         * MainMenu::MainMenuActions */
        --menuitem;
        switch (menuitem) {
        case ActionAddNode:
            _menuActionAddNode();
            break;

        case ActionRemoveNode:
            _menuActionRemoveNode();
            break;

        case ActionPrintAllNodes:
            _menuActionPrintAllNodes();
            break;

        case ActionPrintNodesCount:
            _menuActionPrintNodesCount();
            break;

        case ActionTestIsTreeEmpty:
            _menuActionTestIsTreeEmpty();
            break;

        case ActionFindData:
            _menuActionFindData();
            break;

        case ActionClearTree:
            _menuActionClearTree();
            break;

        case ActionGetNodeMaxDepth:
            _menuActionGetNodeMaxDepth();
            break;

        case ActionDumpTreeStructure:
            _menuActionDumpTreeStructure();
            break;
        }
    }
}

//-----------------------------------------------------------------------------
/** Выводит на экран пункты меню с их номерами.
 *
 * Номера пунктов меню назначаются на основании числовых значений перечисления
 * MainMenu::MainMenuActions.
 */
void MainMenu::_paintMenu() {
    CLEAR_SCREEN();

    /* Элементы перечисления MainMenu::MainMenuActions нумеруются с 0,
     * поэтому прибавляем 1 перед выводом номера пункта, чтобы нумерация
     * в меню шла с 1. */

    // 'Add node' menu item
    cout << (ActionAddNode + 1) << ". " << MenuItemTitleActionAddNode << endl;

    // 'Remove node' menu item
    cout << (ActionRemoveNode + 1) << ". " << MenuItemTitleActionRemoveNode << endl;

    // 'Print all nodes' menu item
    cout << (ActionPrintAllNodes + 1) << ". " << MenuItemTitleActionPrintAllNodes << endl;

    // 'Print nodes count' menu item
    cout << (ActionPrintNodesCount + 1) << ". " << MenuItemTitleActionPrintNodesCount << endl;

    // 'Test if tree is empty' menu item
    cout << (ActionTestIsTreeEmpty + 1) << ". " << MenuItemTitleActionTestIsTreeEmpty << endl;

    // 'Find data' menu item
    cout << (ActionFindData + 1) << ". " << MenuItemTitleActionFindData << endl;

    // 'Clear tree' menu item
    cout << (ActionClearTree + 1) << ". " << MenuItemTitleActionClearTree << endl;

    // 'Find deepest node' menu item
    cout << (ActionGetNodeMaxDepth + 1) << ". " << MenuItemTitleActionGetNodeMaxDepth << endl;

    // 'Dump tree structure menu item'
    cout << (ActionDumpTreeStructure + 1) << ". " << MenuItemTitleActionDumpTreeStructure << endl;
}

//-----------------------------------------------------------------------------
void MainMenu::_menuActionAddNode() {
    CLEAR_SCREEN();
    cout << "Enter number(int): ";
    int key;
    cin >> key;
    if(key) {
        _tree_for_menu_test.insert(key, key);
    }
}

//-----------------------------------------------------------------------------
void MainMenu::_menuActionRemoveNode() {
    CLEAR_SCREEN();
    cout << "Enter number to remove(int): ";
    int key;
    cin >> key;
    _tree_for_menu_test.remove(key);
}

//-----------------------------------------------------------------------------
void MainMenu::_menuActionPrintAllNodes() {
    CLEAR_SCREEN();
    _tree_for_menu_test.print();

    PAUSE();
}



//-----------------------------------------------------------------------------
void MainMenu::_menuActionPrintNodesCount() {
    CLEAR_SCREEN();
    cout << _tree_for_menu_test.count() << " nodes found in tree." << endl;

    PAUSE();
}

//-----------------------------------------------------------------------------
void MainMenu::_menuActionTestIsTreeEmpty() {
    CLEAR_SCREEN();
    if (_tree_for_menu_test.isEmpty()) {
        cout << "Tree IS EMPTY" << endl;
    } else {
        cout << "Tree IS NOT EMPTY" << endl;
    }

    PAUSE();
}



//-----------------------------------------------------------------------------
void MainMenu::_menuActionFindData() {
    CLEAR_SCREEN();
    cout << "Enter number to find(int): ";
    int key;
    cin >> key;
    try {
        int value = _tree_for_menu_test.data(key);
        cout << "Key was found! Data: " << value << endl;
    }
    catch (BSTree<int, int>::Exceptions excpt) {
        cerr << "Exception!";
        switch (excpt) {
        case BSTree<int, int>::ExcptAccessToMissingKey:
            cerr << "Key " << key << " was not found.";
            break;
        }
        cerr << endl;
    }

    PAUSE();
}



//-----------------------------------------------------------------------------
void MainMenu::_menuActionClearTree() {
    CLEAR_SCREEN();
    _tree_for_menu_test.clear();
    cout << "Tree was cleared!";

    PAUSE();
}

//-----------------------------------------------------------------------------
void MainMenu::_menuActionGetNodeMaxDepth() {
    CLEAR_SCREEN();

    _tree_for_menu_test.dbgPrintMaxDepthInfo();

    PAUSE();
}

//-----------------------------------------------------------------------------
void MainMenu::_menuActionDumpTreeStructure() {
    CLEAR_SCREEN();

    _tree_for_menu_test.dbgDumpTreeStructure();

    PAUSE();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
