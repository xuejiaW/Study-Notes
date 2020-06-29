// 两数相加

// 难度：中等

// 标签：
// Math | linked-list

// 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

// 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

// 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

// 示例：

// 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
// 输出：7 -> 0 -> 8
// 原因：342 + 465 = 807

#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2);

void TestAddTwoNumbers()
{
    ListNode *node_2 = new ListNode(2);
    ListNode *node_4 = new ListNode(4);
    ListNode *node_3 = new ListNode(3);
    ListNode *node_5 = new ListNode(5);
    ListNode *node_6 = new ListNode(6);
    ListNode *node_4_1 = new ListNode(4);

    node_2->next = node_4;
    node_4->next = node_3;

    node_5->next = node_6;
    // node_6->next = node_4_1;
    ListNode *result = addTwoNumbers(node_2, node_5);
    while (result != nullptr)
    {
        cout << result->val << endl;
        result = result->next;
    }
}

// ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
// {
//     ListNode *result = new ListNode(-1);
//     ListNode *resultTemp = result;
//     int over = 0;
//     while (l1 && l2)
//     {
//         int sum = l1->val + l2->val + over;
//         resultTemp->val = sum % 10;
//         over = sum / 10;

//         l1 = l1->next;
//         l2 = l2->next;
//         if (l1 || l2)
//         {
//             resultTemp->next = new ListNode(-1);
//             resultTemp = resultTemp->next;
//         }
//     }

//     while (l1)
//     {
//         int sum = l1->val + over;
//         resultTemp->val = sum % 10;
//         over = sum / 10;
//         l1 = l1->next;

//         if (l1)
//         {
//             resultTemp->next = new ListNode(-1);
//             resultTemp = resultTemp->next;
//         }
//     }

//     while (l2)
//     {
//         int sum = l2->val + over;
//         resultTemp->val = sum % 10;
//         over = sum / 10;
//         l2 = l2->next;

//         if (l2)
//         {
//             resultTemp->next = new ListNode(-1);
//             resultTemp = resultTemp->next;
//         }
//     }

//     if (over)
//         resultTemp->next = new ListNode(over);

//     return result;
// }

// Version: optimism, more concise
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    ListNode *resultPrev = new ListNode(-1);
    ListNode *temp = resultPrev;
    int over = 0;
    while (l1 || l2)
    {
        int sum = over + (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
        over = sum / 10;

        temp->next = new ListNode(sum % 10);
        temp = temp->next;

        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }
    if (over)
        temp->next = new ListNode(1);
    return resultPrev->next;
}