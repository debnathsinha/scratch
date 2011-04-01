#include <stdio.h>

int main() {

  char c;
  while( (c = getchar()) != '3' ) {
    printf("%c ", c);
  }
}
