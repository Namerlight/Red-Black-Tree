#include "rbtree.h"
#include "quetype.cpp"
#include <iostream>

using namespace std;

template <class ItemType>
TreeType<ItemType>::TreeType() {
    root = NULL;
}

template <class ItemType>
void Destroy(TreeNode<ItemType>*& tree) {
    if(tree != NULL){
        Destroy(tree->left);
        Destroy(tree->right);
        delete tree;
        tree = NULL;
    }
}
template <class ItemType>
    TreeType<ItemType>::~TreeType(){
    Destroy(root);
}

template <class ItemType>
    void TreeType<ItemType>::MakeEmpty(){
    Destroy(root);
}

template <class ItemType>
bool TreeType<ItemType>::IsEmpty() {
    return root == NULL;
}

template <class ItemType>
bool TreeType<ItemType>::IsFull() {
    TreeNode<ItemType>* location;
    try {
        location = new TreeNode <ItemType>;
        delete location;
        return false;
    } catch(bad_alloc& exception)  {
        return true;
    }
}


template <class ItemType>
int CountNodes(TreeNode<ItemType>* tree) {
    if(tree == NULL) {
        return 0;
    } else {
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
    }
}

template <class ItemType>
int TreeType<ItemType>:: LengthIs()  {
    return CountNodes(root);
}

template <class ItemType>
void Retrieve(TreeNode<ItemType>* tree, ItemType & item, bool& found)  {
    if(tree == NULL) {
        found = false;
    } else if(item<tree->info) {
        Retrieve(tree->left, item,found);
    } else if(item>tree->info) {
        Retrieve(tree->right, item, found);
    } else {
        item = tree->info;
        found = true;
    }
}

template<class ItemType>
void RotateLeft(TreeNode<ItemType> *&root,TreeNode<ItemType> *&nn){
TreeNode<ItemType> *nnR=nn->right;
nn->right = nnR->left;

    if (nn->right != NULL)
        nn->right->parent = nn;

    nnR->parent = nn->parent;

    if (nn->parent == NULL)
        root = nnR;

    else if (nn == nn->parent->left)
        nn->parent->left = nnR;

    else
        nn->parent->right = nnR;

    nnR->left = nn;
    nn->parent = nnR;
}

template<class ItemType>
void RotateRight(TreeNode<ItemType> *&root,TreeNode<ItemType> *&nn)
{
    TreeNode<ItemType> *nnL = nn->left;

    nn->left = nnL->right;

    if (nn->left != NULL)
        nn->left->parent = nn;

    nnL->parent = nn->parent;

    if (nn->parent == NULL)
        root =nnL;

    else if (nn == nn->parent->left)
        nn->parent->left =nnL;

    else
        nn->parent->right = nnL;

    nnL->right = nn;
    nn->parent = nnL;
}

template <class ItemType>
void TreeType<ItemType>::RetrieveItem(ItemType& item, bool& found)  {
    Retrieve(root, item, found);
}

template <class ItemType>
void TreeType<ItemType>::Insert(TreeNode<ItemType>*& tree, ItemType item) {
    if (tree == NULL) {
        tree = new TreeNode<ItemType>;
        tree->right = NULL;
        tree->left = NULL;
        tree->info = item;
        tree->NodeColour = RED;
    } else if (item < tree->info) {
        Insert(tree->left, item);
    } else {
        Insert(tree->right, item);
    }
    FixColours(tree, root);
}

template <class ItemType>
void TreeType<ItemType>::InsertItem(ItemType item) {
    Insert(root, item);
}

template <class ItemType>
void TreeType<ItemType>::Delete(TreeNode<ItemType>*& tree, ItemType item) {
    if (item < tree->info) {
        Delete(tree->left, item);
    } else if (item > tree->info) {
        Delete(tree->right, item);
    } else {
        DeleteNode(tree);
    }
    FixColours(tree, root);
}

template <class ItemType>
void TreeType<ItemType>::DeleteNode(TreeNode<ItemType>*& tree) {
    ItemType data;
    TreeNode<ItemType>* tempPtr;
    tempPtr = tree;
    if (tree->left == NULL) {
        tree = tree->right;
        delete tempPtr;
    } else if (tree->right == NULL) {
        tree = tree->left;
        delete tempPtr;
    } else {
        GetPredecessor(tree->left, data);
        tree->info = data;
        Delete(tree->left, data);
    }
}

template <class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data) {
    while (tree->right != NULL) {
        tree = tree->right;
    }
    data = tree->info;
}

template <class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item) {
    Delete(root, item);
}

template <class ItemType>
void PreOrder(TreeNode<ItemType>* tree, QueType<ItemType>& Que) {
    if(tree != NULL)
    {
        Que.Enqueue(tree->info);
        PreOrder(tree->left, Que);
        PreOrder(tree->right, Que);
    }
}
template <class ItemType>
void InOrder(TreeNode<ItemType>* tree, QueType<ItemType>& Que) {
    if(tree != NULL) {
        InOrder(tree->left, Que);
        Que.Enqueue(tree->info);
        InOrder(tree->right, Que);
    }
}

template <class ItemType>
void PostOrder(TreeNode<ItemType>* tree, QueType<ItemType>& Que) {
    if(tree != NULL) {
        PostOrder(tree->left, Que);
        PostOrder(tree->right, Que);
        Que.Enqueue(tree->info);
    }
}

template <class ItemType>
void TreeType<ItemType>::ResetTree(OrderType order) {
    switch(order) {
        case PRE_ORDER:
            PreOrder(root, preQue);
            break;
        case IN_ORDER:
            InOrder(root, inQue);
            break;
        case POST_ORDER:
            PostOrder(root, postQue);
            break;
    }
}

template <class ItemType>
void TreeType<ItemType>::GetNextItem(ItemType& item, OrderType order, bool& finished) {
    finished = false;
    switch(order) {
        case PRE_ORDER:
            preQue.Dequeue(item);
            if(preQue.IsEmpty()) {
                finished = true;
            }
            break;
        case IN_ORDER:
            inQue.Dequeue(item);
            if(inQue.IsEmpty()) {
                finished = true;
            }
            break;
        case POST_ORDER:
            postQue.Dequeue(item);
            if(postQue.IsEmpty()) {
                finished = true;
            }
            break;
    }
}

template <class ItemType>
void PrintTree(TreeNode<ItemType>* tree) {
    if(tree != NULL) {
        PrintTree(tree->left);
        cout << tree->info << " ";
        PrintTree(tree->right);
    }
}

template<class ItemType>
void TreeType<ItemType>::Print() {
    PrintTree(root);
}

template <class ItemType>
void TreeType<ItemType>::rotateLeft(TreeNode<ItemType> *&root,TreeNode<ItemType> *&rn) {
    TreeNode<ItemType> *rnR=rn->right;
    rn->right = rnR->left;
    if (rn->right != NULL) {
        rn->right->parent = rn;
    }
    rnR->parent = rn->parent;
    if (rn->parent == NULL) {
        root = rnR;
    } else if (rn == rn->parent->left) {
        rn->parent->left = rnR;
    } else {
        rn->parent->right = rnR;
    }
    rnR->left = rn;
    rn->parent = rnR;
}

template<class ItemType>
void TreeType<ItemType>::rotateRight(TreeNode<ItemType> *&root,TreeNode<ItemType> *&rn) {
    TreeNode<ItemType> *rnL = rn->left;
    rn->left = rnL->right;
    if (rn->left != NULL) {
        rn->left->parent = rn;
    }
    rnL->parent = rn->parent;
    if (rn->parent == NULL) {
        root =rnL;
    } else if (rn == rn->parent->left) {
        rn->parent->left =rnL;
    } else {
        rn->parent->right = rnL;
    }
    rnL->right = rn;
    rn->parent = rnL;
}

template<class ItemType>
void TreeType<ItemType>::FixColours(TreeNode<ItemType> *&root, TreeNode<ItemType> *&nn) {
    TreeNode<ItemType> *nnP = NULL;
    TreeNode<ItemType> *nnGP = NULL;
    while ((nn != root) && (nn->NodeColour != BLACK) && (nn->parent->NodeColour == RED)) {
        nnP = nn->parent;
        nnGP = nn->parent->parent;
        if (nnP == nnGP->left) {  //This is Case 1.
            TreeNode<ItemType> *nnU = nnGP->right;
            if (nnU != NULL && nnU->NodeColour == RED) {
                nnGP->NodeColour = RED;
                nnP->NodeColour = BLACK;
                nnU->NodeColour = BLACK;
                nn = nnGP;
            } else {
                if (nn == nnP->right) {  //Case 2.
                    rotateLeft(root, nnP);
                    nn = nnP;
                    nnP = nn->parent;
                }  //Case 3.
                rotateRight(root, nnGP);
                swap(nnP->NodeColour, nnGP->NodeColour);
                nn = nnP;
            }
        } else {
            TreeNode<ItemType> *nnU = nnGP->left;
            if ((nnU != NULL) && (nnU->NodeColour == RED)) {  //Case 4.
                nnGP->NodeColour = RED;
                nnP->NodeColour = BLACK;
                nnU->NodeColour = BLACK;
                nn = nnGP;
            } else {
                if (nn == nnP->left) {  //Case 5.
                    rotateRight(root, nnP);
                    nn = nnP;
                    nnP = nn->parent;
                }  //Case 6.
                rotateLeft(root, nnGP);
                swap(nnP->NodeColour, nnGP->NodeColour);
                nn = nnP;
            }
        }
    }
    root->NodeColour = BLACK;
}


