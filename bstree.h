#ifndef BSTREE_H
#define BSTREE_H


#include <iostream>
#include <stack>
using namespace std;

// Исключения, используемые классом
#define EXCPT_MISSING_KEY -1

template <class TKey, class TValue>
class BSTree {
private:

    /** Класс, представляющий узел дерева */
    class Node {
    public:
        Node(const TKey & key, const TValue & value)
        : _left_child(NULL),
        _right_child(NULL),
        _parent(NULL) {
            this->_key = key;
            this->_value = value;
        }

        //---------------------------------------------------------------------
        /** Возвращает ключ данного узла */
        TKey key() const {
            return _key;
        }

        //---------------------------------------------------------------------
        /** Присваивает новый ключ узлу */
        void setKey(const TKey & key) {
            _key = key;
        }

        //---------------------------------------------------------------------
        /** Возвращает значение данного узла */
        TValue value() const {
            return _value;
        }

        //---------------------------------------------------------------------
        /** Присваивает новое значение узлу */
        void setValue(const TValue & value) {
            _value = value;
        }

        //---------------------------------------------------------------------
        /** Возвращает указатель на корень правого поддерева */
        Node* rightChild() const {
            return _right_child;
        }

        //---------------------------------------------------------------------
        /** Устанавливает корень правого поддерева
         *
         * Если указатель child не равен NULL, производит проверку, не является
         * ли он уже одним из потомкков данного узла */
        void setRightChild(Node * child) {
            // Если производится вызов с параметром NULL, установить NULL-значение
            if(NULL == child) {
                unsetRightChild();
            }
            // Если узел child еще не является потомком данного узла
            else if (!hasChild(child)) {
                _right_child = child;
                if (child) {
                    child->setParent(this);
                }
            }
        }

        //---------------------------------------------------------------------
        /** Возвращает указатель на корень левого поддерева */
        Node* leftChild() const {
            return _left_child;
        }

        //---------------------------------------------------------------------
        /** Устанавливает корень левого поддерева
         *
         * Если указатель child не равен NULL, производит проверку, не является
         * ли он уже одним из потомкков данного узла */
        void setLeftChild(Node * child) {
            // Если производится вызов с параметром NULL, установить NULL-значение
            if (NULL == child) {
                unsetLeftChild();
            }
            // Если узел child еще не является потомком данного узла
            else if (!hasChild(child)) {
                _left_child = child;
                if (child) {
                    child->setParent(this);
                }
            }
        }

        //---------------------------------------------------------------------
        /** Обнуляет указатель на корень левого поддерева */
        void unsetLeftChild() {
            _left_child = NULL;
        }

        //---------------------------------------------------------------------
        /** Обнуляет указатель на корень правого поддерева */
        void unsetRightChild() {
            _right_child = NULL;
        }

        //---------------------------------------------------------------------
        /** Возвращает указатель на родительский узел */
        Node* parent() const {
            return _parent;
        }

        //---------------------------------------------------------------------
        /** Возвращает TRUE, если узел является левым потомком своего родителя */
        bool isLeftChild() const {
            return (parent() != NULL &&
                    parent()->leftChild() == this);
        }

        //---------------------------------------------------------------------
        /** Возвращает TRUE, если узел является правым потомком своего родителя */
        bool isRightChild() const {
            return (parent() != NULL &&
                    parent()->rightChild() == this);
        }

        //---------------------------------------------------------------------
        /** Устанавливает указатель на родительский узел */
        void setParent(Node* node) {
            _parent = node;
        }

        //---------------------------------------------------------------------
        /** Возвращает TRUE, если узел является корнем основного дерева, иначе - FALSE */
        bool isRoot() const {
            return parent() == NULL;
        }

        //---------------------------------------------------------------------
        /** Разрывает связь узла с потомком.
         *
         * Иными словами, метод обнуляет соответствующий указатель на узел child,
         * если он является корнем левого/правого поддерева данного узла */
        void unlinkChild(Node* child) {
            if (rightChild() == child) {
                setRightChild(NULL);
            }
            else if (leftChild() == child) {
                setLeftChild(NULL);
            }
        }

        //---------------------------------------------------------------------
        /** Замещает указатель на левого/правого потомка child указателем replacement, если он является одним из потомков данного узла
         *
         * @param child Узел, который в данный момент является корнем левого или правого поддерева текущего узла
         * @param replacement Узел, который будет помещен на место child */
        void replaceChild(Node* child, Node* replacement) {
            if (leftChild() == child) {
                setLeftChild(replacement);
            }
            else if(rightChild() == child) {
                setRightChild(replacement);
            }
        }

        //---------------------------------------------------------------------
        /** Возвращает TRUE, если указанный узел child является корнем левого/правого поддерева текущего узла */
        bool hasChild(Node* child) const {
            return ( (leftChild() == child) ||
                    (rightChild() == child) );
        }

        //---------------------------------------------------------------------
        /** Возвращает глубину, на которой находится узел в дереве */
        int level() const {
            Node* node_parent = this->parent();
            int lvl = 0;
            while (node_parent) {
                ++lvl;
                node_parent = node_parent->parent();
            }

            return lvl;
        }


    private:
        Node* _left_child;
        Node* _right_child;
        Node* _parent;
        TKey _key;
        TValue _value;



    };

    /** Корень дерева */
    Node* _root;

    /** Счетчик узлов - для оптимального вызова count().
     * Должен увеличивается/уменьшается при вставке/удалении каждого узла */
    int _cnt_nodes;

    //---------------------------------------------------------------------
    /** Возвращает указатель на узел с наименьщим значением ключа из всех узлов поддерева с корнем root
     *
     * Учитывая структуру двоичного дерева поиска и расположение младших ключей в левых ветках дерева,
     * метод просто спускается до самого конца, всё время выбирая левых потомков узлов и возвращает
     * указатель на последний найденный узел, который больше не имеет левого поддерева
     *
     * @param Указатель на корень поддерева, в котором осуществлять поиск */
    Node* _findNodeWithSmallestKey(Node* root) {
        // Спускаться до конца по левой ветке двоичного поддерева
        Node* node_next = root;
        while (node_next->leftChild()) {
            node_next = node_next->leftChild();
        }

        return node_next;
    }

    //---------------------------------------------------------------------
    /** Устанавливает новый корень дерева */
    void _setRootNode(Node* node) {
        _root = node;
        if (node) {
            node->setParent(NULL);
        }
    }

    //---------------------------------------------------------------------
    /** Производит удаление указанного узла из дерева с сохранением корректной структуры двоичного дерева поиска */
    void _removeNode(Node* node_to_remove) {
        if(node_to_remove) {
            /* Родитель удаляемого узла. Может иметь значение NULL, когда удаляемый узел является корнем
                     * основного дерева */
            // Если удаляемый узел не имеет родительского узла, он является корнем дерева
            Node* node_parent = node_to_remove->parent();
            bool has_left_child = (node_to_remove->leftChild() != NULL);
            bool has_right_child = (node_to_remove->rightChild() != NULL);
            bool has_single_child =
                    (has_left_child && !has_right_child) ||
                    (has_right_child && !has_left_child);
            bool has_both_children = (has_left_child && has_right_child);

            // Если узел имеет единственного потомка
            if (has_single_child) {
                Node* node_child_to_move = NULL;
                // Если единственный потомок удаляемого узла - левый
                if (has_left_child) {
                    node_child_to_move = node_to_remove->leftChild();
                    // Иначе единственный потомок удаляемого узла - правый
                } else {    // if (has_right_child)
                    node_child_to_move = node_to_remove->rightChild();
                }

                /* Заменить в родительском узле указатель на удаляемый узел
                         * указателем на этого единственного потомка */
                // Если удаляемый узел является корнем дерева
                if (node_to_remove->isRoot()) {
                    _setRootNode(node_child_to_move);
                }

                else {
                    node_parent->replaceChild(node_to_remove, node_child_to_move);
                }
            }

            // Иначе если узел имеет обоих потомков
            // Найти в правом поддереве узел с наименьшим ключом
            // и поместить его на место удаляемого.
            else if (has_both_children) {
                Node* node_replacement = _findNodeWithSmallestKey(node_to_remove->rightChild());
                /* Узел с наименьшим значением ключа не имеет левого потомка:
                 * однако он может иметь правое поддерево. Чтобы корректно
                 * отделить его от ветки дерева, необходимо заменить указатель
                 * на перемещаемый узел в родителе указателем на правого потомка перемещаемого узла.
                 * Если потомка нет, указатель будет обнулен (замещен значением NULL)
                 */
                node_replacement->parent()->replaceChild(node_replacement,
                                                         node_replacement->rightChild());
                // Помещаем узел на место удаляемого, связывая его с потомками
                node_replacement->setLeftChild(node_to_remove->leftChild());
                node_replacement->setRightChild(node_to_remove->rightChild());

                // Присоединим перемещенный узел к иерархии дерева выше
                // Если удаляемый узел является корнем дерева
                if (node_to_remove->isRoot()) {
                    // Установить новый корень дерева
                    _setRootNode(node_replacement);
                }
                // Иначе связать родительский узел удаляемого узла с новым потомком
                else {
                    node_parent->replaceChild(node_to_remove, node_replacement);
                }
            }

            // Иначе узел не имеет потомков
            else {
                // Если удаляемый узел является корнем дерева
                if (node_to_remove->isRoot()) {
                    // Обнулить указатель на корень
                    _setRootNode(NULL);
                    // Иначе обнулить в родительском узле указатель на удаляемый узел
                } else {
                    node_parent->unlinkChild(node_to_remove);
                }
            }

            // После внесения необходимых изменений в структуру дерева узел уничтожается
            delete node_to_remove;

            // Уменьшить счетчик узлов
            _decrementCachedNodesCount();
        }
    }

    //---------------------------------------------------------------------
    /** Возвращает указатель на корень дерева */
    Node* _rootNode() const {
        return _root;
    }

    //---------------------------------------------------------------------
    /** Ищет узел с заданным ключом в дереве
     *
     * @param key Ключ для поиска
     */
    Node* _findNode(const TKey & key) const {
        Node* node_next = _root;
        while (node_next) {
            // Если узел с ключом найден, прекратить поиск
            if (node_next->key() == key) {
                break;
            }

            // Продолжить поиск узла ниже в подходящей ветке
            if (node_next->key() < key) {
                node_next = node_next->rightChild();
            }
            else {
                node_next = node_next->leftChild();
            }
        }

        /* Вернуть найденный узел.
         * Если он не найден или дерево пусто, будет возвращено значение NULL */
        return node_next;
    }


    //---------------------------------------------------------------------
    /** Возвращает число узлов в поддереве с корнем root */
    int _countNodes(Node* root) const {
        if(!root) {
            return 0;
        }

        int left_children_count = _countNodes(root->leftChild());
        int right_children_count = _countNodes(root->rightChild());

        /* Общее количество узлов складывается из узлов в левом и правом поддеревьях,
         * а также учитывается сам корневой узел */
        return left_children_count + right_children_count + 1;
    }

    ///////////////////////////////////////////////////////////////////////
    struct node_descriptor {
        Node* node;
        int level;

        node_descriptor()
            : node(NULL),
              level(0)
        {  }

        //---------------------------------------------------------------------
        bool isValid() const {
            return (NULL != node);
        }
    };
    ///////////////////////////////////////////////////////////////////////
    //---------------------------------------------------------------------
    node_descriptor _getNodeMaxDepth() {
        node_descriptor desc;
        if(!isEmpty()) {
            iterator iter(this);
            Node* node = NULL;
            while (!iter.atEnd()) {
                node = iter._lastSeenNode();
                int node_level = node->level();
                if (desc.level < node_level) {
                    desc.node = node;
                    desc.level = node_level;
                }
                iter.next();
            }
        }

        return desc;
    }

    //---------------------------------------------------------------------
    int _cachedNodesCount() const {
        return _cnt_nodes;
    }

    //---------------------------------------------------------------------
    void _incrementCachedNodesCount() {
        ++_cnt_nodes;
    }

    //---------------------------------------------------------------------
    void _decrementCachedNodesCount() {
        --_cnt_nodes;
    }

    //---------------------------------------------------------------------
    void _resetCachedNodesCount() {
        _cnt_nodes = 0;
    }

    //---------------------------------------------------------------------

public:
    enum Exceptions {
        ExcptAccessToMissingKey
    };

    BSTree()
        : _root(NULL),
          _cnt_nodes(0)
    {
    }

    //---------------------------------------------------------------------
    ~BSTree() {
        clear();
    }

    //---------------------------------------------------------------------
    /** Возвращает TRUE, если дерево не содержит узлов, иначе - FALSE */
    bool isEmpty() const {
        return (NULL == _root);
    }

    //---------------------------------------------------------------------
    /** Производит вставку в дерево нового узла, создав его и присвоив ему указанные ключ и значение
     *
     * Если узел с заданным ключом уже существует, присваивает ему указанное значение */
    void insert(const TKey & key, const TValue & value) {
        Node* node_existing = NULL;
        /* Если указанный ключ уже присутствует в дереве */
        if ( (node_existing = _findNode(key)) != NULL ) {
            node_existing->setValue(value);
            /* Иначе создаем новый узел и вставляем его */
        } else {
            Node* node_to_insert = new Node(key, value);
            node_to_insert->setKey(key);
            node_to_insert->setValue(value);
            // Если в дереве еще нет узлов, новый узел станет корнем
            if (isEmpty()) {
                _root = node_to_insert;
            }
            else {
                /* Найти позицию для вставки новоло узла:
             * узлы двоичного дерева поиска упорядочены так, что ключ любого
             * родительского узла больше ключа любого узла-потомка из левой ветки
             * и меньше ключа любого узла-потомка из правой ветки. */
                Node* next_node = _root;
                Node* parent = NULL;
                while (next_node) {
                    parent = next_node;
                    if (next_node->key() < node_to_insert->key()) {
                        next_node = next_node->rightChild();
                    }
                    else {
                        next_node = next_node->leftChild();
                    }
                }

                if (node_to_insert->key() < parent->key()) {
                    parent->setLeftChild(node_to_insert);
                }
                else {
                    parent->setRightChild(node_to_insert);
                }
            }

            /* Увеличить счетчик узлов после того, как была произведена вставка нового узла */
            _incrementCachedNodesCount();
        }
    }

    //---------------------------------------------------------------------
    /** Возвращает TRUE, если дерево содержит узел с указанным ключом */
    bool hasKey(const TKey & key) {
        Node* node = _findNode(key, _rootNode());
        return (NULL != node);
    }

    //---------------------------------------------------------------------
    /** Удаляет из дерева узел с указанным ключом, если таковой имеется */
    void remove(TKey key) {
            // Найти элемент с заданным ключом
        Node* node_to_remove = _findNode(key);
        // Если узел найден
        if (node_to_remove) {
            _removeNode(node_to_remove);
        }
    }

    //---------------------------------------------------------------------
    /** Возвращает количество узлов в дереве */
    int count() const {
        /* Вернуть текущее значение счетчика */
        return _cachedNodesCount();
    }

    //---------------------------------------------------------------------
    /** Удаляет все узлы дерева */
    void clear() {
        while (_root) {
            _removeNode(_root);
        }

        /* Обнулить счетчик узлов */
        _resetCachedNodesCount();
    }

    //---------------------------------------------------------------------
    /** Обходит узлы дерева с помощью итератора, выводя их содержимое */
    void print() {
        if (!isEmpty()) {
            iterator iter(this);
            while(!iter.atEnd()) {
                cout << iter.key() << ": " << iter.value() << endl;
                iter.next();
            };
        }
    }

    //---------------------------------------------------------------------
    /** Возвращает данные, ассоциированные с заданнымм ключом
     *
     * Выбрасывает исключение, если данные для ключа отсутствуют
     * (ключ неинициализирован) */
    TValue data(TKey key) {
        Node* node = _findNode(key);
        /* Если ключ неинициализирован */
        if (!node) {
            /* Выбросить исключение */
            throw ExcptAccessToMissingKey;
        }

        /* Вернуть данные */
        return node->value();
    }

    //---------------------------------------------------------------------
    /** "Отдадочный" метод, выводящий на экран информацию о максимальной глубине дерева */
    void dbgPrintMaxDepthInfo() {
        node_descriptor ds = _getNodeMaxDepth();
        if (ds.isValid()) {
            cout << "Max tree depth = " << ds.level << endl;
            cout << "Deepest node is ['"
                 << ds.node->key()
                 << "', '"
                 << ds.node->value()
                 << "']"
                 << endl;
        }
        else {
            cout << "Tree is empty!" << endl;
        }
    }

    //---------------------------------------------------------------------
    /** "Отладочный" метод, выводщий на экран структуру дерева */
    void dbgDumpTreeStructure() {
        if(!isEmpty()) {
            /* Для вывода структуры дерева в консоли удобнее
             * использовать префиксный порядок обхода */

            Node* node = _rootNode();
            stack< Node* > st;
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
        } else {
            cout << "Tree is empty!" << endl;
        }
    }

    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------

    ///////////////////////////////////////////////////////////////////////
    class iterator {
        BSTree<TKey, TValue>* _tree;
        Node* _node_current_ptr;    /// Внутренний указатель итератора, с помощью которого производится обход дерева
        Node* _node_last_seen;  /// Текущий узел с точки зрения клиента/кода, использующего итератор
        std::stack<Node*> _st_nodes_ahead;

        /** Устанавливает итератор в начальное состояние, когда тот
         * указывает на крайнего левого потомка в левом поддереве */
        void _init() {
            _setCurrentNodePointer(_tree->_rootNode());
            next();
        }

        //---------------------------------------------------------------------
        Node* _currentNodePointer() const {
            return _node_current_ptr;
        }

        //---------------------------------------------------------------------
        void _setCurrentNodePointer(Node* node) {
            _node_current_ptr = node;
        }

        //---------------------------------------------------------------------
        Node* _lastSeenNode() const {
            return _node_last_seen;
        }

        //---------------------------------------------------------------------
        void _setLastSeenNode(Node* node) {
            _node_last_seen = node;
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------


    public:
        iterator(BSTree<TKey, TValue>* tree)
            : _tree(tree),
              _node_current_ptr(NULL),
              _node_last_seen(NULL) {
            _init();
        }

        //---------------------------------------------------------------------
        /** Перемещает итератор к следующему узлу, если он доступен
         *
         * Итератор будет продвигаться вперед, пока не достигнет последнего
         * узла, после чего вызов next() переведет итератор в состояние,
         * когда он "указывает в позицию за последним элементом". В этом
         * состоянии метод atEnd() будет возвращать значение TRUE.
         * Это позволяет клиентскому коду объявлять конструкции вида
         *
         * while (!iter.atEnd()) { [Proceed elements...] }
         *
         * @see atEnd()
         */
        void next() {
            if (!atEnd()) {
                if (hasNext()) {
                    // Спускаться по левой ветви до конца
                    while (_currentNodePointer() != NULL) {
                        _st_nodes_ahead.push(_currentNodePointer());
                        _setCurrentNodePointer(_currentNodePointer()->leftChild());
                    }

                    Node* node = NULL;
                    if (!_st_nodes_ahead.empty()) {
                        // Снять со стека следующий узел
                        _setCurrentNodePointer(_st_nodes_ahead.top());
                        _st_nodes_ahead.pop();

                        // Отметить его как текущий для клиента
                        node = _currentNodePointer();
                        _setLastSeenNode(node);

                        // Переместить внутренний указатель итератора далее для обхода правого поддерева
                        _setCurrentNodePointer(_currentNodePointer()->rightChild());
                    }
                } else {
                    _setLastSeenNode(NULL);
                }
            }
        }
        //---------------------------------------------------------------------
        bool atEnd() const {
            return (_lastSeenNode() == NULL) &&
                    !hasNext();

        }

        //---------------------------------------------------------------------
        /** Возвращает TRUE, если доступ к итератору корректен, иначе - FALSE
         *
         * Метод не является индикатором конца итератора, то есть конструкция
         *
         * while (iter.isValid()) { ... }
         *
         * на корректном/непустом дереве никогда не завершится */
        bool isValid() const {
            return _lastSeenNode() != NULL;
        }

        //---------------------------------------------------------------------
        /** Возвращает TRUE, если еще остались узлы для обхода */
        bool hasNext() const {
            return (!_st_nodes_ahead.empty() || (_currentNodePointer() != NULL));
        }

        //---------------------------------------------------------------------
        TValue operator*() {
            return value();
        }

        //---------------------------------------------------------------------
        TKey key() const {
            return _lastSeenNode()->key();
        }

        //---------------------------------------------------------------------
        TValue value() const {
            return _lastSeenNode()->value();
        }

        //---------------------------------------------------------------------
        int nodeDepth() const {
            int depth = -1;
            depth = _lastSeenNode()->level();

            return depth;
        }

        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        //---------------------------------------------------------------------
        friend class BSTree;

    };
    friend class iterator;

    friend class TestBSTree;
};


#endif // BSTREE_H
