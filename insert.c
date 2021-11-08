void insert(int key, btree* myTree) {
  resultTree* iterator = search(key, myTree->root);
  if (iterator->found == true) {
    printf(" already exists ");
    return;
  }
  Node* root = myTree->root;

  if (root->net_key == KEY) {
    Node* new_root = Node_init();
    new_root->leaf = false;
    new_root = split_node(new_root, root);
    myTree->root = new_root;
    myTree->root = non_full_insert(key, myTree->root);
  }
  else {
    myTree->root = non_full_insert(key, myTree->root);
  }
}

//insert in btree when node is not full
Node* non_full_insert(int key, Node* myTree) {
  if (myTree->leaf == true) {
    // insert in right place
    int i = myTree->net_key;
    while (myTree->key_value[i - 1] > key && i > 0) {
      myTree->key_value[i] = myTree->key_value[i - 1];
      i--;
    }
    myTree->key_value[i] = key;
    myTree->net_key++;
    return myTree;
  }

  else {
    int i = myTree->net_key - 1;
    while (myTree->key_value[i] > key && i >= 0) {
      i--;
    }

    if (myTree->child_pointer[i + 1]->net_key == KEY) {
      myTree = split_node(myTree, myTree->child_pointer[i + 1]);
      if (key > myTree->key_value[i + 1]) i = i + 1;
      myTree->child_pointer[i + 1] =
        non_full_insert(key, myTree->child_pointer[i + 1]);
    }

    else {
      myTree->child_pointer[i + 1] =
        non_full_insert(key, myTree->child_pointer[i + 1]);
    }
  }
  return myTree;
}

//spliting node in btree
Node* split_node(Node* parentNode, Node* target) {
  int mid = KEY / 2;

  Node* left = Node_init();
  // entering into new node
  if (!target->leaf) {
    left->leaf = false;
  }
  for (int i = 0; i < mid; i++) {
    left->key_value[i] = target->key_value[i];
  }
  int en_key = target->key_value[mid];

  for (int i = 0; i <= mid; i++) {
    left->child_pointer[i] = target->child_pointer[i];
  }

  // deleting and shifting
  for (int i = mid + 1; i < KEY; i++) {
    target->key_value[i - mid - 1] = target->key_value[i];
    target->key_value[i] = 0;
  }
  for (int i = mid + 1; i < POINTER; i++) {
    target->child_pointer[i - mid - 1] = target->child_pointer[i];
    target->child_pointer[i] = NULL;
  }

  left->net_key = mid;
  target->net_key = KEY - mid - 1;

  int i = parentNode->net_key;
  while (parentNode->key_value[i - 1] > en_key && i > 0) {
    parentNode->key_value[i] = parentNode->key_value[i - 1];
    i--;
  }
  parentNode->key_value[i] = en_key;
  int j = parentNode->net_key + 1;
  while (j > i) {
    parentNode->child_pointer[j + 1] = parentNode->child_pointer[j];
    j--;
  }
  parentNode->child_pointer[j] = left;
  parentNode->child_pointer[j + 1] = target;
  parentNode->net_key++;
  return parentNode;
}