/* @Author
Student Name: Furkan Salık
Student ID: 150200056
E-mail: salik20@itu.edu.tr
Date: 29/12/2021
*/
// Includes: TreeLike.h    TreeLikeNode.h
// Sources: main.cpp     TreeLike.cpp    TreeLikeNode.cpp

#include <iostream>
#include <string>
#include <fstream>
#include "TreeLike.h"

void readTreeLikeFileLine(std::string &line, int &firstCityID, int &secondCityID, int &cost)
{
    std::string lineData[3];
    int dataIndex = 0;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ')
        {
            dataIndex++;
            continue;
        }
        lineData[dataIndex].append(std::string(1, line[i]));
    }

    firstCityID = std::stoi(lineData[0].substr(4));
    secondCityID = std::stoi(lineData[1].substr(4));
    cost = std::stoi(lineData[2]);
}

TreeLike *readTreeLikeFile(const std::string &fileName)
{
    std::fstream fileStream;
    fileStream.open("./" + fileName);

    std::string line;
    std::getline(fileStream, line);

    int firstCityID;
    int secondCityID;
    int cost;

    readTreeLikeFileLine(line, firstCityID, secondCityID, cost); // Read the first line to create head pointer.

    TreeLike *treeLikePtr = new TreeLike(firstCityID);
    treeLikePtr->getHeadPtr()->addChild(secondCityID, cost);

    while (std::getline(fileStream, line))
    {
        readTreeLikeFileLine(line, firstCityID, secondCityID, cost);

        TreeLikeNode *firstCityNodePtr = treeLikePtr->getNodeByID(firstCityID);
        TreeLikeNode *secondCityNodePtr = treeLikePtr->getNodeByID(secondCityID);
        if (secondCityNodePtr == nullptr)
        {
            firstCityNodePtr->addChild(secondCityID, cost);
        }
        else
        {
            if (secondCityNodePtr->getBaseCost() > firstCityNodePtr->getBaseCost() + cost)
            {
                secondCityNodePtr->setBaseCost(firstCityNodePtr->getBaseCost() + cost);
            }
            firstCityNodePtr->addExistingChild(secondCityNodePtr, cost);
        }
    }

    fileStream.close();

    return treeLikePtr;
}

std::pair<int, int> getMinCostMeetingCity(TreeLike *firstTreeLikePtr, TreeLike *secondTreeLikePtr, TreeLikeNode *iteratedNodePtr)
{
    static int minCost = 99999;
    static int minNodeID = -1;

    TreeLikeNode *secondFriendNodePtr = secondTreeLikePtr->getNodeByID(iteratedNodePtr->getID()); // Node from the tree of the second friend.
    if (secondFriendNodePtr != nullptr)
    {
        int totalCost = iteratedNodePtr->getBaseCost() + secondFriendNodePtr->getBaseCost();
        if (totalCost < minCost)
        {
            minCost = totalCost;
            minNodeID = iteratedNodePtr->getID();
        }
    }

    TreeLikeNode *leftChildPtr = iteratedNodePtr->getChild(true);
    if (leftChildPtr != nullptr)
    {
        getMinCostMeetingCity(firstTreeLikePtr, secondTreeLikePtr, leftChildPtr);
    }

    TreeLikeNode *rightChildPtr = iteratedNodePtr->getChild(false);
    if (rightChildPtr != nullptr)
    {
        getMinCostMeetingCity(firstTreeLikePtr, secondTreeLikePtr, rightChildPtr);
    }

    return {minNodeID, minCost};
}

int main(int argc, char **argv)
{
    TreeLike *friend1TreeLikePtr = readTreeLikeFile(argv[1]);
    friend1TreeLikePtr->prune();

    std::cout << "FRIEND-1: ";
    friend1TreeLikePtr->printPreOrder();

    TreeLike *friend2TreeLikePtr = readTreeLikeFile(argv[2]);
    friend2TreeLikePtr->prune();

    std::cout << "FRIEND-2: ";
    friend2TreeLikePtr->printPreOrder();

    std::pair<int, int> minCostNodeIDPair = getMinCostMeetingCity(friend1TreeLikePtr, friend2TreeLikePtr, friend1TreeLikePtr->getHeadPtr());
    std::cout << "MEETING POINT: CITY" << minCostNodeIDPair.first << std::endl;
    std::cout << "TOTAL DURATION COST: " << minCostNodeIDPair.second << std::endl;

    delete friend1TreeLikePtr;
    delete friend2TreeLikePtr;

    return 0;
}