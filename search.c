#include <stdio.h>
#include <stdlib.h>

resultTree* search(int key, Node* root) {
  int i;
  i = root->net_key - 1;
  while (i >= 0 && (key < root->key_value[i])) {
    i--;
  }

  if (i >= 0 && key == root->key_value[i]) {
    resultTree* re_node = initResultNode();
    re_node->res = root;
    re_node->pos = i;
    re_node->found = true;
    return re_node;
  }

  if (root->leaf) {
    resultTree* re_node = initResultNode();
    re_node->found = false;
    return re_node;
  }

  else {
    return search(key, root->child_pointer[i + 1]);
  }
}

//used in search
resultTree* initResultNode() {
  resultTree* temp = (resultTree*)malloc(sizeof(resultTree));
  temp->res = NULL;
  return temp;
}