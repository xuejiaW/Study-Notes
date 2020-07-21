// 原始排序：

// 难度：中等

// Tags：
// Array

// 我手中有一堆扑克牌， 但是观众不知道它的顺序。
// 第一步， 我从牌顶拿出一张牌， 放到桌子上。
// 第二步， 我从牌顶再拿一张牌， 放在手上牌的底部。
// 第三步， 重复第一步的操作， 直到我手中所有的牌都放到了桌子上。
// 最后， 观众可以看到桌子上牌的顺序是：13\12\11\10\9\8\7\6\5\4\3\2\1 请问， 我刚开始拿在手里的牌的顺序是什么？

#include <vector>
#include <iostream>

using namespace std;

vector<int> GetOriginCardOrder(vector<int> &handledCard);

void TestOriginCardOrder()
{
    // vector<int> nums{13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> nums{2, 1};
    vector<int> result = GetOriginCardOrder(nums);
    for (const int &card : result)
        cout << card << endl;
}

class DoubleLinkedNode
{
public:
    DoubleLinkedNode(int v) : val(v), prev(NULL), next(NULL)
    {
    }
    int val;
    DoubleLinkedNode *prev;
    DoubleLinkedNode *next;
};

void RemoveBefore(DoubleLinkedNode *toRemove);
void InsertAfter(DoubleLinkedNode *toInsert, DoubleLinkedNode *head);
vector<int> GetOriginCardOrder(vector<int> &handledCard)
{
    vector<int> result;
    int cardsSize = handledCard.size();
    if (cardsSize == 0 || cardsSize == 1)
        return handledCard;
    if (cardsSize == 2)
    {
        result.push_back(handledCard[1]);
        result.push_back(handledCard[0]);
        return result;
    }

    DoubleLinkedNode *dummyHead = new DoubleLinkedNode(-1);
    DoubleLinkedNode *dummyTail = new DoubleLinkedNode(-1);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;

    DoubleLinkedNode *node = new DoubleLinkedNode(handledCard[0]);
    InsertAfter(node, dummyHead);
    node = new DoubleLinkedNode(handledCard[1]);
    InsertAfter(node, dummyHead);

    for (int i = 2; i != cardsSize; ++i)
    {
        DoubleLinkedNode *toRemove = dummyTail->prev;

        RemoveBefore(toRemove);
        InsertAfter(toRemove, dummyHead);

        DoubleLinkedNode *newNode = new DoubleLinkedNode(handledCard[i]);
        InsertAfter(newNode, dummyHead);
    }

    DoubleLinkedNode *temp = dummyHead->next;
    while (temp != dummyTail)
    {
        result.push_back(temp->val);
        temp = temp->next;
    }

    return result;
}

void InsertAfter(DoubleLinkedNode *toInsert, DoubleLinkedNode *head)
{
    toInsert->next = head->next;
    toInsert->prev = head;

    head->next->prev = toInsert;
    head->next = toInsert;
}

void RemoveBefore(DoubleLinkedNode *toRemove)
{
    DoubleLinkedNode *nextNode = toRemove->next;
    nextNode->prev->prev->next = nextNode;
    nextNode->prev = nextNode->prev->prev;
}