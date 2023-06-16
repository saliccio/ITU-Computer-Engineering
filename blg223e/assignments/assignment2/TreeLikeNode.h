/* @Author
Student Name: Furkan Salık
Student ID: 150200056
E-mail: salik20@itu.edu.tr
Date: 29/12/2021
*/

class TreeLikeNode;

struct NodeVisitData{
    public:
        TreeLikeNode* m_VisitorNodePtr;
        int m_Cost;
        bool m_IsLeftChild;

        NodeVisitData(TreeLikeNode* visitorNodePtr, int cost, bool isLeftChild);
};

class TreeLikeNode{
    private:
        int m_ID;

        int m_BaseCost;  // Cost for coming to this node.

        TreeLikeNode* m_LeftChildPtr;
        int m_LeftCost;  // Cost for going to the left child. (m_BaseCost + individual cost of going to it.)

        TreeLikeNode* m_RightChildPtr;
        int m_RightCost;  // Cost for going to the right child. (m_BaseCost + individual cost of going to it.)

        NodeVisitData m_LastVisitData;  // Data of the last visit to this node.
    public:
        TreeLikeNode(int ID, TreeLikeNode* parentPtr, int baseCost);
        ~TreeLikeNode();

        int getID();

        int getCost(bool left);

        int getBaseCost();
        void setBaseCost(int cost);

        TreeLikeNode* addChild(int ID, int cost);
        void addExistingChild(TreeLikeNode* childPtr, int cost);
        TreeLikeNode* getChild(bool left);

        void printPreOrder();

        // Also visits its children.
        void visit(TreeLikeNode* visitorPtr);
};