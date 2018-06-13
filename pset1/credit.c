/*******************************
 * credit.c
 * By Maxim Stomphorst
 * check if a credit card number is
 * valide
 *******************************/

#include <cs50.h>
#include <stdio.h>

// function declaration
int get_card_lenght(long long card_number);
bool luhns_algorithm(long long card_number);
int get_first_two_digits(long long card_number);

int main(void) {

  // create placeholder for credit card number
  long long card_number;

  // get number and validate input
  do {
    card_number = get_long_long("Number: ");
  } while (card_number < 0);

  // count the digits in card number
  int card_lenght = get_card_lenght(card_number);

  // check credit card number for valide lenght
  if (card_lenght != 13 && card_lenght != 15 && card_lenght != 16) {
    printf("INVALID\n");
    exit(0);
  }

  // check credit card number with luhn's algorithm
  if (luhns_algorithm(card_number) != true) {
    printf("INVALID\n");
    exit(0);
  }

  // get the first two digit's from the credit card number
  int first_two = get_first_two_digits(card_number);

  // check to what compay the credit card belongs
  if (first_two == 34 || first_two == 37) {
    printf("AMEX\n");

  } else if (first_two >= 51 && first_two <= 55) {
    printf("MASTERCARD\n");

  } else if (first_two / 10 == 4) {
    printf("VISA\n");

  } else {
    // if the number doesnt start with a know number
    printf("INVALID\n");
  }
}

/*
  Counts the amount of digits that are given to it.
*/
int get_card_lenght(long long card_number) {

  int count = 0;

  while (card_number != 0) {
    count++;
    card_number = card_number / 10;
  }
  return count;
}

/*
  Implementation of luhn's algorithm credit card number checksum.
  If the number passes the test it returns true.
  If it fails returns fales.
*/
bool luhns_algorithm(long long card_number) {

  int checksum = 0;

  // every loop decreases the number until its 0
  while (card_number != 0) {

    // get the last and second to last digit
    int last_digit = card_number % 10;
    int second_last_digit = (card_number / 10) % 10;

    // first luhns check
    int sum = second_last_digit * 2;

    // if sum is greater than 9 (luhns)
    if (sum > 9) {
      // the sum changes (if 14 its 1+4) (luhns)
      sum = 1 + (sum - 10);
    }

    // creates the checksum (luhns)
    checksum += (sum + last_digit);

    // removes the last 2 digits
    card_number /= 100;
  }

  // check if the checksum ends in a 0 (luhns)
  if (checksum % 10 != 0) {
    return false;
  } else {
    return true;
  }
}

/*
  Returns the first to digits of the number that is given.
*/
int get_first_two_digits(long long digits) {

  // while the number has more than triple digits
  while (digits > 99) {
    // removes the last digit
    digits = digits / 10;
  }
  return digits;
}
