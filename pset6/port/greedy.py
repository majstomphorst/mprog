# greedy.py
# Programmeren 02 - pset 06 - exercise 02
# By Maxim Stomphorst
# 
# Calculte the least amount of coins needed to change.

import cs50


def main():
    
    # getting user input with a restriction
    while True:
        print("change: ", end="")
        input_float = cs50.get_float()
        if input_float > 0.0:
            break

    # converting float to int and rounding off
    money = round(input_float * 100)
    # keeping track off the number of coins
    coin_count = 0
    # declaring coin size's
    coins = [25, 10, 5]
    
    # selecting each coin in coins
    for coin in coins:
        # returns the (remaining) money and the number of coins needed
        money, coin_count = change_calculator(coin, money, coin_count)
    
    # printing least amount of coins needed to change
    print(coin_count + money)


def change_calculator(coin_size, money, coin_count_old):
    remainder = money % coin_size
    coin_count = ((money - remainder) / coin_size) + coin_count_old
    money = remainder
    
    return money, int(coin_count)
    

if __name__ == "__main__":
    main()

