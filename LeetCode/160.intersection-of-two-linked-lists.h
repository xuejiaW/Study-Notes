// 相交链表

// 难度：简单

// Tags：
// linked-list

// 输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
// 输出：Reference of the node with value = 8
// 输入解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
// 从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。
// 在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。

#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);
void TestGetIntersectionNode()
{
    ListNode *node8 = new ListNode(8);
    ListNode *node4 = new ListNode(4);
    ListNode *node1_2 = new ListNode(1);
    ListNode *node5 = new ListNode(5);
    ListNode *node0 = new ListNode(0);
    ListNode *node1 = new ListNode(1);
    ListNode *node5_2 = new ListNode(5);

    node4->next = node1;
    node1->next = node8;

    node5_2->next = node0;
    node0->next = node1_2;
    node1_2->next = node8;

    node8->next = node5;

    ListNode *node = getIntersectionNode(node5_2, node4);
    if (node == nullptr)
        cout << " no intersection" << endl;
    else
        cout << node->val << endl;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    ListNode *tempA = headA, *tempB = headB;
    while (tempA != tempB)
    {
        tempA = tempA == nullptr ? headB : tempA->next;
        tempB = tempB == nullptr ? headA : tempB->next;
    }

    return tempA;
}
