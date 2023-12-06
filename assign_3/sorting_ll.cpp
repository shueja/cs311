/**
 * @brief You will implement the insertion sort and merge sort algorithms for a linked list in this file
 */
//You should always comments to each function to describe its PURPOSE and PARAMETERS

#include "sorting.h"
#include <iostream>

/**
 * Implement the insertion sort algorithm for Linkedlist correctly
 */
LinkedList insertionSortLL(const LinkedList& list, bool reversed) {
    LinkedList result;
    Node* iter = list.front;
    for (; iter != nullptr; iter = iter->next) {
        if (result.isEmpty()) {
            result.addFront(iter->val);
        } else if (
            // if the value needs to be added at the front
            (!reversed && result.front->val > iter->val) || (reversed && result.front->val < iter->val)) {
            result.addFront(iter->val);
        } else if (
            // if the value needs to be added at the rear
            (!reversed && result.rear->val < iter->val) || (reversed && result.rear->val > iter->val)) {
            result.addRear(iter->val);
        }
         else {
            Node* resultIter = result.front;
            int i = 0;
            for (; resultIter != nullptr; resultIter = resultIter->next) {
                if (
                    (!reversed && resultIter->val < iter->val && resultIter->next->val >= iter->val
                    ) ||
                    (reversed && resultIter->val > iter->val && resultIter->next->val <= iter->val
                    )
                ) {
                    result.insertAt(i+1, iter->val);
                }
                i++;
            }
            // if (i == result.length()) {
            //     if (!reversed) {
            //         result.addRear(iter->val);
            //     } else {
            //         result.addFront(iter->val);
            //     }
            // }

        }
        result.displayAll();

    }
    return result;
}

/**
 * Implement the merge sort algorithm for LinkedList correctly
 */
LinkedList mergeSortLL(const LinkedList& list, bool reversed) {

    if (list.length() <= 1) {
        return list;
    }
    LinkedList a;
    LinkedList b;
    int i = 0;
    for (Node* iter = list.front; iter != nullptr; iter = iter->next) {
        if (
            (!reversed && i < list.length() / 2) || (reversed && i >= list.length() / 2)) {
            a.addRear(iter->val);
        } else {
            b.addRear(iter->val);
        }
        i++;
    }
    
    LinkedList sortedA = mergeSortLL(a, reversed);
    LinkedList sortedB = mergeSortLL(b,reversed);
    // Custom merge logic using the reversed value
    LinkedList LC;
    Node* currentA = sortedA.front;
    Node* currentB = sortedB.front;
    while (currentB != nullptr && currentA != nullptr) {
        if (
            (!reversed && currentA->val <= currentB->val) ||
            (reversed && currentA->val > currentB->val)) {
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
