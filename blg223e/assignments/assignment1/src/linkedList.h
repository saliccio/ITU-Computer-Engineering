/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 9/11/2021 */

#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        char id;
        int weight;
        materialNode* next;

        materialNode(char id, int weight);
};

class wagonNode{
    public:
        static int LastWagonId;    // Static variable to store the ID of the last wagon.

        int wagonId;
        materialNode* material;
        wagonNode* next;

        wagonNode();
        ~wagonNode();

        materialNode* insertMaterialNode(char id, int weight);    // Function to insert a material node inside a wagon.
        materialNode* getMaterialPtr(char id);    // Function to get a specific material node.
};

class Train{  

    wagonNode* head;
    
    public:
        void create();
        void addMaterial(char,int);
        void deleteFromWagon(char, int);
        void printWagon(); //Prints wagon info

        wagonNode* addWagon();    // Function to add a new wagon.
        void deleteWagonNode(wagonNode* wagonNodePtr);    // Function to delete a wagon.

        void checkIfWagonIsEmpty(wagonNode* wagonNodePtr);    // Function to check if a wagon is empty. It deletes the wagon if it is empty.
};

#endif