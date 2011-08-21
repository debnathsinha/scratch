#include <iostream>

using namespace std;

class TreeNode {

  int data;
  TreeNode * leftNode;
  TreeNode * rightNode;

public:
  TreeNode(int data): data(data),leftNode(NULL),rightNode(NULL) {}
  bool lookup( int elem );
  void remove( int elem );
  void insert( int elem );
  TreeNode * successor( int elem );
  TreeNode * predecessor( int elem );
  friend ostream& operator<< ( ostream&, TreeNode * );
};

void
TreeNode::insert( int elem ) {

  if( data == elem )
    return;
  else if( data > elem )
    if( leftNode == NULL )
      leftNode = new TreeNode(elem);
    else
      leftNode->insert(elem);
  else
    if( rightNode == NULL )
      rightNode = new TreeNode(elem);
    else
      rightNode->insert(elem);
}

void
TreeNode::remove( int elem ) {

  if( data == elem ) {
    //proceed to delete
  } else if( data < elem ) {
    if( leftNode == NULL )
      return;
    else
      leftNode->remove(elem);
  } else {
    if( rightNode == NULL )
      return;
    else
      rightNode->remove(elem);
  }
}

class Tree {

  TreeNode * root_;
public:
  Tree(): root_(NULL) {}
  void insert( int elem );

  friend ostream& operator<< ( ostream& o, Tree &t );
};

void
Tree::insert( int elem ) {

  if( root_ == NULL )
    root_ = new TreeNode(elem);
  else
    root_->insert(elem);
}

ostream&
operator<< ( ostream& o, TreeNode * n ) {

  if( n->leftNode != NULL )
    o << n->leftNode;
  o << n->data << " ";
  if( n->rightNode != NULL )
    o << n->rightNode;
  return o;
}

ostream&
operator<< ( ostream& o, Tree &t ) {
  if( t.root_ == NULL )
    o << "Tree is empty" << endl;
  else {
    o << t.root_ << " " << endl;
  }
  return o;
}

int main() {

  Tree * t = new Tree();
  cout << *t;
  t->insert( 20 );
  t->insert( 10 );
  t->insert( 30 );
  cout << *t;

  Tree * t1 = new Tree();
  t->insert(10);
  t->insert(20);
  t->insert(30);

}
