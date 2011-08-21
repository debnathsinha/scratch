#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <istream_iterator>

using namespace std;

int main( int argc, char ** argv ) {

  if( argc != 1 )
    throw("Usage: rshuffle\n");

  vector<string> v;
  copy(istream_iterator<string>(cin), istream_iterator<string>(), 
       inserter(v,v.end()));
  random_shuffle(v.begin(), v.end());
  copy(v.begin, v.end, ostream_iterator<string>(cout));

}
