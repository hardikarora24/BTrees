// Hardik Arora(2K20/SE/53)
// Kartik Bansal(2K20/SE/68)

#include <stdio.h>
#include <stdlib.h>
#include "globals.c"
#include "dataTypes.c"
#include "prototypes.c"
#include "initializers.c"
#include "insert.c"
#include "delete.c"
#include "printBtree.c"
#include "search.c"

int main() {
  printf("Hardik Arora-2K20/SE/53\nKartik Bansal-2K20/SE/68");
  btree myTree;
  myTree.root = Node_init();
  int flag;
  int data;

  while (true) {
    printf("\n1. insert\n2. search\n3. delete\n4. print\n");
    scanf("%d", &flag);
    switch (flag) {
      case 1: printf("Enter the key to be inserted : ");
        scanf("%d", &data);
        insert(data, &myTree);
        printf("\nThe btree now is:\n");
        print_node(myTree.root);
        break;
      case 2: printf("Enter the key to be searched : ");
        scanf("%d", &data);
        resultTree* res = search(data, myTree.root);
        printf("\n");
        if (res->found) {
          printf("\nfound ");
        }
        else {
          printf(" missing ");
        }
        break;
      case 3: printf("Enter the key to be deleted : ");
        scanf("%d", &data);
        remove_key(myTree.root, data);
        printf("\nThe btree now is:\n");
        print_node(myTree.root);
        break;
      case 4: print_node(myTree.root);
        break;
      default:printf("Choose from the options 1/2/3/4 only");
        fflush(stdin);
    }
  }
  return 0;
}
