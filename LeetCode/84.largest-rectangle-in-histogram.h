//  [84] 柱状图中最大的矩形

//  https://leetcode-cn.com/problems/largest-rectangle-in-histogram/description/

//  algorithms
//  Hard (41.65%)

//  给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

//  求在该柱状图中，能够勾勒出来的矩形的最大面积。
//  以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。
//  图中阴影部分为所能勾勒出的最大矩形面积，其面积为 10 个单位。

//  示例:

//  输入: [2,1,5,6,2,3]
//  输出: 10

#include "parser.h"
#include "debug.h"
#include <stack>

int largestRectangleArea(vector<int> &heights);
void TestlargestRectangleArea()
{
    // vector<int> heights = parse2Vector_int("[2,1,5,6,2,3]");
    vector<int> heights = parse2Vector_int("[2,1,7,8,5,6,2,3,6,6,6,1,3,4,1,8,8,8]");
    cout << largestRectangleArea(heights);
}

// Version: Violence
// int largestRectangleArea(vector<int> &heights)
// {
//     int heightsSize = heights.size();
//     if (heightsSize == 0)
//         return 0;
//     if (heightsSize == 1)
//         return heights[0];

//     int result = 0;

//     for (int i = 0; i != heightsSize; ++i)
//     {
//         int h = heights[i];
//         int left = i, right = i;
//         while (left >= 0 && heights[left] >= h)
//             left--;

//         while (right <= heightsSize - 1 && heights[right] >= h)
//             right++;

//         result = max(result, h * ((right - 1) - (left + 1) + 1));
//     }
//     return result;
// }

// // Version: stack
// int largestRectangleArea(vector<int> &heights)
// {
//     int heightsSize = heights.size();
//     if (heightsSize == 0)
//         return 0;
//     if (heightsSize == 1)
//         return heights[0];

//     int result = 0;

//     vector<int> leftBoarderList(heightsSize), rightBoarderList(heightsSize);
//     stack<int> mono;

//     for (int i = 0; i != heightsSize; ++i)
//     {
//         while (!mono.empty() && heights[mono.top()] >= heights[i])
//             mono.pop();

//         leftBoarderList[i] = mono.empty() ? 0 : mono.top() + 1;
//         mono.push(i);
//     }

//     mono = stack<int>();

//     for (int i = heightsSize - 1; i >= 0; i--)
//     {
//         while (!mono.empty() && heights[mono.top()] >= heights[i])
//             mono.pop();
//         rightBoarderList[i] = mono.empty() ? heightsSize - 1 : mono.top() - 1;
//         mono.push(i);
//     }

//     for (int i = 0; i != heightsSize; ++i)
//     {
//         result = max(result, heights[i] * (rightBoarderList[i] - leftBoarderList[i] + 1));
//     }

//     return result;
// }

// Version: stack,optimize
int largestRectangleArea(vector<int> &heights)
{
    int heightsSize = heights.size();
    if (heightsSize == 0)
        return 0;
    if (heightsSize == 1)
        return heights[0];

    int result = 0;

    vector<int> leftBoarderList(heightsSize,0),rightBoarderList(heightsSize,heightsSize-1);
    stack<int> mono;

    for (int i = 0; i != heightsSize; ++i)
    {
        while(!mono.empty() && heights[mono.top()]>=heights[i])
        {
            rightBoarderList[mono.top()]=i-1;
            mono.pop();
        }

        leftBoarderList[i]=mono.empty()?0:mono.top()+1;
        mono.push(i);
    }

    for(int i=0;i!=heightsSize;++i)
    {
        result=max(result,heights[i]*(rightBoarderList[i]-leftBoarderList[i]+1));
    }

    return result;
}
