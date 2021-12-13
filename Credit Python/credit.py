from cs50 import get_int
import sys

# Getting input from user
number = get_int("Number: ")

# Coverting input to string
s = str(number)
length = len(s)

# checking for valid input length
if length < 13 or length > 16:
    print("INVALID")
    sys.exit()

# setting a total variable
total = 0

# checking for card validity using luhn's algorithm
if len(s) % 2 == 0:
    for i in range(0, length, 2):
        multiplied = int(s[i]) * 2
        if multiplied > 9:
            multiplied = str(multiplied)
            total = total + int(multiplied[0]) + int(multiplied[1])
        else:
            total += int(s[i]) * 2
   
    for i in range(1, length, 2):
        total += int(s[i])
    
    if total % 10 != 0:
        print("INVALID")
        sys.exit()
    
else:
    for i in range(1, length, 2):
        multiplied = int(s[i]) * 2
        if multiplied > 9:
            multiplied = str(multiplied)
            total = total + int(multiplied[0]) + int(multiplied[1])
        else:
            total += int(s[i]) * 2
    
    for i in range(0, length, 2):
        total += int(s[i])
    
    if total % 10 != 0:
        print("INVALID")
        sys.exit()
    
# checking if card is AMEX
if length == 15 and int(s[0]) == 3 and int(s[1]) in [4, 7]:
    print("AMEX")
    sys.exit()

# OR MASTERCARD
elif length == 16 and int(s[0]) == 5 and int(s[1]) in [1, 2, 3, 4, 5]:
    print("MASTERCARD")
    sys.exit()

# OR VISA
elif int(s[0]) == 4 and length in [13, 14, 15, 16]:
    print("VISA")
    sys.exit()
