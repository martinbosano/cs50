from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break

width = (height * 2) + 2
counter = 0
for row in range(height):
    counter += 1
    for line in range(height):
        if line < height - counter:
            print(" ", end="")
            line += 1
        else:
            print("#", end="")
    print("  ", end= "")
    for line in range(height):
        line += 1
        if line < counter + 1:
            print("#", end="")
    print()