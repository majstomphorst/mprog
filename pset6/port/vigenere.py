# vigenere.py
# Programmeren 02 - pset 06 - exercise 03
# By Maxim Stomphorst
#
# This converts text to ciphertext with a key that the user give's.
# But the key is a word in this case.

import cs50
import sys

# checking if the user gave a key
if not len(sys.argv) == 2:
    print("Usage: ./vigenere key")
    exit(1)

# check if the key alphabetical
if not sys.argv[1].isalpha():
    print("the key must be alphabetica!")
    exit(2)

# converting key too lowercase
key = sys.argv[1].lower()

# asking user for input
print("Plaintext: ", end="")
plaintext = cs50.get_string()

# indipendent counter for iterating over the key
j = 0
key_lenght = len(key)
print("ciphertext: ", end="")

# gowing through plaintext char for char (i)
# gowing throug key char for char (j) only j++ when used
for letter in plaintext:
    # checking if ith char is upper
    if letter.isupper():
        # convert ascii(upper) to alphabet count (0...26) | - 64
        # wrap around key | j % key_lenght
        # convert ascii(lower) to alphabet count (0...26) | - 97
        # wrap around alphabet | % 26
        # convert alphabet count back to ascii(upper) | + 64
        print(chr(((ord(letter) - ord('A') + (ord(key[j % key_lenght]) -
                                              ord('a'))) % 26) + ord('A')), end="")
        j += 1

    # checking if ith char is lower
    elif letter.islower():
        # every char is lower - 97 no convertion too / from upper
        print(chr(((ord(letter) - ord('a') + (ord(key[j % key_lenght]) -
                                              ord('a'))) % 26) + ord('a')), end="")
        j += 1

else:
    # downt convert
    print(letter, end="")

print()
exit(0)

