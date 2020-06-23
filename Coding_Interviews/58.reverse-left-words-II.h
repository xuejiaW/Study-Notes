// 左旋转字符串

// 难度：简单

// Tags:
// string

// 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。

//  

// 示例 1：
// 输入: s = "abcdefg", k = 2
// 输出: "cdefgab"

// 示例 2：
// 输入: s = "lrloseumgh", k = 6
// 输出: "umghlrlose"

#include <string>
#include <iostream>

using namespace std;

string reverseLeftWords(string s, int n);

void TestReverseLeftWords()
{
    string s("abcdefg");
    string result = reverseLeftWords(s, 2);
    cout << "result is " << result << endl;
}

// // Version: using substr and erase
// string reverseLeftWords(string s, int n)
// {
//     string sub = s.substr(0, n);
//     return s = s.erase(0, n) + sub;
// }

string reverseLeftWords(string s, int n)
{
    string result = "";
    int length = s.size();
    for (int i = n; i < n + length; ++i)
        result += s[i % length];
    return result;
}