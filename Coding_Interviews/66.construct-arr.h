// 构建乘积数组

// 难度：简单

// 给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B 中的元素 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

// 示例:

// 输入: [1,2,3,4,5]
// 输出: [120,60,40,30,24]

#include <vector>
#include <iostream>

using namespace std;

vector<int> constructArr(vector<int> &a);
void TestConstructArr()
{
    vector<int> a{1, 2, 3, 4, 5};
    vector<int> result = constructArr(a);
    for (const int i : result)
        cout << i << endl;
}

// 思路：https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/solution/mian-shi-ti-66-gou-jian-cheng-ji-shu-zu-biao-ge-fe/
// 代码不同
vector<int> constructArr(vector<int> &a)
{
    if (a.empty())
        return vector<int>();

    int aSize = a.size();

    vector<int> result(aSize);
    result[0] = 1;

    int temp = 1;
    for (int i = 0; i != aSize - 1; ++i) // Calculate below half
    {
        temp *= a[i];
        result[i + 1] = temp;
    }

    temp = 1;
    for (int i = aSize - 1; i != 0; --i) // Calculate top half
    {
        temp *= a[i];
        result[i - 1] *= temp;
    }

    return result;
}