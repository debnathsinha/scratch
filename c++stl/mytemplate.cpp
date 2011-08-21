#include <iostream>
#include <string>

using namespace std;

// Function template
template<class T>
T getMax(T a, T b) {
  return (a>b)?a:b;
}

//Class Template
template<class T>
class mypair {

  T a,b;
public:
  mypair(T a, T b):a(a),b(b) {
  }
  T getMax();
  //T getMax() { return a > b ? a : b; }
};
    
template<class T>
T mypair<T>::getMax() {
  return a>b?a:b;
}

template<> class mypair <float> {
  float a,b;
public:
  mypair(float a, float b):a(a),b(b) {}

  float getMax() { return 3.14; }

};


class Shape {
public:
  void draw() {
    cout << "Drawing shape" << endl;
  }
};

class Square : public Shape {
  void draw() {
    cout << "Drawing Sq" << endl;
  }
public:  
  string shape() {
    return "Square";
  }
};
  
class Circle : public Shape {
public:
  string shape() {
    return "Circle";
  }
};

template<class M = int, class N = int>
class mypair1 {
  M a,b;
  N c,d;

public:
  mypair1(M a, M b, N c, N d):a(a),b(b),c(c),d(d) {}

  bool equal( mypair1<M,N> & rhs ) {
    return rhs.a == a && rhs.b == b && rhs.c == c && rhs.d == d;
  }
};

// template<class myType>
// void myType::draw() {
// 
//   cout << "Drawing" << shape() << endl;
// 
// }

int main(int argc, char *argv[]) {

  int i = 0;
  printf("%d\n", argc);
  while( i < argc ) {
    printf("%s\n", argv[i]);
    i++;

  }

  Shape *sh = new Square();
  Circle *cir = new Circle();
  Square *sq = (Square *)sh;
  
  sh->draw();
  //sq->draw();
  //cir.draw();
  cout << getMax<int>(3,4) << endl;
  cout << getMax<string>("foo","bar") << endl;
  

  mypair<int> intpair(10,20);
  mypair<string> strpair("foo","bar");
  mypair<float> fpair((float)1.23,(float)2.56);
  

  mypair1<int,int> intpair1(3,4,5,6);
  mypair1<int,int> intpair2(3,4,5,6);
  mypair1<> intpair3(1,2,3,4);

  mypair1<int,string> mixpair(1,2,"foo","bar");
  cout << intpair.getMax() << endl;
  cout << strpair.getMax() << endl;
  cout << fpair.getMax() << endl;
  cout << intpair1.equal(intpair2) << endl;
  cout << intpair1.equal(intpair3) << endl;
  //Below: compile time error since string &
  // are apples and oranges
  //cout << intpair1.equal(mixpair) << endl;
}
