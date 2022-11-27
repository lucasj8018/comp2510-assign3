#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

/**
 * This function prints the node list to the console.
 *
 * @param: NodePtr node as the first node of the list
 */
void printNode(NodePtr node) {
  NodePtr temp = node;

  while (temp != NULL) {
    printf("%s %d %d\n", temp->blockType, temp->base, temp->limit);
    temp = temp->next;
  }
}

/**
 * This function adds a memory node to the list.
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

/**
 * This function opens the input file and save each input line
 * to the memory block list.  It thens also calls the mergeSort()
 * function to sort the list base on the base index.
 *
 * @param: NodePtr head as the first node of the list
 * @param: char filePath as the input file path
 */
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

/**
 * This function merge the consecutive free blocks (holes) in the memory
 * block list into one single free block.
 *
 * @param: NodePtr head as the first node of the list
 */
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

/**
 * This function prints the memory info of the memory block list.
 *
 * @param: NodePtr node as the first node of the list
 */
void printMemory(NodePtr head) {
  NodePtr temp = head;
  int count = 1;

  while (temp != NULL) {
    if (strcmp(temp->blockType, "H") == 0) {
      printf("Node %d: %s (Hole), ", count, temp->blockType);

    } else {
      printf("Node %d: %s, ", count, temp->blockType);
    }

    printf("base = %d, limit = %d\n", temp->base, temp->limit);
    count++;
    temp = temp->next;
  }
}