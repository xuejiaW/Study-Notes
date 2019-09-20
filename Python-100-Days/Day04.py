# 99 multiplication table

import random
for i in range(1, 10):
    for j in range(1, i+1):
        print("%d * %d = %d" % (i, j, i*j))

# guess the number


randomNumber = random.randint(1, 100)

while True:
    guess = int(input("Guess a number :"))
    if guess > randomNumber:
        print("Should be smaller")
    elif guess < randomNumber:
        print("Should be larger")
    else:
        print("Right, the number is %d" % randomNumber)
        break
