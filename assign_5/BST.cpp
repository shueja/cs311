/**
 * Implementation of BST class.
 */
//You should always comments to each function to describe its PURPOSE and PARAMETERS

// =======================================================
// Your name: Jeremiah Shue
// Compiler:  g++
// File type: cpp file BST.cpp
// @brief This class implements a BST search tree
//=======================================================

#include "BST.h"
#include <vector>
#include <iostream>

/**
 * Implement the BST constructor
 */
BST::BST() {
    root = nullptr;
    numElements=0;
    numLevels = 0;
}

/**
 * Implement the BST destructor
 */
BST::~BST() {
    delete root;
}

/**
 * Implement size() correctly
 */
unsigned int BST::size() const {
    return numElements;
}

/**
 * Implement clear() correctly without memory leaks
 */
void BST::clear() {
    delete root;
    root = nullptr;
    numElements = 0;
    numLevels = 0;
}

bool BST::insertHelper(T element, unsigned int level, Node* node, Node* parent = nullptr, bool leftChild = true) {
    if (node == nullptr) {
        // if node is nullptr, this is where we actually insert
        Node* newNode = new Node(element);
        if (parent != nullptr) {
            if (leftChild) {
                parent->leftChild= newNode;
            } else {
                parent->rightChild = newNode;
            }
        }else {
            root = newNode;
        }
        newNode->parent = parent; 
        if (level > numLevels) {
            numLevels++;
        }
        return true;
    }
    else if (element == node->data) {
        return false;
    } else if (element < node->data) {
        return insertHelper(element, level+1, node->leftChild, node, true);
    } else {
        return insertHelper(element, level+1, node->rightChild, node, false);
    }
}
/**
 * Implement insert() correctly
 */
bool BST::insert(T element) {
    if (insertHelper(element, 0, root)) {
        
        numElements++;
        return true;
    }
    return false;
}

bool BST::findHelper(const T &query, Node* node) const {
    if (node == nullptr) {
        return false;
    }
    else if (query == node->data) {
        return true;
    }
    else if (query < node->data) {
        return findHelper(query, node->leftChild);
    }
    else {
        return findHelper(query, node->rightChild);
    }
}
/**
 * Implement find() correctly
 */
bool BST::find(const T &query) const {
    return findHelper(query, root);
}

/**
 * Implement the height() function correctly
 */
int BST::height() const {
    return numLevels;
}

/**
 * Implement the getRoot() function correctly
 */
BST::Node* BST::getRoot() {
    return root;
}

/**
 * @brief Print the subtree at node using inorder traversal
 * @param node a pointer to node in BST
 */
void BST::printInorder(Node* node) {
    if (node == nullptr) {
        return;
    } else {
        printInorder(node->leftChild);
        std::cout<<node->data<<" ";
        printInorder(node->rightChild);
    }
    if (node == root) {
        std::cout<<std::endl;
    }
}

/**
* @brief Print the subtree at node using preorder traversal
* @param node a pointer to node in BST
*/
void BST::printPreorder(Node* node) {
    
    if (node == nullptr) {
        return;
    } else {
        std::cout<<node->data<<" ";
        printPreorder(node->leftChild);
        printPreorder(node->rightChild);
    }
    if (node == root) {
        std::cout<<std::endl;
    }
}

/**
* @brief Print the subtree at node using postorder traversal
* @param node a pointer to node in BST
*/
void BST::printPostorder(Node* node) {
    if (node == nullptr) {
        return;
    } else {      
        printPostorder(node->leftChild);
        printPostorder(node->rightChild);
        std::cout<<node->data<<" ";
    }
    if (node == root) {
        std::cout<<std::endl;
    }
}

/**
 * Implement the getLeftMostNode() function correctly
 */
BST::Node *BST::getLeftMostNode() {
    return getLeftMostNode(root);
}

BST::Node *BST::getLeftMostNode(Node* node) {
    Node* cur = node;
    while (cur->leftChild != nullptr) {
        cur = cur->leftChild;
    }
    return cur;
}

/**
 * Implement the BST successor function correctly
 */
BST::Node *BST::successor(Node *node) {
    
    if (node->rightChild != nullptr) {
        return getLeftMostNode(node->rightChild);
    }else {
        Node* cur = node;
        while (cur->parent != nullptr && cur->parent->leftChild != cur) {
            cur = cur->parent;
        }
        return cur->parent;

    }
}

