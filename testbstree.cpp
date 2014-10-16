#include "testbstree.h"

// Инициализация констант класса
const string TestBSTree::MenuItemTitleActionAddNode = "Add Node";
const string TestBSTree::MenuItemTitleActionRemoveNode = "Remove Node";
const string TestBSTree::MenuItemTitleActionPrintAllNodes = "Print All Nodes";
const string TestBSTree::MenuItemTitleActionPrintNodesCount = "Print Nodes Count";
const string TestBSTree::MenuItemTitleActionTestIsTreeEmpty = "Test If Tree Is Empty";
const string TestBSTree::MenuItemTitleActionFindData = "Find Data By Key";
const string TestBSTree::MenuItemTitleActionClearTree = "Clear Tree";
const string TestBSTree::MenuItemTitleActionGetNodeMaxDepth = "Find Deepest Node";
const string TestBSTree::MenuItemTitleActionDumpTreeStructure = "Dump Tree Structure";
const string TestBSTree::MenuItemTitleActionExit = "Exit";

//-----------------------------------------------------------------------------
TestBSTree::TestBSTree() {
}

//-----------------------------------------------------------------------------
bool TestBSTree::testInsert() {
    cout << "Running insert() test...";
    int key_3 = 3;
    int val_3 = key_3;

    BSTree<int, int> tree;
    tree.insert(key_3, val_3);
    BSTree<int, int>::Node* root_node = tree._findNode(key_3);
    if (!(root_node && root_node->key() == key_3)) {
        _notifyTestFailed();
        return false;
    }

    int key_2 = 2;
    int val_2 = key_2;
    tree.insert(key_2, val_2);
    BSTree<int, int>::Node* node_2 = tree._findNode(key_2);
    /* Проверить, найден ли node_2, имеет ли его ключ верное значение и
         * находится ли он в верной позиции (является левым потомком корня) */
    if (  ! ( node_2 &&
              node_2->key() == key_2 &&
              (root_node->leftChild() == node_2) )  ) {
        _notifyTestFailed();
        return false;
    }

    int key_5 = 5;
    int val_5 = key_5;
    tree.insert(key_5, val_5);
    BSTree<int, int>::Node* node_5 = tree._findNode(key_5);
    /* Проверить, найден ли node_5, имеет ли его ключ верное значение и
         * находится ли он в верной позиции (является правым потомком корня) */
    if (  ! ( node_5 &&
              node_5->key() == key_5 &&
              (root_node->rightChild() == node_5) )  ) {
        _notifyTestFailed();
        return false;
    }

    _testPassed();
    return true;
}

//-----------------------------------------------------------------------------
bool TestBSTree::testRemove() {
    cout << "Running remove() test...";

    /* Для тестирования операций удаления необходимо проверить следующие случаи:
     * 1. Когда удаляемый узел - корень дерева:
     *      а) Когда удаляемый узел не имеет потомков
     *      б) Когда удаляемый узел имеет единственного левого или правого потомка
     *      в) Когда удаляемый узел имеет обоих потомков
     * * 2. Когда удаляемый узел не является корнем дерева:
     *      а) Когда удаляемый узел не имеет потомков
     *          а1. Когда удаляемый узел не имеет потомков и сам является правым потомком
     *          а1. Когда удаляемый узел не имеет потомков и сам является левым потомком
     *      б) Когда удаляемый узел имеет единственного левого или правого потомка
     *          б1. Узел имеет единственного правого потомка и сам является правым потомком
     *          б2. Узел имеет единственного левого потомка и сам является правым потомком
     *          б3. Узел имеет единственного правого потомка и сам является левым потомком
     *          б4. Узел имеет единственного левого потомка и сам является левым потомком
     *      в) Когда удаляемый узел имеет обоих потомков
     *          в1. Узел имеет обоих потомков и сам является левым потомком
     *          в2. Узел имеет обоих потомков и сам является правым потомком
  */

    /* Дерево 1а:
     * (x)
     * 
     *
     * Дерево 1б1:
     * (x)
     *   \
     *   (b)
     * Условия:
     * x < b
     *
     *
     * Дерево 1б2:
     *  (x)
     *  /
     *(a)
     * Условия:
     * a < x
     *
     *
     * Дерево 1в:
     *  (x)
     *  /  \
     *(a)  (b)
     * Условия:
     * a < x
     * x < b
     *
     * Дерево 2а1:
     *   (c)
     *     \
     *     (x)
     * Условия:
     * c < x
     *
     * Дерево 2а2:
     *   (b)
     *   /
     * (x)
     * Условия:
     * x < b
     *
     * Дерево 2б1:
     *   (c)
     *     \
     *     (x)
     *       \
     *       (b)
     * Условия:
     * c < x
     * x < b
     *
     * Дерево 2б2:
     *   (c)
     *     \
     *     (x)
     *     /
     *   (a)
     * Условия:
     * c < x
     * a < x
     * c < a
     *
     * Дерево 2б3:
     *
     *     (b)
     *     /
     *   (x)
     *     \
     *     (d)
     * Условия:
     * x < b
     * x < d
     * d < b
     *
     * Дерево 2б4:
     *
     *     (b)
     *     /
     *   (x)
     *   /
     * (a)
     * Условия:
     * x < b
     * a < x
     *
     * Дерево 2в1:
     *     (b)
     *     /
     *   (x)
     *   / \
     * (a) (d)
     * Условия:
     * x < b
     * a < x
     * x < d
     * d < b
     *
     * Дерево 2в2:
     *   (c)
     *     \
     *     (x)
     *     / \
     *   (a) (b)
     * Условия:
     * c < x
     * a < x
     * c < a
     * x < b
     *
     * */

    /* Узел с ключом x - узел, подлежащий удалению.
     * Значения ключей x,a,b,c должны выбираться так, чтобы  выполнялись условия:
     * x < b
     * a < x
     * c < x
     * c < a
     * x < d
     * d < b
     * или в компактной записи
     * c < a < x < d < b
     */
    int c = 10;
    int a = 20;
    int x = 30;
    int d = 40;
    int b = 50;

    /* Дерево 1а:
     * (x)       (NULL)
     *      =>
     */
    BSTree<int, int> tree_1a;
    tree_1a.insert(x, x);
    tree_1a.remove(x);
    if ( !tree_1a.isEmpty() ) {
        _notifyTestFailed("tree.1a not passed the test");
        return false;
    }

    /* Дерево 1б1:
     * (x)           (b)
     *   \     =>
     *   (b)
     */
    BSTree<int, int> tree_1b1;
    tree_1b1.insert(x, x);
    tree_1b1.insert(b, b);
    tree_1b1.remove(x);
    bool is_node_x_not_found_in_1b1 = (tree_1b1._findNode(x) == NULL);
    bool is_node_b_new_root_of_1b1 = (tree_1b1._findNode(b) == tree_1b1._rootNode());
    if ( ! (is_node_b_new_root_of_1b1 && is_node_x_not_found_in_1b1)   ) {
        _notifyTestFailed("tree.1b1 not passed the test");
        return false;
    }

    /* Дерево 1б2:
     *  (x)        (a)
     *  /     =>
     *(a)
     */
    BSTree<int, int> tree_1b2;
    tree_1b2.insert(x, x);
    tree_1b2.insert(a, a);
    tree_1b2.remove(x);
    bool is_node_x_not_found_in_1b2 = (tree_1b2._findNode(x) == NULL);
    bool is_node_a_new_root_of_1b2 = (tree_1b2._findNode(a) == tree_1b2._rootNode());
    if ( ! (is_node_x_not_found_in_1b2 && is_node_a_new_root_of_1b2)  ) {
        _notifyTestFailed("tree.1b2 not passed the test");
        return false;
    }


    /* Дерево 1в:
     *  (x)           (b)
     *  /  \    =>    /
     *(a)  (b)      (a)
     */
    BSTree<int, int> tree_1c;
    tree_1c.insert(x, x);
    tree_1c.insert(a, a);
    tree_1c.insert(b, b);
    tree_1c.remove(x);
    bool is_node_x_not_found_in_1c = (tree_1c._findNode(x) == NULL);
    bool is_node_b_new_root_of_1c = (tree_1c._findNode(b) == tree_1c._rootNode());
    if ( ! (is_node_x_not_found_in_1c && is_node_b_new_root_of_1c)  ) {
        _notifyTestFailed("tree.1c not passed the test");
        return false;
    }


    /* Дерево 2а1:
     *   (c)           (c)
     *     \     =>
     *     (x)
     */
    BSTree<int, int> tree_2a1;
    tree_2a1.insert(c, c);
    tree_2a1.insert(x, x);
    tree_2a1.remove(x);
    bool is_node_x_not_found_in_2a1 = (tree_2a1._findNode(x) == NULL);
    if ( ! is_node_x_not_found_in_2a1 ) {
        _notifyTestFailed("tree.2a1 not passed the test");
        return false;
    }

    /* Дерево 2а2:
     *   (b)         (b)
     *   /      =>
     * (x)
     */
    BSTree<int, int> tree_2a2;
    tree_2a2.insert(b, b);
    tree_2a2.insert(x, x);
    tree_2a2.remove(x);
    bool is_node_x_not_found_in_2a2 = (tree_2a2._findNode(x) == NULL);
    if ( ! is_node_x_not_found_in_2a2 ) {
        _notifyTestFailed("tree.2a2 not passed the test");
        return false;
    }

    /* Дерево 2б1:
     *   (c)           (c)
     *     \             \
     *     (x)    =>     (b)
     *       \
     *       (b)
     */
    BSTree<int, int> tree_2b1;
    tree_2b1.insert(c, c);
    tree_2b1.insert(x, x);
    tree_2b1.insert(b, b);
    tree_2b1.remove(x);
    bool is_node_x_not_found_in_2b1 = (tree_2b1._findNode(x) == NULL);
    BSTree<int, int>::Node* node_c_in_2b1 = tree_2b1._findNode(c);
    bool is_node_c_root_in_2b1 = (node_c_in_2b1 &&
                                  node_c_in_2b1->isRoot());
    bool is_node_b_right_child_of_c_in_2b1 = (node_c_in_2b1->rightChild() &&
                                              node_c_in_2b1->rightChild()->key() == b);
    if ( ! (is_node_x_not_found_in_2b1 &&
            is_node_c_root_in_2b1 &&
            is_node_b_right_child_of_c_in_2b1) ) {
        _notifyTestFailed("tree.2b1 not passed the test");
        return false;
    }

    /* Дерево 2б2:
        *   (c)         (c)
        *     \           \
        *     (x)   =>    (a)
        *     /
        *   (a)
        */
    BSTree<int, int> tree_2b2;
    tree_2b2.insert(c, c);
    tree_2b2.insert(x, x);
    BSTree<int, int>::Node* node_x_in_2b2 = tree_2b2._findNode(x);
    BSTree<int, int>::Node* node_a_in_2b2 = new BSTree<int, int>::Node(a, a);
    node_x_in_2b2->setLeftChild(node_a_in_2b2);
    tree_2b2.remove(x);
    bool is_node_x_not_found_in_2b2 = (tree_2b2._findNode(x) == NULL);
    BSTree<int, int>::Node* node_c_in_2b2 = tree_2b2._findNode(c);
    bool is_node_c_root_in_2b2 = (node_c_in_2b2 &&
                                  node_c_in_2b2->isRoot());
    bool is_node_a_right_child_of_c_in_2b2 = (node_c_in_2b2->rightChild() &&
                                              node_c_in_2b2->rightChild() == node_a_in_2b2);
    if ( ! (is_node_x_not_found_in_2b2 &&
            is_node_c_root_in_2b2 &&
            is_node_a_right_child_of_c_in_2b2) ) {
        _notifyTestFailed("tree.2b2 not passed the test");
        return false;
    }

    /* Дерево 2б3:
     *
     *     (b)          (b)
     *     /            /
     *   (x)      =>  (d)
     *     \
     *     (d)
     */
    BSTree<int, int> tree_2b3;
    tree_2b3.insert(b, b);
    tree_2b3.insert(x, x);
    tree_2b3.insert(d, d);
    tree_2b3.remove(x);
    bool is_node_x_not_found_in_2b3 = (tree_2b3._findNode(x) == NULL);
    BSTree<int, int>::Node* node_b_in_2b3 = tree_2b3._findNode(b);
    bool is_node_b_root_in_2b3 = (node_b_in_2b3 &&
                                  tree_2b3._rootNode() == node_b_in_2b3);
    BSTree<int, int>::Node* node_d_in_2b3 = tree_2b3._findNode(d);
    bool is_node_d_left_child_of_b_in_2b3 = (node_d_in_2b3 &&
                                             node_b_in_2b3->leftChild() == node_d_in_2b3);
    if ( ! (is_node_x_not_found_in_2b3 &&
            is_node_b_root_in_2b3 &&
            is_node_d_left_child_of_b_in_2b3) ) {
        _notifyTestFailed("tree.2b3 not passed the test");
        return false;
    }


    /* Дерево 2б4:
     *
     *     (b)          (b)
     *     /            /
     *   (x)    =>    (a)
     *   /
     * (a)
     */
    BSTree<int, int> tree_2b4;
    tree_2b4.insert(b, b);
    tree_2b4.insert(x, x);
    tree_2b4.insert(a, a);
    tree_2b4.remove(x);
    bool is_node_x_not_found_in_2b4 = (tree_2b4._findNode(x) == NULL);
    BSTree<int, int>::Node* node_b_in_2b4 = tree_2b4._findNode(b);
    bool is_node_b_root_in_2b4 = (node_b_in_2b4 &&
                                  tree_2b4._rootNode() == node_b_in_2b4);
    BSTree<int, int>::Node* node_a_in_2b4 = tree_2b4._findNode(a);
    bool is_node_a_left_child_of_b_in_2b4 = (node_a_in_2b4 &&
                                             node_b_in_2b4->leftChild() == node_a_in_2b4);
    if ( ! (is_node_x_not_found_in_2b4 &&
            is_node_b_root_in_2b4 &&
            is_node_a_left_child_of_b_in_2b4) ) {
        _notifyTestFailed("tree.2b4 not passed the test");
        return false;
    }


    /* Дерево 2в1:
     *     (b)              (b)
     *     /                /
     *   (x)        =>    (d)
     *   / \              /
     * (a) (d)          (a)
     */
    // Подготовить дерево
    BSTree<int, int> tree_2c1;
    tree_2c1.insert(b, b);
    tree_2c1.insert(x, x);
    tree_2c1.insert(a, a);
    tree_2c1.insert(d, d);
    // Удалить узел x
    tree_2c1.remove(x);
    // Проверить корректность удаления
    BSTree<int, int>::Node* node_b_in_2c1 = tree_2c1._findNode(b);
    bool is_node_b_root_in_2c1 = (tree_2c1._rootNode() &&
                                  tree_2c1._rootNode() == node_b_in_2c1);
    BSTree<int, int>::Node* node_d_in_2c1 = tree_2c1._findNode(d);
    bool is_node_d_left_child_of_b_in_2c1 = (node_d_in_2c1 &&
                                             node_b_in_2c1->leftChild() == node_d_in_2c1);
    BSTree<int, int>::Node* node_a_in_2c1 = tree_2c1._findNode(a);
    bool is_node_a_left_child_of_d_in_2c1 = (node_a_in_2c1 &&
                                             node_d_in_2c1->leftChild() == node_a_in_2c1);
    if ( ! (is_node_b_root_in_2c1 &&
            is_node_d_left_child_of_b_in_2c1 &&
            is_node_a_left_child_of_d_in_2c1) ) {
        _notifyTestFailed("tree.2c1 not passed the test");
        return false;
    }


    /* Дерево 2в2:
    *   (c)                 (c)
    *     \                    \
    *     (x)       =>         (b)
    *     / \                  /
    *   (a) (b)              (a)
    */
    // Подготовить дерево
    BSTree<int, int> tree_2c2;
    tree_2c2.insert(c, c);
    tree_2c2.insert(x, x);
    tree_2c2.insert(a, a);
    tree_2c2.insert(b, b);
    BSTree<int, int>::Node* node_x_in_2c2 = tree_2c2._findNode(x);
    node_x_in_2c2->setLeftChild(new BSTree<int, int>::Node(a, a));
    node_x_in_2c2->setRightChild(new BSTree<int, int>::Node(b, b));
    tree_2c2.remove(x);
    BSTree<int, int>::Node* node_c_in_2c2 = tree_2c2._findNode(c);
    bool is_node_c_root_in_2c2 = (node_c_in_2c2 &&
                                  tree_2c2._rootNode() == node_c_in_2c2);
    BSTree<int, int>::Node* node_b_in_2c2 = tree_2c2._findNode(b);
    bool is_node_b_right_child_of_c_in_2c2 = (node_b_in_2c2 &&
                                              node_c_in_2c2->rightChild() == node_b_in_2c2);
    BSTree<int, int>::Node* node_a_in_2c2 = tree_2c2._findNode(a);
    bool is_node_a_left_chils_of_b_in_2c2 = (node_a_in_2c2 &&
                                             node_b_in_2c2->leftChild() == node_a_in_2c2);
    if (! (is_node_c_root_in_2c2 &&
           is_node_b_right_child_of_c_in_2c2 &&
           is_node_a_left_chils_of_b_in_2c2) ) {
        _notifyTestFailed("tree.2c2 not passed the test");
        return false;
    }

    _testPassed();
    return true;
}

//-----------------------------------------------------------------------------
bool TestBSTree::testCount() {
    cout << "Running count() test...";

    BSTree<int, int> tree;
    int nodes_count = 20;
    for (int i = 0; i < nodes_count; ++i) {
        tree.insert(i, i);
    }

    if (tree.count() != nodes_count) {
        _notifyTestFailed();
        return false;
    }

    _testPassed();
    return true;
}

//-----------------------------------------------------------------------------
bool TestBSTree::testClear() {
    cout << "Running clear() test...";

    BSTree<int, int> tree;
    int nodes_count = 20;
    for (int i = 0; i < nodes_count; ++i) {
        tree.insert(i, i);
    }

    tree.clear();
    if (tree.count()) {
        _notifyTestFailed();
        return false;
    }

    _testPassed();
    return true;
}

//-----------------------------------------------------------------------------
bool TestBSTree::testIterator() {
    cout << "Running interator test..." << endl;

    BSTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);
    tree.insert(5, 5);

    BSTree<int, int>::iterator iter(&tree);
    while (iter.isValid()) {
        cout << " " << (*iter);
        iter.next();
    }
    cout << endl;
    _testPassed();

    return true;
}

//-----------------------------------------------------------------------------
bool TestBSTree::testMaxDepth() {
    cout << "Running MaxDepth test...";

    BSTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);
    tree.insert(5, 5);

    BSTree<int, int>::node_descriptor node_deepest_ds = tree._getNodeMaxDepth();
    cout << "maxDepth: " << node_deepest_ds.level << endl;
    cout << "key: " << node_deepest_ds.node->key() << endl;

    _testPassed();
    return true;
}

//-----------------------------------------------------------------------------
void TestBSTree::runMainMenu() {
    char chbuff;
    int menuitem;
    while (true) {
        // Вывести пункты тестового меню
        _paintMainMenu();

        // Ожидать, пока пользователь выберет пункт меню
        cout << endl << "Enter menu item number and hit <Enter>: ";
        chbuff = getchar();

        menuitem = atoi(&chbuff);
        /* Отнимаем 1 от номера пункта меню, чтобы получить значение из перечисления
         * TestBSTree::MainMenuActions */
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

//        case ActionExit:
//            exit(0);
//            break;
        }
    }

}

//-----------------------------------------------------------------------------
/** Выводит на экран пункты меню с их номерами.
 *
 * Номера пунктов меню назначаются на основании числовых значений перечисления
 * TestBSTree::MainMenuActions.
 */
void TestBSTree::_paintMainMenu() {
    CLEAR_SCREEN();

    /* Элементы перечисления TestBSTree::MainMenuActions нумеруются с 0,
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

    // 'Exit' menu item
//    cout << (ActionExit + 1) << ". " << MenuItemTitleActionExit << endl;
}

//-----------------------------------------------------------------------------
void TestBSTree::_menuActionAddNode() {
    CLEAR_SCREEN();
    cout << "Enter number(int): ";
    int key;
    cin >> key;
    if(key) {
        _tree_for_menu_test.insert(key, key);
    }
}



//-----------------------------------------------------------------------------
void TestBSTree::_menuActionRemoveNode() {
    CLEAR_SCREEN();
    cout << "Enter number to remove(int): ";
    int key;
    cin >> key;
    _tree_for_menu_test.remove(key);
}

//-----------------------------------------------------------------------------
void TestBSTree::_menuActionPrintAllNodes() {
    CLEAR_SCREEN();
    _tree_for_menu_test.print();

    PAUSE();
}



//-----------------------------------------------------------------------------
void TestBSTree::_menuActionPrintNodesCount() {
    CLEAR_SCREEN();
    cout << _tree_for_menu_test.count() << " nodes found in tree." << endl;

    PAUSE();
}

//-----------------------------------------------------------------------------
void TestBSTree::_menuActionTestIsTreeEmpty() {
    CLEAR_SCREEN();
    if (_tree_for_menu_test.isEmpty()) {
        cout << "Tree IS EMPTY" << endl;
    } else {
        cout << "Tree IS NOT EMPTY" << endl;
    }

    PAUSE();
}



//-----------------------------------------------------------------------------
void TestBSTree::_menuActionFindData() {
    CLEAR_SCREEN();
    cout << "Enter number to find(int): ";
    int key;
    cin >> key;
    BSTree<int, int>::Node* node = _tree_for_menu_test._findNode(key);
    if (node) {
        cout << "Key was found! Data: " << node->value() << endl;
    } else {
        cout << "Key was not found!" << endl;
    }

    PAUSE();
}



//-----------------------------------------------------------------------------
void TestBSTree::_menuActionClearTree() {
    CLEAR_SCREEN();
    _tree_for_menu_test.clear();
    cout << "Tree was cleared!";

    PAUSE();
}

//-----------------------------------------------------------------------------
void TestBSTree::_menuActionGetNodeMaxDepth() {
    CLEAR_SCREEN();
    BSTree<int, int>::node_descriptor ds = _tree_for_menu_test._getNodeMaxDepth();
    if (ds.isValid()) {
        cout << "Node found! Depth = " << ds.level << ", data = " << ds.node->value() << endl;
    } else {
        cout << "Node was not found! (Maybe tree is empty?)" << endl;
    }

    PAUSE();
}

//-----------------------------------------------------------------------------
void TestBSTree::_menuActionDumpTreeStructure() {
    CLEAR_SCREEN();

    if(!_tree_for_menu_test.isEmpty()) {
        /* Для вывода структуры дерева в консоли удобнее
         * использовать префиксный порядок обхода */

        BSTree<int, int>::Node* node = _tree_for_menu_test._rootNode();
        stack< BSTree<int, int>::Node* > st;
        while (!st.empty() || node != NULL) {
            if (NULL != node) {
                int depth = node->level();
                if (0 < depth) {
                    cout << string(depth-1, '|');
                    char tip = ' ';
                    if (node->isLeftChild()) {
                        tip = 195;
                    } else {
                        tip = 192;
                    }
                    cout << tip;
                }
                cout << node->key();
                if (node->isLeftChild()) {
                    cout << " (LEFT CHILD)";
                } else if (node->isRightChild()) {
                    cout << " (RIGHT CHILD)";
                }

                cout << endl;

                if (node->rightChild()) {
                    st.push(node->rightChild());
                }
                node = node->leftChild();
            } else {
                    node = st.top();
                    st.pop();
                }
            }
//            depth = iter.nodeDepth();
//            cout << string(depth, '|')
//                 << (char) 195
//                 << " "
//                 << iter.key()
//                 << endl;

    } else {
        cout << "Tree is empty!" << endl;
    }

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
