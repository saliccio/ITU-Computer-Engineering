/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 26/10/2021 */


#include <iostream>
#include <stdio.h>

#include "linkedList.h"

using namespace std;

Node::~Node()
{ // Destructor to make a recursive deletion
    if (next != NULL)
    {
        delete next;
    }
}

void Node::setNextRecursive(Node *newNext, LinkedList *listPtr)
{ // This method makes the next pointer point to itself and updates the next pointer to the argument 'newNext'  (I have used this method to reverse the list)
    if (next != NULL)
    {
        next->setNextRecursive(this, listPtr);
    }
    else
    {
        listPtr->setHead(this);
    }

    next = newNext;
}

LinkedList::LinkedList()
{
    head = new Node();
}

void LinkedList::reorderList()
{
    Node *newHeadNode = new Node();
    Node *tempCurrentNode = newHeadNode;

    Node *currentNode = head;

    while (currentNode != NULL)
    {
        Node *innerCurrentNode = head;
        Node *innerMinNode = head;
        int innerMinValue = 9999;
        while (innerCurrentNode != NULL)
        {
            if (innerCurrentNode->letter < innerMinValue)
            {
                innerMinValue = innerCurrentNode->letter;
                innerMinNode = innerCurrentNode;
            }

            innerCurrentNode = innerCurrentNode->next;
        }

        tempCurrentNode->letter = innerMinValue;
        innerMinNode->letter = 123;

        if (currentNode->next != NULL)
        {
            tempCurrentNode->next = new Node();
            tempCurrentNode = tempCurrentNode->next;
        }

        currentNode = currentNode->next;
    }

    delete head; // Clearing the list

    head = newHeadNode; // Make the linked list point to the nodes that are ordered
}

void LinkedList::removeDublicates()
{
    Node *previousNode = head;
    Node *currentNode = head->next;

    char lastChar = head->letter;
    while (currentNode != NULL)
    {
        if (currentNode->letter == lastChar)
        {
            previousNode->next = currentNode->next;
            currentNode->next = NULL;
            delete currentNode;
            currentNode = previousNode->next;
        }
        else
        {
            lastChar = currentNode->letter;
            currentNode = currentNode->next;
            previousNode = previousNode->next;
        }
    }
};

void LinkedList::reverseList()
{
    head->setNextRecursive(NULL, this); // Recursively reversing the list
};

void LinkedList::printList()
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->letter << " ";
        temp = temp->next;
    }
    cout << endl;
};

Node *LinkedList::getHead()
{
    return head;
}

void LinkedList::setHead(Node *newHead)
{
    head = newHead;
}