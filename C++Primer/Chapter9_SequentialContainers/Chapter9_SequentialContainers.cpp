#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <forward_list>
#include <deque>
#include <array>
#include <stack>
#include <queue>

using namespace std;

class NoDefault
{
private:
public:
    NoDefault(int value1)
    {
    }

    NoDefault(int value1, int value2)
    {
    }

    ~NoDefault()
    {
    }
};

void TestContainerInitialization();
void TestAssignmentAndSwap();
void TestInsert();
void TestAccessing();
void TestErasingElements();
void Exercise9_27();
void Exercise9_28(forward_list<string> slist, string target, string value);
void TestResize();
void TestCapacity();
void TestString();
void TestStringSearch();
void TestAdaptorContainer();

int main()
{
    // TestContainerInitialization();
    // TestAssignmentAndSwap();
    // TestInsert();
    // TestAccessing();
    // TestErasingElements();
    // Exercise0_27();

    // forward_list<string> slist = {"abc", "def", "ghi", "abc"};
    // Exercise9_28(slist, "abc", "123");
    // TestResize();
    // TestCapacity();
    // TestString();
    // TestStringSearch();
    TestAdaptorContainer();
    return 0;
}

void TestContainerInitialization()
{
    vector<NoDefault> v1(10, 2);
    // vector<NoDefault> v1(10);   //Error, NoDefault do not have default constructor
    // vector<NoDefault> v2(10,2,3);    //Error, Can only pass one initialize parameter

    list<string> authors_list = {"Ben", "Shake", "Austen"};
    vector<string> authors_vector = {"Ben", "Shake", "Austen"};
    list<const char *> articles_list = {"a", "aa", "the"};
    vector<const char *> articles_vector = {"Ben", "Shake", "Austen"};

    list<string> list2(authors_list);
    // list<string> list3(authors_vector); //error, container type not match
    // list<string> list4(articles_list);// error, elements type not match

    list<string> list5(articles_list.begin(), articles_list.end());     //correct, although element type not match
    list<string> list6(articles_vector.begin(), articles_vector.end()); // correct, although element and container type not match

    vector<int> ivec(10, -1);         // ten int elements, each elements is -1
    list<string> svec(10, "hi");      // ten int elements, each element is "hi"
    forward_list<int> ivec_fList(10); // ten int elements, each element is default 0
    deque<string> svec_deque(10);     // ten string elements, each element is default ""
    vector<NoDefault> v2(10, 2);
    // vector<NoDefault> v1(10);   //Error, NoDefault do not have default constructor
    // vector<NoDefault> v2(10,2,3);    //Error, Can only pass one initialize parameter
}

void TestContainerArray()
{
    array<int, 42> array42;
    array<string, 10> string10;

    array<int, 42>::size_type array42Type;
    // array<int>::size_type arrayType; // error, array size is part of the array type

    int digs[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // int cpy[10] = digs; //error, build-in array not support copy initialization

    array<int, 10> digs_array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    array<int, 10> cpy_array = digs_array; // support copy initialization
    cpy_array = digs_array;                // support copy assignment

    // array<int, 8> cpy2_array = digs_array; //error, array container type(type) must match
}

void TestAssignmentAndSwap()
{
    list<int> intList;
    list<int> intList2 = {1, 2, 3};

    intList = intList2;
    intList = {4, 5, 6};

    array<int, 3> intArray = {0};
    array<int, 3> intArray2 = {1, 2, 3};
    intArray = intArray2;
    intArray = {4, 5, 6}; // C++ 11 not support, but c++ 14 support

    // intList.assign(intArray);    //error, container type not match
    intList.assign(intArray.begin(), intArray.end());
    intList.assign(5, 3); //container value is {3,3,3,3,3}

    list<int> intList3 = {4, 5, 6};
    list<int> intList4 = {7, 8, 9, 10};
    // intList3.swap(intArray); // error, container type not match
    intList3.swap(intList4);

    cout << "Int list 3" << endl;
    for (int i : intList3)
        cout << "value is " << i << endl;

    cout << endl;
    cout << "Int list 4" << endl;
    for (int i : intList4)
        cout << "value is " << i << endl;

    /*
    Int list 3
    value is 7
    value is 8
    value is 9
    value is 10

    Int list 4
    value is 4
    value is 5
    value is 6
    */

    cout << endl;

    list<int>::iterator list3Begin = intList3.begin();
    cout << "Value is " << *list3Begin << endl;
    intList3.swap(intList4);
    cout << "Value is " << *list3Begin << endl;
    /*
    value is 7
    value is 7
    */

    cout << endl;
    array<int, 3> intArray3_1 = {1, 2, 3};
    array<int, 3> intArray3_2 = {7, 8, 9};
    array<int, 5> intArray5_1 = {2, 3, 4, 5};

    // intArray3_1.swap(intArray5_1);//error, container type not match

    array<int, 3>::iterator intArray3Begin = intArray3_1.begin();

    cout << "Value is " << *intArray3Begin << endl;
    intArray3_1.swap(intArray3_2);
    cout << "Value is " << *intArray3Begin << endl;

    /*
    Value is 1
    Value is 7
    */

    cout << intArray5_1.max_size() << endl;
    cout << intList4.max_size() << endl;
}

void TestInsert()
{
    vector<string> svec = {"a", "b", "c", "d"};
    list<string> slist = {"e", "f", "g", "h"};

    svec.insert(svec.begin(), "aaa");                      // Version 1
    svec.insert(svec.begin(), slist.begin(), slist.end()); //Version 2
    svec.insert(svec.begin(), {"ee", "ff"});               //Version 3
    svec.insert(svec.begin(), 3, "qq");                    //Version 4
    for (string s : svec)
        cout << "value is " << s << endl;

    /*
    value is qq
    value is qq
    value is qq
    value is ee
    value is ff
    value is e
    value is f
    value is g
    value is h
    value is aaa
    value is a
    value is b
    value is c
    value is d
    */

    vector<NoDefault> nDlist;
    // nDlist.emplace_back();   //error, there is no non parameter constructor for NoDefault
    nDlist.emplace_back(1);    // use NoDefault(int) constructor
    nDlist.emplace_back(1, 2); // use NoDefault(int,int) constructor
    // nDlist.push_back(1, 2);    // error, push_back can not take arguments
    nDlist.push_back(NoDefault(1, 2)); // create a NoDefault temporary instance, and the copy of instance will actually be inserted
}

void TestAccessing()
{
    vector<int> ivec = {4, 5, 6, 7};
    int value1 = *ivec.cbegin(), value2 = ivec.front();  // these two operations are the same
    int value3 = *(--ivec.cend()), value4 = ivec.back(); // these two operations are the same

    cout << "Value 1 is " << value1 << ", Value 2 is " << value2 << endl;
    cout << "Value 3 is " << value3 << ", Value 4 is " << value4 << endl;

    ivec.front() = 8; //what front return is reference
    value1 = *ivec.cbegin(), value2 = ivec.front();
    cout << "Value 1 is " << value1 << ", Value 2 is " << value2 << endl;

    /*
    Value 1 is 4, Value 2 is 4
    Value 3 is 7, Value 4 is 7
    Value 1 is 8, Value 2 is 8
    */

    vector<string> svec;
    // cout << "Before use at access" << endl;
    // cout << svec.at(0);
    // cout << "Before use subscripting access" << endl;
    cout << svec[0];
    // cout << "After use subscripting access" << endl;
}

void TestErasingElements()
{
    vector<int> ivec = {4, 5, 6, 7, 8, 9};
    vector<int>::iterator ivecBegin = ivec.begin();

    vector<int>::iterator result = ivec.erase(ivecBegin);
    cout << *result << endl;

    result = ivec.erase(ivecBegin, ivecBegin + 3);
    cout << *result << endl;

    /*
    5
    7
    */
}

void Exercise9_27()
{
    forward_list<int> ifList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 11, 12};

    forward_list<int>::iterator prev = ifList.before_begin();
    forward_list<int>::iterator curr = ifList.before_begin();

    while (curr != ifList.end())
    {
        if (*curr % 2 == 1)
        {
            //No need to move prev, after delele_after, prev iterator still is the prev iterator
            curr = ifList.erase_after(prev);
        }
        else
        {
            prev = curr;
            ++curr;
        }
    }

    for (int i : ifList)
        cout << "value is " << i << endl;

    /*
    value is 2
    value is 4
    value is 6
    value is 8
    value is 10
    value is 12
    */
}

void Exercise9_28(forward_list<string> slist, string target, string value)
{
    forward_list<string>::iterator prev = slist.before_begin();
    forward_list<string>::iterator curr = slist.begin();
    bool found = false;
    while (curr != slist.end())
    {
        if (*curr == target)
        {
            prev = curr;
            curr = slist.insert_after(curr, value);
            found = true;
        }
        else
        {
            prev = curr;
            ++curr;
        }
    }

    if (!found)
        slist.insert_after(slist.end(), value);

    for (string s : slist)
        cout << "value is " << s << endl;

    /*
    value is abc
    value is 123
    value is def
    value is ghi
    value is abc
    value is 123
    */
}

void TestResize()
{
    vector<NoDefault> nDVector;
    // nDVector.resize(10);//Runtime error, no default constructor

    vector<int> iVector = {1, 2, 3, 4, 5, 6};
    iVector.resize(8); //Expand

    cout << "After Resizing to 8: " << endl;

    for (int i : iVector)
        cout << "value is " << i << endl;

    iVector.resize(3, 5); //Shink, The second parameter has no meaning

    cout << "After Resizing to 3: " << endl;

    for (int i : iVector)
        cout << "value is " << i << endl;

    /*
    After Resizing to 8: 
    value is 1
    value is 2
    value is 3
    value is 4
    value is 5
    value is 6
    value is 0
    value is 0
    After Resizing to 3: 
    value is 1
    value is 2
    value is 3
    */
}

void TestCapacity()
{
    vector<int> ivec;
    cout << "Size is " << ivec.size() << " Capacity is " << ivec.capacity() << endl;

    for (int i = 0; i != 24; ++i)
        ivec.push_back(i);

    cout << "Size is " << ivec.size() << " Capacity is " << ivec.capacity() << endl;

    ivec.reserve(50);
    cout << "Size is " << ivec.size() << " Capacity is " << ivec.capacity() << endl;

    /*
    Size is 0 Capacity is 0
    Size is 24 Capacity is 32
    Size is 24 Capacity is 50
    */

    while (ivec.size() != ivec.capacity())
        ivec.push_back(0);
    cout << "Size is " << ivec.size() << " Capacity is " << ivec.capacity() << endl;
    ivec.push_back(0);
    cout << "Size is " << ivec.size() << " Capacity is " << ivec.capacity() << endl;
    ivec.reserve(50);
    cout << "Size is " << ivec.size() << " Capacity is " << ivec.capacity() << endl;

    /*
    Size is 50 Capacity is 50
    Size is 51 Capacity is 100
    Size is 51 Capacity is 100
    */

    ivec.shrink_to_fit();
    cout << "Size is " << ivec.size() << " Capacity is " << ivec.capacity() << endl;

    /*
    Size is 51 Capacity is 51
    */
}

void TestString()
{
    const char *cp = "Stately, plump Buck";
    string s = "abc";

    s.insert(0, "def"); // "defabc"
    cout << s << endl;

    s.insert(0, 5, 'i'); //Like the vector insert version, "iiiiidefabc"
    cout << s << endl;

    s.assign(cp, 7); //Reassign s, "Stately"
    cout << s << endl;

    s.insert(s.size(), cp + 7); //"Stately, plump Buck"
    cout << s << endl;

    string anOther = "hhh";
    s.insert(s.size(), anOther); //"Stately, plump Buckhhh"
    cout << s << endl;

    /*
    defabc
    iiiiidefabc
    Stately
    Stately, plump Buck
    Stately, plump Buckhhh
    */

    s.insert(s.size(), "ggg"); //"Stately, plump Buckhhhggg"
    cout << s << endl;

    s.append("ggg"); //"Stately, plump Buckhhhgggggg"
    cout << s << endl;

    /*
    Stately, plump Buckhhhggg
    Stately, plump Buckhhhgggggg
    */

    s.assign({"abcdef"});
    s.erase(2, 3);        //"abf"
    s.insert(2, "qqqqq"); //"abqqqqqf"
    cout << s << endl;

    s.assign({"abcdef"}); //Equals to above
    s.replace(2, 3, "qqqqq");
    cout << s << endl;

    /*
    abqqqqqf
    abqqqqqf
    */
}

void TestStringSearch()
{
    string name("AnnaBella");
    string::size_type result = name.find("Bella");
    cout << result << endl; //"0",
    result = name.find("bella");
    cout << result << endl; // find is case-sensitive

    /*
    4
    18446744073709551615
    */

    cout << endl;
    string numbers("0123456789"), pName("r2d2");
    string::size_type index = pName.find_first_of(numbers); // find the first character index which belongs to numbers
    cout << index << endl;
    index = pName.find_first_not_of(numbers); //// find the first character index which not belongs to numbers
    cout << index << endl;
    /*
    1
    0
    */

    cout << endl;

    pName.assign("123r456");
    index = pName.find_first_of(numbers, 3);
    cout << index << endl;
    index = pName.find("123456", 0, 3);
    cout << index << endl;
    /*
    4
    0
    */

    cout << endl;
    cout << stoi("123abadcF") << endl;
    cout << stoi("A123aba", 0, 16) << endl;
    cout << stoi("a123abaz", 0, 16) << endl;
    cout << stoi("a123", 0, 16) << endl;
    cout << stoi("0xa123", 0, 16) << endl;
    cout << stod(".123") << endl;
    cout << stof(".123") << endl;
    cout << stof("123E-3") << endl;
    /*
    123
    168966842
    168966842
    41251
    41251
    0.123
    0.123
    0.123
    */
}

void TestAdaptorContainer()
{
    //Construct a stack<int> based on empty deque<int>
    stack<int> istk;

    //Construct a stack<int> based on existing deque<int>
    deque<int> ideq;
    stack<int> istk_2(ideq);

    //Construct a stack<int> based on empty vector<int>
    stack<int, vector<int>> istk_vec;

    //Construct a stack<int> based on existing vecot<int>
    vector<int> ivec;
    stack<int, vector<int>> istk_vec(ivec);

    queue<int> iQue;
    priority_queue<int> ipQue;

}