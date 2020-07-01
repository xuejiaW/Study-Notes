// 两数相加 II

// 难度：中等

// Tags
// linked-list

// 给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

// 你可以假设除了数字 0 之外，这两个数字都不会以零开头。

// 进阶：

// 如果输入链表不能修改该如何处理？换句话说，你不能对列表中的节点进行翻转。

// 示例：

// 输入：(7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
// 输出：7 -> 8 -> 0 -> 7

#include "parser.h"
#include "debug.h"
#include <stack>

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2);

void TestAddTwoNum()
{
    ListNode *l1 = parse2List("[7,2,4,3]");
    ListNode *l2 = parse2List("[5,6,4]");
    ListNode *result = addTwoNumbers(l1, l2);
    DebugListNode(result);
}

// Version: using reverse
// ListNode *reverseList(ListNode *head);
// ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
// {
//     ListNode *reverseL1 = reverseList(l1), *reverseL2 = reverseList(l2);

//     ListNode *dummyHead = new ListNode(-1);
//     ListNode *temp = dummyHead;
//     int over = 0;

//     while (reverseL1 || reverseL2 || over)
//     {
//         int curr = ((reverseL1 ? reverseL1->val : 0) + (reverseL2 ? reverseL2->val : 0) + over);
//         temp->next = new ListNode(curr % 10);
//         over = curr / 10;
//         if (reverseL1)
//             reverseL1 = reverseL1->next;
//         if (reverseL2)
//             reverseL2 = reverseL2->next;
//         temp = temp->next;
//     }

//     return reverseList(dummyHead->next);
// }

// ListNode *reverseList(ListNode *head)
// {
//     if (!head)
//         return head;

//     ListNode *prev = nullptr;
//     ListNode *later = head;
//     while (later)
//     {
//         ListNode *next = later->next;
//         later->next = prev;
//         prev = later;
//         later = next;
//     }
//     return prev;
// }

// Version, not reversing but with vector
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    if (!l1)
        return l2;
    if (!l2)
        return l1;

    stack<int> l1Stack, l2Stack;

    while (l1)
    {
        l1Stack.push(l1->val);
        l1 = l1->next;
    }

    while (l2)
    {
        l2Stack.push(l2->val);
        l2 = l2->next;
    }

    int over = 0;

    ListNode *currNode = nullptr;
    ListNode *temp = nullptr;
    while (!l1Stack.empty() || !l2Stack.empty() || over)
    {
        int curr = (!l1Stack.empty() ? l1Stack.top() : 0) + (!l2Stack.empty() ? l2Stack.top() : 0) + over;
        over = curr / 10;
        currNode = new ListNode(curr % 10);
        currNode->next = temp;
        temp = currNode;

        if (!l1Stack.empty())
            l1Stack.pop();
        if (!l2Stack.empty())
            l2Stack.pop();
    }
    return currNode;
}
