#ifndef REDBLACK_H_INCLUDED
#define REDBLACK_H_INCLUDED
#include "quetype.h"

enum Colour {BLACK, RED};

template<class ItemType>
struct TreeNode{
    ItemType info;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    Colour NodeColour;
};

enum OrderType{PRE_ORDER, IN_ORDER, POST_ORDER};

template<class ItemType>
class TreeType{
public:
    TreeType();
    ~TreeType();
    void MakeEmpty();
    bool IsEmpty();
    bool IsFull();
    int LengthIs();
    void RetrieveItem(ItemType&, bool&);
    void Insert(TreeNode<ItemType> *&, ItemType);
    void InsertItem(ItemType item);
    void Delete(TreeNode<ItemType> *&, ItemType);
    void DeleteItem(ItemType item);
    void DeleteNode(TreeNode<ItemType> *&);
    void ResetTree(OrderType order);
    void rotateLeft(TreeNode<ItemType> *&, TreeNode<ItemType> *&);
    void rotateRight(TreeNode<ItemType> *&, TreeNode<ItemType> *&);
    void FixColours(TreeNode<ItemType> *&, TreeNode<ItemType> *&);
    void GetNextItem(ItemType& item, OrderType order, bool& finished);
    void Print();
private:
    TreeNode<ItemType>* root;
    QueType<ItemType> preQue;
    QueType<ItemType> inQue;
    QueType<ItemType> postQue;
};
#endif // REDBLACK_H_INCLUDED
