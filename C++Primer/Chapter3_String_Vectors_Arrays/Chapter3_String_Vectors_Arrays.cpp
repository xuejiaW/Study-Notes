// Chapter3_String_Vectors_Arrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using std::begin;
using std::cin;
using std::cout;
using std::end;
using std::endl;
using std::string;
using std::vector;

void TestNamespace();
void TestStringInitialization();
void TestStringInput();
void TestStringGetLine();
void TestAddingLiterals();
void TestRangeFor();
void TestSubscriptIteration();
void Exercise3_10();
void TestVectorInitialization();
void TestIteratorLoop();
void BinarySearchUsingIterator();
void TestArrayInitialization();
void TestComplicatedArrayDeclaration();
void TestAccessElementsInArray();
void TestPointersAndArrays();
void TestPointerAsIterators();
void TestDereferencAndPointerArithmetic();
void TestSubscriptsAndPointers();
void Exercise3_36();
void TestCStyleCharacterString();
void TestInterfacingToOlderCode();
void TestUsingArrayToInitializeVector();
void TestUsingRangeForWithMultidimensionalArray();
void TestPointerAndMultidimensionalArrays();
void TestSubscriptionMultidimensionalArray();
void TestTypeAliasesForMultidimensionalArray();

int main()
{
    // TestNamespace();
    // TestStringInitialization();
    // TestStringGetLine();
    // TestAddingLiterals();
    // TestRangeFor();
    // TestSubscriptIteration();
    // Exercise3_10();
    // TestVectorInitialization();
    // TestIteratorLoop();
    // BinarySearchUsingIterator();
    // TestComplicatedArrayDeclaration();
    // TestAccessElementsInArray();
    // TestPointersAndArrays();
    // TestPointerAsIterators();
    // TestDereferencAndPointerArithmetic();
    // TestSubscriptsAndPointers();
    // Exercise3_36();
    // TestCStyleCharacterString();
    // TestInterfacingToOlderCode();
    // TestUsingArrayToInitializeVector();
    // TestUsingRangeForWithMultidimensionalArray();
    // TestPointerAndMultidimensionalArrays();
    // TestSubscriptionMultidimensionalArray();
    TestTypeAliasesForMultidimensionalArray();
}

void TestTypeAliasesForMultidimensionalArray()
{
    // using int_array = int[4];
    typedef int int_array[4];

    int ic[3][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};

    for (int_array *p = ic; p != ic + 3; ++p)
    {
        for (int *q = (*p); q != (*p) + 4; q++)
        {
            cout << (*q) << " ";
        }
    }
    cout << endl;
    /*
    0 1 2 3 4 5 6 7 8 9 10 11
    */
}

void TestPointerAndMultidimensionalArrays()
{
    int ic[3][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};

    for (int(*p)[4] = ic; p != ic + 3; ++p)
    {
        for (int *q = (*p); q != (*p) + 4; q++)
        {
            cout << (*q) << " ";
        }
    }
    cout << endl;
    /*
    0 1 2 3 4 5 6 7 8 9 10 11
    */

    for (int(*p)[4] = begin(ic); p != end(ic); ++p)
    {
        for (int *q = begin(*p); q != end(*p); q++)
        {
            cout << (*q) << " ";
        }
    }
    cout << endl;
    /*
    0 1 2 3 4 5 6 7 8 9 10 11
    */
}

void TestSubscriptionMultidimensionalArray()
{
    int ic[3][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << ic[i][j] << " ";
        }
    }
    cout << endl;
    /*
    0 1 2 3 4 5 6 7 8 9 10 11
    */
}

void TestUsingRangeForWithMultidimensionalArray()
{
    int ic[3][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};
    for (auto &row : ic)
    {
        for (auto &col : row)
        {
            cout << col << " ";
        }
    }
    cout << endl;

    for (auto &row : ic)
    {
        for (auto col : row)
        {
            cout << col << " ";
        }
    }
    cout << endl;

    // for (auto row : ic)
    // {
    //     for (auto col : row)
    //     {
    //         cout << col << " ";
    //     }
    // }
    // cout << endl;

    /*
    0 1 2 3 4 5 6 7 8 9 10 11 
    0 1 2 3 4 5 6 7 8 9 10 11
    */
}

void TestMultidimensionalArrayInitialization()
{
    int ia[3][4];   //without initialization;
    int ib[3][4]{}; //All elements will be 0
    int ic[3][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}};
    int id[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int ie[3][4] = {{0}, {4}, {8}};
    int ix[3][4] = {0, 4, 8};
}

void TestUsingArrayToInitializeVector()
{
    int intArr[]{0, 1, 2, 3, 4, 5};
    vector<int> intVec(begin(intArr), end(intArr));
    for (auto i : intVec)
    {
        cout << i << " ";
    }
    cout << endl;

    intVec = vector<int>(intArr, intArr + 3);
    for (auto i : intVec)
    {
        cout << i << " ";
    }
    cout << endl;

    /*
    0 1 2 3 4 5 
    0 1 2
    */
}

void TestInterfacingToOlderCode()
{
    string s = "ABCD";
    cout << "value is " << s << ", size is " << s.size() << endl;
    char cs[]{'A', 'B', 'C', 'D', '\0'};
    string sc = cs;
    cout << "value is " << sc << ", size is " << sc.size() << endl;
    char cs2[]{'A', 'B', 'C', 'D'};
    string sc2 = cs2;
    cout << "value is " << sc2 << ", size is " << sc2.size() << endl;

    /*
    value is ABCD, size is 4
    value is ABCD, size is 4
    value is ABCD慅a, size is 7
    */

    // char *cs3 = s; //error,can't direct convert
    const char *cs3 = s.c_str();
    cout << "value is " << cs3 << endl;
    s = "DEFC";
    cout << "value is " << cs3 << endl;
    string css = cs3;
    cout << "value is " << css << ", size is " << css.size() << endl;

    /*
    value is ABCD
    value is DEFC
    value is DEFC, size is 4
    */
}

void TestCStyleCharacterString()
{
    string s1 = "A string example";
    string s2 = "A different string";
    cout << (s1 > s2) << endl;
    char cs1[] = "A string example";
    char cs2[] = "A different string";
    cout << (cs1 > cs2) << endl;      //wrong way,no meaning, is comparing address of first element
    cout << strcmp(cs1, cs2) << endl; //correct way

    /*
    1
    1
    1

    Although cs1>cs1 also yield correct result,but it's no meaning.
    */

    char ca[]{'a', 'b', 'c'};
    cout << strlen(ca) << endl;

    /*
    21
    */
}

bool CompareTwoArray(int *const pb1, int *const pe1, int *const pb2, int *const pe2)
{
    if ((pe1 - pb1) != (pe2 - pb2))
        return false; //Different length

    for (auto i = pb1, j = pb2; i < pe1 && j < pe2; i++, j++)
    {
        if ((*i) != (*j))
            return false;
    }
    return true;
}

void Exercise3_36()
{
    int arr1[]{1, 2, 3, 4};
    int arr2[]{1, 2, 3, 4};
    int arr3[]{1, 2, 3, 4, 5};
    int arr4[]{1, 2, 3, 5};
    cout << CompareTwoArray(begin(arr1), end(arr1), begin(arr2), end(arr2)) << endl;
    cout << CompareTwoArray(begin(arr1), end(arr1), begin(arr3), end(arr3)) << endl;
    cout << CompareTwoArray(begin(arr1), end(arr1), begin(arr4), end(arr4)) << endl;

    /*
    1
    0
    0
    */
}

void TestSubscriptsAndPointers()
{
    int ia[] = {0, 2, 4, 6, 8, 10};
    int *iaP = &ia[2];
    cout << *iaP << endl;       //Third element
    cout << iaP[-2] << endl;    //First element
    cout << *(iaP - 2) << endl; //First element,same with last expression
    cout << iaP[-3] << endl;    //undefined result

    int a = 2;
    int *ap = &a;
    cout << ap[0] << endl;  // a
    cout << ap[-1] << endl; //undefined result
}

void TestDereferencAndPointerArithmetic()
{
    int ia[] = {0, 2, 4, 6, 8, 10};
    cout << *(ia + 4) << endl; //Access the fifth element
    cout << *ia + 4 << endl;   //Access the first element and add 4 to the result

    /*
    8
    4
    */
}

void TestPointerAsIterators()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *endPtr = &arr[10]; //point to one past last elemment
    cout << "value is: " << endl;
    for (int *i = arr; i != endPtr; i++)
    {
        cout << (*i) << " ";
    }
    cout << endl;

    /*
    value is: 
    0 1 2 3 4 5 6 7 8 9
    */

    int *oBeg = arr;
    int *oEnd = &arr[10];
    int *beg = std::begin(arr);
    int *end = std::end(arr);
    cout << "Begin is " << (oBeg == beg ? "the same" : "not the same") << endl;
    cout << "End is " << (oEnd == end ? "the same" : "not the same") << endl;
    /*
    Begin is the same
    End is the same
    */

    cout << "value of end is " << *end << endl;
    cout << "value of end next is " << *(++end) << endl;

    int i = 0, sz = 42;
    int *p = &i, *e = &sz;
    cout << (p < e ? "p is smaller than e" : "p is larger than e") << endl;
}

void TestPointersAndArrays()
{
    string nums[] = {"one", "two", "three"};
    cout << (*nums) << endl;
    string *p = nums;
    string *pp = &nums[0];
    if (p == pp)
        cout << "two pointers are the same" << endl;
    else
        cout << "they are different" << endl;

    /*
    one
    two pointers are the same
    */

    auto pnums = nums; // same as auto pnums = &nums[0]
    // pnums = "zero";
    (*pnums) = "zero";
    cout << "first element is " << nums[0] << endl;

    /*
    first element is zero
    */

    decltype(nums) another = {"abc", "def"};
    for (auto n : another)
    {
        cout << "value is " << n << endl;
    }
    /*
    value is abc
    value is def
    value is
    */
}

void TestAccessElementsInArray()
{
    // unsigned scores[11];//warning,not defined value
    unsigned scores[11] = {};
    unsigned grade;
    while (cin >> grade)
    {
        if (grade <= 100)
        {
            ++scores[grade / 10];
        }
    }
    for (auto c : scores)
    {
        cout << " " << c << " ";
    }
}

void TestComplicatedArrayDeclaration()
{
    int array[10];
    int *ptrs[10]; // ptrs is an array of size 10 where elements type is int*
    // int &refs[10];//error,refs seems to be an array where elemtns type is int&, however reference is not object
    int(*parray)[10] = &array;   //parray is a pointer point to an int array of size 10
    int(&rarray)[10] = array;    //rarray is a reference bind to an int array of size 10
    int *(*pparray)[10] = &ptrs; //pparray is a pointer point to an int* array of size 10
}

void TestArrayInitialization()
{
    unsigned num = 42;
    const unsigned cnum = 42;
    int arr[10];
    // int arr2[]; //error,must indicate array size
    // auto aarr[] = {1, 2, 3}; //error,can not use auto
    // auto aarr[10]; //error,can not use auto
    // int arr2[num]; //error,num is not const
    int arr3[cnum];

    const unsigned sz = 3;
    int ia1[sz] = {1, 2, 3};
    int a2[] = {0, 1, 2};          //array size is 3
    int a3[5] = {0, 1, 2};         //array size is 5, value is 0,1,2,0,0
    string sa[sz] = {"hi", "byt"}; //size is 3,value is "hi" "bye" ""
    // int a4[sz] = {0, 1, 2, 3};     //error, list elements count is greater than array size

    char ca1[] = {'c', 'b', 'a'};       //size is 3
    char ca2[] = {'c', 'b', 'a', '\0'}; //size is 4
    char ca3[] = "abc";                 //size is 4
    // const char a4[6] = "Daniel";       //error,no space for \0

    int a[] = {0, 1, 2};
    // int aa[] = a;   //error
    // int aa[] = a[]; //still error
    int aa[3];
    // aa = a;         //error,can't use assignment
}

void BinarySearchUsingIterator()
{
    string text = "abcdefghijk";
    char toSearch;
    cin >> toSearch;
    auto beg = text.cbegin(), end = text.cend();
    auto mid = beg + (end - beg) / 2;
    while (mid != end && (*mid) != toSearch)
    {
        if (toSearch < (*mid))
            end = mid;
        else
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }
    cout << (end != mid ? "Found" : "Not Found") << endl;
}

void TestIteratorType()
{
    vector<int> v1{1, 2, 3};
    const vector<string> v2{"a", "b", "c"};

    vector<int>::iterator v1Iter = v1.begin();
    vector<int>::const_iterator v1Iter2 = v1.begin();
    const vector<int>::iterator v1Iter3 = v1.begin();
    // (*v1Iter2) = 2;//error,can't modify value through const_iterator
    ++v1Iter2;
    // ++v1Iter3; //can't modify const iterator

    // vector<string>::iterator v2Iter = v2.begin(); //error, must be const_iterator
    vector<string>::const_iterator v2Iter2 = v2.begin();
    // const vector<string>::iterator v2Iter3 = v2.begin(); //error,still must be const_iterator

    auto cIter = v1.cbegin();
}

void TestIteratorLoop()
{
    string s("Hello World!!!");

    for (decltype(s.size()) i = 0; i != s.size(); i++)
    {
        s[i] = toupper(s[i]);
    }

    cout << "result is " << s << endl;

    s = "Hello World!!!";
    for (auto i = s.begin(); i != s.end(); i++)
    {
        (*i) = toupper(*i);
    }

    cout << "result is " << s << endl;

    /*
    result is HELLO WORLD!!!
    result is HELLO WORLD!!!
    */
}

void TestVectorInitialization()
{
    vector<int> intList_1(10);
    // vector<string> intList_1("abc");//error
    vector<int> intList_2{10};
    vector<int> intList_3(10, 1);
    vector<int> intList_4{10, 1};
    cout << "vector_1 size is " << intList_1.size() << endl;
    cout << "vector_2 size is " << intList_2.size() << endl;
    cout << "vector_3 size is " << intList_3.size() << endl;
    cout << "vector_4 size is " << intList_4.size() << endl;
    /*
    vector_1 size is 10
    vector_2 size is 1
    vector_3 size is 10
    vector_4 size is 2
    */

    vector<string> v5{"hi"};
    // vector<string> v6("hi");//Error, value in parentheses must be digit
    vector<string> v7{10};
    vector<string> v8{10, "hi"}; //try to analyse as parentheses
    // vector<string> v9{10, 20};//Error, analyse as parenthese still not work
    cout << "v5 size is " << v5.size() << endl;
    cout << "v7 size is " << v7.size() << endl;
    cout << "v8 size is " << v8.size() << endl;

    /*
    v5 size is 1
    v7 size is 10
    v8 size is 10
    */

    // vector::size_type size = 1; //error
    vector<int>::size_type size = 1;
}

void Exercise3_10()
{
    //Write a program that reads a string of characters including punctuation
    //and writes what was read but with the punctuation removed.

    string s;
    cin >> s;
    for (decltype(s.size()) i = 0; i < s.size(); i++)
    {
        if (!ispunct(s[i]))
            cout << s[i];
    }
    cout << endl;

    /*
    $ ./a.exe
    ABC!!!ADDD
    ABCADDD
    */
}

void TestSubscriptIteration()
{
    string s("Hello World!!!");

    for (decltype(s.size()) i = 0; i != s.size(); i++)
    {
        s[i] = toupper(s[i]);
    }

    cout << "result is " << s << endl;

    /*
    HELLO WORLD!!!
    */
}

void TestRangeFor()
{
    string s("Hello World!!!");
    decltype(s.size()) punct_cnt = 0; //type is size_t
    for (auto c : s)
    {
        if (ispunct(c))
            ++punct_cnt;
    }

    cout << "There are " << punct_cnt << " punctuation characters in " << s << endl;

    /*
    There are 3 punctuation characters in Hello World!!!
    */

    for (auto &c : s)
    {
        c = toupper(c);
    }

    cout << "result is " << s << endl;

    /*
    HELLO WORLD!!!
    */
}

void TestAddingLiterals()
{
    string s1 = "hello", s2 = "world";
    string s3 = s1 + ',' + s2 + "\n";
    cout << s3;
    // string s4 = "Hello" + "world";  //error,both sides of + are literals
    string s4 = s1 + "," + s2; //ok, s1 + "," return string
}
void TestStringGetLine()
{
    string line;
    while (getline(cin, line))
    {
        cout << "result is " << line << endl;
    }
    /*
    $ ./a.exe
    123  456   789
    result is 123  456   789
        Hello World    
    result is     Hello World 
    */
}

void TestStringInput()
{
    string s1, s2;
    cin >> s1 >> s2;                //input is "   Hello World!    "
    cout << "s1 is " << s1 << endl; //Hello
    cout << "s2 is " << s2 << endl; //World!
}

void TestStringInitialization()
{
    string s3("value");
    string s4 = "value";
    string s5 = s3 + s4;
    char str[] = "value";
    cout << sizeof(str) / sizeof(*str) << endl; //6
    cout << s3.length() << endl;                //5
    cout << s4.length() << endl;                //6

    int n = -3;
    if (n < s3.length())
        cout << "n is smaller" << endl;
    else
        cout << "s3 length is smaller" << endl;

    /*
    s3 length is smaller"
    */
}

void TestNamespace()
{
    cout << "Enter two number" << endl;
    int v1, v2;
    cin >> v1 >> v2;
    cout << "The sum is " << v1 << " and " << v2 << " is " << v1 + v2 << endl;
}
