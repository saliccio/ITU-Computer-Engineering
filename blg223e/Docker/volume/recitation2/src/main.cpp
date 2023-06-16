/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 26/10/2021 */

#include <iostream>
#include <stdlib.h>

#include "linkedList.h"

using namespace std;

int main(int argc, char *argv[])
{
    system("clear"); // make this line as comment if you are compiling on Linux or Mac
                     //system("cls"); // make this line as comment if you are compiling on Windows

    LinkedList newLinkedList;
    Node *currentNode = newLinkedList.getHead();

    FILE *readFile = fopen(argv[1], "r");
    while (true)
    {
        char character = fgetc(readFile);
        if (std::feof(readFile))
        {
            break;
        }
        if (character != '\n')
        {
            currentNode->letter = character;
            currentNode->next = new Node();
            currentNode = currentNode->next;
        }
    }
    fclose(readFile);

    cout << "Readed letters in linked list: ";
    newLinkedList.printList();

    newLinkedList.reorderList();
    cout << "After reordering: ";
    newLinkedList.printList();

    newLinkedList.removeDublicates();
    cout << "After removing dublicates: ";
    newLinkedList.printList();

    newLinkedList.reverseList();
    cout << "Reversed list: ";
    newLinkedList.printList();

    return EXIT_SUCCESS;
}