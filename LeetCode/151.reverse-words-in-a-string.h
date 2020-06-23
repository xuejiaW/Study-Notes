// 翻转字符串里的单词

// 难度：中等

// Tags:
// string | todo

// 给定一个字符串，逐个翻转字符串中的每个单词。

//  

// 示例 1：

// 输入: "the sky is blue"
// 输出: "blue is sky the"

// 示例 2：

// 输入: "  hello world!  "
// 输出: "world! hello"
// 解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。

// 示例 3：

// 输入: "a good   example"
// 输出: "example good a"
// 解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string reverseWords(string s);

void TestReverseWord()
{
    string result = reverseWords("the sky is blue");
    cout << result << endl;
}

// Version: using vector
string reverseWords(string s)
{
    string result = "";
    vector<string> wordVec;

    int wordBegin = 0, wordEnd = 0;
    while (wordBegin != -1 && wordEnd != -1)
    {
        wordBegin = s.find_first_not_of(' ', wordEnd);
        if (wordBegin != -1)
        {
            wordEnd = s.find_first_of(' ', wordBegin);
            wordVec.push_back(s.substr(wordBegin, wordEnd - wordBegin));
        }
    }

    if (!wordVec.empty())
    {
        for (vector<string>::reverse_iterator i = wordVec.rbegin(); i != wordVec.rend() - 1; ++i)
        {
            result += (*i) + ' ';
        }
        result += *wordVec.begin();
    }
    return result;
}

// Version: without vector
// https://leetcode-cn.com/problems/reverse-words-in-a-string/solution/fan-zhuan-zi-fu-chuan-li-de-dan-ci-by-leetcode-sol/
