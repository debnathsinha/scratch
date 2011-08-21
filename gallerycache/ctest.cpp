#include <iostream>
#include <vector>
using namespace std;

#define ARR_SIZE 64 * 1024 * 1024

vector<int> arr(ARR_SIZE);

int main() {
	//for(int i = 0; i< arr.size(); i++) { arr[i] = arr[i] * 5 + 4; }
	for(int i = 0; i < arr.size(); i+=16) { arr[i] = arr[i] * 5 + 4; }
}
