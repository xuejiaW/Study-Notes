// 用队列实现栈

// 难度：简单

// Tags
// stack | design

// 使用队列实现栈的下列操作：

// push(x) -- 元素 x 入栈
// pop() -- 移除栈顶元素
// top() -- 获取栈顶元素
// empty() -- 返回栈是否为空

#include "parser.h"
#include "debug.h"
#include <queue>

class MyStack
{
public:
    /** Initialize your data structure here. */
    MyStack()
    {
    }

    /** Push element x onto stack. */
    void push(int x)
    {
        main.push(x);
        for (int i = 0; i != main.size() - 1; ++i)
        {
            main.push(main.front());
            main.pop();
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop()
    {
        int val = main.front();
        main.pop();
        return val;
    }

    /** Get the top element. */
    int top()
    {
        return main.front();
    }

    /** Returns whether the stack is empty. */
    bool empty()
    {
        return main.empty();
    }

private:
    queue<int> main;
};
