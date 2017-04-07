# mario.py More comfortable
# Programmeren 02 - pset 06 - exercise 01
# By Maxim Stomphorst
#
# this is a port form C to Python.
# Print 2 Mario pyramid's one up and one down with space in between.

import cs50

# Get pyramid height and restricht user input
while True:
    print("height: ", end="")
    height = cs50.get_int()
    if height > 0 and height < 23:
        break

# printing the pyramid
# the fist loop print the enters
# the inner loops prints the space and hash's
# first " " second "#" third "  " fourth "#"
for enter in range(height):
    for space in range(height - enter):
        print(" ", end="")

    for space in range(enter + 1):
        print("#", end="")

    print("  ", end="")

    for space in range(enter + 1):
        print("#", end="")

    print("")
