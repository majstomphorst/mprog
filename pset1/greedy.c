/****************************************************************************
 * greedy.c methode: %
 * Programmeren 1 - pset1 - exercise 04
 * By Maxim Stomphorst
 *
 * Calculte the least amount of coins needed to change.
 ***************************************************************************/

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void) {
  float input_float;
  do {
    // asking the amount of change
    // float value because it money
    printf("Change: ");
    input_float = get_float();
  }
  // restricting user input
  while (input_float < 0.0);

  // convert because of impressision
  int input = (int)roundf(input_float * 100);
  // count is the number of coins needed
  int count = 0;
  // change is money left
  int change = 0;

  // callculating the coins
  // every if update's the input, count, change
  change = input % 25;
  count += ((input - change)) / 25;
  input = change;

  change = input % 10;
  count += ((input - change)) / 10;
  input = change;

  change = input % 5;
  count += ((input - change)) / 5;
  input = change;

  change = input % 1;
  count += ((input - change)) / 1;
  input = change;

  // printing least amount of coins needed to change
  printf("%i\n", count);
}
