# Day5 is the practice of the logic, so i have skipped it


# # function example
# def factorial(num):
#     result = 1
#     for n in range(1, num+1):
#         result *= n
#     return result


# m = int(input("m= "))
# n = int(input("n= "))

# print("result = %d " % (factorial(m) // factorial(n) // factorial(m-n)))


# # arguments array example
# def add(* args):
#     result = 1
#     for n in args:
#         result += n
#     return result


# print("Add function %d" % add(1, 2, 3, 4, 5))


# # Test multiplay functions with the same name

# def foo() :
#     print("This is foo function 1")

# def foo() :
#     print("This is foo function 2")

# foo()

# # import the method in other's name
# from Module1 import foo
# from Module2 import foo

# foo()

# # import the other file as other name

# import Module1 as M1
# import Module2 as M2

# M1.foo()
# M2.foo()


# # global argument and local argument

# a = 100
# print("a value before change is %d" % a)

# def testLocalArgument():
#     nonlocal a
#     a = 200

# testLocalArgument()
# print("a value is %d" % a)

# nested argument and local argument

def testNestedArgument():
    a=100
    print("a value in function is %d" % a)
    def NestedFunction(): 
        nonlocal a
        a=200
    NestedFunction()
    print("a value after  nested function is %d" % a)    

testNestedArgument()
    