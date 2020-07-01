// 排序链表

// Tags
// linked-list | sort

// 在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

// 示例 1:

// 输入: 4->2->1->3
// 输出: 1->2->3->4
// 示例 2:

// 输入: -1->5->3->4->0
// 输出: -1->0->3->4->5

#include "parser.h"
#include "debug.h"

ListNode *sortList(ListNode *head);

void TestSortList()
{
    // ListNode *node = parse2List("[4,2,1,3]");
    ListNode *node = parse2List("[-1,5,3,4,0]");
    node = sortList(node);
    DebugListNode(node);
}

// // Version: two pointer, O(n^2)
// ListNode *sortList(ListNode *head)
// {
//     if (!head)
//         return head;

//     ListNode *toInsert = head->next;
//     head->next = nullptr;

//     ListNode *rightEnd = head, *leftBegin = head;
//     while (toInsert)
//     {
//         ListNode *curr = toInsert;
//         toInsert = toInsert->next;
//         if (curr->val > rightEnd->val)
//         {
//             rightEnd->next = curr;
//             curr->next = nullptr;
//             rightEnd = curr;
//         }
//         else if (curr->val < leftBegin->val)
//         {
//             curr->next = leftBegin;
//             leftBegin = curr;
//         }
//         else
//         {
//             ListNode *temp = curr->val < head->val ? leftBegin : head;
//             ListNode *end = curr->val < head->val ? head : rightEnd;
//             while (temp != end && curr->val > temp->next->val)
//                 temp = temp->next;
//             curr->next = temp->next;
//             temp->next = curr;
//         }
//     }
//     return leftBegin;
// }

// // Version: Merge sorting, recurrance
// ListNode *sortList(ListNode *head)
// {
//     if (!head || !head->next)
//         return head;

//     ListNode *fast = head->next, *slow = head;
//     while (fast && fast->next)
//     {
//         slow = slow->next;
//         fast = fast->next->next;
//     }

//     ListNode *rightPartHead = slow->next;
//     slow->next = nullptr; // divide

//     ListNode *orderedLeftPart = sortList(head);
//     ListNode *orderedRightPart = sortList(rightPartHead);

//     ListNode *resultPrev = new ListNode(0);
//     ListNode *temp = resultPrev;

//     while (orderedLeftPart && orderedRightPart)
//     {
//         if (orderedLeftPart->val < orderedRightPart->val)
//         {
//             temp->next = orderedLeftPart;
//             orderedLeftPart = orderedLeftPart->next;
//         }
//         else
//         {
//             temp->next = orderedRightPart;
//             orderedRightPart = orderedRightPart->next;
//         }
//         temp = temp->next;
//     }

//     temp->next = orderedLeftPart ? orderedLeftPart : orderedRightPart;

//     return resultPrev->next;
// }

// Version: Merge sorting, iterative
ListNode *sortList(ListNode *head)
{
    if (!head)
        return head;
    ListNode *remainingList = head;
    int length = 0;
    while (remainingList)
    {
        ++length;
        remainingList = remainingList->next;
    }
    int groupSize = 1;

    ListNode *dummyResult = new ListNode(0);
    dummyResult->next = head;

    for (int groupSize = 1; groupSize < length; groupSize *= 2)
    {
        ListNode *toInsert = dummyResult;
        remainingList = dummyResult->next;
        while (remainingList)
        {
            // divide left and right part
            ListNode *left = remainingList;
            int partRemaining = groupSize;
            while (remainingList && partRemaining)
                remainingList = remainingList->next, partRemaining--;
            if (partRemaining != 0) // there is no right part
                break;

            ListNode *right = remainingList;
            partRemaining = groupSize;
            while (remainingList && partRemaining)
                remainingList = remainingList->next, partRemaining--;

            // merge part
            int leftPartSize = groupSize;
            int rightPartSize = groupSize - partRemaining;
            while (leftPartSize && rightPartSize)
            {
                if (left->val < right->val)
                {
                    toInsert->next = left;
                    left = left->next;
                    --leftPartSize;
                }
                else
                {
                    toInsert->next = right;
                    right = right->next;
                    --rightPartSize;
                }
                toInsert = toInsert->next;
            }
            // merge left part remaining
            while (leftPartSize-- > 0)
            {
                toInsert->next = left;
                left = left->next;
                toInsert = toInsert->next;
            }
            /// merge right part remaining
            while (rightPartSize-- > 0)
            {
                toInsert->next = right;
                right = right->next;
                toInsert = toInsert->next;
            }

            // combine list together
            toInsert->next = remainingList;
        }
    }

    return dummyResult->next;
}