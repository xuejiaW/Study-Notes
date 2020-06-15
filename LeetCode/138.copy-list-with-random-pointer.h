// Tags: 
// hash-table | linked-list

// A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

// Return a deep copy of the list.

// The Linked List is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:
//     val: an integer representing Node.val
//     random_index: the index of the node (range from 0 to n-1) where random pointer points to, or null if it does not point to any node.

// Example 1:

// Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

// Example 2:

// Input: head = [[1,1],[2,1]]
// Output: [[1,1],[2,1]]

// Example 3:

// Input: head = [[3,null],[3,0],[3,null]]
// Output: [[3,null],[3,0],[3,null]]

// Example 4:

// Input: head = []
// Output: []
// Explanation: Given linked list is empty (null pointer), so return null.

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node *copyRandomList(Node *head);

void TestCopyRandomList()
{
    vector<Node *> nodeVec;

    nodeVec.push_back(new Node(7));
    nodeVec.push_back(new Node(13));
    nodeVec.push_back(new Node(11));
    nodeVec.push_back(new Node(10));
    nodeVec.push_back(new Node(1));

    int nodesRandom[5]{-1, 0, 4, 2, 0};
    for (int i = 0; i != nodeVec.size(); ++i)
    {
        nodeVec[i]->random = (nodesRandom[i] == -1 ? nullptr : nodeVec[nodesRandom[i]]);
        nodeVec[i]->next = (i + 1) == nodeVec.size() ? nullptr : nodeVec[i + 1];
    }

    Node *n = copyRandomList(nodeVec[0]);
    cout << "after copy" << endl;
    while (n != nullptr)
    {
        cout << "Value is " << n->val << ", random  value is " << ((n->random == nullptr) ? -1 : n->random->val) << endl;
        n = n->next;
    }
}

// //Version: using vector and unordered_map
// Node *copyRandomList(Node *head)
// {
//     if (head == nullptr)
//         return nullptr;

//     vector<Node *> NodesVec;
//     unordered_map<Node *, int> nodePosMap;
//     int pos = 0;

//     Node *node = head;
//     while (node != nullptr)
//     {
//         NodesVec.push_back(new Node(node->val));
//         nodePosMap[node] = pos++;
//         node = node->next;
//     }

//     node = head;

//     int vecSize = NodesVec.size();
//     for (int i = 0; i != vecSize; ++i)
//     {
//         NodesVec[i]->random = node->random == nullptr ? nullptr : NodesVec[nodePosMap[node->random]];
//         NodesVec[i]->next = (i + 1) == vecSize ? nullptr : NodesVec[i + 1];
//         node = node->next;
//     }

//     return NodesVec[0];
// }

//Version: only using list

Node *copyRandomList(Node *head)
{
    if (head == nullptr)
        return nullptr;

    Node *node = head;
    Node *nodeNext = head->next;
    while (node != nullptr)
    {
        //copy every node after itself
        //i.g. 7 -> 13 -> 5 ==> 7 -> 7 -> 13 -> 13 -> 5 -> 5
        nodeNext = node->next;

        node->next = new Node(node->val);
        node->next->next = nodeNext;

        node = nodeNext;
    }

    node = head;
    while (node != nullptr)
    {
        // set random for copied nodes
        if (node->random == nullptr)
        {
            node->next->random == nullptr;
        }
        else
        {
            node->next->random = node->random->next;
        }

        node = node->next->next;
    }

    node = head;
    Node *copiedHead = head->next;
    Node *result = copiedHead;

    while (node != nullptr)
    {
        // Split origin list and copied list
        node->next = node->next->next; // node->next is copied node so it must exist
        copiedHead->next = copiedHead->next == nullptr ? nullptr : copiedHead->next->next;

        node = node->next;
        copiedHead = copiedHead->next;
    }
    return result;
}
