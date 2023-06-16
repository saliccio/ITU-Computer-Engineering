#include <iostream>

template <typename T>
class RBNode {
    private:
        bool m_Black;
        T m_Value;
        int m_Size;
        RBNode<T>* m_ParentPtr;
        RBNode<T>* m_LeftPtr;
        RBNode<T>* m_RightPtr;
    public:
        RBNode()
            : m_Black(false), m_Size(1), m_ParentPtr(nullptr), m_LeftPtr(nullptr), m_RightPtr(nullptr) {}
        RBNode(bool black, T value)
            : m_Black(black), m_Value(value), m_Size(1), m_ParentPtr(nullptr), m_LeftPtr(nullptr), m_RightPtr(nullptr) {}
        
        // Returns true if the color is black.
        bool getColor() const { return m_Black; }
        T getValue() const { return m_Value; }
        RBNode<T>* getParent() const { return m_ParentPtr; }
        RBNode<T>* getLeft() const { return m_LeftPtr; }
        RBNode<T>* getRight() const { return m_RightPtr; }
        int getSize() const { return m_Size; }

        void setColor(bool black) { m_Black = black; }
        void setValue(T value) { m_Value = value; }
        void setParent(RBNode<T>* parentPtr) { m_ParentPtr = parentPtr; }
        void setLeft(RBNode<T>* leftPtr) { m_LeftPtr = leftPtr; }
        void setRight(RBNode<T>* rightPtr) { m_RightPtr = rightPtr; }
        void setSize(int size) { m_Size = size; }

        ~RBNode<T>() {
            delete m_LeftPtr;
            delete m_RightPtr;
        }
};

template <typename T>
class RBTree {
    private:
        RBNode<T>* m_RootPtr;
    private:
        // Left rotation
        void leftRotate(RBNode<T>* node) {
            RBNode<T>* y = node->getRight();
            node->setRight(y->getLeft());
            if(y->getLeft() != nullptr) {
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
            y->setSize(node->getSize());
            node->setSize((node->getLeft() == nullptr ? 0 : node->getLeft()->getSize()) + (node->getRight() == nullptr ? 0 : node->getRight()->getSize()) + 1);
        }

        // Right rotation
        void rightRotate(RBNode<T>* node) {
            RBNode<T>* y = node->getLeft();
            node->setLeft(y->getRight());
            if(y->getRight() != nullptr) {
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
            y->setSize(node->getSize());
            node->setSize((node->getLeft() == nullptr ? 0 : node->getLeft()->getSize()) + (node->getRight() == nullptr ? 0 : node->getRight()->getSize()) + 1);
		}

        // Fixes the violations of the rb-tree that are caused by inserting a new element.
        void insertFix(RBNode<T>* node) {
            while(node->getParent() != nullptr && !node->getParent()->getColor()) {
                bool parent_is_left_child = node->getParent() == node->getParent()->getParent()->getLeft();
                if(parent_is_left_child) {
                    RBNode<T>* unclePtr = node->getParent()->getParent()->getRight();
                    if(unclePtr != nullptr && !unclePtr->getColor()) {  // Case if uncle node is red 
                        node->getParent()->setColor(true);
                        unclePtr->setColor(true);
                        node->getParent()->getParent()->setColor(false);
                        node = node->getParent()->getParent();
                    } else {  // Case if uncle node is black and added new node is a right child
                        if(node->getParent() != nullptr && node == node->getParent()->getRight()) {
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
                    if(unclePtr != nullptr && !unclePtr->getColor()) {
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

        void printInorder(const RBNode<T>* nodePtr) const {
            if(nodePtr->getLeft() != nullptr) {
                printInorder(nodePtr->getLeft());
            }
            std::cout << nodePtr->getValue() << " ";
            if(nodePtr->getRight() != nullptr) {
                printInorder(nodePtr->getRight());
            }
        }
    public:
        RBTree<T>() 
            : m_RootPtr(nullptr) {}

        RBNode<T>* getRoot() const { return m_RootPtr; }

        // Inserts given node to the rb-tree.
        void insert(RBNode<T>* node) {
            RBNode<T>* targetPtr = nullptr;
            RBNode<T>* iteratorPtr = m_RootPtr;
            while(iteratorPtr != nullptr) {
                targetPtr = iteratorPtr;
                iteratorPtr->setSize(iteratorPtr->getSize() + 1);
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

        void printInorder() const {
            printInorder(m_RootPtr);
        }

        // Returns the ith smallest value.
        T getithSmallest(RBNode<T>* rootPtr, int i) const {
            int rank = 1;  // Holds the rank of the node rootPtr.
            if(rootPtr->getLeft() != nullptr) {
                rank += rootPtr->getLeft()->getSize();
            }
            if(i == rank) {
                return rootPtr->getValue();  // The desired rank is found.
            } else if(i < rank) {
                if(rootPtr->getLeft() == nullptr) { return rootPtr->getValue(); }  // Nullcheck
                return getithSmallest(rootPtr->getLeft(), i);  // The rank we are looking for is in the left subtree.
            } else {
                if(rootPtr->getRight() == nullptr) { return rootPtr->getValue(); }  // Nullcheck
                return getithSmallest(rootPtr->getRight(), i - rank);  // Skip the left subtree if the rank we are looking for is greater than the left subtree's size.
            }
        }

        ~RBTree<T>() {
            delete m_RootPtr;
        }
};