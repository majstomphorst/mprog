#include <stdio.h>
#include <cs50.h>

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

        // check valide lenght
        if (card_lenght != 13 &&
            card_lenght != 15 &&
            card_lenght != 16) {
                printf("INVALID\n");
                exit(0);
        }

        // peform luhn's algorithm
        if (luhns_algorithm(card_number) != true) {
                printf("INVALID\n");
                exit(0);
        }

        // get the first two digit's from the card number
        int first_two = get_first_two_digits(card_number);

        if (first_two == 34 || first_two == 37) {
                printf("AMEX\n");

        } else if (first_two >= 51 && first_two <= 55) {
                printf("MASTERCARD\n");

        } else if (first_two / 10 == 4) {
                printf("VISA\n");

        } else {
                printf("INVALID\n");
        }

}

int get_card_lenght(long long card_number) {

        int count = 0;

        while (card_number != 0) {
                count++;
                card_number = card_number / 10;
        }
        return count;
}

bool luhns_algorithm(long long card_number) {

        int checksum = 0;

        while (card_number != 0) {

                int last_digit = card_number % 10;
                int second_last_digit = (card_number / 10) % 10;

                int sum = second_last_digit * 2;

                if (sum > 9) {
                        sum = 1 + (sum - 10);
                }

                checksum += (sum + last_digit);
                card_number /= 100;
        }

        if (checksum % 10 != 0) {
                return false;
        } else {
                return true;
        }
}

int get_first_two_digits(long long digits) {

        // get first 2 digits
        while (digits >= 100) {
                digits = digits / 10;
        }

        return digits;
}
