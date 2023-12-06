//CS311 Yoshii S22 Linked List class

//INSTRUCTION:
//It helps to first create if-then-else structure to fill in later.
//- Make sure PURPOSE and PARAMETER comments are given in detail
//  Highly recommended to copy HW3P1-help as PURPOSE of each function.
//  Add sufficient comments to your code body to describe what it does.
//      - Make sure all if-then-else are commented describing which case it is
//      - Make sure all local variables are described fully with their purposes

//You must complete the TODO parts and then complete LinkedList.cpp. Delete "TODO" after you are done.

// ====================================================
//Your name: Jeremiah Shue
//Compiler:  g++
//File type: linkedList.cpp implementation file
//=====================================================

#include <iostream>
#include "linkedlist.h"

using namespace std;

/**
 * @brief Destructor to destroy all nodes and release memory
 */
LinkedList::~LinkedList() {
    T x = 0;
    // delete front until out of range (meaning list is empty)
    // empty-body while loop reruns the condition (deleteFront) until condition returns false;
    while(deleteFront(x)) {}
}

/**
 * @brief Purpose: Checks if the list is empty
 * @return true if the list is empty, false otherwise
 */
bool LinkedList::isEmpty() const {
    return count == 0;
} 

/**
 * @brief  Get the number of nodes in the list
 * @return int The number of nodes in the list
 */
int LinkedList::length() const{
    return count;
}

/**
 * @brief Convert the list to a string
 *
 */
string LinkedList::toString() {
    string str = "[";
    Node *ptr = front;
    if (ptr != nullptr) {
        // Head node is not preceded by separator
        str += to_string(ptr->val);
        ptr = ptr->next;
    }
    while (ptr != nullptr) {
        str += ", " + to_string(ptr->val);
        ptr = ptr->next;
    }
    str  += "]";
    return str;
}

/**
 * @brief Displays the contents of the list
 */
void LinkedList::displayAll() {
    cout << toString() << endl;
}

/**
 * @brief Adds a node to the end of the list
 * @param val The data in the node to add
*/
void LinkedList::addRear(T val) {
    Node* node = new Node(val);
    // consider the two cases of whether the list was empty
    // rear and front are both nullptr if list is empty
    if (rear != nullptr) {
        rear->next = node;
        rear = node;
    } else {
        // If the list was empty, point rear and front to the new node.
        rear = node;
        front = node;
    }
    count++;

}

/**
 * @brief Adds a node to the front of the list
 * @param val T The data in the node to add
*/
void LinkedList::addFront(T val) {
    Node* node = new Node(val);
    // consider the two cases of whether the list was empty
    // rear and front are both nullptr if list is empty
    if (front != nullptr) {
        node->next = front;
        front = node;
    } else {
        // if list was empty, set rear and front to node.
        rear = node;
        front = node;
    }
    count++;
} 

/**
 * @brief Remove the front node of the list
 * @param OldNum T& the reference by which to return the deleted data.
 * @return true if deletion was successful, false if list was empty. 
*/
bool LinkedList::deleteFront(T &OldNum) {
    if (front == nullptr) {
        return false;
    } else if (front == rear) {
        // If deleting the only node in the list
        OldNum = front->val;
        delete front;
        // set front and rear back to nullptr.
        front = nullptr;
        rear = nullptr;
        count = 0;
        return true;
    } else {
        // Save the new front so the pointer can be changed
        // after the current front is deleted.
        Node* newFront = front->next;
        OldNum = front->val;
        delete front;
        front = newFront;
        count--;
        return true;
    }
} 


/**
 * @brief Remove the rear node of the list
 * @param OldNum T& the reference by which to return the deleted data.
 * @return true if deletion was successful, false if list was empty.
*/
bool LinkedList::deleteRear(T &OldNum) {
    if (rear == nullptr) {
        return false;
    } else if (count == 1) {
        // If deleting the only node in the list
        OldNum = front->val;
        delete front;
        // set front and rear back to nullptr.
        front = nullptr;
        rear = nullptr;
        count = 0;
        return true;
    } else {
        Node* newRear = front;
        while (newRear->next != rear) {
            newRear = newRear->next;
        }
        // Save the new front so the pointer can be changed
        // after the current front is deleted.
        OldNum = rear->val;
        delete rear;
        rear = newRear;
        rear->next = nullptr;
        count--;
        return true;
    }
} 

/* --- harder ones for test 2 and 3 -- */

/**
 * @brief Delete a node at a given position from the list. The
 * node at position pos is deleted and the value of the deleted node is returned in val.
 * The valid range of pos is 0 to count-1. pos = 0 for the first node, and pos = count-1 for the last node.
 * @param pos: position of the node to be deleted
 * @param val: it is set to the value of the node to be deleted
 * @return true: if the node was deleted successfully
 * @return false: if the node was not deleted successfully because the position was out of range
*/
bool LinkedList::deleteAt(int pos, T &val) {
    // if count = 0, this becomes (pos < 0 || pos > -1) which is always true for integer pos
    // So this check handles empty lists as well as 
    if (pos < 0 || pos > count-1) {
        return false;
    }
    // Deleting the front
    if (pos == 0) {
        return deleteFront(val);
    }
    // deleting the rear
    if (pos == count-1) {
        return deleteRear(val);
    }
    // Move a pointer to the node before the one we want to delete
    Node* prev = front;
    for (int i = 0; i < pos-1; ++i) {
        prev = prev->next;
    }
    Node* current = prev->next;
    // relink the chain of nexts
    prev->next = current->next;
    val = current->val;
    count--;
    delete current;

    return true;
}

/**
 * @brief Insert a value at a specified position in the list. The valid pos is in the range of 0 to count.
 * The value will be inserted before the node at the specified position. if pos = 0, the value will be inserted
 * at the front of the list. if pos = count, the value will be inserted at the rear of the list.
 * @param pos: position to insert the value at.
 * @param val: value to insert.
 * @return true: if the value was inserted.
 * @return false: if the value was not inserted because pos is out of the range.
 */
bool LinkedList::insertAt(int pos, T val) {
    if (pos < 0 || pos > count) {
        return false;
    }
    if (pos  == 0) {
        addFront(val);
        return true;
    }
    if (pos == count) {
        addRear(val);
        return true;
    }
    // move a pointer to the node before the one we add
    Node* beforeNew = front;
    for (int i = 0; i < pos - 1; i++) {
        beforeNew = beforeNew->next;
    }
    Node* newNode = new Node(val);
    newNode->next = beforeNew->next;
    beforeNew->next = newNode;
    count++;
    return true;
}

/**
 * @brief Copy Constructor to allow pass by value and return by value of a LinkedList
 * @param other LinkedList to be copied
 */
LinkedList::LinkedList(const LinkedList &other) {
    // Start with an empty list
    front = nullptr;
    rear = nullptr;
    count = 0;
    // Iterate through the other list and add a new node to this list
    // for each node in the other list. The new node should have the same value as the other node.
    for (Node* iter = other.front; iter != nullptr; iter = iter->next) {
        addRear(iter->val);
    }
}

/**
 * @brief Overloading of = (returns a reference to a LinkedList)
 * @param other LinkedList to be copied
 * @return reference to a LinkedList
 */
LinkedList &LinkedList::operator=(const LinkedList &other) {
    if(this != &other) { // check if the same object
        // Delete all nodes in this list
        T x = 0;
        while(deleteFront(x)) {}
        // Iterate through the other list and add a new node to this list
        for (Node* iter = other.front; iter != nullptr; iter = iter->next) {
            addRear(iter->val);
        }
    }
    return *this;
}

