#include <iostream>
#include <vector>
#include <string>

using namespace std;

int findOddEven( int i ) {
  cout << i << endl;
  if( i %2 == 0 ) {
    return 0;
  } else {
    return 1;
  }
}

int main() {

  vector<int> in;
  vector<string> out;
  vector<int> outn;

  in.push_back(1);
  in.push_back(2);
  in.push_back(3);

  findOddEven(1);
  findOddEven(0);
  findOddEven(3);
  transform(in.begin(), in.end(), outn.begin(), findOddEven);

}
