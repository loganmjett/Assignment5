// TreeNode header

#ifndef TREENODE
#define TREENODE

#include <iostream>

using namespace std;

template <typename T>
class TreeNode {
    public:
        TreeNode();
        TreeNode(T *key);
        ~TreeNode();

        T *key;
        TreeNode *left;
        TreeNode *right;
};

#endif


// TreeNode implementation

template <typename T>
TreeNode<T>::TreeNode() {
    left = NULL;
    right = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(T *value) {
    key = new T(*value);
    left = NULL;
    right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode() {
    delete key;
    left = NULL;
    right = NULL;
}
