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
#include <iomanip>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>

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
    if (root) { root->deleteSubtree(); delete root;}
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
    if (root) { root->deleteSubtree();}
    root = nullptr;
    numElements = 0;
    numLevels = 0;
}

bool BST::insertHelper(T element, unsigned int level, Node* node, Node* parent = nullptr, bool leftChild = true) {
    bool result = false;
    if (node == nullptr) {
        // if node is nullptr, this is where we actually insert
        if (parent != nullptr) {
            if (leftChild) {
                parent->leftChild = new Node(element);
                parent->leftChild->parent = parent;
                updateHeight(parent->leftChild);
            } else {
                parent->rightChild = new Node(element);
                parent->rightChild->parent = parent; 
                updateHeight(parent->rightChild);
            }
            Node* toUpdate = parent;
            while (toUpdate != nullptr) {
                updateHeight(toUpdate);
                toUpdate = toUpdate->parent;
            }
        }else {
            root = new Node(element);
        }
        
        if (level > numLevels) {
            numLevels++;
        }
        result = true;
        return result;
    }
    else if (element == node->data) {
        result = false;
    } else if (element < node->data) {
        result = insertHelper(element, level+1, node->leftChild, node, true);
    } else {
        result = insertHelper(element, level+1, node->rightChild, node, false);
    }
    if (node->parent) {
        rebalance(node->parent);
    }

    return result;
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

int BST::balanceFactor(Node* node) {
    if (!node) {
        return 0;
    }
    int leftHeight = -1;
    if (node->leftChild != nullptr){
      leftHeight = node->leftChild->height;
    }

   int rightHeight = -1;
   if (node->rightChild != nullptr) {
      rightHeight = node->rightChild->height;
   }
   return leftHeight - rightHeight;
}

void BST::printBalanceFactors(Node* node) {
    if (node){
        printBalanceFactors(node->leftChild);
        std::cout << " " << balanceFactor(node) << " ";
        printBalanceFactors(node->rightChild);
    }

}

void BST::updateHeight(Node* node) {
    if (node) {
        node->height = std::max(heightOf(node->leftChild), heightOf(node->rightChild)) + 1;
    }

}
int BST::heightOf(Node* node) {
    if (!node) {
        return -1;
    }
    return node->height;
}

void BST::setChild(Node* parent, bool leftChild, Node* child) {
   if (leftChild) {
    parent->leftChild = child;
   }  
   else {
    parent->rightChild = child;
   }
   if (child != nullptr) {
      child->parent = parent;
   }
    Node* toUpdate = parent;
    while (toUpdate != nullptr) {
        updateHeight(toUpdate);
        toUpdate = toUpdate->parent;
    }
   
}

void BST::replaceChild(Node* parent, Node* currentChild, Node* newChild) {
   if (parent->leftChild == currentChild) {
      setChild(parent, true, newChild);
   }
   else if (parent->rightChild == currentChild) {
      setChild(parent, false, newChild);
   }

}

bool BST::removeNode(Node* node) {
        // Parent needed for rebalancing
        Node* parent = node->parent;
                
        // Case 1: Internal node with 2 children
        if (node->leftChild != nullptr && node->rightChild != nullptr) {
            // Find successor
            Node* successor = node->rightChild;
            while (successor->leftChild != nullptr) {
                successor = successor->leftChild;
            }

            // Copy the key from the successor node
            node->data = successor->data;
                    
            // Recursively remove successor
            removeNode(successor);
                    
            // Nothing left to do since the recursive call will have rebalanced
            return true;
        }

        // Case 2: Root node (with 1 or 0 children)
        else if (node == root) {
            Node* originalRoot = root;
            if (node->leftChild != nullptr) {
                root = node->leftChild;
            }
            else {
                root = node->rightChild;
            }
            if (root != nullptr) {
                root->parent = nullptr;
            }
            delete originalRoot;
            return true;
        }

        // Case 3: Internal with left child only
        else if (node->leftChild != nullptr) {
            replaceChild(parent, node, node->leftChild);
        }
        // Case 4: Internal with right child only OR leaf
        else {
            replaceChild(parent, node, node->rightChild);
        }

        // node is gone. Anything that was below node that has persisted is already correctly
        // balanced, but ancestors of node may need rebalancing.
        node = parent;
        while (node != nullptr) {
            rebalance(node);      
            node = node->parent;
        }
        return true;
}

bool BST::removeHelper(const T query, Node* node){
    if (node == nullptr) {
        return false;
    }
    else if (query < node->data) {
        return removeHelper(query, node->leftChild);
    }
    else if (query > node->data) {
        return removeHelper(query, node->rightChild);
    } else {
        return removeNode(node);
    }
}

bool BST::remove(T element) {
    return removeHelper(element, root);
}

void BST::rotateLeft(Node* node){
    //
    Node* rightLeftChild = node->rightChild->leftChild;
   if (node->parent != nullptr) {
      replaceChild(node->parent, node, node->rightChild);
   }

   else { // node is root
      root = node->rightChild;
      root->parent = nullptr;
   }
   setChild(node->rightChild, true, node);
   setChild(node, false, rightLeftChild);
}

void BST::rotateRight(Node* node){
    // if (!node->leftChild) {
    //     return;
    // }
   Node* leftRightChild = node->leftChild->rightChild;
   if (node->parent != nullptr) {
      replaceChild(node->parent, node, node->leftChild);
   }

   else { // node is root
      root = node->leftChild;
      root->parent = nullptr;
   }
   setChild(node->leftChild, false, node);
   setChild(node, true, leftRightChild);
}

void BST::rebalance(Node* node){
    updateHeight(node);       
   if (balanceFactor(node) == -2) {
      if (balanceFactor(node->rightChild) == 1) {
         // Double rotation case.
         rotateRight(node->rightChild);
      }
      rotateLeft(node);
   }
   else if (balanceFactor(node) == 2) {
      if (balanceFactor(node->leftChild) == -1) {
         // Double rotation case.
         rotateLeft(node->leftChild);
      }
      rotateRight(node);
   }
}



