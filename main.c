// Hardik Arora(2K20/SE/53)
// Kartik Bansal(2K20/SE/68)

//header files
#include <stdio.h>
#include <stdlib.h>


//bool definition
typedef short bool;

#define true 1
#define false 0

//btree key / t values
#define KEY 5
#define POINTER 6
#define t 3

//Tree Node Definition
typedef struct Node Node;
struct Node {
  int net_key;
  int key_value[POINTER];
  Node* child_pointer[POINTER];
  bool leaf;
};


//Queue Node definition
typedef struct __Node __Node;
struct __Node {
  __Node* NEXT;
  Node* val;
};

//queue definition
typedef struct Queue Queue;
struct Queue {
  __Node* HEAD;
  __Node* TAIL;
  int size;
};


//used for searching
typedef struct resultTree resultTree;
struct resultTree {
  Node* res;
  bool found;
  int pos;
};

//btree definition
typedef struct btree btree;
struct btree {
  Node* root;
  int order;
};


//function prototyping start
void init(Queue* queue);
void push(Queue* queue, Node* node);
bool empty(Queue* queue);
void pop(Queue* queue);
Node* top(Queue* queue);
void insert(int key, btree* nodet);
void print_node(Node* noode);
resultTree* search(int key, Node* nodet);
Node* remove_key(Node* nodet, int key);
resultTree* get_result_node();
Node* Node_init();
Node* split_node(Node* parent, Node* to_split);
Node* non_full_insert(int key, Node* nodet);
Node* merge(Node* nodet, int pos);
int get_pred(int pos, Node* nodet);
int get_succ(int pos, Node* nodet);
Node* rem_from_leaf(int key, Node* nodet, int pos);
Node* rem_from_int(int key, Node* nodet, int pos);
Node* borrow_from_left(Node* nodet, int pos);
Node* borrow_from_right(Node* nodet, int pos);
Node* remove_key(Node* nodet, int key);
//prototyping end

//main 
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



//inserting in btree ---------------------------

//insert in a btree
void insert(int key, btree* nodet) {
  resultTree* iterator = search(key, nodet->root);
  if (iterator->found == true) {
    printf(" already exists ");
    return;
  }
  Node* root = nodet->root;

  if (root->net_key == KEY) {
    Node* new_root = Node_init();
    new_root->leaf = false;
    new_root = split_node(new_root, root);
    nodet->root = new_root;
    nodet->root = non_full_insert(key, nodet->root);
  }
  else {
    nodet->root = non_full_insert(key, nodet->root);
  }
}

//insert in btree when node is not full
Node* non_full_insert(int key, Node* nodet) {
  if (nodet->leaf == true) {
    // insert in right place
    int i = nodet->net_key;
    while (nodet->key_value[i - 1] > key && i > 0) {
      nodet->key_value[i] = nodet->key_value[i - 1];
      i--;
    }
    nodet->key_value[i] = key;
    nodet->net_key++;
    return nodet;
  }

  else {
    int i = nodet->net_key - 1;
    while (nodet->key_value[i] > key && i >= 0) {
      i--;
    }

    if (nodet->child_pointer[i + 1]->net_key == KEY) {
      nodet = split_node(nodet, nodet->child_pointer[i + 1]);
      if (key > nodet->key_value[i + 1]) i = i + 1;
      nodet->child_pointer[i + 1] =
        non_full_insert(key, nodet->child_pointer[i + 1]);
    }

    else {
      nodet->child_pointer[i + 1] =
        non_full_insert(key, nodet->child_pointer[i + 1]);
    }
  }
  return nodet;
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

//inserting end----------------------------------------


//deleting in btree----------------------

//used in delete
int get_pred(int pos, Node* nodet) {
  Node* pred = nodet->child_pointer[pos];

  while (!pred->leaf) {
    pred = pred->child_pointer[pred->net_key];
  }

  return pred->key_value[pred->net_key - 1];
}

//used in delete
int get_succ(int pos, Node* nodet) {
  Node* suc = nodet->child_pointer[pos + 1];

  while (!suc->leaf) {
    suc = suc->child_pointer[0];
  }

  return suc->key_value[0];
}

//used in delete
Node* rem_from_leaf(int key, Node* nodet, int pos) {
  int i = pos;

  while (i < nodet->net_key) {
    nodet->key_value[i] = nodet->key_value[i + 1];
    i++;
  }
  nodet->key_value[nodet->net_key - 1] = 0;
  nodet->net_key--;
  return nodet;
}

//used in delete
Node* rem_from_int(int key, Node* nodet, int pos) {
  if (nodet->child_pointer[pos]->net_key >= t) {
    int pred = get_pred(pos, nodet);
    nodet->key_value[pos] = pred;
    nodet->child_pointer[pos] = remove_key(nodet->child_pointer[pos], pred);
  }

  else if (nodet->child_pointer[pos + 1]->net_key >= t) {
    int suc = get_succ(pos, nodet);
    nodet->key_value[pos] = suc;
    nodet->child_pointer[pos + 1] =
      remove_key(nodet->child_pointer[pos + 1], suc);
  }

  else {
    merge(nodet, pos);
    nodet->child_pointer[pos] = remove_key(nodet->child_pointer[pos], key);
  }

  return nodet;
}

//used in delete
Node* borrow_from_left(Node* nodet, int pos) {
  int from_parrent;
  int from_left;
  Node* left_sib = nodet->child_pointer[pos - 1];
  from_parrent = nodet->key_value[pos - 1];
  from_left = left_sib->key_value[left_sib->net_key - 1];

  Node* borrowed_from_left = left_sib->child_pointer[left_sib->net_key];
  left_sib->key_value[left_sib->net_key - 1] = 0;
  left_sib->child_pointer[left_sib->net_key] = NULL;

  nodet->key_value[pos - 1] = from_left;
  Node* main_sib = nodet->child_pointer[pos];

  int i = main_sib->net_key;
  while (i >= 1) {
    main_sib->key_value[i] = main_sib->key_value[i - 1];
    i--;
  }
  main_sib->key_value[0] = from_parrent;

  i = main_sib->net_key + 1;
  while (i < 0) {
    main_sib->child_pointer[i] = main_sib->child_pointer[i - 1];
    i--;
  }
  main_sib->child_pointer[0] = borrowed_from_left;
  main_sib->net_key++;
  left_sib->net_key--;
  return nodet;
}

//used in delete
Node* merge(Node* nodet, int pos) {
  Node* merged_child = Node_init();

  Node* left_child = nodet->child_pointer[pos];
  Node* right_child = nodet->child_pointer[pos + 1];
  left_child->key_value[left_child->net_key] = nodet->key_value[pos];
  int i = 0, j = left_child->net_key + 1;
  while (i < right_child->net_key) {
    left_child->key_value[j] = right_child->key_value[i];
    i++, j++;
  }

  i = 0, j = left_child->net_key + 1;

  while (i <= right_child->net_key) {
    left_child->child_pointer[j] = right_child->child_pointer[i];
    i++, j++;
  }

  i = pos;
  while (i < nodet->net_key - 1) {
    nodet->key_value[i] = nodet->key_value[i + 1];
    i++;
  }
  nodet->key_value[nodet->net_key - 1] = 0;

  left_child->net_key = left_child->net_key + right_child->net_key + 1;
  int l = 0;
  while (l < left_child->net_key) {
    printf("%d ", left_child->key_value[l]);
    l++;
  }
  printf("\n");
  nodet->child_pointer[pos] = left_child;
  i = pos + 1;
  while (i < nodet->net_key) {
    nodet->child_pointer[i] = nodet->child_pointer[i + 1];
    i++;
  }
  nodet->child_pointer[nodet->net_key] = NULL;
  nodet->net_key--;

  if (nodet->net_key == 0) nodet = nodet->child_pointer[0];
  return nodet;
}


//used in delete
Node* borrow_from_right(Node* nodet, int pos) {
  // key form parent
  int from_parent;
  //    key form sib
  int from_right;
  //    the right sibling
  Node* right_sib = nodet->child_pointer[pos + 1];
  from_parent = nodet->key_value[pos];
  from_right = right_sib->key_value[0];
  //    child borrowed from right sib
  Node* borrowed_from_right = right_sib->child_pointer[0];
  nodet->key_value[pos] = from_right;
  nodet->child_pointer[pos]->key_value[nodet->child_pointer[pos]->net_key] =
    from_parent;

  int i = 0;
  while (i < right_sib->net_key) {
    right_sib->key_value[i] = right_sib->key_value[i + 1];
    i++;
  }
  i = 0;
  while (i <= right_sib->net_key) {
    right_sib->child_pointer[i] = right_sib->child_pointer[i + 1];
    i++;
  }
  Node* main_sib = nodet->child_pointer[pos];
  main_sib->child_pointer[main_sib->net_key + 1] = borrowed_from_right;
  right_sib->net_key--;
  nodet->child_pointer[pos]->net_key++;
  return nodet;
}


//deleting a node
Node* remove_key(Node* nodet, int key) {
  int i = 0;
  while (nodet->key_value[i] < key && i < nodet->net_key) {
    i++;
  }

  //   if key is found
  if (i < nodet->net_key && nodet->key_value[i] == key) {
    printf("found\n");
    if (nodet->leaf) {
      nodet = rem_from_leaf(key, nodet, i);
    }
    else {
      nodet = rem_from_int(key, nodet, i);
    }
  }
  else {
    printf("not in this node \n");
    // if node is a leaf node
    if (nodet->leaf) {
      printf(" key not present\n");
    }

    else {
      // if the next child node has atleast t keys
      if (nodet->child_pointer[i]->net_key >= t) {
        nodet->child_pointer[i] =
          remove_key(nodet->child_pointer[i], key);
      }

      else {
        // checking for left sibling to borrow
        if (i > 0 && !(nodet->child_pointer[i - 1]->net_key < t)) {
          nodet = borrow_from_left(nodet, i);
        }
        //  if left sib. doesn't have enough key then lookn at right
        //  node
        else if (i < nodet->net_key &&
          !(nodet->child_pointer[i + 1]->net_key < t)) {
          nodet = borrow_from_right(nodet, i);
        }

        // if none of the imm. sib. has enough children
        // merge with a sibbling
        else {
          // merge with left
          if (i > 0) {
            nodet = merge(nodet, i - 1);
          }

          // merge with right
          else {
            nodet = merge(nodet, i);
          }
        }

        //   a a   a   a
        //  b b |b| |b| b
        nodet = remove_key(nodet, key);
      }
    }
  }
  return nodet;
}

//deleting in btree end --------------------------

//searching -------------------------------------
//used in search
resultTree* get_result_node() {
  resultTree* neww = (resultTree*)malloc(sizeof(resultTree));
  neww->res = NULL;
  return neww;
}

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