// 实现 Trie (前缀树)

// 难度：中等

// Tags
// design | trie

// 实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。

// 示例:

// Trie trie = new Trie();

// trie.insert("apple");
// trie.search("apple");   // 返回 true
// trie.search("app");     // 返回 false
// trie.startsWith("app"); // 返回 true
// trie.insert("app");   
// trie.search("app");     // 返回 true
// 说明:

// 你可以假设所有的输入都是由小写字母 a-z 构成的。
// 保证所有输入均为非空字符串。


#include "parser.h"
#include "debug.h"
#include <set>

// // Version: using set
// class Trie
// {
// public:
//     /** Initialize your data structure here. */
//     Trie() : stringSet(set<string>())
//     {
//     }

//     /** Inserts a word into the trie. */
//     void insert(string word)
//     {
//         stringSet.insert(word);
//     }

//     /** Returns if the word is in the trie. */
//     bool search(string word)
//     {
//         return stringSet.find(word) != stringSet.end();
//     }

//     /** Returns if there is any word in the trie that starts with the given prefix. */
//     bool startsWith(string prefix)
//     {
//         int prefixSize = prefix.size();
//         for (const string &str : stringSet)
//         {
//             int strSize = str.size();

//             if (prefixSize > strSize)
//                 continue;

//             bool match = true;
//             for (int i = 0; i != prefixSize; ++i)
//             {
//                 if (prefix[i] != str[i])
//                 {
//                     match = false;
//                     break;
//                 }
//             }
//             if (match)
//             {
//                 return true;
//             }
//         }
//         return false;
//     }

// private:
//     set<string> stringSet;
// };

class Trie
{
public:
    Trie() : isEnd(false)
    {
        for (int i = 0; i != 26; ++i)
            nextChars[i] = nullptr;
    }

    void insert(string word)
    {
        Trie *curr = this;
        for (const char &c : word)
        {
            if (!curr->nextChars[c - 'a'])
                curr->nextChars[c - 'a'] = new Trie();
            curr = curr->nextChars[c - 'a'];
        }
        curr->isEnd = true;
    }

    bool search(string word)
    {
        Trie *curr = this;
        for (const char &c : word)
        {
            if (!curr->nextChars[c - 'a'])
                return false;
            curr = curr->nextChars[c - 'a'];
        }
        return curr->isEnd;
    }

    bool startsWith(string prefix)
    {
        Trie *curr = this;
        for (const char &c : prefix)
        {
            if (!curr->nextChars[c - 'a'])
                return false;
            curr = curr->nextChars[c - 'a'];
        }
        return true;
    }

private:
    bool isEnd;
    Trie *nextChars[26];
};

void TestTrie()
{
    Trie trie;

    // trie.insert("apple");
    // cout << trie.search("apple") << endl;   // 返回 true
    // cout << trie.search("app") << endl;     // 返回 false
    // cout << trie.startsWith("app") << endl; // 返回 true
    // trie.insert("app");
    // cout << trie.search("app") << endl; // 返回 true

    trie.insert("ab");
    cout << trie.search("abc") << endl;
    cout << trie.search("ab") << endl;
    cout << trie.startsWith("abc") << endl;
    cout << trie.startsWith("ab") << endl;
    trie.insert("ab");
    cout << trie.search("abc") << endl;
    cout << trie.startsWith("abc") << endl;
    trie.insert("abc");
    cout << trie.search("abc") << endl;
    cout << trie.startsWith("abc") << endl;
}
