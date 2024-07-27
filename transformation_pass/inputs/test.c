#include <stdio.h>

void test() 
{
  int x = 15;

  if (x > 45) {
    printf("Greater\n");
  } else {
    printf("Lesser\n");
  }
}

int main() {
  test();
  return 0;
}