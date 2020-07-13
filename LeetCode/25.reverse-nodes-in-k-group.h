// K 个一组翻转链表

// 难度：困难

// Tags:
// linked-list

// 给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

// k 是一个正整数，它的值小于或等于链表的长度。

// 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

//  

// 示例：

// 给你这个链表：1->2->3->4->5

// 当 k = 2 时，应当返回: 2->1->4->3->5

// 当 k = 3 时，应当返回: 3->2->1->4->5

#include "parser.h"
#include "debug.h"

ListNode *reverseKGroup(ListNode *head, int k);
void TestReverseKGroup()
{
    // ListNode *node = parse2List("[1,2,3,4,5]");
    ListNode *node = parse2List("[1,2,3,4]");
    DebugListNode(node);
    ListNode *result = reverseKGroup(node, 4);
    cout << "after" << endl;
    DebugListNode(result);
}

ListNode *reverseKGroup(ListNode *head, int k)
{
    if (!head || !head->next)
        return head;

    ListNode *prev = nullptr;
    ListNode *curr = head;
    ListNode *nextGroup = head;
    ListNode *prevGroupTail = nullptr;
    ListNode *result = nullptr;

    while (true)
    {
        int toSkip = k;
        while (toSkip != 0 && nextGroup)
        {
            nextGroup = nextGroup->next;
            toSkip--;
        }

        if (toSkip != 0)
            break;

        ListNode *tempHead = curr; // record tempHead, after reversing, this head will become the tail
        // Reverse list
        while (curr != nextGroup)
        {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        tempHead->next = nextGroup; // connect curr with remaining list

        if (prevGroupTail)
            prevGroupTail->next = prev; // connect previous reversed list with this reversed part

        prevGroupTail = tempHead;

        if (result == nullptr)
            result = prev;


        curr = nextGroup;
        prev = nullptr;
    }

    return result;
}
