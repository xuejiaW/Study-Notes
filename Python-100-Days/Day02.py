# Parameter

# intNum1 = 321
# intNum2 = 123

# print(intNum1 + intNum2)
# print(intNum1 - intNum2)
# print(intNum1 * intNum2)
# print(intNum1 / intNum2)  # Auto switch to float
# print(intNum1 // intNum2)  # will not Auto switch to float
# print(intNum1 % intNum2)  # Module Operation
# print(intNum1 ** intNum2)  # Exp Operation


# inputNum = int(input("intNum1="))
# print("Input Num is %d" % inputNum)

# intNum3 = 100
# floatNum1 = 12.345
# complexNum = 1+5j
# string1 = "hellow world"
# boolean1 = True

# print(type(intNum3))
# print(type(floatNum1))
# print(type(complexNum))
# print(type(string1))
# print(type(boolean1))

# # Convert Fahrenheit to Celsius
# FTem = int(input("请输入华氏温度: "))
# CTem = FTem*1.8+32
# print("摄氏温度为 %.1f" % CTem)

# Judge whether it is leap year
year = int(input("请输入年份："))
leap = year % 4 == 0 and year % 100 != 0 \
        or year % 400 == 0
print(leap)
