#include <stdio.h>
#include <stdlib.h>


//searching -------------------------------------
//search for an element in btree
resultTree* search(int key, Node* nodet) {
  int i;
  i = nodet->net_key - 1;

  while (i >= 0 && (key < nodet->key_value[i])) {
    i--;
  }

  if (i >= 0 && key == nodet->key_value[i]) {
    resultTree* re_node = get_result_node();
    re_node->res = nodet;
    re_node->pos = i;
    re_node->found = true;
    return re_node;
  }

  if (nodet->leaf) {
    resultTree* re_node = get_result_node();
    re_node->found = false;
    return re_node;
  }

  else {
    return search(key, nodet->child_pointer[i + 1]);
  }
}
//search end------------------------