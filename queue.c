
//malloc queue node
__Node* _createNode(Node* node) {
  __Node* _node = (__Node*)malloc(sizeof(__Node));
  _node->val = node;
  _node->NEXT = NULL;
}

//queue initialiser
void init(Queue* queue) {
  queue->HEAD = NULL;
  queue->TAIL = NULL;
  queue->size = 0;
}



//checks if a queue is empty
bool empty(Queue* queue) { return (queue->HEAD == NULL); }

//push element in a queue
void push(Queue* queue, Node* node) {
  __Node* newNode = _createNode(node);

  if (queue->HEAD == NULL) {
    queue->HEAD = newNode;
  }
  else {
    queue->TAIL->NEXT = newNode;
  }
  queue->size++;
  queue->TAIL = newNode;
}

//pop element from a queue
void pop(Queue* queue) {
  if (empty(queue)) {
    return;
  }

  queue->size--;
  __Node* temp = queue->HEAD;
  queue->HEAD = queue->HEAD->NEXT;

  if (queue->HEAD == NULL) queue->TAIL = NULL;

  free(temp);
}

//returns the queue head value
Node* top(Queue* queue) {
  if (empty(queue)) {
    return NULL;
  }

  return queue->HEAD->val;
}