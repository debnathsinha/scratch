#include <iostream>
#include <vector>
#include <list>

int main() {

  std::cout << "Hello World" << std::endl;

  const int N = 3;

  std::vector<int> region1(N);
  std::list<int> region2;

  region2.push_back(1);
  region2.push_back(0);
  region2.push_back(3);

  std::copy(region2.begin(), region2.end(), region1.begin());

  for( int i = 0; i < N; i++ )
    std::cout << region1[i] << " ";

  std::cout << std::endl;

}
