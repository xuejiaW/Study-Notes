#include <string>
#include <iostream>

using namespace std;

string replaceSpace(string s);

void TestReplaceSpace()
{
    // string s = "we are happy";
    string s = "  ";
    string result = replaceSpace(s);
    cout << "result is " << result << endl;
}

// // Version: use replace
// string replaceSpace(string s)
// {
//     if (s.empty())
//         return "";

//     int index = s.find(" ");
//     while (index != -1)
//     {
//         s.replace(index, 1, "%20");
//         index = s.find(" ");
//     }
//     return s;
// }

// Version: do not use replace
string replaceSpace(string s)
{
    string result = "";
    for (const char &c : s)
    {
        if (c == ' ')
            result += "%20";
        else
            result += c;
    }
    return result;
}
