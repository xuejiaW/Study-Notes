// 用栈实现队列

// 难度：简单

// Tags
// stack | design

// 使用栈实现队列的下列操作：

// push(x) -- 将一个元素放入队列的尾部。
// pop() -- 从队列首部移除元素。
// peek() -- 返回队列首部的元素。
// empty() -- 返回队列是否为空。

// 示例:

// MyQueue queue = new MyQueue();

// queue.push(1);
// queue.push(2);  
// queue.peek();  // 返回 1
// queue.pop();   // 返回 1
// queue.empty(); // 返回 false

#include "parser.h"
#include "debug.h"
#include <stack>

class MyQueue
{
public:
    /** Initialize your data structure here. */
    MyQueue()
    {
    }

    /** Push element x to the back of queue. */
    void push(int x)
    {
        inputStack.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop()
    {
        if (outputStack.empty())
        {
            while (!inputStack.empty())
            {
                int val = inputStack.top();
                outputStack.push(val);
                inputStack.pop();
            }
        }

        if (!outputStack.empty())
        {
            int val = outputStack.top();
            outputStack.pop();
            return val;
        }
        else
            return -1;
    }

    /** Get the front element. */
    int peek()
    {
        if (outputStack.empty())
        {
            while (!inputStack.empty())
            {
                int val = inputStack.top();
                outputStack.push(val);
                inputStack.pop();
            }
        }

        if (!outputStack.empty())
        {
            int val = outputStack.top();
            return val;
        }
        else
            return -1;
    }

    /** Returns whether the queue is empty. */
    bool empty()
    {
        return inputStack.empty() && outputStack.empty();
    }

private:
    stack<int> inputStack;
    stack<int> outputStack;
};

void TestQueue()
{
    MyQueue que;
    que.push(1);
    que.push(2);
    que.push(3);
    cout<<que.pop()<<endl;
    cout<<que.pop()<<endl;

}
