
#include <stdio.h>
void happy(int score) { printf("%d is great!\n", score); }

void sad(int score) { printf("%d sucks!\n", score); }

int main() {
  // Declare funciton pointer variable
  void (*my_func)(int);

  // Change value, just like a variable, no ()
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      my_func = happy;
    } else {
      my_func = sad;
    }

    my_func(i);
  }
  return 0;
}
