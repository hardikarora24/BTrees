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