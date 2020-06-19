// 盛最多水的容器

// 难度：中等

// Tags:
// array | two-pointers

// 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

// 说明：你不能倾斜容器，且 n 的值至少为 2。

// 输入：[1,8,6,2,5,4,8,3,7]
// 输出：49

// 解释：
// 上述数据中，容器的左边界的索引为1，值为8，右边界的索引为8，值为7，因此结果为 (8 - 1) * 7 = 49


//Can not use divide and conquer?
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int GetMaxArea(vector<int> &height, int begin, int end);
int GetMaxCrossArea(vector<int> &height, int begin, int middle, int end);
int maxArea(vector<int> &height);

void TestMaxArea()
{
    // vector<int> height{1, 8, 6, 2, 5, 4, 8, 3, 7};
    vector<int> height{1, 2, 4, 3};
    cout << "before result" << endl;
    int result = maxArea(height);
    cout << "after result" << endl;
    cout << "result is " << result << endl;
}

//two-pointer, first with widest container, then shrink gradually
int maxArea(vector<int> &height)
{
    int left = 0, right = height.size() - 1;
    int capacity = 0, h = 0;

    while (left < right)
    {
        h = min(height[left], height[right]);
        capacity = max(capacity, h * (right - left));

        // when height[x] <= h, the capacity must be equal or less, so skip
        while (height[left] <= h && left < right)
            left++;
        while (height[right] <= h && left < right)
            right--;
    }
    return capacity;
}
