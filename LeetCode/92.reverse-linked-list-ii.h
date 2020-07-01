// 反转链表 II

// 难度：中等

// Tags
// linked-list

// 反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。

// 说明:
// 1 ≤ m ≤ n ≤ 链表长度。

// 示例:

// 输入: 1->2->3->4->5->NULL, m = 2, n = 4
// 输出: 1->4->3->2->5->NULL

#include "parser.h"
#include "debug.h"

ListNode *reverseBetween(ListNode *head, int m, int n);

void TestRevertBetween()
{
    ListNode *node = parse2List("[1]");
    node = reverseBetween(node, 1, 1);
    DebugListNode(node);
}

// Version： two pointer
ListNode *reverseBetween(ListNode *head, int m, int n)
{
    // 1 <= m <= n <= listLength

    if (m == n)
        return head;

    int jumpTimes = 0; // when times==1, curr should equals to head
    ListNode *rangeBegin = nullptr;
    ListNode *rangeEnd = nullptr;
    ListNode *beforeRangeBegin = nullptr;
    ListNode *afterRangeEnd = nullptr;
    ListNode *curr = nullptr;

    while (jumpTimes <= n)
    {
        if (jumpTimes == m - 1)
        {
            beforeRangeBegin = curr;
            rangeBegin = curr ? curr->next : head;
        }
        else if (jumpTimes == n)
        {
            rangeEnd = curr;
            afterRangeEnd = curr->next;
        }

        curr = curr ? curr->next : head;
        jumpTimes++;
    }

    ListNode *former = nullptr;
    ListNode *later = rangeBegin;
    while (later != afterRangeEnd)
    {
        ListNode *next = later->next;

        later->next = former;
        former = later;
        later = next;
    }

    if (beforeRangeBegin)
        beforeRangeBegin->next = rangeEnd;
    rangeBegin->next = afterRangeEnd;

    return m == 1 ? rangeEnd : head;
}
