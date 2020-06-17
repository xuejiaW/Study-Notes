// Tags:
// array | two-pointers

// Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

// Note: You may not slant the container and n is at least 2.

// Input: [1,8,6,2,5,4,8,3,7]
// Output: 49

// Explanation:
// Left edge of the container is at index 1(value = 8), right edge is at index 8 (value is 7), so the result is min(7,8) * (8-1) = 49


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

        // when height[x] <=h, the capacity must be equal or less, so skip
        while (height[left] <= h && left < right)
            left++;
        while (height[right] <= h && left < right)
            right--;
    }
    return capacity;
}
