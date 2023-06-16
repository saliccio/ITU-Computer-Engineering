#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include "Process.h"

template <typename T>
class RBTree;  // Forward declaration

template <typename T>
class RBNode {
    private:
        bool m_Black;
        T m_Value;
        RBNode<T>* m_ParentPtr;
        RBNode<T>* m_LeftPtr;
        RBNode<T>* m_RightPtr;
    public:
        RBNode()
            : m_Black(false), m_ParentPtr(nullptr), m_LeftPtr(RBTree<T>::NIL_PTR), m_RightPtr(RBTree<T>::NIL_PTR) {}
        RBNode(bool black, T value)
            : m_Black(black), m_Value(value), m_ParentPtr(nullptr), m_LeftPtr(RBTree<T>::NIL_PTR), m_RightPtr(RBTree<T>::NIL_PTR) {}

        // Returns true if the color is black.
        bool getColor() const { return m_Black; }
        T getValue() const { return m_Value; }
        T& getValueRef() { return m_Value; }
        RBNode<T>* getParent() const { return m_ParentPtr; }
        RBNode<T>* getLeft() const { return m_LeftPtr; }
        RBNode<T>* getRight() const { return m_RightPtr; }

        // Returns the minimum element's pointer of the tree rooted at this node
        RBNode<T>* getMin() {
            if(m_LeftPtr == nullptr) {
                throw "getMin() called on an empty tree!";
            }

            if(m_LeftPtr == RBTree<T>::NIL_PTR) {
                return this;
            } else {
                return m_LeftPtr->getMin();
            }
        }

        bool isNIL() const { return this == RBTree<T>::NIL_PTR; }

        void setColor(bool black) { m_Black = black; }
        void setValue(T value) { m_Value = value; }
        void setParent(RBNode<T>* parentPtr) { m_ParentPtr = parentPtr; }
        void setLeft(RBNode<T>* leftPtr) { m_LeftPtr = leftPtr; }
        void setRight(RBNode<T>* rightPtr) { m_RightPtr = rightPtr; }

        ~RBNode<T>() {
            if(m_LeftPtr != RBTree<T>::NIL_PTR) {   // To avoid double free error
                delete m_LeftPtr;
            }
            if(m_RightPtr != RBTree<T>::NIL_PTR) {  // To avoid double free error
                delete m_RightPtr;
            }
        }
};

template <typename T>
class RBTree {
    private:
        static RBNode<T>* NIL_PTR;  // This is the sentinel node
        friend class RBNode<T>;
    private:
        RBNode<T>* m_RootPtr;
    private:
        // Left rotation
        void leftRotate(RBNode<T>* node) {
            RBNode<T>* y = node->getRight();
            node->setRight(y->getLeft());
            if(y->getLeft() != NIL_PTR) {
                y->getLeft()->setParent(node);
            }
            y->setParent(node->getParent());
            if(node->getParent() == nullptr) {
                m_RootPtr = y;
            } else if(node == node->getParent()->getLeft()) {
                node->getParent()->setLeft(y);
            } else {
                node->getParent()->setRight(y);
            }
            y->setLeft(node);
            node->setParent(y);
        }

        // Right rotation
        void rightRotate(RBNode<T>* node) {
            RBNode<T>* y = node->getLeft();
            node->setLeft(y->getRight());
            if(y->getRight() != NIL_PTR) {
                y->getRight()->setParent(node);
            }
            y->setParent(node->getParent());
            if(node->getParent() == nullptr) {
                m_RootPtr = y;
            } else if(node == node->getParent()->getRight()) {
                node->getParent()->setRight(y);
            } else {
                node->getParent()->setLeft(y);
            }
            y->setRight(node);
            node->setParent(y);
		}

        // Fixes the violations of the rb-tree that are caused by inserting a new element.
        void insertFix(RBNode<T>* node) {
            while(node != m_RootPtr && !node->getParent()->getColor()) {
                bool parent_is_left_child = node->getParent() == node->getParent()->getParent()->getLeft();
                if(parent_is_left_child) {
                    RBNode<T>* unclePtr = node->getParent()->getParent()->getRight();
                    if(!unclePtr->getColor()) {  // Case if uncle node is red 
                        node->getParent()->setColor(true);
                        unclePtr->setColor(true);
                        node->getParent()->getParent()->setColor(false);
                        node = node->getParent()->getParent();
                    } else {  // Case if uncle node is black and added new node is a right child
                        if(node == node->getParent()->getRight()) {
                            node = node->getParent();
                            leftRotate(node);
                        }

                        // Case if uncle node is black and added new node is a right child, above condition is there to ensure this case
                        node->getParent()->setColor(true);
                        node->getParent()->getParent()->setColor(false);
                        rightRotate(node->getParent()->getParent());
                    }
                } else {  // Every operation below is symmetrical with if(parent_is_left_child) condition's body (lefts and rights are exchanged)
                    RBNode<T>* unclePtr = node->getParent()->getParent()->getLeft();
                    if(!unclePtr->getColor()) {
                        node->getParent()->setColor(true);
                        unclePtr->setColor(true);
                        node->getParent()->getParent()->setColor(false);
                        node = node->getParent()->getParent();
                    } else {
                        if(node->getParent() != nullptr && node == node->getParent()->getLeft()) {
                            node = node->getParent();
                            rightRotate(node);
                        }
                        node->getParent()->setColor(true);
                        node->getParent()->getParent()->setColor(false);
                        leftRotate(node->getParent()->getParent());
                    }
                }
            }
            m_RootPtr->setColor(true);  // Set the root node's color as black as it always must be
        }

        // Transplant is a method that is called when removing nodes. It replaces the subtree whose root is node1Ptr with another subtree rooted at node2Ptr.
        void transplant(RBNode<T>* node1Ptr, RBNode<T>* node2Ptr) {
            if(node1Ptr->getParent() == nullptr) {
                m_RootPtr = node2Ptr;
            } else if(node1Ptr == node1Ptr->getParent()->getLeft()) {
                node1Ptr->getParent()->setLeft(node2Ptr);
            } else {
                node1Ptr->getParent()->setRight(node2Ptr);
            }
            node2Ptr->setParent(node1Ptr->getParent());
        }

        // Removes the given node from the tree. 
        void remove(RBNode<T>* nodePtr) {
            // START normal BST removal
            bool y_color_is_black = nodePtr->getColor();
            RBNode<T>* y = nodePtr;
            RBNode<T>* x;
            if(nodePtr->getLeft() == NIL_PTR) {
                x = nodePtr->getRight();
                transplant(nodePtr, nodePtr->getRight());
            } else if(nodePtr->getRight() == NIL_PTR) {
                x = nodePtr->getLeft();
                transplant(nodePtr, nodePtr->getLeft());
            } else {
                y = nodePtr->getRight()->getMin();
                y_color_is_black = y->getColor();
                x = y->getRight();
                if(y->getParent() == nodePtr) {
                    x->setParent(y);
                } else {
                    transplant(y, y->getRight());
                    y->setRight(nodePtr->getRight());
                    y->getRight()->setParent(y);
                }
                transplant(nodePtr, y);
                y->setLeft(nodePtr->getLeft());
                y->getLeft()->setParent(y);
                y->setColor(nodePtr->getColor());
            }
            // END normal BST removal

            // START fixup part
            if(y_color_is_black) {
                while(x != m_RootPtr && x->getColor()) {
                    bool parent_is_left_child = x == x->getParent()->getLeft();
                    if(parent_is_left_child) {
                        RBNode<T>* siblingPtr = x->getParent()->getRight();
                        if(!siblingPtr->getColor()) {   // Case if x's sibling is red
                            siblingPtr->setColor(true);
                            x->getParent()->setColor(false);
                            leftRotate(x->getParent());
                            siblingPtr = x->getParent()->getRight();
                        }
                        if(siblingPtr->getRight()->getColor() && siblingPtr->getLeft()->getColor()) {   // Case if x's sibling is black, and x's sibling's children are black
                            siblingPtr->setColor(false);
                            x = x->getParent();
                        } else {
                            if(siblingPtr->getRight()->getColor()) {    // Case if x's sibling is black, x's sibling's left child is red, and right child is black
                                siblingPtr->getLeft()->setColor(true);
                                siblingPtr->setColor(false);
                                rightRotate(siblingPtr);
                                siblingPtr = x->getParent()->getRight();
                            }

                            // Case if x's sibling is black, x's sibling's right child is red
                            siblingPtr->setColor(x->getParent()->getColor());
                            siblingPtr->getParent()->setColor(true);
                            siblingPtr->getRight()->setColor(true);
                            leftRotate(x->getParent());
                            x = m_RootPtr;
                        }
                    } else {    // Every operation below is symmetrical with if(parent_is_left_child) condition's body (lefts and rights are exchanged)
                        RBNode<T>* siblingPtr = x->getParent()->getLeft();
                        if(!siblingPtr->getColor()) {
                            siblingPtr->setColor(true);
                            x->getParent()->setColor(false);
                            rightRotate(x->getParent());
                            siblingPtr = x->getParent()->getLeft();
                        }
                        if(siblingPtr->getRight()->getColor() && siblingPtr->getLeft()->getColor()) {
                            siblingPtr->setColor(false);
                            x = x->getParent();
                        } else {
                            if(siblingPtr->getLeft()->getColor()) {
                                siblingPtr->getRight()->setColor(true);
                                siblingPtr->setColor(false);
                                leftRotate(siblingPtr);
                                siblingPtr = x->getParent()->getLeft();
                            }
                            siblingPtr->setColor(x->getParent()->getColor());
                            x->getParent()->setColor(true);
                            siblingPtr->getLeft()->setColor(true);
                            rightRotate(x->getParent());
                            x = m_RootPtr;
                        }
                    }
                }
                x->setColor(true);  // Recoloring x
            }
            // END fixup part
        }

        // Returns inorder traversal string of a specific node.
        std::string getInorder(const RBNode<T>* nodePtr) const {
            std::string inorderStr;
            if(nodePtr->getLeft() != NIL_PTR) {
                inorderStr = getInorder(nodePtr->getLeft());
            }
            inorderStr += nodePtr->getValue() + " ";
            if(nodePtr->getRight() != NIL_PTR) {
                inorderStr += getInorder(nodePtr->getRight());
            }
            return inorderStr;
        }
    public:
        RBTree<T>() 
            : m_RootPtr(NIL_PTR) {}

        RBNode<T>* getRoot() const { return m_RootPtr; }

        // Inserts given node to the rb-tree.
        void insert(RBNode<T>* node) {
            RBNode<T>* targetPtr = nullptr;
            RBNode<T>* iteratorPtr = m_RootPtr;
            while(iteratorPtr != NIL_PTR) {
                targetPtr = iteratorPtr;
                if(node->getValue() < iteratorPtr->getValue()) {
                    iteratorPtr = iteratorPtr->getLeft();
                } else {
                    iteratorPtr = iteratorPtr->getRight();
                }
            }
            node->setParent(targetPtr);
            if(targetPtr == nullptr) {
                m_RootPtr = node;
            } else if(node->getValue() < targetPtr->getValue()) {
                targetPtr->setLeft(node);
            } else {
                targetPtr->setRight(node);
            }
            
            node->setColor(false);
            insertFix(node);
        }

        // Inserts the given value to the rb-tree.
        void insert(T value) {
            RBNode<T>* nodePtr = new RBNode<T>(false, value);
            insert(nodePtr);
        }

        // Removes the element with the minimum value from the tree.
        void pop() {
            if(m_RootPtr == NIL_PTR) {
                throw "Called pop() while the tree is empty!";
            }
            RBNode<T>* min_node_ptr = m_RootPtr->getMin();
            remove(min_node_ptr);
        }

        // Returns the minimum element's node pointer in the tree.
        RBNode<T>* getMin() const {
            return m_RootPtr->getMin();
        }

        // Returns the inorder traversal string of the tree.
        std::string getInorder() const {
            if(isEmpty()) {
                return "";
            }
            return getInorder(m_RootPtr);
        }

        // Returns whether the tree is empty.
        bool isEmpty() const {
            return m_RootPtr == NIL_PTR;
        }

        ~RBTree<T>() {
            delete NIL_PTR;
            if(m_RootPtr != NIL_PTR) {  // To avoid double free error
                delete m_RootPtr;
            }
        }
};

// Specific definition of node inorder traversal for RBTree<Process> (T=Process)
template <>
std::string RBTree<Process>::getInorder(const RBNode<Process>* nodePtr) const {
    std::string inorderStr;
    if(nodePtr->getLeft() != NIL_PTR) {
        inorderStr = getInorder(nodePtr->getLeft());
    }
    inorderStr += nodePtr->getValue().name + ":" + std::to_string(nodePtr->getValue().running_time) + "-" + (nodePtr->getColor() ? "Black" : "Red") + ";";
    if(nodePtr->getRight() != NIL_PTR) {
        inorderStr += getInorder(nodePtr->getRight());
    }
    return inorderStr;
}

// Specific definition of tree inorder traversal for RBTree<Process> (T=Process)
template <>
std::string RBTree<Process>::getInorder() const {
    if(isEmpty()) {
        return "";
    }
    std::string inorderStr = getInorder(m_RootPtr);
    inorderStr.pop_back();
    return inorderStr;
}

// Define the sentinel node
template <typename T>
RBNode<T>* RBTree<T>::NIL_PTR = new RBNode<T>(true, T());

#endif