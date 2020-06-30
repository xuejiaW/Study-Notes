// 删除链表的倒数第N个节点

// 难度：中等

// Tags:

// linked list | two pointer_safety

// 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

// 示例：

// 给定一个链表: 1->2->3->4->5, 和 n = 2.

// 当删除了倒数第二个节点后，链表变为 1->2->3->5.
// 说明：

// 给定的 n 保证是有效的。

#include "parser.h"
#include "debug.h"

ListNode *removeNthFromEnd(ListNode *head, int n);
void TestRemoveNthFromEnd()
{
    // ListNode *node = parse2List("[1,2,3,4,5]");
    ListNode *node = parse2List("[1]");
    node = removeNthFromEnd(node, 1);
    DebugListNode(node);
}

// // Version: hashMap
// ListNode *removeNthFromEnd(ListNode *head, int n)
// {
//     if (!head)
//         return head;

//     vector<ListNode *> nodeVec;

//     ListNode *headTemp = head;
//     while (headTemp)
//     {
//         nodeVec.push_back(headTemp);
//         headTemp = headTemp->next;
//     }

//     int nodeLength = nodeVec.size();
//     cout << "length is " << nodeLength << endl;

//     if (n == nodeLength)
//         return head->next;
//     else if (n < nodeLength)
//         nodeVec[nodeLength - n - 1]->next = nodeVec[nodeLength - n]->next;

//     return head;
// }

// Version: two pointer
ListNode *removeNthFromEnd(ListNode *head, int n)
{
    if (!head)
        return head;

    ListNode *backUp = head, *fast = head, *slow = head;

    while (fast->next != nullptr && n--)
        fast = fast->next;

    if (n == 1) // n equals to list length
        return head->next;
    if (n > 1) //n larger than list length
        return head;

    while (fast->next != nullptr)
    {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = slow->next->next;

    return backUp;
}