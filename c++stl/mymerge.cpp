#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <allocate>

using namespace std;

void merge_array() {
  int a[1000];
  int b[2000];

  int c[3000];

  for(int i = 0; i < 1000; i++ )
    a[i] = i;

  for( int i = 0; i < 2000; i++ )
    b[i] = i + 1000;

  merge(a,a+1000,b,b+2000,c);

  for( int i = 0; i < 3000; i++)
    cout << c[i] << " ";

  cout << endl;


}

class Employee {

  string name;
  static int uid;
  string designation;

public:
  Employee() {
    cout << "Creating employee" << ++uid;
  }
};

void merge_containers() {

  vector<Employee> v(2);
  list<Employee>   li(2);

  Employee * c = allocate(v.size() + li.size(), (Employee *)0);

}

int main( int argc, char ** argv ) {

  if( argc != 1 ) 
    throw("Usage: mymerge");

  merge_array();
  merge_containers();
}
