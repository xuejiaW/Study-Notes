// LFU缓存

// 难度：
// 困难

// Tags
// design

// 请你为 最不经常使用（LFU）缓存算法设计并实现数据结构。它应该支持以下操作：get 和 put。
// get(key) - 如果键存在于缓存中，则获取键的值（总是正数），否则返回 -1。
// put(key, value) - 如果键已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量时，则应该在插入新项之前，使最不经常使用的项无效。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除最久未使用的键。
// 「项的使用次数」就是自插入该项以来对其调用 get 和 put 函数的次数之和。使用次数会在对应项被移除后置为 0 。
// 进阶：
// 你是否可以在 O(1) 时间复杂度内执行两项操作？

// 示例：

// LFUCache cache = new LFUCache( 2 /* capacity (缓存容量) */ );

// cache.put(1, 1);
// cache.put(2, 2);
// cache.get(1);       // 返回 1
// cache.put(3, 3);    // 去除 key 2
// cache.get(2);       // 返回 -1 (未找到key 2)
// cache.get(3);       // 返回 3
// cache.put(4, 4);    // 去除 key 1
// cache.get(1);       // 返回 -1 (未找到 key 1)
// cache.get(3);       // 返回 3
// cache.get(4);       // 返回 4

#include <unordered_map>
#include "parser.h"
#include "debug.h"

class DoubleLinkedNode
{
public:
    int key;
    int value;
    int times;
    DoubleLinkedNode *prev;
    DoubleLinkedNode *next;
    DoubleLinkedNode(int k, int v) : key(k), value(v), times(1), prev(nullptr), next(nullptr) {}
    DoubleLinkedNode() : key(-1), value(-1), times(0), prev(nullptr), next(nullptr) {}
};

class LFUCache
{
public:
    LFUCache(int capacity)
    {
        maxCapacity = capacity;
        currNodesNum = 0;
        dummyHead = new DoubleLinkedNode();
        dummyTail = new DoubleLinkedNode();
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
        time2FirstNodes[0] = dummyTail;
    }

    int get(int key)
    {
        if (maxCapacity == 0)
            return -1;
        if (key2Nodes.find(key) == key2Nodes.end())
            return -1;
        else
        {
            DoubleLinkedNode *nodes = key2Nodes[key];
            RemoveNodesFromCurrPos(nodes);

            nodes->times++;
            AddNodesBeforeFirstNodesOfTimes(nodes);

            return nodes->value;
        }
    }

    void put(int key, int value)
    {
        if (maxCapacity == 0)
            return;
        if (key2Nodes.find(key) != key2Nodes.end())
        {
            DoubleLinkedNode *nodes = key2Nodes[key];
            RemoveNodesFromCurrPos(nodes);

            nodes->value = value;
            nodes->times++;
            AddNodesBeforeFirstNodesOfTimes(nodes);
        }
        else
        {
            if (currNodesNum < maxCapacity)
            {
                currNodesNum++;
            }
            else
            {
                DoubleLinkedNode *toDelete = dummyTail->prev;
                key2Nodes.erase(toDelete->key);
                RemoveNodesFromCurrPos(toDelete);
                delete toDelete;
            }

            DoubleLinkedNode *nodes = new DoubleLinkedNode(key, value);
            AddNodesBeforeFirstNodesOfTimes(nodes);
            key2Nodes.insert({key, nodes});
        }
    }

private:
    int maxCapacity;
    int currNodesNum;
    unordered_map<int, DoubleLinkedNode *> key2Nodes;
    unordered_map<int, DoubleLinkedNode *> time2FirstNodes;
    DoubleLinkedNode *dummyHead;
    DoubleLinkedNode *dummyTail;

    void RemoveNodesFromCurrPos(DoubleLinkedNode *nodes)
    {
        // remove from currPos;
        if (time2FirstNodes.find(nodes->times) != time2FirstNodes.end() && time2FirstNodes[nodes->times] == nodes)
        {
            if (nodes->next->times == nodes->times)
                time2FirstNodes[nodes->times] = nodes->next;
            else
                time2FirstNodes.erase(nodes->times);
        }

        nodes->next->prev = nodes->prev;
        nodes->prev->next = nodes->next;
    }

    void AddNodesBeforeFirstNodesOfTimes(DoubleLinkedNode *nodes)
    {
        DoubleLinkedNode *firstNodes = nullptr;

        for (int times = nodes->times; times >= 0; --times)
        {
            if (time2FirstNodes.find(times) != time2FirstNodes.end())
            {
                firstNodes = time2FirstNodes[times];
                break;
            }
        }

        time2FirstNodes[nodes->times] = nodes;

        // insert to the first element of the corresponding times
        firstNodes->prev->next = nodes;
        nodes->prev = firstNodes->prev;
        firstNodes->prev = nodes;
        nodes->next = firstNodes;
    }
};

void TestLFUCache()
{
    LFUCache *cache = new LFUCache(2 /* capacity (缓存容量) */);

    cache->put(1, 1);
    cache->put(2, 2);
    cout << cache->get(1) << endl; // 返回 1
    cache->put(3, 3);              // 去除 key 2
    cout << cache->get(2) << endl; // 返回 -1 (未找到key 2)
    cout << cache->get(3) << endl; // 返回 3
    cache->put(4, 4);              // 去除 key 1
    cout << cache->get(1) << endl; // 返回 -1 (未找到 key 1)
    cout << cache->get(3) << endl; // 返回 3
    cout << cache->get(4) << endl; // 返回 4

    // cache->put(2, 2);
    // cache->put(1, 1);
    // cout << cache->get(2) << endl;
    // cout << cache->get(1) << endl;
    // cout << cache->get(2) << endl;
    // cache->put(3, 3);
    // cache->put(4, 4);
    // cout << cache->get(3) << endl;
    // cout << cache->get(2) << endl;
    // cout << cache->get(1) << endl;
    // cout << cache->get(4) << endl;

}