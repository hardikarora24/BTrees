#include <stdio.h>
#include <stdlib.h>


//priting btree using queue----------------------

//printing btree
void print_node(Node* noode) {
  Queue qu;
  init(&qu);
  push(&qu, noode);
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


//print btree using queue end -----------------------