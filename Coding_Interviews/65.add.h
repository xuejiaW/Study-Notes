// 不用加减乘除做加法

// 难度：简单

// 标签：
// 位运算

// 写一个函数，求两个整数之和，要求在函数体内不得使用 “+”、“-”、“*”、“/” 四则运算符号。
//  
// 示例:

// 输入: a = 1, b = 1
// 输出: 2

#include <iostream>

using namespace std;

int add(int a, int b);

void TestAdd()
{
    cout << "result is " << add(20, 17);
}

// Version: using xor and &&
// Explanation: https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof/solution/mian-shi-ti-65-bu-yong-jia-jian-cheng-chu-zuo-ji-7/
int add(int a, int b)
{
    while (b != 0)
    {
        unsigned int carryOver = (unsigned int)(a & b) << 1; // moving operation for int is undefined
        a ^= b;
        b = carryOver;
    }
    return a;
}