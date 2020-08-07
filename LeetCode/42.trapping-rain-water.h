// 接雨水：

// 难度：困难

// Tags
// array | two-pointers | stack

// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

// 示例:

// 输入: [0,1,0,2,1,0,1,3,2,1,2,1]
// 输出: 6

#include "parser.h"
#include "debug.h"
#include <stack>

int trap(vector<int> &height);

void TestTrappingRainWater()
{
    vector<int> nums = vector<int>{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << trap(nums) << endl;
}

// // Version: stack
// int trap(vector<int> &height)
// {
//     int heightSize = height.size();
//     if (heightSize == 0)
//         return 0;

//     stack<int> wait2HandleIndex;
//     int result = 0;
//     for (int i = 0; i != heightSize; ++i)
//     {
//         while (!wait2HandleIndex.empty() && height[i] > height[wait2HandleIndex.top()])
//         {
//             int handleIndex = wait2HandleIndex.top();
//             wait2HandleIndex.pop();
//             if (wait2HandleIndex.empty())
//                 break;
//             int left = wait2HandleIndex.top();
//             int right = i;
//             int distance = right - left - 1;
//             int holdHeight = (min(height[left], height[right]) - height[handleIndex]);
//             result += (distance)*holdHeight;
//         }
//         wait2HandleIndex.push(i);
//     }

//     return result;
// }

// Version: two pointer
int trap(vector<int> &height)
{
    int leftIndex = 0, rightIndex = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int result = 0;
    while (leftIndex < rightIndex)
    {
        if (height[leftIndex] < height[rightIndex]) //height is decied by left
        {
            if (leftMax < height[leftIndex])
                leftMax = height[leftIndex]; // currHeight is temporarily the highest
            else
                result += (leftMax - height[leftIndex]);
            leftIndex++;
        }
        else
        {
            if (rightMax < height[rightIndex])
                rightMax = height[rightIndex];
            else
                result += (rightMax - height[rightIndex]);
            rightIndex--;
        }
    }
    return result;
}
