/**
 * @brief Implementation of unionLinkedList and mergeLinkedList functions
 */

#include "linkedlist.h"

/**
    * @brief Assume two linked lists that represent Set A and Set B respectively.
    * Compute the union A U B and return the result as a new linked list.
    *
    * @param LA Input linkedlist A as a set (no duplicated element)
    * @param LB Input linkedlist B as a set (no duplicated element)
    * @return LinkedList return the unioned linkedlist 
    */
LinkedList unionLinkedList(const LinkedList& LA, const LinkedList& LB) {
    LinkedList LC(LA);
    Node* currentB = LB.front;
    while (currentB != nullptr) {
        if (LA.search(currentB->val) == -1) {
            LC.addRear(currentB->val);
        }
        currentB = currentB->next;
    }
    return LC;
}

/**
     * @brief Assume two input linked lists, LA and LB, whose elements are both in the non-descending order.
     * This function merges LA and LB into a new linked list (as the return value).
     * The elements in the new list should still be in the non-descending order.
     *
     * @param LA
     * @param LB
     * @return LinkedList
     */
LinkedList mergeLinkedList(const LinkedList& LA, const LinkedList& LB) {
    LinkedList LC;
    Node* currentA = LA.front;
    Node* currentB = LB.front;
    while (currentB != nullptr && currentA != nullptr) {
        if (currentA->val <= currentB->val) {
            LC.addRear(currentA->val);
            currentA = currentA->next;
        } else {
            LC.addRear(currentB->val);
            currentB = currentB->next;
        }
    }
    while (currentA != nullptr) {
        LC.addRear(currentA->val);
        currentA = currentA->next;
    }
    while (currentB != nullptr) {
        LC.addRear(currentB->val);
        currentB = currentB->next;
    }
    return LC;
}