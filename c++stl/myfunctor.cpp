#include <iostream>
#include <vector>

using namespace std;

class Add2 {

public:
  Add2() {}

  int operator()(int y) {
    return y+2;
  }

};

class Mul3 {

public:

  Mul3() {}

  int operator()(int y ) {
    return y * 3;
  }

};

int gadd( int n ) {
  return n + 2;
}

void myforeachfunc( int i, int j = 3 ) {

  cout << i << " " << j << endl;
}

int main() {

  vector<int> in;
  vector<int> out;
  Add2 a;
  Mul3 m;
  
  in.push_back(1);
  in.push_back(0);
  in.push_back(3);

  cout << a(2) << " " << m(5) << endl;

  for_each(in.begin(), in.end(), myforeachfunc);
  //transform(in.begin(), in.end(), out.begin(), gadd);
  //transform(in.begin(), in.end(), out.begin(), m(5));

  
}
