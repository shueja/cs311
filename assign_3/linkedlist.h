//CS311 LinkedList.h
//INSTRUCTION:
//Linkedlist class - header file template 
//You should always comments to each function to describe its PURPOSE and PARAMETERS 
#pragma once

#include <string>
using namespace std;

// =======================================================
// Your name: Jeremiah Shue
// Compiler:  g++ 
// File type: headher file  linkedlist.h
//=======================================================

// Datatype T : element type definition
typedef int T;  // int for now but can change later

//a list node is defined here as a struct Node for now
struct Node {
    T val;   // stored value
    Node *next;  // pointer to the next node

    // Constructor
    Node(T val = 0, Node *next = nullptr) {
        this->val = val;
        this->next = next;
    }
};
//---------------------------------------------------------

class LinkedList {
private:
    Node *front;       // pointer to the front node
    Node *rear;        // pointer to the rear node
    int count;        // the number of nodes in the list

public:
    LinkedList() {     // constructor to create an empty list
        front = nullptr;
        rear = nullptr;
        count = 0;
    }
    
    ~LinkedList();     // destructor to destroy all nodes and release memory

    /**
     * @brief Copy Constructor to allow pass by value and return by value of a LinkedList
     * @param other LinkedList to be copied
     */
    LinkedList(const LinkedList &other);

    /**
     * @brief Overloading of = (returns a reference to a LinkedList)
     * @param other LinkedList to be copied
     * @return reference to a LinkedList
     */
    LinkedList &operator=(const LinkedList &other);


    /**
     * @brief Purpose: Checks if the list is empty
     * @return true if the list is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief  Get the number of nodes in the list
     * @return int The number of nodes in the list
     */
    int length() const;
    
    /**
     * @brief Convert the contents of the list to a string
     */
    string toString();

    /**
     * @brief  Displays the contents of the list
     *
     */
    void displayAll();

/**
     * @brief Adds a node to the front of the list
     * @param val T The data in the node to add
    */
    void addFront(T val);

    /**
     * @brief Adds a node to the end of the list
     * @param val The data in the node to add
    */
    void addRear(T val);

    /**
     * @brief Remove the front node of the list
     * @param OldNum T& the reference by which to return the deleted data.
     * @return true if deletion was successful, false if list was empty. 
    */
    bool deleteFront(T &val);

    /**
     * @brief Remove the rear node of the list
     * @param OldNum T& the reference by which to return the deleted data.
     * @return true if deletion was successful, false if list was empty.
    */
    bool deleteRear(T &val);

    /**
     * @brief Delete a node at a given position from the list. The
     * node at position pos is deleted and the value of the deleted node is returned in val.
     * The valid range of pos is 0 to count-1. pos = 0 is the first node, and pos = count-1 is the last node.
     * @param pos: position of the node to be deleted
     * @param val: it is set to the value of the node to be deleted
     * @return true: if the node was deleted successfully
     * @return false: if the node was not deleted successfully because the position was out of range
    */
    bool deleteAt(int pos, T &val);

    /**
     * @brief Insert a value at a specified position in the list. The valid pos is in the range of 0 to count.
     * The value will be inserted before the node at the specified position. if pos = 0, the value will be inserted
     * at the front of the list. if pos = count, the value will be inserted at the rear of the list.
     * @param pos: position to insert the value at.
     * @param val: value to insert.
     * @return true: if the value was inserted.
     * @return false: if the value was not inserted because pos is out of the range.
     */
    bool insertAt(int pos, T val);

    /**
     * @brief check whether a value is in the list or not
     * @param val
     * @return int: the position of the value in the list. If the value is not in the list, return -1.
     */
    int search(const T& val) const;
    
    /**
     * @brief Assume two linked lists that represent Set A and Set B respectively. 
     * Compute the union A U B and return the result as a new linked list. 
     * 
     * @param LA Input linkedlist A as a set (no duplicated element)
     * @param LB Input linkedlist B as a set (no duplicated element)
     * @return LinkedList* return the linkedlist of the union
     */
    friend LinkedList unionLinkedList(const LinkedList& LA, const LinkedList& LB);

    /**
     * @brief Assume two input linked lists, LA and LB, whose elements are both in the non-descending order.
     * This function merges LA and LB into a new linked list (as the return value).
     * The elements in the new list should still be in the non-descending order.
     * 
     * @param LA 
     * @param LB 
     * @return LinkedList
     */
    friend LinkedList mergeLinkedList(const LinkedList& LA, const LinkedList& LB);

    /**
     * @brief Insertion sort algorithm for linked lists
     * 
     * @param list Input linked list
     * @param reversed if reversed = true, the list should be sorted in descending order, otherwise in ascending order
     * @return LinkedList Sorted linked list
     */
    friend LinkedList insertionSortLL(const LinkedList& list, bool reversed);

    /**
     * @brief Merge sort algorithm for linked lists
     * 
     * @param list Input linked list
     * @param reversed if reversed = true, the list should be sorted in descending order, otherwise in ascending order
     * @return LinkedList Sorted linked list
     */
    friend LinkedList mergeSortLL(const LinkedList& list, bool reversed);
};

// LinkedList insertionSortLL(const LinkedList& list, bool reversed = false);

// LinkedList mergeSortLL(const LinkedList& list, bool reversed = false);