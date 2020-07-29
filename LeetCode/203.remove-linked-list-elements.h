// 移除链表元素

// 难度：简单

// Tags
// linked-list

// 删除链表中等于给定值 val 的所有节点。

// 示例:

// 输入: 1->2->6->3->4->5->6, val = 6
// 输出: 1->2->3->4->5


#include "parser.h"
#include "debug.h"

ListNode *removeElements(ListNode *head, int val);

void TestRemoveElements()
{
    ListNode *list = parse2List("[1,2,6,3,4,5,6]");
    DebugListNode(removeElements(list, 6));
}

ListNode *removeElements(ListNode *head, int val)
{
    ListNode *prev = NULL;
    ListNode *curr = head;

    while (curr != NULL)
    {
        if (curr->val == val)
        {
            if (prev)
                prev->next = curr->next;
            else
                head = curr->next;
        }
        else
            prev = curr; // only set prev when the node's value is not val

        curr = curr->next;
    }

    return head;
}
