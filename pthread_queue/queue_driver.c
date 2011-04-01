#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main() {

  queue * q;
  int i = 0;
  node * mynode;
  q = malloc( sizeof(queue) );
  queue_init(q);
  mynode = malloc( sizeof(node) );
  mynode->data = 1;
  queue_put(q,mynode);
  mynode = malloc( sizeof(node) );
  mynode->data = 2;
  queue_put(q,mynode);
  mynode = malloc( sizeof(node) );
  mynode->data = 4;
  queue_put(q,mynode);
  for( i = 0; i < 3; i++) {
    node * newnode = queue_get(q);
    printf(" %d", newnode->data );
    free(newnode);
  }
  printf("\n");
}
