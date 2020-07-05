#include "parser.h"
#include "debug.h"

void sortColors(vector<int> &nums);

void TestSortColors()
{
    vector<int> nums = {2, 0, 2, 1, 1, 0};
    sortColors(nums);
    DebugVector(nums);
}

// Version: traverse twice
// void sortColors(vector<int> &nums)
// {
//     int redNums = 0, whiteNums = 0, blueNums = 0;
//     for (const int &i : nums)
//     {
//         redNums += i == 0;
//         whiteNums += i == 1;
//         blueNums += i == 2;
//     }

//     int pos = 0, size = nums.size();
//     while (pos != size)
//     {
//         while (redNums-- != 0)
//             nums[pos++] = 0;
//         while (whiteNums-- != 0)
//             nums[pos++] = 1;
//         while (blueNums-- != 0)
//             nums[pos++] = 2;
//     }
// }

// Version: three pointer
void sortColors(vector<int> &nums)
{
    int redPoint = 0, curr = 0, bluePoint = nums.size() - 1;
    while (curr <= bluePoint)
    {
        if (nums[curr] == 0)
            swap(nums[curr++], nums[redPoint++]);
        else if (nums[curr] == 2)
            swap(nums[curr], nums[bluePoint--]);
        else
            curr++;
    }
}