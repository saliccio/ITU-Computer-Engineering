/* @Author
Student Name: Furkan Salık
Student ID: 150200056
E-mail: salik20@itu.edu.tr
Date: 29/12/2021
*/

#include "TreeLikeNode.h"

class TreeLike
{
private:
    TreeLikeNode *m_HeadPtr;

public:
    TreeLike(int headID);
    ~TreeLike();

    TreeLikeNode *getHeadPtr();

    TreeLikeNode *getNodeByID(int ID, TreeLikeNode *iteratedNodePtr = nullptr);

    void printPreOrder();

    void prune();
};