// 合并K个排序链表

// 难度：
// 困难

// Tags:
// linked-list | divide-and-conquer

// 合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。

// 示例:

// 输入:
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// 输出: 1->1->2->3->4->4->5->6

#include "parser.h"
#include "debug.h"

void TestMergeKLists()
{
    vector<ListNode*> listsVec;
    listsVec.push_back(parse2List("[1,4,5]"));
    listsVec.push_back(parse2List("[1,3,4]"));
    listsVec.push_back(parse2List("[2,6]"));

    DebugListNode(mergeKLists(listsVec));
}


ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode* dummyHead=new ListNode(-1);
    ListNode* temp=dummyHead;

    while (l1 && l2)
    {
        if (l1->val<l2->val)
        {
            temp->next=l1;
            l1=l1->next;
        }
        else
        {
            temp->next=l2;
            l2=l2->next;
        }

        temp=temp->next;
    }

    temp->next=l1?l1:l2;

    temp=dummyHead->next;
    dummyHead->next=NULL;

    delete dummyHead;

    return temp;
}

ListNode* mergeKLists(vector<ListNode*>& lists, int beginIndex, int endIndex)
{
    int listsSize=endIndex-beginIndex+1;
    if (beginIndex>endIndex)
        return NULL;
    if (beginIndex==endIndex)
        return lists[beginIndex];
    if (endIndex-beginIndex==1)
        return mergeTwoLists(lists[beginIndex], lists[endIndex]);

    ListNode* firstPart=mergeKLists(lists, beginIndex, beginIndex+listsSize/2);
    ListNode* secPart=mergeKLists(lists, beginIndex+listsSize/2+1, endIndex);

    return mergeTwoLists(firstPart, secPart);

}

ListNode* mergeKLists(vector<ListNode*>& lists)
{
    return mergeKLists(lists, 0, lists.size()-1);
}