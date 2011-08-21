#include <iostream>

using namespace std;

class Node {

  int data_;
  Node * leftChild_;
  Node * rightChild_;

public:
  Node(int n): data_(n),leftChild_(NULL),rightChild_(NULL) {}
};

class Tree {

  Node * root_;
  
public:
  Tree(): root_(NULL) {}
  void insert( Node * n );
  bool lookup( int n );

};

void
Tree::insert( Node * node ) {

  if( root_ == NULL )
    root_ = node;
  else
    root_.insert( node );
}

bool
Tree::lookup( int n ) {
  
  if( root_ == NULL )
    return -1;
  else
    return root_.lookup(n);
}

void
Node::insert( int n ) {

  if( n < data_ )
    if( leftChild_ == NULL )
      leftChild_ = new Node(n);
    else
      leftChild_.insert(n);
  else if( n > data_ )
    if( rightChild_ == NULL )
      rightChild_ = new Node(n);
    else
      rightChild_.insert(n);
  else {
    //Specify behavior for equality
    return; // Current behavior, don't allow duplicates
  }
}
    
void
Node::lookup(int n) {

  if( n == data_ )
    return true;

  if( n < data_ )
    if( leftChild_ == NULL )
      return false;
    else
      return leftChild_.lookup(n);
  else
    if( n > data_ )
      if( rightChild_ == NULL )
	return true;
      else
	return rightChild_.lookup(n);

}
    

}

ostream&
operator<< (ostream& o, Tree& t) {

  cout << "Printing tree";

}

int main() {
  
  Tree t;
  t.insert(new Node(10));
  t.insert(new Node(20));
  t.insert(new Node(30));

  cout << t;
}


