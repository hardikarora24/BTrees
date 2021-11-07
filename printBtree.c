#include <stdio.h>
#include <stdlib.h>
#include "queue.c"

void print_node(Node* iterator) {
  Queue qu;
  init(&qu);
  push(&qu, iterator);
  while (!empty(&qu)) {
    int count = qu.size;
    printf("|| ");

    while (count > 0) {
      Node* top_node = top(&qu);

      for (int i = 0; i < top_node->net_key; i++) {
        printf("%d ", top_node->key_value[i]);
      }

      if (!top_node->leaf)
        for (int i = 0; i <= top_node->net_key; i++) {
          push(&qu, top_node->child_pointer[i]);
        }

      pop(&qu);
      printf("||");
      count--;
    }
    printf("\n");
  }
}

