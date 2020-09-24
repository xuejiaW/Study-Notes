
// @lc app=leetcode.cn id=125 lang=cpp
//
// [125] 验证回文串
//
// https://leetcode-cn.com/problems/valid-palindrome/description/
//
// Tags
//   two-pointers | string
// Easy (46.33%)
//
// 给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
//
// 说明：本题中，我们将空字符串定义为有效的回文串。
//
// 示例 1:
//
// 输入: "A man, a plan, a canal: Panama"
// 输出: true
//
//
// 示例 2:
//
// 输入: "race a car"
// 输出: false
  
  
 

#include "parser.h"
#include "debug.h"

bool isPalindrome(string s);

void TestIsPalindrome()
{
    cout << isPalindrome("A man, a plan, a canal: Panama");
}

int isCharacterOrDigit(const char &c)
{
    if (c >= 'a' && c <= 'z')
        return 0;
    if (c >= 'A' && c <= 'Z')
        return 1;
    if (c >= '0' && c <= '9')
        return 2;

    return -1;
}
bool isPalindrome(string s)
{
    int sSize = s.size();
    if (sSize == 0)
        return true;

    int leftPtr = 0, rightPtr = sSize - 1;

    while (leftPtr < rightPtr)
    {
        int leftCharacter = isCharacterOrDigit(s[leftPtr]);
        int rightCharacter = isCharacterOrDigit(s[rightPtr]);
        if (leftCharacter == -1)
        {
            leftPtr++;
            continue;
        }
        if (rightCharacter == -1)
        {
            rightPtr--;
            continue;
        }

        int leftDelta = 0, rightDelta = 0;
        if (leftCharacter != 2 && rightCharacter != 2)
        {
            leftDelta = leftCharacter == 0 ? s[leftPtr] - 'a' : s[leftPtr] - 'A';
            rightDelta = rightCharacter == 0 ? s[rightPtr] - 'a' : s[rightPtr] - 'A';
        }
        else
        {
            leftDelta = s[leftPtr] - '0';
            rightDelta = s[rightPtr] - '0';
        }

        if (leftDelta != rightDelta)
            return false;

        leftPtr++;
        rightPtr--;
    }

    return true;
}
