// 验证栈序列

// 难度：中等

// Tags:
// stack

// 给定 pushed 和 popped 两个序列，每个序列中的 值都不重复，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop 操作序列的结果时，返回 true；否则，返回 false 。

 

// 示例 1：

// 输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
// 输出：true
// 解释：我们可以按以下顺序执行：
// push(1), push(2), push(3), push(4), pop() -> 4,
// push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
// 示例 2：

// 输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
// 输出：false
// 解释：1 不能在 2 之前弹出。
 

// 提示：

// 0 <= pushed.length == popped.length <= 1000
// 0 <= pushed[i], popped[i] < 1000
// pushed 是 popped 的排列。

#include <stack>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>

using namespace std;

bool validateStackSequences(vector<int> &pushed, vector<int> &popped);

void TestValidateStackSequences()
{
    vector<int> pushed{1, 2, 3, 4, 5}, popped{4, 5, 3, 2, 1};
    bool result = validateStackSequences(pushed, popped);
    cout << "result is " << result;
}

// // Version: based on popped vector
// bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
// {
//     if (pushed.size() != popped.size())
//         return false;

//     stack<int> auxiliary;
//     int pushedIndex = 0;

//     for (int i = 0; i != popped.size(); ++i)
//     {
//         if (!auxiliary.empty() && auxiliary.top() == popped[i])
//             auxiliary.pop(); // the element wanted to popped has already in the auxiliary stack
//         else
//         {
//             while (pushedIndex != pushed.size() && pushed[pushedIndex] != popped[i])
//                 auxiliary.push(pushed[pushedIndex++]);

//             if (pushedIndex >= pushed.size()) // the element waitted to popped is not in the pushed vector
//                 return false;
//             else
//                 pushedIndex++;
//         }
//     }

//     return true;
// }

// Version: based on pushed stack

bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    if (pushed.size() != popped.size())
        return false;

    stack<int> auxiliary;
    int poppedIndex = 0;
    for (const int &val : pushed)
    {
        auxiliary.push(val);
        while (!auxiliary.empty() && auxiliary.top() == popped[poppedIndex])
        {
            auxiliary.pop();
            poppedIndex++;
        }
    }

    return auxiliary.empty();
}
