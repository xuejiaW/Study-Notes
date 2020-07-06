// LRU缓存机制

// 难度：中等

// Tags:
// design

// 运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。

// 获取数据 get(key) - 如果关键字 (key) 存在于缓存中，则获取关键字的值（总是正数），否则返回 -1。
// 写入数据 put(key, value) - 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字/值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

// 示例:

// LRUCache cache = new LRUCache( 2 /* 缓存容量 */ );

// cache.put(1, 1);
// cache.put(2, 2);
// cache.get(1);       // 返回  1
// cache.put(3, 3);    // 该操作会使得关键字 2 作废
// cache.get(2);       // 返回 -1 (未找到)
// cache.put(4, 4);    // 该操作会使得关键字 1 作废
// cache.get(1);       // 返回 -1 (未找到)
// cache.get(3);       // 返回  3
// cache.get(4);       // 返回  4


#include "debug.h"
#include <stack>
#include <unordered_map>

struct DoubleLinkedList
{
    int key, value;
    DoubleLinkedList *prev;
    DoubleLinkedList *next;
    DoubleLinkedList() : key(0), value(0), prev(nullptr), next(nullptr){};
    DoubleLinkedList(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr){};
};

class LRUCache
{
public:
    LRUCache(int capacity) : maxSize(capacity), dummyHead(new DoubleLinkedList()), dummyTail(new DoubleLinkedList())
    {
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
    }

    int get(int key)
    {
        if (key2NodeMap.find(key) != key2NodeMap.end())
        {
            DoubleLinkedList *node = key2NodeMap[key];

            // Move to head
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->prev = dummyHead;
            node->next = dummyHead->next;
            dummyHead->next->prev = node;
            dummyHead->next = node;
            // cout << "value is " << node->value << endl;
            return node->value;
        }
        else
        {
            // cout << "value is " << -1 << endl;
            return -1;
        }
    }

    void put(int key, int value)
    {
        if (key2NodeMap.find(key) != key2NodeMap.end())
        {
            DoubleLinkedList *node = key2NodeMap[key];
            node->value = value;

            // Move to head
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->prev = dummyHead;
            node->next = dummyHead->next;
            dummyHead->next->prev = node;
            dummyHead->next = node;
        }
        else
        {
            if (key2NodeMap.size() >= maxSize)
            {
                //delete last node
                DoubleLinkedList *toDelete = dummyTail->prev;
                key2NodeMap.erase(toDelete->key);
                dummyTail->prev->prev->next = dummyTail;
                dummyTail->prev = dummyTail->prev->prev;
                delete toDelete;
            }

            DoubleLinkedList *node = new DoubleLinkedList(key, value);
            key2NodeMap[key] = node;

            // Add to head
            node->next = dummyHead->next;
            node->prev = dummyHead;
            dummyHead->next->prev = node;
            dummyHead->next = node;
        }
    }

private:
    int maxSize = 0;
    unordered_map<int, DoubleLinkedList *> key2NodeMap;
    DoubleLinkedList *dummyHead;
    DoubleLinkedList *dummyTail;
};

void TestLRUCache()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);
    cache.put(3, 3);
    cache.get(2);
    cache.put(4, 4);
    cache.get(1);
    cache.get(3);
    cache.get(4);
}
