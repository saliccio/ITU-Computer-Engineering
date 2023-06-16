/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 26/10/2021 */

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

class LinkedList;

class Node{
    public:
        char letter;
        Node* next;

        ~Node();    // Destructor to make a recursive deletion

        void setNextRecursive(Node* newNext, LinkedList* listPtr);   // This method makes the next pointer point to itself and updates the next pointer to the argument 'newNext'  (I have used this method to reverse the list)
};


class LinkedList{

    Node* head;

    public:
        LinkedList();
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
        Node* getHead();
        void setHead(Node* newHead);
};

#endif