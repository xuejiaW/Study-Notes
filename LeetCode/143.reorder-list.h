// 重排链表

// Tags
// linked-list

// 给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
// 将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

// 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

// 示例 1:

// 给定链表 1->2->3->4, 重新排列为 1->4->2->3.
// 示例 2:

// 给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.

#include "parser.h"
#include "debug.h"
#include <deque>

void reorderList(ListNode *head);

void TestReorderList()
{
    ListNode *node = parse2List("[1,2]");
    reorderList(node);
    DebugListNode(node);
}

// // Version: using vector
// void reorderList(ListNode *head)
// {
//     vector<ListNode *> nodeVec;

//     ListNode *temp = head;
//     while (temp)
//     {
//         nodeVec.push_back(temp);
//         temp = temp->next;
//     }

//     int length = nodeVec.size();
//     if (length == 0 || length == 1 || length == 2)
//         return;

//     int begin = 1, end = length - 1;
//     bool fromEnd = true;
//     temp = head;
//     while (begin <= end)
//     {
//         temp->next = fromEnd ? nodeVec[end--] : nodeVec[begin++];
//         fromEnd = !fromEnd;
//         temp = temp->next;
//     }
//     temp->next = nullptr;
// }

// // Version: using deque
// void reorderList(ListNode *head)
// {
//     deque<ListNode *> nodeDeque;
//     ListNode *temp = head;
//     while (temp)
//     {
//         nodeDeque.push_back(temp);
//         temp = temp->next;
//     }

//     ListNode *dummyHead = new ListNode(-1);
//     temp = dummyHead;
//     bool fromStart = true;
//     while (!nodeDeque.empty())
//     {
//         temp->next = fromStart ? nodeDeque.front() : nodeDeque.back();
//         fromStart ? nodeDeque.pop_front() : nodeDeque.pop_back();
//         fromStart = !fromStart;
//         temp = temp->next;
//     }
//     temp->next = nullptr;
//     head = dummyHead->next;
// }

// Version: divide->revert->combine
void reorderList(ListNode *head)
{
    if (!head || !head->next)
        return;

    // find sec half
    ListNode *slow = head, *fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *prev = nullptr;
    ListNode *later = slow->next;
    slow->next = nullptr; //divide first and sec half, head is first half
    while (later)         // reverse second half
    {
        ListNode *next = later->next;
        later->next = prev;
        prev = later;
        later = next;
    }

    ListNode *secHalfHead = prev;

    ListNode *dummyHead = new ListNode(-1);
    ListNode *temp = dummyHead;

    // combination
    //Notes: first half length must equals to (even) or larger (odds) than sec half
    bool fromBegin = true;
    while (secHalfHead)
    {
        temp->next = fromBegin ? head : secHalfHead;
        fromBegin ? (head = head->next) : (secHalfHead = secHalfHead->next);
        temp = temp->next;
        fromBegin = !fromBegin;
    }
    temp->next = head;
    head = dummyHead->next;
}