// 删除链表的节点

// 难度：简单

// Tags:
// list | double-pointer

// 给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。

// 返回删除后的链表的头节点。

// 注意：此题对比原题有改动

// 示例 1:

// 输入: head = [4,5,1,9], val = 5
// 输出: [4,1,9]
// 解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
// 示例 2:

// 输入: head = [4,5,1,9], val = 1
// 输出: [4,5,9]
// 解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.

#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *deleteNode(ListNode *head, int val);

void TestDeleteNode()
{
    ListNode *node1 = new ListNode(4);
    ListNode *node2 = new ListNode(5);
    ListNode *node3 = new ListNode(1);
    ListNode *node4 = new ListNode(9);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    ListNode *result = deleteNode(node1, 9);
    // ListNode *result = node1;
    cout << "after result" << endl;
    while (result != nullptr)
    {
        cout << result->val << endl;
        result = result->next;
    }
}

ListNode *deleteNode(ListNode *head, int val)
{
    ListNode *temp = head;
    ListNode *prev = head;

    while (temp != nullptr)
    {
        if (temp->val == val)
        {
            if (temp == head) //prev is null
                head = head->next;
            else
                prev->next = temp->next;
        }

        prev = temp;
        temp = temp->next;
    }

    return head;
}