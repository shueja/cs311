//BST class - Binary Search Tree
//You should always comments to each function to describe its PURPOSE and PARAMETERS

// =======================================================
// Your name: Jeremiah Shue
// Compiler:  g++
// File type: headher file BST.h
// @brief This class defines a BST search tree
//=======================================================

#ifndef ASSIGN_5_BST_H
#define ASSIGN_5_BST_H

// T: element data type
// int for node element typ now, but can be changed to any data type.
typedef int T;

/**
 * Class to implement a Binary Search Tree (BST)
 */
class BST {
public:
    /**
     * Nested helper Node class
     */
    class Node {
    public:
        /**
         * The data stored within a node
         */
        T data;

        /**
         * Pointer to the node's left child
         */
        Node* leftChild;

        /**
         * Pointer to the node's right child
         */
        Node* rightChild;

        /**
         * Pointer to the node's parent
         */
        Node* parent;

        /**
         * Height of the node (maximum number of nodes in a chain to the leaf)
        */
        int height;


        /**
         * Node constructor, which initializes everything
         */
        Node(T d) : data(d), leftChild(nullptr), rightChild(nullptr), parent(nullptr), height(0) {}

        void deleteSubtree() {
            if (leftChild){ leftChild->deleteSubtree();}
            if (rightChild) {rightChild->deleteSubtree();}
        }
        ~Node() {
        }

    };

    /**
     * BST Constructor, which should initialize an empty BST
     */
    BST();

    /**
     * BST Destructor, which should deallocate anything dynamic
     */
    ~BST();

    bool insertHelper(T element, unsigned int level, Node* node, Node* parent, bool leftChild);
    /**
     * Insert a new element to this BST, and rebalance the tree.
     *
     * @param element The new element to insert
     * @return true if the insertion was successful, otherwise false (e.g. duplicate)
     */
    bool insert(T element);

    bool findHelper(const T & query, Node* node) const;
    /**
     * Find a query element in this BST
     *
     * @param query The query element to find
     * @return true if query exists in this BST, otherwise false
     */
    bool find(const T & query) const;

    /**
     * Return pointer to the left-most node in this BST
     *
     * @return The left-most node in this BST
     */
    Node* getLeftMostNode();

    /**
     * Return the left-most node of a subtree rooted at the node
     * @param node
     * @return
     */
    Node* getLeftMostNode(Node* node);

    /**
     * Remove all elements from the BST and deallocate all nodes
     */
    void clear();

    /**
     * Return the number of elements in the BST
     *
     * @return The number of elements in the BST
     */
    unsigned int size() const;

    /**
     * @brief Return the maximum height of the BST. Root is at height 0
     * @return The height of the BST
     */
    int height() const;

    /**
     * @brief Return pointer to the root node of the BST
     * @return The root node of the BST. nullptr if the BST is empty
     */
     Node* getRoot();

    /**
     * @brief Print the subtree at the given node using inorder traversal
     * @param node a pointer to node in BST
     */
     void printInorder(Node* node);

    /**
    * @brief Print the subtree at node using preorder traversal
    * @param node a pointer to node in BST
    */
     void printPreorder(Node* node);

    /**
   * @brief Print the subtree at node using postorder traversal
   * @param node a pointer to node in BST
   */
    void printPostorder(Node* node);

    /**
     * Find the successor of this Node in the BST
     * @param node The node to find the successor of
     * @return Node* Pointer to the successor of this Node, or nullptr if none exists
     */
    Node* successor(Node *node);

    /**
     * Find the balance factor of this Node in the BST
     * @param node The node to find the balance factor of;
     * @return the balance factor of this node.
    */
    int balanceFactor(Node *node);

    bool remove(T element);

    bool removeHelper(const T query, Node* node);

    bool removeNode(Node* node);

    void rotateLeft(Node* node);

    void rotateRight(Node* node);

    void rebalance(Node* node);

    void printBalanceFactors(Node* node);

    int heightOf(Node* node);

    void updateHeight(Node* node);
private:
    /**
     * Pointer to the root node of this BST
     */
    Node* root;

    /**
     * Total number of elements currently in the BST
     */
    unsigned int numElements;

    unsigned int numLevels;

    void setChild(Node* parent, bool leftChild, Node* child);
    void replaceChild(Node* parent, Node* currentChild, Node* newChild);
    /* New AVL functions*/
};

#endif //ASSIGN_5_BST_H
