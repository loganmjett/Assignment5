// BinarySearchTree header

#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include "TreeNode.h"

using namespace std;

template <typename T>
class BinarySearchTree {

    public:
        BinarySearchTree(); // default constructor
        BinarySearchTree(const BinarySearchTree<T>& other); // copy constructor
        ~BinarySearchTree(); // destructor

        bool searchNode(T *value);
        T* getNode(T *value);
        void insertNode(T *value);
        bool deleteNode(T *value);

        void recDelete(TreeNode<T> *node); // used by destructor

        void printEntireTree();
        void recPrint(TreeNode<T> *node);

        bool isEmpty();
        unsigned int getSize();
        T* getMin();
        T* getMax();


        TreeNode<T>* getSuccessor(TreeNode<T> *d); // d represents the node to be deleted

    private:
        TreeNode<T> *root;
        unsigned int size;

        void recCopy(TreeNode<T>* &copyTo, const TreeNode<T>* copyFrom) const; // used by copy constructor
};

#endif


// BinarySearchTree implementation

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {
    root = NULL;
    size = 0;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other) {
    recCopy(this->root, other.root);
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    // ITERATE AND DELETE +> O(n)
    recDelete(root);
}

template <typename T>
bool BinarySearchTree<T>::searchNode(T* value) {
    if(isEmpty())
        return false;
    else {
        TreeNode<T> *current = root;

        while(*current->key != *value) {
            if(*value < *current->key)
                current = current->left;
            else
                current = current->right;

            if(current == NULL)
                return false;
        }
    }
    return true;
}

template <typename T>
T* BinarySearchTree<T>::getNode(T *value) {
    if(isEmpty())
        return NULL;
    else {
        TreeNode<T> *current = root;

        while(*current->key != *value) {
            if(*value < *current->key)
                current = current->left;
            else
                current = current->right;

            if(current == NULL)
                return NULL;
        }
        return current->key;
    }
}

template <typename T>
void BinarySearchTree<T>::insertNode(T* value) {

    TreeNode<T> *node = new TreeNode<T>(value);
    size++;

    if(isEmpty()) {
        root = node;
    } else {
        TreeNode<T> *current = root;
        TreeNode<T> *parent = NULL;

        while(true) {
            parent = current;

            if(*value < *current->key) {
                current = current->left;

                if(current == NULL) {
                    parent->left = node;
                    break;
                }
            } else {
                current = current->right;

                if(current == NULL) {
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

template <typename T>
bool BinarySearchTree<T>::deleteNode(T* value) {
    if(isEmpty())
        return false;

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeftChild = true;

    // usual code to find a TreeNode

    while(*current->key != *value) {
        parent = current;
        if(*value < *current->key) {
            isLeftChild = true;
            current = current->left;
        } else {
            isLeftChild = false;
            current = current->right;
        }

        if(current == NULL)
            return false;
    }

    // if we make here, we found our key/value
    // let's proceed to delete

    // case: node to be deleted has no children, AKA is a leaf node
    if(current->left == NULL && current->right == NULL) {
        if(current == root) {
            root = NULL; // removed root
        } else if(isLeftChild) {
            parent->left = NULL;
        } else { // right child
            parent->right = NULL;
        }
    }
    // case: node to be deleted has one child, need to determine whether node has left or right child
    else if(current->right == NULL) { // node has one child and it's a left, no right child
        if(current == root) {
            root = current->left;
        } else if(isLeftChild) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }

    } else if(current->left == NULL) { // node has one child and it's a right, no left child
        if(current == root) {
            root = current->right;
        } else if(isLeftChild) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    }

    // case: node to be deleted has two children
    else {
        TreeNode<T> *successor = getSuccessor(current);

        if(current == root) {
            root = successor;
        } else if(isLeftChild) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }

        successor->left = current->left;
    }
    delete current;
    size--;
    return true;
}

template <typename T>
void BinarySearchTree<T>::recDelete(TreeNode<T> *node) {
    if(node != NULL) {
        //cout << "deleting node " << *node->key << endl;
        recDelete(node->left);
        recDelete(node->right);
        delete node;
    }
}

template <typename T>
void BinarySearchTree<T>::printEntireTree() {
    recPrint(root);
}

template <typename T>
void BinarySearchTree<T>::recPrint(TreeNode<T> *node) {
    if(node != NULL) {
        recPrint(node->left);
        cout << *node->key << endl;
        cout << node << endl;
        recPrint(node->right);
    }
}

template <typename T>
bool BinarySearchTree<T>::isEmpty() {
    return (root == NULL);
}

template <typename T>
unsigned int BinarySearchTree<T>::getSize() {
    return size;
}

template <typename T>
T* BinarySearchTree<T>::getMin() {
    TreeNode<T> *current = root;

    if(isEmpty())
        return NULL;

    while(current->left != NULL) {
        current = current->left;
    }

    return current->key;
}

template <typename T>
T* BinarySearchTree<T>::getMax() {
    TreeNode<T> *current = root;

    if(isEmpty())
        return NULL;

    while(current->right != NULL) {
        current = current->right;
    }

    return current->key;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::getSuccessor(TreeNode<T> *d) { // d represents the node we are deleting
    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;

    while(current != NULL) {
        sp = successor;
        successor = current;
        current = current->left;
    }
    // once we exit the while loop, pointers should be in correct positions

    // we need to check whether or not successor is descendant of right child
    if(successor != d->right) {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}

template <typename T>
void BinarySearchTree<T>::recCopy(TreeNode<T>* &copyTo, const TreeNode<T>* copyFrom) const
{
    if(copyFrom == NULL) {
        copyTo = NULL;
    } else {
        copyTo = new TreeNode<T>(copyFrom->key);
        recCopy(copyTo->left, copyFrom->left);
        recCopy(copyTo->right, copyFrom->right);
    }
}
