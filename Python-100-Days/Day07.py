# String Part

# # Test quotes
# s1 = 'hello, world'
# s2 = "hello, world"

# s3 = """
# hello,
# world!
# """

# print(s1, s2, s3, end='')


# # Test some operators
# s1 = "hello" * 3
# print("s1 is ", s1)
# S2 = 'world'
# s1 += S2
# print("new S1 is ", s1)

# print("Whether s1 include ll ", "ll" in s1)
# print("Whether s1 include aa ", "aa" in s1)

# s3 = 'abc123456'

# print(s3[2])  # c
# print(s3[2:5])  # c12
# print(s3[2:]) # c123456
# print(s3[2::2]) # c246 :: means step
# print(s3[2:5][::2]) #c2 multiply [] can be used together
# print(s3[::-1]) # 654321cba
# print(s3[-3:-1]) #45


# # Test some build-in method about string

# s1 = "hello, world!"

# print(len(s1))
# print(s1.capitalize())  # Get a copy with the capitalization of the first letter
# print(s1.title())  # Get a copy with the capitalization of the every letter
# print(s1.lower())
# print(s1.upper())
# print(s1)  # To ensure all the methods haven't changed the original string
# print(s1.find("or"))
# print(s1.find("shit"))
# print(s1.index("or"))
# # print(s1.index("shit")) # will trigger a error
# print(s1.startswith("He"))
# print(s1.startswith("hel"))
# print(s1.endswith("!"))
# print(s1.center(50, "*"))
# print(s1.rjust(50, "*"))

# s2 = "abc123456"
# print(s2.isdigit())  # all number, false
# print(s2.isalpha())  # all alpha, false
# print(s2.isalnum())  # mixture of number and alpha, true

# s3 = '   abc    '
# print("String 3 is ", s3)
# print("String 3 with strip is ", s3.strip())


# # Format Method

# a, b = 5, 10
# print("%d * %d = %d " % (a, b, a*b))
# print("{0} * {1}= {2}".format(a, b, a*b))
# print(f"{a} * {b} = {a*b}")


# List Part

# # basic method of List
# list1 = [1, 3, 5, 7, 100]
# print(list1)
# list2 = ["hello"] * 5
# print(list2)
# print(len(list1))  # 5
# print(list1[0])  # 1
# print(list1[4])  # 100
# # print(list1[5]) # IndexError: list index out of range
# print(list1[-1])  # 100
# print(list1[-3])  # 5
# list1[2] = 300
# print(list1)  # 1, 3, 300, 7, 100

# list1.append(200)
# list1.insert(1, 400)
# print(list1)  # 1, 400, 3, 300, 7, 100, 200
# list1 += [1000, 2000]
# print(list1)  # 1, 400, 3, 300, 7, 100, 200, 1000, 2000

# list1.remove(3)
# if 1234 in list1:
#     # remove the 1234, if there is no 1234,will throw ValueError
#     list.remove(1234)

# print(list1)  # 1, 400, 300, 7, 100, 200, 1000, 2000
# del list1[0]
# print(list1)  # 400, 300, 7, 100, 200, 1000, 2000

# list1.clear()
# print(list1)  # []

# # slice method of list

# fruits = ["grapa", "apple", "strawberry", "waxberry"]
# fruits += ["pitaya", "pear", "mango"]

# for fruit in fruits:
#     print(fruit.title(), end=" ")

# fruits2 = fruits[1:4]
# print("\nfruits2 is ", fruits2, end=" ") # fruits2 is only the copy of the fruits
# print("\nfruits is ", fruits, end=" ")
# fruitsReverse = fruits[::-1]
# print("\nfruitsReverse is ", fruitsReverse, end=" ")

# # Sort Method

# list1= ["orange", "apple", "zoo", "internationalization", "blueberry"]
# list2= sorted(list1) # a sorted copy of list1
# list3=sorted(list1,reverse=True)
# list4=sorted(list1,key=len)
# print("List1 is ",list1) # 'orange', 'apple', 'zoo', 'internationalization', 'blueberry'
# print("List2 is ",list2) # 'apple', 'blueberry', 'internationalization', 'orange', 'zoo'
# print("List3 is ",list3) # 'zoo', 'orange', 'internationalization', 'blueberry', 'apple'
# print("List4 is ",list4) # 'zoo', 'apple', 'orange', 'blueberry', 'internationalization'

# list1.sort(reverse = True) # This will change the list1
# print(list1) # 'zoo', 'orange', 'internationalization', 'blueberry', 'apple'

# # List Genreate

# import sys
# f = [x for x in range(1, 10)]
# print(f)  # 1,2,3,4,5.....10
# f = [x+y for x in "ABCDE" for y in "1234567"]
# print(f)  # A1,A2,A3......E5,E6,E7
# f = [x**2 for x in range(1, 10)] # [] means a list
# print(sys.getsizeof(f)) # Memory Used by f
# print(f)
# f=( x**2 for x in range(1,10)) # () means a generator
# print(sys.getsizeof(f)) # Memory Used by f
# print(f)

# # make a generator

# def fib(n):
#     a, b = 0, 1
#     for _ in range(n):
#         a, b = b, a+b
#         yield a


# for val in fib(20):
#     print(val)


# # Tuple

# tup = ("ABC", 38, True,)
# print(tup)
# print(tup[0])
# for t in tup:
#     print(t)
# # tup[0] = "DEF" # Will throw type error
# list1 = list(tup)  # change the tuple to List
# list1[0] = "DEF"
# for i in list1:
#     print(i)

# tup2=tuple(list1) # change the list to tuple


# # Set

# set1 = {1, 2, 3, 3, 2}
# print(set1)  # 1, 2, 3
# print("length of set1 is ", len(set1))
# set2 = set(range(1, 10))
# print(set2)  # 1,2,3,4,5,6,7,8,9
# set1.add(4)
# set1.add(5)
# set2.update([11, 12])  # union
# print(set2)  # 1,2,3,4,5,6,7,8,9,11,12
# if(4 in set2):  # need to check first or there will be a error
#     set2.remove(4)
# set3 = set((1, 2, 3, 3, 2, 1))
# print("set 1 is ", set1)  # 1,2,3,4,5
# print("set 2 is ", set2)  # 1,2,3,5,6,7,8,9,11,12
# print("set 3 is ", set3)  # 1,2,3
# print("set 1 & set 2 is ", set1 & set2)  # 1,2,3,5
# print("set 1 | set 2 is ", set1 | set2)  # 1,2,3,4,5,6,7,8,9,11,12
# # 4 the elements which set1 has but set2 doesn't has
# print("set 1 - set 2 is ", set1 - set2)
# # 6,7,8,11,12 the elements which set2 has but set1 doesn't has
# print("set 2 - set 1 is ", set2 - set1)
# # 4,6,7,8,11,12 the elements in either the set or other but not both
# print("set 1 ^ set 2 is ", set1 ^ set2)

# print(set2 <= set1)
# print(set3 <= set1)
# print(set1 >= set2)
# print(set1 >= set3)

# Dictionay

dict1 = {"ABC": 95, "DEF": 100, "GHI": 120}

print(dict1["ABC"])
# print(dict1["JKL"]) # Will throw key error
print(dict1.get("JKL"))  # return null
print(dict1.get("JKL", 50)) # return 50
for elem in dict1:
    print(" %s \t ---> \t %d" % (elem, dict1[elem]))
    
dict1.popitem() # pop the last item, if the dict is empty,throw key error
dict1.pop("ABC",93) # pop the item with key "ABC",if exist return the key value,else return default value 93

print(dict1)
