// Operator overloading
#include <iostream>
#include <string>

using namespace std;

class Foo {

private:
  string name;

public:
  Foo() { 
    cout << "Constructor" << endl;
  }

  Foo( string str ) {
    name = str;
  }

  ~Foo() {
    cout << "Destructor" << endl;
  }

  bool operator==(const Foo & f ) const {
    if( f.name == name ) {
      return 1;
    } else {
      return 0;
    }
  }

};

int main() {

  Foo f;
  Foo abc("abc");
  Foo def("def");
  Foo xyz("abc");

  if( abc == def ) {
    cout << "abc equals def" << endl;
  } else {
    cout << "abc does not equal def" << endl;
  }

  if( abc == xyz ) {
    cout << "abc equals xyz" << endl;
  } else {
    cout << "abc does not equal xyz" << endl;
  }

}
