// 复制带随机指针的链表

// 难度：中等

// 标签：
// 哈希表 | 链表

// 给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。

// 要求返回这个链表的 深拷贝。 

// 我们用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

// val：一个表示 Node.val 的整数。
// random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。

// 示例 1:

// 输入: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// 输出: [[7,null],[13,0],[11,4],[10,2],[1,0]]

// 示例 2:

// 输入: head = [[1,1],[2,1]]
// 输出: [[1,1],[2,1]]

// 示例 3:

// 输入: head = [[3,null],[3,0],[3,null]]
// 输出: [[3,null],[3,0],[3,null]]

// 示例 4:

// 输入: head = []
// 输出: []
// 解释: 给定的链表为空（空指针），因此返回 null。

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

// // Version: using vector and unordered_map
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

// Version: only using list
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
