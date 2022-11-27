#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

/**
 * This function prints the node list to the console.
 *
 * @param: NodePtr node as the first node on the list
 */
void printNode(NodePtr node) {
  NodePtr temp = node;

  while (temp != NULL) {
    printf("%s %d %d\n", temp->blockType, temp->base, temp->limit);
    temp = temp->next;
  }
}

/**
 * This function adds a node to the list.
 *
 * @param: NodePtr head as the head of the list
 * @param: int base as the start index of the memory block
 * @param: int limit as the number of byte
 */
void pushNode(NodePtr* head, char *blockType, int base, int limit) {

  NodePtr newNode = (struct Node*) malloc(sizeof(struct Node));
  strcpy(newNode->blockType, blockType);
  newNode->base = base;
  newNode->limit = limit;
  newNode->next = NULL;

  if (*head == NULL) {
    *head = newNode;

  } else {
    NodePtr tail = *head;

    while (tail->next != NULL) {
      tail = tail->next;
    }
    tail->next = newNode;
  }
}

NodePtr fileHandler(NodePtr head, char *filePath) {
  FILE *inputFilePtr = fopen(filePath, "r");

  if (inputFilePtr == NULL) {
    printf("Error: cannot find file path.");
    exit(1);
  }

  char buffer[100];

  while(fgets(buffer, 100, inputFilePtr) != NULL){

    int base, limit;
    char blockType[30];
    sscanf(buffer, "%s %d %d", blockType, &base, &limit);
    pushNode(&head, blockType, base, limit);
  }
  mergeSort(&head);
  printNode(head);
  return head;
}

void mergeFreeBlocks(NodePtr head){

  if (head == NULL) {
    printf("Memory is empty.\n");
    return;
  }

  NodePtr auxiliaryHead = (NodePtr) malloc(sizeof(NodePtr));
  strcpy(auxiliaryHead->blockType, head->blockType);


  while (head != NULL) {
    NodePtr nextNode;

    if (strcmp(auxiliaryHead->blockType, "H") == 0) {
      nextNode = head;
      strcpy(auxiliaryHead->blockType, "P");

    } else {
      nextNode = head->next;

    }

    if (nextNode != NULL && strcmp(nextNode->blockType, "H") == 0) {

      NodePtr mergedHole = (NodePtr) malloc(sizeof(NodePtr));
      mergedHole->base = nextNode->base;
      strcpy(mergedHole->blockType, "H");
      int limit = nextNode->limit;

      NodePtr temp = nextNode->next;

      while (temp != NULL && strcmp(temp->blockType, "H") == 0) {
        limit += temp->limit;
        temp = temp->next;
      }

      mergedHole->limit = limit;
      mergedHole->next = temp;
      head->next = mergedHole;

    } else if (nextNode != NULL && nextNode->next == NULL) {
        break;
    }
    head = head->next;

  }
  printf("operation successful.\n");
}