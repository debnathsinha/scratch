typedef struct node {
  int data;
  struct node *next;
} node;

typedef struct queue {
  node *head, *tail;
} queue;

void queue_init(queue *myroot);
void queue_put(queue *myroot, node *mynode);
node *queue_get(queue *myroot);
