#ifndef BSTREE_H
#define BSTREE_H


#include <iostream>
using namespace std;

template <class TKey, class TValue>
class BSTree {
private:

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
        TKey key() const {
            return _key;
        }

        //---------------------------------------------------------------------
        void setKey(const TKey & key) {
            _key = key;
        }

        //---------------------------------------------------------------------
        TValue value() const {
            return _value;
        }

        //---------------------------------------------------------------------
        void setValue(const TValue & value) {
            _value = value;
        }

        //---------------------------------------------------------------------
        Node* rightChild() const {
            return _right_child;
        }

        //---------------------------------------------------------------------
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
        Node* leftChild() const {
            return _left_child;
        }

        //---------------------------------------------------------------------
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
        void unsetLeftChild() {
            _left_child = NULL;
        }

        //---------------------------------------------------------------------
        void unsetRightChild() {
            _right_child = NULL;
        }

        //---------------------------------------------------------------------
        Node* parent() const {
            return _parent;
        }

        //---------------------------------------------------------------------
        void setParent(Node* node) {
            _parent = node;
        }

        //---------------------------------------------------------------------
        bool isRoot() const {
            return parent() == NULL;
        }

        //---------------------------------------------------------------------
        void unlinkChild(Node* child) {
            if (rightChild() == child) {
                setRightChild(NULL);
            }
            else if (leftChild() == child) {
                setLeftChild(NULL);
            }
        }

        //---------------------------------------------------------------------
        void replaceChild(Node* child, Node* replacement) {
            if (leftChild() == child) {
                setLeftChild(replacement);
            }
            else if(rightChild() == child) {
                setRightChild(replacement);
            }
        }

        //---------------------------------------------------------------------
        bool hasChild(Node* child) const {
            return ( (leftChild() == child) ||
                    (rightChild() == child) );
        }

    private:
        Node* _left_child;
        Node* _right_child;
        Node* _parent;
        TKey _key;
        TValue _value;
    };

    Node* _root;

    //---------------------------------------------------------------------
    Node* _findNodeWithSmallestKey(Node* root) {
        // Спускаться до конца по левой ветке двоичного поддерева
        Node* node_next = root;
        while (node_next->leftChild()) {
            node_next = node_next->leftChild();
        }

        return node_next;
    }

    //---------------------------------------------------------------------
    void _setRootNode(Node* node) {
        _root = node;
        if (node) {
            node->setParent(NULL);
        }
    }

    //---------------------------------------------------------------------
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
                /* Узел с наименьшим значением ключа - лист. Чтобы отделить его от ветки дерева,
                         * обнулим указатель на него в родителе */
                node_replacement->parent()->unlinkChild(node_replacement);
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
        }
    }

    //---------------------------------------------------------------------
    Node* _rootNode() const {
        return _root;
    }
public:
    BSTree()
        : _root(NULL)
    {
    }

    //---------------------------------------------------------------------
    ~BSTree() {
        while (_root) {
            _removeNode(_root);
        }
    }

    //---------------------------------------------------------------------
    bool isEmpty() const {
        return (NULL == _root);
    }

    //---------------------------------------------------------------------
    void insert(const TKey & key, const TValue & value) {
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
    }

    //---------------------------------------------------------------------
    Node* findNode(const TKey & key) const {
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
    void remove(TKey key) {
            // Найти элемент с заданным ключом
        Node* node_to_remove = findNode(key);
        // Если узел найден
        if (node_to_remove) {
            _removeNode(node_to_remove);
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
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------

    friend class TestBSTree;
};


#endif // BSTREE_H
