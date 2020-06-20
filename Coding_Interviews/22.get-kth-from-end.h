// 链表中倒数第k个节点

// 难度：简单

// tags:

// hash-map | two-pointer

// 输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。

//  

// 示例：

// 给定一个链表: 1->2->3->4->5, 和 k = 2.

// 返回链表 4->5.

#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *getKthFromEnd(ListNode *head, int k);

void TestGetKthFromEnd()
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

    ListNode *result = getKthFromEnd(node1, 2);
    cout << "after result" << endl;
    while (result != nullptr)
    {
        cout << result->val << endl;
        result = result->next;
    }
}

// // Version: hash-map
// ListNode *getKthFromEnd(ListNode *head, int k)
// {
//     vector<ListNode *> nodeVec;
//     ListNode *temp = head;

//     while (temp != nullptr)
//     {
//         nodeVec.push_back(temp);
//         temp = temp->next;
//     }

//     if (k > nodeVec.size())
//         return head;
//     else
//         return nodeVec[nodeVec.size() - k];
// }

// Version: two-pointer
ListNode *getKthFromEnd(ListNode *head, int k)
{
    ListNode *former = head;
    ListNode *later = head;

    int gap = 0;
    while ((gap++) != k && later != nullptr)
        later = later->next;

    while (later != nullptr)
    {
        later = later->next;
        former = former->next;
    }

    return former;
}