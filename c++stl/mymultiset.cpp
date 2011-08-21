#include <iostream>
#include <set>
#include <map>

using namespace std;

bool fncomp (int lhs, int rhs) { return lhs < rhs; }

struct classcomp {
  bool operator() ( const int &lhs, const int & rhs) const {
    return lhs < rhs;
  }
};

int main() {

  multiset<int> first;
  
  int myints[] = {10,20,40,30,40,50};

  multiset<int> second (myints, myints+6);
  multiset<int> third(second);
  multiset<int> fourth(second.begin(), second.end());

  multiset<int, classcomp> fifth;

  bool(*fn_pt)(int,int) = fncomp;

  multiset<int, bool(*)(int,int)> sixth (fn_pt);

  second.insert(29);

  for( multiset<int>::iterator it = second.begin(); it!= second.end(); it++ )
    cout << *(it) << endl;

  
  map<char,int> mymap;

  mymap['a'] = 65;
  mymap['b'] = 66;
  mymap['c'] = 68;

  for( char c = 'a'; c < 'h'; c++ )
    if( mymap.count(c) > 0 )
      cout << c << "is an element of mymap with value" << mymap[c] << "\n";
    else
      cout << c << "is not an element of mymap\n";

  return 0;

  

}
