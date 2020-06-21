// 最小栈

// 难度：简单

// Tags
// stack

// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

// push(x) —— 将元素 x 推入栈中。
// pop() —— 删除栈顶的元素。
// top() —— 获取栈顶元素。
// getMin() —— 检索栈中的最小元素。
 

// 示例:

// 输入：
// ["MinStack","push","push","push","getMin","pop","top","getMin"]
// [[],[-2],[0],[-3],[],[],[],[]]

// 输出：
// [null,null,null,null,-3,null,0,-2]

// 解释：
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin();   --> 返回 -3.
// minStack.pop();
// minStack.top();      --> 返回 0.
// minStack.getMin();   --> 返回 -2.

#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

class MinStack
{
public:
    MinStack()
    {
        auxiliary.push(INT_MAX);
    }

    void push(int x)
    {

        main.push(x);
        auxiliary.push(std::min(auxiliary.top(), x));
    }

    void pop()
    {
        main.pop();
        auxiliary.pop();
    }

    int top()
    {
        return main.top();
    }

    int getMin()
    {
        return auxiliary.top();
    }

private:
    stack<int> main;
    stack<int> auxiliary; // push the min value together when push the other value
};

void TestMinStack()
{
    MinStack s;
    s.push(-1);
    s.push(3);
    cout << s.getMin() << endl;
    cout << s.top() << endl;
    s.push(-3);
    cout << s.getMin() << endl;
    cout << s.top() << endl;
    s.pop();
    cout << s.getMin() << endl;
    cout << s.top() << endl;
}
