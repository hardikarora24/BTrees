//btree node initialiser
Node* Node_init() {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->net_key = 0;
  newNode->leaf = true;
  for (int i = 0; i < POINTER; i++) {
    newNode->child_pointer[i] = NULL;
    newNode->key_value[i] = 0;
  }
  return newNode;
}

//used in search
resultTree* initResultNode() {
  resultTree* temp = (resultTree*)malloc(sizeof(resultTree));
  temp->res = NULL;
  return temp;
}
