# Judge what to do next according to the dice

from random import randint  # Use the randint function in random module

face = randint(1, 6)

if face == 1:
    print("唱首歌")
elif face == 2:
    print("跳个舞")
elif face == 3:
    print("学狗叫")
elif face == 4:
    print("俯卧撑")
elif face == 5:
    print("绕口令")
else:
    print("讲笑话")
