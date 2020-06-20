// 反转链表

// 难度：简单

// Tags:
// two-pointer | list

// 反转一个单链表。

// 示例:

// 输入: 1->2->3->4->5->NULL
// 输出: 5->4->3->2->1->NULL

#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *reverseList(ListNode *head);

void TestReverseList()
{
    ListNode *node1 = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    ListNode *node3 = new ListNode(3);
    ListNode *node4 = new ListNode(4);
    ListNode *node5 = new ListNode(5);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    ListNode *result = reverseList(node1);
    cout << "after result" << endl;
    while (result != nullptr)
    {
        cout << result->val << endl;
        result = result->next;
    }
}

// // Version: copy
// ListNode *reverseList(ListNode *head)
// {
//     ListNode *result = nullptr;

//     while (head != nullptr)
//     {
//         ListNode *node = new ListNode(head->val);
//         node->next = result;
//         result = node;

//         head = head->next;
//     }
//     return result;
// }

// // Version: iterative with two-pointer
// ListNode *reverseList(ListNode *head)
// {
//     ListNode *former = nullptr;
//     ListNode *later = head;

//     ListNode *temp = nullptr;

//     while (later != nullptr)
//     {
//         temp = later->next;

//         later->next = former;
//         former = later;
//         later = temp;
//     }

//     return former;
// }

// Version: recurrance
ListNode *reverseList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode *p = reverseList(head->next); // to make the list from head->next reversed
    head->next->next = head;
    head->next = nullptr;
    return p;
}
// https: //leetcode-cn.com/problems/reverse-linked-list/solution/fan-zhuan-lian-biao-by-leetcode/