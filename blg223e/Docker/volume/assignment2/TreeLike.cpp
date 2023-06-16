/* @Author
Student Name: Furkan Salık
Student ID: 150200056
E-mail: salik20@itu.edu.tr
Date: 29/12/2021
*/

#include <iostream>
#include "TreeLike.h"

TreeLike::TreeLike(int headID)
{
    m_HeadPtr = new TreeLikeNode(headID, nullptr, 0);
}

TreeLike::~TreeLike()
{
    delete m_HeadPtr;
}

TreeLikeNode *TreeLike::getHeadPtr()
{
    return m_HeadPtr;
}

TreeLikeNode *TreeLike::getNodeByID(int ID, TreeLikeNode *iteratedNodePtr)
{
    if (iteratedNodePtr == nullptr)
    {
        iteratedNodePtr = m_HeadPtr;
    }

    if (iteratedNodePtr->getID() == ID)
    {
        return iteratedNodePtr;
    }

    TreeLikeNode *searchedNodePtr = nullptr;

    TreeLikeNode *leftChildPtr = iteratedNodePtr->getChild(true);
    if (leftChildPtr != nullptr)
    {
        searchedNodePtr = getNodeByID(ID, leftChildPtr);
        if (searchedNodePtr != nullptr)
        {
            return searchedNodePtr;
        }
    }

    TreeLikeNode *rightChildPtr = iteratedNodePtr->getChild(false);
    if (rightChildPtr != nullptr)
    {
        searchedNodePtr = getNodeByID(ID, rightChildPtr);
        if (searchedNodePtr != nullptr)
        {
            return searchedNodePtr;
        }
    }

    return nullptr;
}

void TreeLike::printPreOrder()
{
    m_HeadPtr->printPreOrder();
    std::cout << std::endl;
}

void TreeLike::prune()
{
    m_HeadPtr->visit(nullptr);
}