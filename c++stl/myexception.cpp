#include <iostream>

using namespace std;

int b( int n ) {

  throw n;
}

int be( int n ) {
  try {
    throw n;
  } catch( int e ) {
    cout << "Handling exception in be()" << endl;
    throw;
  }
}

void nestedException(int n) {

  try {
    cout << n++;
    try {
      cout << n;
      throw n;
    } catch( int e ) {
      cout << "Caught first exception" << e << endl;
      throw;
    }
  } catch( int e ) {
    cout << "Caught the exception again" << e << endl;
  }
}


int a( int n ) {

  try {
    be(n);
  } catch( int e ) {
    cout << "Caught exception for b() in a()" << e << endl;
  }
}


int main() {

  try {
    throw 20;
  } catch( int e ) {
    cout << "An exception occurred" << e << endl;
  }
  a(10);

  nestedException(10);
  return 0;
}
