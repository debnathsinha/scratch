#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;

int * intersect( int a[], int a_len, int b[], int b_len ) {

  sort(a, a + a_len);
  sort(b, b + b_len);

  int *c = (int *)malloc( sizeof(int) * min(a_len , b_len));
  int a_head = 0, b_head = 0;
  int k = 0;
  for( int i = 0,j = 0; i < a_len && j < b_len; ) {
      if( a[i] < b[j] ) {
	i++;
      }else if( a[i] > b[j] ) {
	j++;
      } else {
	assert( a[i] == b[j] );
	c[k++] = a[i++]; 
      }
    }
  for( int k1 = 0; k1 < k; k1++ )
    cout << c[k1] << " ";
  cout << endl << k << endl;
  return c;
}

int * setunion( int a[], int a_len, int b[], int b_len ) {

  sort(a, a + a_len);
  sort(b, b + b_len);

  int * c = (int *) malloc( sizeof(int) * (a_len + b_len) );
  int i,j, k = 0;
  for( i = 0, j = 0; i < a_len && j < b_len; ) {
    assert( (i + j) < (a_len + b_len) );
    if( a[i] < b[j] ) {
      c[k++] = a[i++];
    } else if ( a[i] > b[j] ) {
      c[k++] = b[j++];
    } else {
      assert( a[i] == b[j] );
      c[k++] = a[i++];
      j++;
    }
  }
  assert(!((i < a_len) && (j < b_len)));

  for( ; i < a_len; )
    c[k++] = a[i++];

  for( ; j < b_len; )
    c[k++] = b[j++];

  k--;
  assert( k <= a_len + b_len );
  for( int k1 = 0; k1 < k; k1++ )
    cout << c[k1] << " ";
  cout << endl << k << " " << i  << " " << j << endl;

  return c;
}

int main( int argc, char ** argv ) {

  int a[] = { 1,2,3,4,5,6,7,8,9};
  int b[] = {2,4,6,8};

  intersect(a,9,b,5);
  setunion(a,9,b,5);
}
