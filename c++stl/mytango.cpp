#include <iostream>

using namespace std;


typedef struct node {

  int data;
  node * next;

  void insert( int n );
  void print();
  node(int n): data(n), next(NULL) {}

} node;

node * head;

void
node::insert(int n ) {

  node * newNode = new node(n);
  newNode->next = head;
  head = newNode;
}

void
node::print() {

  cout << "Printing node" << endl;
  node * traverseNode = head;
  while(traverseNode != NULL ) {
    cout << traverseNode->data << " ";
    traverseNode = traverseNode->next;
  }
}


int main() {

  cout << "Hello World" << endl;

  head->insert(10);
  head->insert(20);
  head->print();

  
}
