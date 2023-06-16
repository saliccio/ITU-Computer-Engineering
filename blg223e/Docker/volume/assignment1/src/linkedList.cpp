/* @Author
Student Name: Furkan Salık
Student ID : 150200056
Date: 9/11/2021 */

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

int wagonNode::LastWagonId = 0;

materialNode::materialNode(char id, int weight)
{
    this->id = id;
    this->weight = weight;
}

wagonNode::wagonNode()
{
    LastWagonId++;
    wagonId = LastWagonId;    // Assign the wagon ID.
}

wagonNode::~wagonNode()    // If a wagon gets destroyed, destructor deletes materials inside it to prevent memory leak.
{
    materialNode *currentMaterialNode = material;
    while (currentMaterialNode != NULL)
    {
        materialNode *tempNextMaterialNode = currentMaterialNode->next;
        delete currentMaterialNode;
        currentMaterialNode = tempNextMaterialNode;
    }

    LastWagonId--;
}

materialNode *wagonNode::insertMaterialNode(char id, int weight)    // Function to insert a material node inside a wagon.
{
    materialNode *insertedMaterial = new materialNode(id, weight);    // Node that is going to be inserted.

    materialNode *currentMaterialNode = material;    // Pointer that iterates the material list.
    if (currentMaterialNode == NULL)
    {
        material = insertedMaterial;    // If there is no head node, make the inserted material head.
    }
    else
    {
        materialNode *previousMaterialNode = NULL;    // Pointer that holds the previous node of current node.
        while (currentMaterialNode != NULL)    // Linked list iteration loop
        {
            if (currentMaterialNode->id > id)    // To keep the A-B-C-D order, make a check.
            {
                if (previousMaterialNode == NULL)
                {
                    material = insertedMaterial;
                }
                else
                {
                    previousMaterialNode->next = insertedMaterial;
                }

                insertedMaterial->next = currentMaterialNode;
                break;
            }

            materialNode *tempNextMaterialNode = currentMaterialNode->next;    // Temp material that points to the next node.
            if (tempNextMaterialNode == NULL)
            {
                currentMaterialNode->next = insertedMaterial;    // If this is the end of the list, simply insert the material to the end.
                break;
            }

            previousMaterialNode = currentMaterialNode;
            currentMaterialNode = currentMaterialNode->next;
        }
    }

    return insertedMaterial;
}

materialNode *wagonNode::getMaterialPtr(char id)    // Function to get a specific material node.
{
    materialNode *currentMaterialNode = material;    // Pointer that iterates the material list.
    materialNode *searchedMaterialNode = NULL;    // Pointer that will hold the node we are searching for.
    while (currentMaterialNode != NULL)    // Iteration loop
    {
        if (currentMaterialNode->id == id)
        {
            searchedMaterialNode = currentMaterialNode;    // When we find the node, assign the pointer.
            break;
        }

        currentMaterialNode = currentMaterialNode->next;
    }

    if (searchedMaterialNode == NULL)
    {
        searchedMaterialNode = insertMaterialNode(id, 0);    // If the material type does not exists in the list, add it.
    }
    return searchedMaterialNode;
}

void Train::create()
{
    head = NULL;
};

void Train::addMaterial(char material, int weight)
{
    if (head == NULL)
    {
        head = new wagonNode();    // If there is no head, create a head node.
    }

    int weightLeft = weight;
    wagonNode *currentWagonNode = head;    // Pointer that iterates the linked list.
    while (currentWagonNode != NULL)    // Iteration loop
    {
        materialNode *searchedMaterialNode = currentWagonNode->getMaterialPtr(material);    // Material node in the wagon that we will add to.
        int weightLoaded = min(weightLeft, 2000 - searchedMaterialNode->weight);    // Limiting the material node to maximum 2000 KG.
        searchedMaterialNode->weight += weightLoaded;    // Adding weight to material node.
        weightLeft -= weightLoaded;    // Updating the weight left to be added.

        if (weightLeft == 0)
        {
            break;    // If all of the desired weight is added, break the loop.
        }
        else if (currentWagonNode->next == NULL)
        {
            addWagon();    // If the wagon capacities are exceeded, add a new one.
        }

        currentWagonNode = currentWagonNode->next;
    }
};

void Train::deleteFromWagon(char material, int weight)
{
    int weightLeft = weight;
    bool succeeded = false;

    wagonNode *currentNode = head;
    wagonNode *nodes[wagonNode::LastWagonId];    // Array that holds the nodes, we need this to iterate backwards.
    int nodeArrayIndex = 0;    // Length of the array above.
    while (currentNode != NULL)    // Loop to add the nodes to the array.
    {
        nodes[nodeArrayIndex] = currentNode;
        nodeArrayIndex++;
        currentNode = currentNode->next;
    }

    for (int i = nodeArrayIndex - 1; i >= 0; i--)    // Backwards iteration loop
    {
        wagonNode *currentWagonNode = nodes[i];

        materialNode *currentMaterialNode = currentWagonNode->material;
        while (currentMaterialNode != NULL)    // Material list iteration
        {
            if (currentMaterialNode->id == material)    // If the material type we wanted is found, unload the desired amount.
            {
                int weightUnloaded = min(weightLeft, currentMaterialNode->weight);    // Determining how much we want to unload.
                currentMaterialNode->weight -= weightUnloaded;    // Unloading
                weightLeft -= weightUnloaded;    // Updating the amount left to be unloaded.

                checkIfWagonIsEmpty(currentWagonNode);    // Check if the wagon is empty, delete if it is.

                if (weightLeft == 0)
                {
                    succeeded = true;    // If all of the desired amount is unloaded, make the success boolean true.
                }

                break;
            }

            currentMaterialNode = currentMaterialNode->next;
        }

        if (succeeded)
        {
            break;
        }
    }
};

void Train::printWagon()
{
    wagonNode *tempWagon = head;

    if (tempWagon == NULL)
    {
        cout << "Train is empty!!!" << endl;
        return;
    }

    while (tempWagon != NULL)
    {
        materialNode *tempMat = tempWagon->material;
        cout << tempWagon->wagonId << ". Wagon:" << endl;
        while (tempMat != NULL)
        {
            cout << tempMat->id << ": " << tempMat->weight << "KG, ";
            tempMat = tempMat->next;
        }
        cout << endl;
        tempWagon = tempWagon->next;
    }
    cout << endl;
};

wagonNode *Train::addWagon()    // Function to add a new wagon.
{
    wagonNode *newTail = new wagonNode();

    wagonNode *currentWagonNode = head;
    while (currentWagonNode->next != NULL)
    {
        currentWagonNode = currentWagonNode->next;
    }
    currentWagonNode->next = newTail;    // Update the next node of the old ending node.

    return newTail;
}

void Train::deleteWagonNode(wagonNode *wagonNodePtr)        // Function to delete a wagon.
{
    if (wagonNodePtr != NULL)
    {
        if (head == wagonNodePtr)
        {
            head = wagonNodePtr->next;    // If head node is to be deleted, update the head pointer.
        }
        else
        {
            wagonNode *previousNode = head;    // Previous node of the wagon we want to delete.
            while (previousNode->next != wagonNodePtr)
            {
                previousNode = previousNode->next;
            }
            previousNode->next = wagonNodePtr->next;    // Update the previous node's next pointer.
        }

        delete wagonNodePtr;
    }
}

void Train::checkIfWagonIsEmpty(wagonNode *wagonNodePtr)    // Function to check if a wagon is empty. It deletes the wagon if it is empty.
{
    if (wagonNodePtr != NULL)
    {
        materialNode *previousMaterialNode = NULL;    // If a material deletion occurs, this is the previous node of the node we delete.
        materialNode *currentMaterialNode = wagonNodePtr->material;    // Pointer that iterates the list.
        bool isFullyEmpty = true;    // Boolean that indicates that the wagon is fully empty or not, it is initially true and is made false if at least one material exists.
        while (currentMaterialNode != NULL)    // Iteration loop
        {
            materialNode *tempNextMaterialNode = currentMaterialNode->next;    // Temp pointer that stores the next node.
            if (currentMaterialNode->weight != 0)
            {
                isFullyEmpty = false;    // If at least one material exists, the wagon is not fully empty.
            }
            else    // Material node deletion, because the weight is 0.
            {
                if (previousMaterialNode != NULL)
                {
                    previousMaterialNode->next = currentMaterialNode->next;    // If previous node exists, update its next pointer.
                }
                else
                {
                    wagonNodePtr->material = currentMaterialNode->next;    // If previous node does not exist, this means that we want to delete material head node, so we are updating the head node.
                }

                delete currentMaterialNode;
            }

            if (currentMaterialNode != NULL)
            {
                previousMaterialNode = currentMaterialNode;    // If current material node is not deleted, update the previous node pointer.
            }

            currentMaterialNode = tempNextMaterialNode;    // Go to the next node.
        }

        if (isFullyEmpty)
        {
            deleteWagonNode(wagonNodePtr);    // If the wagon is fully empty, delete it.
        }
    }
}