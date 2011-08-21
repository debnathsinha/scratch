#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>

struct add_x {
public:
  add_x(int x) : x(x) {}
  int operator()(int y) { return x + y; }

private:
  int x;
};

void printvec(int n) {

  std::cout << n << std::endl;
}

int main() {
  // Now you can use it like this:
  add_x add42(42); // create a functor
  int i = add42(8); // and "call" it
  assert(i == 50); // and it added 42 to its argument

  std::vector<int> in; // assume this contains a bunch of values)
  std::vector<int> out;

  in.push_back(1);
  in.push_back(0);
  in.push_back(3);
  std::transform(in.begin(), in.end(), out.begin(), add_x(1)); // Pass a functor to
  // std::transform, which calls the functor on every element in the
  // input sequence, and stores the result to the output sequence
  //assert(out[i] == in[i] + 1); // for all i
  std::cout << out.size() << std::endl;
  for_each(out.begin(), out.end(), printvec);
}
