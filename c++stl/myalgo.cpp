#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string>

using namespace std;

class Employee {

  string name;
  string designation;
  int id;
  friend ostream & operator<< (ostream &, Employee);
  friend bool operator== (Employee &, Employee &);

public:

  Employee( string name, string designation, int id ) :
    name(name), designation(designation), id(id) {}
};

ostream &
operator<< ( ostream & out, Employee e) {

  out << e.name << " " << e.designation << " " << e.id << endl;

}

bool
operator== (Employee & lhs, Employee & rhs ) {

  return lhs.name == rhs.name &&
    lhs.designation == rhs.designation &&
    lhs.id == rhs.id;
}

int main( int argc, char ** argv ) {
  
  if( argc != 1 )
    throw "Too many arguments";

  vector<Employee> a;
  vector<Employee> b;

  a.push_back(Employee("Joe","Manager",1));
  b.push_back(Employee("Jack","Worker",2));

  cout << *(a.begin()) << *(b.begin());
  // xxx cout << (a==b ? "equal" : "not equal") << endl;
  

  //FIXIT: check semantics of raw_storage_iterator
  //Employee *c = (a.size() + b.size(), (Employee *)0);

  //merge(a.begin(), a.end(), b.begin(), b.end(), 
  //	raw_storage_iterator<Employee *, Employee>(c));

}
