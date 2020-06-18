#include <vector>
#include <deque>
#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

vector<int> reversePrint(ListNode *head);

void TestReversePrint()
{
    ListNode *head = new ListNode(1);
    ListNode *node1 = new ListNode(3);
    ListNode *node2 = new ListNode(2);
    head->next = node1;
    node1->next = node2;

    vector<int> result = reversePrint(head);
    for (const int &i : result)
        cout << i << " ";
}

// // Version: use insert
// vector<int> reversePrint(ListNode *head)
// {
//     vector<int> result;
//     while (head != nullptr)
//     {
//         result.insert(result.begin(), head->val);
//         head = head->next;
//     }
//     return result;
// }

// Version: use deque
vector<int> reversePrint(ListNode *head)
{
    deque<int> resultQueue;
    while (head != nullptr)
    {
        resultQueue.push_front(head->val);
        head = head->next;
    }
    return vector<int>(resultQueue.begin(),resultQueue.end());
}