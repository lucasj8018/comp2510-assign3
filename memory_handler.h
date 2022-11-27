#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char blockType[30];
    int base;
    int limit;

    struct Node* next;
} Node;

typedef struct Node* NodePtr;

NodePtr fileHandler(NodePtr head, char *filePath);

void pushNode(NodePtr* head, char *blockType, int base, int limit);

void printNode(NodePtr node);

void mergeFreeBlocks(NodePtr head);
