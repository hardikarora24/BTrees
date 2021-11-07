
//bool definition
typedef short bool;


//Tree Node Definition
typedef struct Node Node;
struct Node {
  int net_key;
  int key_value[KEY];
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





