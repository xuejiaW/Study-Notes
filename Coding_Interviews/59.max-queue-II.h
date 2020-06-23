// 队列的最大值

// 难度：中等

// 标签：
// deque

// 请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。

// 若队列为空，pop_front 和 max_value 需要返回 -1

// 示例 1：

// 输入:
// ["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
// [[],[1],[2],[],[],[]]
// 输出: [null,null,null,2,1,2]
// 示例 2：

// 输入:
// ["MaxQueue","pop_front","max_value"]
// [[],[],[]]
// 输出: [null,-1,-1]

#include <queue>
#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

class MaxQueue
{
public:
    MaxQueue()
    {
    }

    int max_value()
    {
        if (maxDeque.empty())
            return -1;
        return maxDeque.front();
    }

    void push_back(int value)
    {
        normal.push(value);
        while (!maxDeque.empty() && value > maxDeque.back())
            maxDeque.pop_back();
        maxDeque.push_back(value);
    }

    int pop_front()
    {
        if (normal.empty())
            return -1;

        int val = normal.front();
        normal.pop();

        if (!maxDeque.empty() && val == maxDeque.front())
            maxDeque.pop_front();

        return val;
    }

private:
    queue<int> normal;
    deque<int> maxDeque;
};

void TestMaxQueue()
{
    MaxQueue q;
    q.push_back(1);
    q.push_back(-2);
    q.push_back(3);
    q.push_back(-3);
    cout << "max is " << q.max_value() << endl;
    cout << "pop is " << q.pop_front() << endl;
    cout << "max is " << q.max_value() << endl;
    cout << "pop is" << q.pop_front() << endl;
    cout << "pop is" << q.pop_front() << endl;
    cout << "max is " << q.max_value() << endl;
}