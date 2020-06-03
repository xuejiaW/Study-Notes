#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <list>
#include <functional>
#include <iterator>

using namespace std;

void TestFind();
void TestAccumlate();
void TestEqual();
void TestFill();
void TestBack_Iterator();
void TestCopy();
void TestReplace();
void TestReplace_Copy();
void TestSort();
void TestUnique();
void DeleteDuplicate();
void TestSortByLength();
void TestStable_Sort();
void TestLambdaExpression();
void TestFind_if();
void TestFor_each();
void TestLambdaValueCapture();
void TestLambdaReferenceCapture();
void TestLambdaImplicitCaptures();
void TestLambdaMutableCapture();
void TestTransformAlgorithms();
void TestTransformReturnLambda();
void TestBindAlgorithms();
void TestFrontInsertIterator();
void TestBackInsertIterator();
void TestInsertIterator();
void TestIStreamIterator();
void TestIstreamAlgorithms();
void TestOStreamIterator();

int main()
{
    // TestFind();
    //  TestAccumlate();
    // TestEqual();
    // TestFill();
    // TestBack_Iterator();
    // TestCopy();
    // TestReplace();
    // TestReplace_Copy();
    // TestSort();
    // TestUnique();
    // DeleteDuplicate();
    // TestSortByLength();
    // TestStable_Sort();
    // TestLambdaExpression();
    // TestFind_if();
    // TestFor_each();
    // TestLambdaValueCapture();
    // TestLambdaReferenceCapture();
    // TestLambdaImplicitCaptures();
    // TestLambdaMutableCapture();
    // TestTransformAlgorithms();
    // TestTransformReturnLambda();
    // TestBindAlgorithms();
    // TestFrontInsertIterator();
    // TestBackInsertIterator();
    // TestInsertIterator();
    // TestIStreamIterator();
    // TestIstreamAlgorithms();
    TestOStreamIterator();
}

void TestFind()
{
    int val = 42;
    vector<int> iVac{1, 2, 3, 4, 52, 42, 47};
    list<int> iList{1, 2, 3, 4, 52, 43, 47};

    auto iVacResult = find(iVac.begin(), iVac.end(), val);
    auto iListResult = find(iList.begin(), iList.end(), 42);

    if (iVacResult != iVac.end())
        cout << "Find result in ivac" << endl;
    if (iListResult != iList.end())
        cout << "Find result in iList" << endl;

    /*
    Find result in ivac
    */

    int ia[] = {27, 21, 12, 42, 109, 83};
    int target = 109;
    auto result = find(begin(ia), end(ia), target);
    if (result != end(ia))
        cout << "Find result in array" << endl;

    /*
    Find Result in array
    */
}

void TestAccumlate()
{
    vector<string> sVec = {"abc", "edf", "ghi"};
    string sum = accumulate(sVec.begin(), sVec.end(), string(""));

    //Error, "" is string literal which is actually is const char*
    // sum = accumulate(sVec.begin(), sVec.end(), "");
    cout << "result is :" << sum << endl;
}

void TestEqual()
{
    vector<string> sVec = {"abc", "edf", "ghi"};
    vector<string> sVec2 = {"abc", "edf", "ghi", "jkl"};

    bool result = equal(sVec.begin(), sVec.end(), sVec2.begin());

    if (result)
        cout << "Two vector string is equal" << endl;

    vector<const char *> ccVec = {"Abc", "Def", "Ghi"};
    vector<const char *> ccVec2 = {"Abc", "Def", "Ghi"};

    result = equal(ccVec.begin(), ccVec.end(), ccVec2.begin());

    if (result)
        cout << "Two c style string  vector is equal" << endl;

    cout << "ccVec address is: " << endl;
    for (const char *c : ccVec)
        cout << static_cast<const void *>(c) << endl;

    cout << endl;
    cout << "ccVec2 address is: " << endl;
    for (const char *c : ccVec2)
        cout << static_cast<const void *>(c) << endl;

    /*
    Two c style string  vector is equal
    ccVec address is:
    0x408077
    0x40807b
    0x40807f

    ccVec2 address is:
    0x408077
    0x40807b
    0x40807f
   */
}

void TestFill()
{
    vector<int> ivec(10);
    fill(ivec.begin(), ivec.end(), 1);
    fill(ivec.begin(), ivec.begin() + ivec.size() / 2, 10);
    for (int i : ivec)
        cout << "Value is " << i << endl;
    /*
    Value is 10
    Value is 10
    Value is 10
    Value is 10
    Value is 10
    Value is 1
    Value is 1
    Value is 1
    Value is 1
    Value is 1
   */

    cout << endl;
    fill_n(ivec.begin(), 3, 5);
    for (int i : ivec)
        cout << "Value is " << i << endl;

    /* 
    Value is 5 
    Value is 5 
    Value is 5 
    Value is 10
    Value is 10
    Value is 1 
    Value is 1 
    Value is 1 
    Value is 1 
    Value is 1 
    */

    vector<int> ivec2;
    fill(ivec2.begin(), ivec2.begin() + 10, 1);
    for (int i : ivec)
        cout << "Value is " << i << endl;
    /*
    Segmentation fault
    */
}

void TestBack_Iterator()
{
    vector<int> vec;
    back_insert_iterator<vector<int>> it = back_inserter(vec);
    *it = 42;

    for (int i : vec)
        cout << "value is " << i << endl;

    /*
    value is 42
    */

    cout << endl;

    vector<int> ivec;
    fill_n(back_inserter(ivec), 5, 2);
    for (int i : ivec)
        cout << "value is " << i << endl;

    /*
    value is 2
    value is 2
    value is 2
    value is 2
    value is 2
    */
}

void TestCopy()
{
    int a1[] = {0, 1, 2, 3, 4, 5};
    int a2[sizeof(a1) / sizeof(*a1)];
    auto ret = copy(begin(a1), end(a1), a2);
    for (int i : a2)
        cout << "value is " << i << endl;

    /*
    value is 0
    value is 1
    value is 2
    value is 3
    value is 4
    value is 5
    */
}

void TestReplace()
{
    vector<int> ivec = {1, 2, 3, 4, 5, 7, 8, 9, 9, 9, 0};
    replace(ivec.begin(), ivec.end(), 9, 0);
    for (int i : ivec)
        cout << "Value is " << i << endl;

    /*
    Value is 1
    Value is 2
    Value is 3
    Value is 4
    Value is 5
    Value is 7
    Value is 8
    Value is 0
    Value is 0
    Value is 0
    Value is 0
    */
}

void TestReplace_Copy()
{
    vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 0};
    list<int> iList;
    replace_copy(ivec.begin(), ivec.end(), back_inserter(iList), 9, 0);
    for (int i : iList)
        cout << "value is " << i << endl;

    /*
    value is 1
    value is 2
    value is 3
    value is 4
    value is 5
    value is 6
    value is 7
    value is 8
    value is 0
    value is 0
    value is 0
    value is 0
    */
}

void TestSort()
{
    vector<int> iVec = {1, 2, 2, 3, 4, 5, 4, 4, 7, 6, 7, 7, 8};
    sort(iVec.begin(), iVec.end());
    for (int i : iVec)
        cout << "Value is " << i << endl;
    /*
    Value is 1
    Value is 2
    Value is 2
    Value is 3
    Value is 4
    Value is 4
    Value is 4
    Value is 5
    Value is 6
    Value is 7
    Value is 7
    Value is 7
    Value is 8
    */
}

void TestUnique()
{
    vector<int> iVec = {1, 2, 3, 4, 5, 4, 5};
    vector<int>::iterator it = unique(iVec.begin(), iVec.end());

    cout << "Whole Int Vac is: " << endl;
    for (int i : iVec)
        cout << "Value is " << i << endl;

    cout << endl;

    int lastHalfElementsCount = iVec.end() - it;
    cout << "Last Half elements counts are: " << lastHalfElementsCount << endl;

    cout << "After Unique, result is " << endl;
    for (int i : iVec)
        cout << "Value is " << i << endl;
    /*
    Whole Int Vac is: 
    Value is 1
    Value is 2
    Value is 3
    Value is 4
    Value is 5
    Value is 4
    Value is 5

    Last Half elements counts are: 0
    After Unique, result is
    Value is 1
    Value is 2
    Value is 3
    Value is 4
    Value is 5
    Value is 4
    Value is 5
    */

    cout << endl;
    sort(iVec.begin(), iVec.end());
    it = unique(iVec.begin(), iVec.end());

    lastHalfElementsCount = iVec.end() - it;
    cout << "Last Half elements counts are: " << lastHalfElementsCount << endl;
    cout << "After Unique and sort, result is " << endl;
    for (int i : iVec)
        cout << "Value is " << i << endl;

    /*
    Last Half elements counts are: 2
    After Unique and sort, result is
    Value is 1
    Value is 2
    Value is 3
    Value is 4
    Value is 5
    Value is 5
    Value is 5
    */
}

void DeleteDuplicate()
{
    vector<int> iVec = {1, 2, 3, 1, 2, 3, 4, 4, 5, 6, 5, 6, 7};
    sort(iVec.begin(), iVec.end());
    vector<int>::iterator it = unique(iVec.begin(), iVec.end());
    iVec.erase(it, iVec.end());
    for (int i : iVec)
        cout << "Result is " << i << endl;

    /*
    Result is 1
    Result is 2
    Result is 3
    Result is 4
    Result is 5
    Result is 6
    Result is 7
    */
}

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void TestSortByLength()
{
    vector<string> stringVec = {"aaa", "b", "cc"};
    sort(stringVec.begin(), stringVec.end(), isShorter);
    for (string s : stringVec)
        cout << "value is " << s << endl;

    /*
    value is b
    value is cc
    value is aaa
    */
}

void TestStable_Sort()
{
    vector<string> stringVec = {"fox", "the", "slow",
                                "jumps", "quick", "fox", "over", "red",
                                "turtle", "turtle", "fox"};

    //To delete duplicate elements
    sort(stringVec.begin(), stringVec.end());
    vector<string>::iterator it = unique(stringVec.begin(), stringVec.end());
    stringVec.erase(it, stringVec.end());

    stable_sort(stringVec.begin(), stringVec.end(), isShorter);
    for (string s : stringVec)
        cout << "value is " << s << endl;

    /*
    value is fox
    value is red
    value is the
    value is over
    value is slow
    value is jumps
    value is quick
    value is turtle
    */
}

void TestLambdaExpression()
{
    auto f = [] { return 42; };
    cout << f() << endl;

    /*
    42
    */

    vector<string> stringVec = {"fox", "the", "slow",
                                "jumps", "quick", "fox", "over", "red",
                                "turtle", "turtle", "fox"};

    //To delete duplicate elements
    sort(stringVec.begin(), stringVec.end());
    vector<string>::iterator it = unique(stringVec.begin(), stringVec.end());
    stringVec.erase(it, stringVec.end());

    stable_sort(stringVec.begin(), stringVec.end(),
                [](const string &a, const string &b) { return a.size() < b.size(); });
    for (string s : stringVec)
        cout << "value is " << s << endl;

    /*
    value is fox
    value is red
    value is the
    value is over
    value is slow
    value is jumps
    value is quick
    value is turtle
    */
}

int length = 5;
void TestFind_if()
{
    vector<string> stringVec = {"fox", "the", "slow",
                                "jumps", "quick", "fox", "over", "red",
                                "turtle", "turtle", "fox"};
    vector<string>::iterator it = find_if(stringVec.begin(), stringVec.end(),
                                          [](const string &std) { return std.size() >= 5; });
    if (it != stringVec.end())
        cout << "Found value is " << *it << endl;
    else
        cout << "There is no found value" << endl;
    /*
    Found value is jumps
    */

    //error, predicate should be unary predicate
    // it = find_if(stringVec.begin(), stringVec.end(),
    //              [](const string &std, int length) { return std.size() >= length; });

    it = find_if(stringVec.begin(), stringVec.end(),
                 [](const string &std) { return std.size() >= length; });
    if (it != stringVec.end())
        cout << "Found value is " << *it << endl;
    else
        cout << "There is no found value" << endl;
    /*
    Found value is jumps
    */

    int toFindLength = 5;
    it = find_if(stringVec.begin(), stringVec.end(),
                 [toFindLength](const string &std) { return std.size() >= toFindLength; });
    if (it != stringVec.end())
        cout << "Found value is " << *it << endl;
    else
        cout << "There is no found value" << endl;
    /*
    Found value is jumps
    */
}

void TestFor_each()
{

    vector<string> stringVec = {"fox", "the", "slow",
                                "jumps", "quick", "fox", "over", "red",
                                "turtle", "turtle", "fox"};
    for_each(stringVec.begin(), stringVec.end(),
             [](const string &std) { cout << "Value is " << std << endl; });

    /*
    Value is fox
    Value is the
    Value is slow
    Value is jumps
    Value is quick
    Value is fox
    Value is over
    Value is red
    Value is turtle
    Value is turtle
    Value is fox
    */
}

void TestLambdaValueCapture()
{
    int v1 = 42;
    auto f = [v1] { return v1; }; //Value capture
    v1 = 0;
    int j = f();
    cout << "result is " << j << endl;

    // result is 42
}

void TestLambdaReferenceCapture()
{
    int v1 = 42;
    auto f = [&v1] { return v1; };
    v1 = 0;
    int j = f();
    cout << "result is " << j << endl;

    // result is 0
}

void TestLambdaImplicitCaptures()
{
    vector<string> words = {"abc", "def", "ghi"};

    char c = '|';
    ostream &os = cout;

    for_each(words.begin(), words.end(), [&, c](const string &s) { os << s << c; });

    cout << endl;

    for_each(words.begin(), words.end(), [=, &os](const string &s) { os << s << c; });

    // abc|def|ghi|
    // abc|def|ghi|
}

void TestLambdaMutableCapture()
{
    int v1 = 42;
    auto f = [v1]() mutable { return ++v1; };
    v1 = 0;
    int j = f();
    cout << "result is " << j << endl;

    // result is 43

    int v2 = 42;
    auto ff = [&v2] { return ++v2; };
    v2 = 0;
    int k = ff();
    cout << "result is " << k << endl;
    // result is 1
}

void TestTransformAlgorithms()
{
    list<int> ivec = {0, -1, -2, 3, 4, -5};
    transform(ivec.begin(), ivec.end(), ivec.begin(), [](int i) { return i < 0 ? -i : i; });

    for (int i : ivec)
        cout << "element is " << i << endl;

    // element is 0
    // element is 1
    // element is 2
    // element is 3
    // element is 4
    // element is 5
}

void TestTransformReturnLambda()
{
    // Can pass compilation, however the C++ 11 standard not support
    list<int> ivec = {0, -1, -2, 3, 4, -5};
    transform(ivec.begin(), ivec.end(), ivec.begin(), [](int i) {
        if (i < 0)
            return -i;
        else
            return i;
    });

    // C++ 11 standard recommended
    transform(ivec.begin(), ivec.end(), ivec.begin(), [](int i) -> int {
        if (i < 0)
            return -i;
        else
            return i;
    });
}

bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}

void Debug5(int a, int b, int c, int d, int e)
{
    cout << "Debug5 result is " << a << "  " << b << "  " << c << "  " << d << "  " << e << endl;
}

using namespace std::placeholders;

void print(ostream &os, const string &s, char c)
{
    os << s << c;
}

void TestBindAlgorithms()
{

    vector<string> stringVec = {"fox", "the", "slow",
                                "jumps", "quick", "fox", "over", "red",
                                "turtle", "turtle", "fox"};
    int toFindLength = 5;
    vector<string>::iterator it = find_if(stringVec.begin(), stringVec.end(),
                                          [toFindLength](const string &std) { return std.size() >= toFindLength; });

    // it = find_if(stringVec.begin(), stringVec.end(), check_size);//Error, should use unary predicate

    auto debug2 = bind(Debug5, 5, 10, _2, _1, 15);
    debug2(1, 2);
    // Debug5 result is 5  10  2  1  15

    it = find_if(stringVec.begin(), stringVec.end(), bind(&check_size, std::placeholders::_1, toFindLength));

    vector<string> words = {"abc", "def", "ghi"};

    char c = '|';
    ostream &os = cout;

    for_each(words.begin(), words.end(), [&os, c](const string &s) { os << s << c; });
    cout << endl;
    for_each(words.begin(), words.end(), bind(print, ref(os), _1, c));

    // abc|def|ghi|
    // abc|def|ghi|
}

void TestFrontInsertIterator()
{
    list<int> lst = {1, 2, 3, 4};

    std::front_insert_iterator<list<int>> frontIterator(lst);

    *frontIterator = 5;
    *frontIterator = 6;

    for (int i : lst)
        cout << i << " ";

    cout << endl;

    // 6 5 1 2 3 4
}

void TestBackInsertIterator()
{
    list<int> lst = {1, 2, 3, 4};

    std::back_insert_iterator<list<int>> backIterator(lst);

    *backIterator = 7;
    *backIterator = 8;

    for (int i : lst)
        cout << i << " ";

    cout << endl;

    // 1 2 3 4 7 8
}

void TestInsertIterator()
{
    list<int> lst = {1, 2, 3, 4};

    // insert_iterator<list<int>> beginInsertIterator(lst, lst.begin());
    insert_iterator<list<int>> beginInsertIterator = inserter(lst, lst.begin());
    *beginInsertIterator = 9;
    *beginInsertIterator = 10;

    for (int i : lst)
        cout << i << " ";

    cout << endl;

    insert_iterator<list<int>> endInsertIterator(lst, lst.end());
    *endInsertIterator = 9;
    *endInsertIterator = 10;

    for (int i : lst)
        cout << i << " ";

    // 9 10 1 2 3 4
    // 9 10 1 2 3 4 9 10
}

void TestIStreamIterator()
{
    istream_iterator<int> int_it(cin);
    istream_iterator<int> int_eof;

    list<int> iList;

    while (int_it != int_eof)
    {
        iList.push_back(*int_it++);
    }

    for (int i : iList)
        cout << i << " ";

    /*
    Input:
    1
    2
    3
    4
    5
    ^Z
    
    Output:
    1 2 3 4 5
    */

    list<int> iiList(int_it, int_eof);
    for (int i : iiList)
        cout << i << " ";

    /*
    Input:
    1
    2
    3
    4
    5
    ^Z
    
    Output:
    1 2 3 4 5
    */
}

void TestIstreamAlgorithms()
{
    istream_iterator<int> in(cin), eof;
    cout << accumulate(in, eof, 0) << endl;

    /*
    Input:
    1
    2
    3
    ^Z
    
    Output:
    6
    */
}

void TestOStreamIterator()
{
    ostream_iterator<int> out_iter(cout, "*");
    vector<int> ivec{1, 2, 3};
    for (int i : ivec)
        *out_iter++ = i;

    cout << endl;

    // 1*2*3*

    copy(ivec.begin(), ivec.end(), out_iter);
    // 1*2*3*
}
