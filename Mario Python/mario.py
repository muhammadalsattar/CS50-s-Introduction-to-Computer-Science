from cs50 import get_int

# getting height from user
h = get_int("Hieght: ")

# prompting user for height if entered invalid value
while h < 1 or h > 8:
    h = get_int("Hieght: ")

# bulding the pyramids
for i in range(1, h+1):
    
    # printing pre-spaces for left side pyramid
    for r in range(h - i):
        print(" ", end='')
    
    # building left-side pyramid
    for j in range(1, i+1):
        print("#", end='')
    
    # printing in-between spaces
    print("  ", end='')

    # printing right-side pyramid
    for k in range(1, i+1):
        print("#", end='')
    
    # ending each line with line break
    print("")