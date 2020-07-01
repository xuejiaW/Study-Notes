// 两两交换链表中的节点

// 难度：中等

// Tags:

// linked list

// 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

// 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

// 示例:

// 给定 1->2->3->4, 你应该返回 2->1->4->3.

#include "parser.h"
#include "debug.h"

ListNode *swapPairs(ListNode *head);

void TestSwapPairs()
{
    ListNode *node = parse2List("[1,2,3,4,5]");
    node = swapPairs(node);
    DebugListNode(node);
}

ListNode *swapPairs(ListNode *head)
{
    if (!head)
        return head;

    ListNode *curr = head;
    ListNode *next = head->next;
    ListNode *result = next == nullptr ? curr : next;

    while (curr && next)
    {
        ListNode *nextGroup = next->next;
        next->next = curr;
        curr->next = (nextGroup && nextGroup->next) ? nextGroup->next : nextGroup;

        curr = nextGroup;
        next = curr ? curr->next : nullptr;
    }

    return result;
}
