/* @Author
Student Name: Furkan Salık
Student ID: 150200056
E-mail: salik20@itu.edu.tr
Date: 29/12/2021
*/

#include <iostream>
#include "TreeLikeNode.h"

NodeVisitData::NodeVisitData(TreeLikeNode *visitorNodePtr, int cost, bool isLeftChild)
    : m_VisitorNodePtr(visitorNodePtr), m_Cost(cost), m_IsLeftChild(isLeftChild)
{
}

TreeLikeNode::TreeLikeNode(int ID, TreeLikeNode *parentPtr, int baseCost)
    : m_ID(ID), m_BaseCost(baseCost), m_LeftChildPtr(nullptr), m_LeftCost(baseCost), m_RightChildPtr(nullptr), m_RightCost(baseCost),
    m_LastVisitData(nullptr, 99999, true)
{
}

TreeLikeNode::~TreeLikeNode()
{
    delete m_LeftChildPtr;
    delete m_RightChildPtr;
}

int TreeLikeNode::getID()
{
    return m_ID;
}

int TreeLikeNode::getCost(bool left)
{
    if (left)
    {
        return m_LeftCost;
    }
    else
    {
        return m_RightCost;
    }
}

int TreeLikeNode::getBaseCost()
{
    return m_BaseCost;
}

void TreeLikeNode::setBaseCost(int cost)
{
    m_BaseCost = cost;
}

TreeLikeNode *TreeLikeNode::addChild(int ID, int cost)
{
    if (m_LeftChildPtr == nullptr)
    {
        m_LeftChildPtr = new TreeLikeNode(ID, this, m_BaseCost + cost);
        m_LeftCost = m_BaseCost + cost;
        return m_LeftChildPtr;
    }
    else if (m_RightChildPtr == nullptr)
    {
        m_RightChildPtr = new TreeLikeNode(ID, this, m_BaseCost + cost);
        m_RightCost = m_BaseCost + cost;
        return m_RightChildPtr;
    }

    return nullptr;
}

void TreeLikeNode::addExistingChild(TreeLikeNode *childPtr, int cost)
{
    if (m_LeftChildPtr == nullptr)
    {
        m_LeftChildPtr = childPtr;
        m_LeftCost = m_BaseCost + cost;
    }
    else if (m_RightChildPtr == nullptr)
    {
        m_RightChildPtr = childPtr;
        m_RightCost = m_BaseCost + cost;
    }
}

TreeLikeNode *TreeLikeNode::getChild(bool left)
{
    if (left)
    {
        return m_LeftChildPtr;
    }
    else
    {
        return m_RightChildPtr;
    }
}

void TreeLikeNode::printPreOrder()
{
    std::cout << "CITY" << m_ID << " ";

    TreeLikeNode *leftChildPtr = getChild(true);
    if (leftChildPtr != nullptr)
    {
        leftChildPtr->printPreOrder();
    }

    TreeLikeNode *rightChildPtr = getChild(false);
    if (rightChildPtr != nullptr)
    {
        rightChildPtr->printPreOrder();
    }
}

void TreeLikeNode::visit(TreeLikeNode *visitorPtr)  // If a node gets visited, visitor (which is always parent) with more cost will no longer be a parent of that node.
{
    if (visitorPtr != nullptr)
    {
        bool isLeftChildOfVisitor = (visitorPtr->m_LeftChildPtr == this);
        bool isRightChildOfVisitor = (visitorPtr->m_RightChildPtr == this);

        if (m_LastVisitData.m_VisitorNodePtr == nullptr)
        {
            m_LastVisitData.m_VisitorNodePtr = visitorPtr;
            if (isLeftChildOfVisitor)
            {
                m_LastVisitData.m_Cost = visitorPtr->m_LeftCost;
                m_LastVisitData.m_IsLeftChild = true;
            }
            else if (isRightChildOfVisitor)
            {
                m_LastVisitData.m_Cost = visitorPtr->m_RightCost;
                m_LastVisitData.m_IsLeftChild = false;
            }
        }
        else
        {
            if (isLeftChildOfVisitor)
            {
                if (m_LastVisitData.m_Cost < visitorPtr->m_LeftCost)
                {
                    visitorPtr->m_LeftChildPtr = nullptr;
                }
                else if (m_LastVisitData.m_Cost > visitorPtr->m_LeftCost)
                {
                    if (m_LastVisitData.m_IsLeftChild)
                    {
                        m_LastVisitData.m_VisitorNodePtr->m_LeftChildPtr = nullptr;
                    }
                    else
                    {
                        m_LastVisitData.m_VisitorNodePtr->m_RightChildPtr = nullptr;
                    }
                    m_LastVisitData.m_VisitorNodePtr = visitorPtr;
                    m_LastVisitData.m_Cost = visitorPtr->m_LeftCost;
                    m_LastVisitData.m_IsLeftChild = true;
                }
            }
            else if (isRightChildOfVisitor)
            {
                if (m_LastVisitData.m_Cost < visitorPtr->m_RightCost)
                {
                    visitorPtr->m_RightChildPtr = nullptr;
                }
                else
                {
                    if (m_LastVisitData.m_IsLeftChild)
                    {
                        m_LastVisitData.m_VisitorNodePtr->m_LeftChildPtr = nullptr;
                    }
                    else
                    {
                        m_LastVisitData.m_VisitorNodePtr->m_RightChildPtr = nullptr;
                    }
                    m_LastVisitData.m_VisitorNodePtr = visitorPtr;
                    m_LastVisitData.m_Cost = visitorPtr->m_RightCost;
                    m_LastVisitData.m_IsLeftChild = false;
                }
            }
        }
    }

    if (m_LeftChildPtr != nullptr)
    {
        m_LeftChildPtr->visit(this);
    }
    if (m_RightChildPtr != nullptr)
    {
        m_RightChildPtr->visit(this);
    }
}