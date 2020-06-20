// 合并两个有序链表

// 难度：简单

// Tags:

// list

// 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

//  

// 示例：

// 输入：1->2->4, 1->3->4
// 输出：1->1->2->3->4->4


#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2);

void TestMergeTwoSortedList()
{
    ListNode *node1 = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    ListNode *node3 = new ListNode(4);

    node1->next = node2;
    node2->next = node3;

    ListNode *node4 = new ListNode(1);
    ListNode *node5 = new ListNode(3);
    ListNode *node6 = new ListNode(4);
    ListNode *node7 = new ListNode(8);

    node4->next = node5;
    node5->next = node6;
    node6->next = node7;

    ListNode *result = mergeTwoLists(node1, node4);
    cout << "after result" << endl;
    while (result != nullptr)
    {
        cout << result->val << endl;
        result = result->next;
    }
}

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    if (l1 == nullptr)
        return l2;
    if (l2 == nullptr)
        return l1;

    ListNode *resultTemp = new ListNode(-1);
    ListNode *result = resultTemp;

    result = resultTemp;

    while (l1 != nullptr && l2 != nullptr)
    {
        if (l1->val < l2->val)
        {
            resultTemp->next = l1;
            l1 = l1->next;
        }
        else
        {
            resultTemp->next = l2;
            l2 = l2->next;
        }
        resultTemp = resultTemp->next;
    }

    if (l1 != nullptr)
        resultTemp->next = l1;
    else
        resultTemp->next = l2;

    return result->next;
}
