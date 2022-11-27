#include "sort.h"

int main() {

  int menu = 0;
  NodePtr headRef = NULL;

  while (menu != 5) {
    printf("1. load an input file\n");
    printf("2. merge holes\n");
    printf("3. compact memory\n");
    printf("4. print memory view\n");
    printf("5. exit the program\n");
    scanf("%d", &menu);

    if (menu == 1) {
      char filePath[30];
      printf("Input your file path: ");
      scanf("%s", filePath);
      headRef = fileHandler(headRef, filePath);

    } else if (menu == 2) {
      mergeFreeBlocks(headRef);
      printNode(headRef);

    } else if (menu == 3) {
      printf("compact memory");

    } else if (menu == 4) {
      printMemory(headRef);

    } else if (menu == 5) {
      printf("exit the program");
      break;
    }

  }
  return 0;
}
