#include <iostream>

using namespace std;

void swap( int * a, int * b ) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

class Heap {

  int tail_;
  int maxSize_;
  int * arr_;

  void propogateDown( int pos ) {
    int leftChild = 2 * pos;
    int rightChild = 2 * pos + 1;

    int largestPos = pos;
    if( arr_[leftChild] > arr_[pos] )
      largestPos = leftChild;

    if( arr_[rightChild] > arr_[pos] &&
	arr_[rightChild] > arr_[leftChild] )
      largestPos = rightChild;
    
    if( largestPos != pos ) {
      swap( &arr_[pos],&arr_[largestPos]);
      propogateDown(largestPos);
    }
  }

  void bubbleUp( int pos ) {
    int parent = pos / 2;
    if( parent == 0 )
      return;
    if( arr_[parent] < arr_[pos] )
      swap(&arr_[parent],&arr_[pos]);
    bubbleUp(parent);
  }

  void traverse( int pos ) {

    if( pos > tail_ )
      return;
    int leftChild = 2 * pos;
    int rightChild = 2 * pos + 1;
    traverse(leftChild);
    cout << arr_[pos] << " ";
    traverse(rightChild);
  }
    
public:
  Heap(int maxSize) : maxSize_(maxSize), tail_(0) {
    arr_ = new int[maxSize_];
  }

  int extractMax() {
    int a = arr_[1];
    arr_[1] = arr_[tail_--];

    propogateDown(1);
    return a;
  }

  void insert( int n ) {
    arr_[++tail_] = n;
    bubbleUp(tail_);
  }

  void print() {
    traverse(1);
    cout << endl;
    cout << "linear ";
    for( int i = 1; i <= tail_; i++ )
      cout << arr_[i] << " ";
    cout << endl;
  }
};

ostream&
operator<< ( ostream & o, Heap h ) {

  h.print();

}


int main() {

  Heap h(10);

  h.insert(10);
  h.insert(20);
  h.insert(30);
  h.print();
  h.insert(15);
  h.print();
  h.insert(25);
  h.print();
  cout << h.extractMax() << endl;
  h.print();

  cout << "printing thru operator";
  cout << h;
}
