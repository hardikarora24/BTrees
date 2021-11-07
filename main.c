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
  insert(7, &myTree);
  insert(8, &myTree);
  insert(6, &myTree);
  insert(10, &myTree);
  insert(11, &myTree);
  insert(12, &myTree);
  insert(13, &myTree);
  insert(1, &myTree);
  resultTree* res = search(13, myTree.root);
  printf("\n");
  if (res->found) {
    printf("\nfound ");
  }

  else {
    printf(" missing ");
  }
  printf("\n");
  print_node(myTree.root);

  return 0;
}
