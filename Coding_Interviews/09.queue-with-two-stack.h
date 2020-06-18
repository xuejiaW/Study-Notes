// 面试题09： 用两个栈实现队列

// 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )

//  

// 示例 1：

// 输入：
// ["CQueue","appendTail","deleteHead","deleteHead"]
// [[],[3],[],[]]
// 输出：[null,null,3,-1]
// 示例 2：

// 输入：
// ["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
// [[],[],[5],[2],[],[]]
// 输出：[null,-1,null,null,5,2]


#include <stack>

using namespace std;

class CQueue
{
public:
    CQueue()
    {
    }

    void appendTail(int value)
    {
        input.push(value);
    }

    int deleteHead()
    {
        if (output.empty())
        {
            while (!input.empty())
            {
                output.push(input.top());
                input.pop();
            }
        }

        if (output.empty())
            return -1;
        else
        {
            int value = output.top();
            output.pop();
            return value;
        }
    }

private:
    stack<int> input;
    stack<int> output;
};

void TestQueue()
{
    CQueue q;
    q.appendTail(1);
    q.appendTail(2);
    q.appendTail(5);
    q.appendTail(6);
    cout << q.deleteHead() << endl;
    cout << q.deleteHead() << endl;
    cout << q.deleteHead() << endl;
    cout << q.deleteHead() << endl;
    cout << q.deleteHead() << endl;
    cout << q.deleteHead() << endl;
}
