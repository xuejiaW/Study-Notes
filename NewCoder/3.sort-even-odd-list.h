// 算法题：1->4->3->2->5 给定一个链表奇数部分递增，偶数部分递减，要求在O(n)时间复杂度内将链表变成递增，

// 思路：先将链表拆成奇偶两个链表，将偶链表翻转，再归并在一起

#include "../LeetCode/parser.h"
#include "../LeetCode/debug.h"

ListNode *SortList(ListNode *head);

void TestSortList()
{
    ListNode *head = parse2List("[7,6]");
    DebugListNode(SortList(head));
}

ListNode *SortList(ListNode *head)
{
    if (!head || !head->next)
        return head;
    ListNode *odd = head;
    ListNode *oddBackUp = odd;
    ListNode *even = head->next;
    ListNode *evenBackUp = even;
    ListNode *temp = head->next->next;
    int count = 0;

    // divide list to even list and odd list
    while (temp != nullptr)
    {
        if (count % 2 == 0)
        {
            odd->next = temp;
            odd = odd->next;
        }
        else
        {
            even->next = temp;
            even = even->next;
        }
        count++;
        temp = temp->next;
    }

    odd->next = nullptr;
    even->next = nullptr;

    odd = oddBackUp;
    even = evenBackUp;

    // Reverse even list
    ListNode *prev = nullptr;
    ListNode *later = even;
    while (later)
    {
        ListNode *next = later->next;

        later->next = prev;
        prev = later;
        later = next;
    }
    even = prev;

    // merge two list
    ListNode *dummyHead = new ListNode(-1);
    temp = dummyHead;
    while (odd && even)
    {
        if (odd->val <= even->val)
        {
            temp->next = odd;
            odd = odd->next;
        }
        else
        {
            temp->next = even;
            even = even->next;
        }

        temp = temp->next;
    }

    if (odd)
        temp->next = odd;
    else if (even)
        temp->next = even;

    return dummyHead->next;
}