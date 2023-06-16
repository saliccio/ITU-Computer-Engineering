#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

class Node{
    public:
        char letter;
        Node* next;

        ~Node();    // Destructor to make a recursive deletion

        void setNextRecursive(Node* newNext);   // This method makes the next pointer point to itself and updates the next pointer to the argument 'newNext'  (I have used this method to reverse the list)
};


class LinkedList{

    Node* head;

    public:
       
        void reorderList();
        void removeDublicates();
        void reverseList();
        void printList();
        Node* getHead();
};

#endif