// 环形链表

// Tags
// linked-list | two-pointers

// 给定一个链表，判断链表中是否有环。

// 为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
// 如果 pos 是 -1，则在该链表中没有环。

// 示例 1：

// 输入：head = [3,2,0,-4], pos = 1
// 输出：true
// 解释：链表中有一个环，其尾部连接到第二个节点。

// 示例 2：

// 输入：head = [1,2], pos = 0
// 输出：true
// 解释：链表中有一个环，其尾部连接到第一个节点。

// 示例 3：

// 输入：head = [1], pos = -1
// 输出：false
// 解释：链表中没有环。

#include "parser.h"
#include "debug.h"
#include <unordered_set>

bool hasCycle(ListNode *head);

void TestHasCycle()
{
    ListNode *node = parse2List("[3,2,0,1]");

    bool result = hasCycle(node);
    cout << result << endl;

    //Make a cycle
    ListNode *head = node;
    while (node->next)
        node = node->next;
    node->next = head;

    result = hasCycle(node);
    cout << result << endl;
}

// // Version: using hashmap
// bool hasCycle(ListNode *head)
// {
//     unordered_set<ListNode *> visitedSet;
//     ListNode *temp = head;
//     while (temp)
//     {
//         if (visitedSet.find(temp) != visitedSet.end())
//             return true;
//         visitedSet.insert(temp);
//         temp = temp->next;
//     }
//     return false;
// }

// Version: using two pointer
bool hasCycle(ListNode *head)
{
    // no node or only one node
    if (!head || !head->next)
        return false;

    ListNode *slow = head, *fast = head->next;
    while (slow != fast)
    {
        if (!fast || !fast->next)
            return false;
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}
