#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "queue.h"
#include "dbug.h"

struct work_q {
  data_control control;
  queue work;
} wq;


typedef struct work_node {
  struct node *next;
  int jobnum;
} wnode;

struct cleanup_queue {
  data_control control;
  queue cleanup;
} cq;

typedef struct cleanup_node {

  struct node *next;
  int threadnum;
  pthread_t tid;
} cnode;

void *threadfunc(void *myarg) {

  wnode *mywork;
  cnode *mynode;
  mynode = (cnode *)myarg;
  pthread_mutex_lock(&wq.control.mutex);
  while(wq.control.active) {
    while( wq.work.head == NULL && wq.control.active ) {
      pthread_cond_wait( &wq.control.cond, &wq.control.mutex);
    }
    if(!wq.control.active)
      break;

    mywork = (wnode *) queue_get(&wq.work);
    pthread_mutex_unlock(&wq.control.mutex);
    // Perform processing
    printf("Thread: %d performing job: %d\n",mynode->threadnum, mywork->jobnum);

    free(mywork);
    pthread_mutex_lock(&wq.control.mutex);
  }

  pthread_mutex_unlock(&wq.control.mutex);
  pthread_mutex_unlock(&cq.control.mutex);
  queue_put(&cq.cleanup, (node *)mynode);
  pthread_mutex_unlock(&cq.control.mutex);
  pthread_cond_signal(&cq.control.cond);
  printf("Thread:%d shutting down...\n",mynode->threadnum);
  return NULL;
}

#define NUM_WORKERS 4
int numthreads;
void join_threads(void) {

  cnode *curnode;
  printf("joining threads...\n");
  while(numthreads) {
    pthread_mutex_lock(&cq.control.mutex);
    
    while(cq.cleanup.head == NULL) {
      pthread_cond_wait(&cq.control.cond, &cq.control.mutex);
    }

    curnode = (cnode *) queue_get(&cq.cleanup);
    pthread_mutex_unlock(&cq.control.mutex);
    pthread_join(curnode->tid, NULL);
    printf("joined with thread %d\n", curnode->threadnum);
    free(curnode);
    numthreads--;
  }
}

int create_threads(void) {
  int x;
  cnode *curnode;
  for( x = 0; x < NUM_WORKERS; x++) {
    curnode = malloc(sizeof(cnode));
    if(!curnode)
      return 1;
    curnode->threadnum=x;
    if(pthread_create(&curnode->tid, NULL, threadfunc, (void *) curnode))
      return;
    printf("create thread %d\n", x);
    numthreads++;
  }
  return 0;
}

void initialize_structs(void) {
  numthreads = 0;
  if(control_init(&wq.control))
    dabort();
  queue_init(&wq.work);
  if(control_init(&cq.control)) {
    control_destroy(&wq.control);
    dabort();
  }
  queue_init(&wq.work);
  control_activate(&wq.control);
}


void cleanup_structs(void) {
  control_destroy(&cq.control);
  control_destroy(&wq.control);
}

int main(void) {
  int x;
  wnode *mywork;
  initialize_structs();
  
  if(create_threads()) {
    printf("Error starting threads..cleaning up\n");
    join_threads();
    dabort();
  }

  pthread_mutex_lock(&wq.control.mutex);
  for(x = 0; x < 16000; x++ ) {
    mywork = malloc(sizeof(wnode));
    if(!mywork) {
      printf("Can't malloc\n");
      break;
    }
    mywork->jobnum = x;
    queue_put(&wq.work, (node *)mywork);
  }

  pthread_mutex_unlock(&wq.control.mutex);
  pthread_cond_broadcast(&wq.control.cond);
  printf("sleeping....\n");
  sleep(2);
  printf("deactivating work queue....\n");
  control_deactivate(&wq.control);
  join_threads();
  cleanup_structs();
}
