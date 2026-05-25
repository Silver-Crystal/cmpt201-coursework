#include <stdio.h>
#include <stdlib.h>

int make_abs_get_product(int *pA, int *pB) {
  *pA = abs(*pA);
  *pB = abs(*pB);
  return *pA * *pB;
}
int main() {
  int w = -4;
  int h = 5;
  int area = make_abs_get_product(&w, &h);
  printf("%d X %d = %d", w, h, area);
  return 0;
}
