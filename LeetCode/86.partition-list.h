// 分隔链表

// Tags
// linked-list | two-pointers

// 给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。

// 你应当保留两个分区中每个节点的初始相对位置。

// 示例:

// 输入: head = 1->4->3->2->5->2, x = 3
// 输出: 1->2->2->4->3->5

#include "parser.h"
#include "debug.h"

ListNode *partition(ListNode *head, int x);

void TestPartition()
{
    ListNode *head = parse2List("[1,4,3,2,5,2]");
    ListNode *result = partition(head, 3);
    DebugListNode(result);
}

ListNode *partition(ListNode *head, int x)
{
    queue<ListNode *> toInsert;
    bool insertPosFound = false;
    ListNode *insertPos = NULL;

    ListNode *prev = NULL;
    ListNode *later = head;
    while (later)
    {
        if (!insertPosFound && later->val >= x)
        {
            insertPos = prev;
            insertPosFound = true;
        }

        if (insertPosFound && later->val < x)
        {
            if (prev)
                prev->next = later->next;
            else
                head = later->next;
            toInsert.push(later);
        }
        else
            prev = prev == NULL ? head : prev->next;

        later = later->next;
    }

    while (!toInsert.empty())
    {
        ListNode *node = toInsert.front();
        toInsert.pop();

        if (insertPos != NULL)
        {
            node->next = insertPos->next;
            insertPos->next = node;
        }
        else
        {
            node->next = head;
            head = node;
        }

        insertPos = node;
    }

    return head;
}
