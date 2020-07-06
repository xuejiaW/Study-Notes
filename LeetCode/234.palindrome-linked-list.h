// 回文链表

// 难度：简单

// Tags
// linked-list | two-pointers

// 请判断一个链表是否为回文链表。

// 示例 1:
// 输入: 1->2
// 输出: false

// 示例 2:
// 输入: 1->2->2->1
// 输出: true

#include "parser.h"
#include "debug.h"

bool isPalindrome(ListNode *head);
void TestIsPalindrome()
{
    // ListNode *node = parse2List("[1,2]");
    ListNode *node = parse2List("[1,2,3,2,1]");
    // ListNode *node = parse2List("[1]");
    cout << isPalindrome(node) << endl;
    DebugListNode(node);
}

// Version: with vector
// bool isPalindrome(ListNode *head)
// {
//     if (!head)
//         return true;

//     vector<int> nodeVec;
//     ListNode *temp = head;
//     while (temp)
//     {
//         nodeVec.push_back(temp->val);
//         temp = temp->next;
//     }

//     int begin = 0, end = nodeVec.size() - 1;
//     while (begin <= end)
//     {
//         if (nodeVec[begin++] != nodeVec[end--])
//             return false;
//     }

//     return true;
// }

// Version: reverse
bool isPalindrome(ListNode *head)
{
    if (!head)
        return true;
    ListNode *slow = head, *fast = head->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *middle = slow->next;
    slow->next = nullptr; // divide first and sec half

    // reverse sec half
    ListNode *prev = nullptr, *later = middle;
    while (later)
    {
        ListNode *next = later->next;

        later->next = prev;
        prev = later;
        later = next;
    }

    ListNode *secHalfHead = prev;
    ListNode *secHalfHeadTemp = secHalfHead;
    ListNode *headTemp = head;

    // compare the first half and reversed sec half
    bool result = true;
    while (secHalfHeadTemp && headTemp)
    {
        if (secHalfHeadTemp->val != headTemp->val)
        {
            result = false;
            break;
        }

        secHalfHeadTemp = secHalfHeadTemp->next;
        headTemp = headTemp->next;
    }

    // restore the sec half, although it will not affect the result
    prev = nullptr, later = secHalfHead;
    while (later)
    {
        ListNode *next = later->next;

        later->next = prev;
        prev = later;
        later = next;
    }
    slow->next = prev; // combine first and sec half

    return result;
}
