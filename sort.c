/**
 * File: sort.c
 *
 * Author: JinRong (Lucas) Jian, Justin Ng, Eric Dong, and Eric
 * Date: Nov 15, 2020
 * Course: COMP 2510
 *
 * Summary of File:
 *
 *  The following merge sort functions are reproduced from the GeeksforGeeks' implementation
 *  of the merge sort algorithm.
 *
 *  This file contains codes which implements the merge sort algorithm to sort a
 *  memory block LinkedList.  The sorting order is based on the memory block base
 *  index.
 */

#include "sort.h"

/**
 * This function implements the splitting of a LinkedList in the merge
 * sort algorithm.
 *
 * @param: NodePtr head as the head of the node list
 * @param: NodePtr left as the left half of the node list
 * @param: NodePtr right as the right half of the node list
 */
void splitNodeList(NodePtr head, NodePtr* left, NodePtr* right) {

  NodePtr fast;
  NodePtr slow;
  slow = head;
  fast = head->next;

  // Move fast two nodes and slow one node
  while (fast != NULL) {
    fast = fast->next;
    if (fast != NULL) {
      slow = slow->next;
      fast = fast->next;
    }
  }

  // Split the first half of the list at slow before the mid point
  *left = head;
  *right = slow->next;
  slow->next = NULL;
}

/**
 * This function compares two data types.
 *
 * @param: NodePtr nodeOne as the first node for comparison
 * @param: NodePtr nodeTwo as the second node for comparison
 */
int compare(NodePtr nodeOne, NodePtr nodeTwo) {
  return nodeOne->base - nodeTwo->base;
}

/**
 * This function implements the sorting of a LinkedList in the merge
 * sort algorithm.
 *
 * @param: NodePtr nodeOne as the first node to be compared
 * @param: NodePtr nodeTwo as the second node to be compared
 */
NodePtr sortNode(NodePtr nodeOne, NodePtr nodeTwo) {

  NodePtr sortedNode = NULL;

  // Base case
  if (nodeOne == NULL) {
    return nodeTwo;

  } else if (nodeTwo == NULL) {
    return nodeOne;
  }

  if (compare(nodeOne, nodeTwo) <= 0) {
    sortedNode = nodeOne;
    sortedNode->next = sortNode(nodeOne->next, nodeTwo);

  } else {
    sortedNode = nodeTwo;
    sortedNode->next = sortNode(nodeOne, nodeTwo->next);

  }
  return sortedNode;
}

/**
 * This function implements calls the merge sort algorithm processes.
 *
 * @param: NodePtr *headRef as the head address of the list
 */
void mergeSort(NodePtr* headRef) {

  NodePtr head = *headRef;
  NodePtr nodeOne;
  NodePtr nodeTwo;

  // Base case for student list length of 0 or 1
  if ((head == NULL) || (head->next == NULL)) {
    return;
  }

  splitNodeList(head, &nodeOne, &nodeTwo);

  mergeSort(&nodeOne);
  mergeSort(&nodeTwo);

  *headRef = sortNode(nodeOne, nodeTwo);
}