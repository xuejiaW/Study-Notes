// 用 Rand7() 实现 Rand10()

// 难度：中等

// Tags：
// Design

// 已有方法 rand7 可生成 1 到 7 范围内的均匀随机整数，试写一个方法 rand10 生成 1 到 10 范围内的均匀随机整数。

// 不要使用系统的 Math.random() 方法。

#include "parser.h"
#include "debug.h"

int rand10();

void TestRand10()
{
    cout << rand10();
}
int rand7()
{
    return 1 + rand() % 7;
}

int rand10()
{
    while (true)
    {
        int val = (rand7() - 1) * 7 + rand7(); // get 1-49
        if (val <= 40)
            return 1 + (val) % 10;
    }
}

// // Version: with optimize
int rand10()
{
    while (true)
    {
        int val = (rand7() - 1) * 7 + rand7(); // get 1-49
        if (val <= 40)
            return 1 + val % 10;

        val = (val - 40) * 7 + rand7(); // get 1-63
        if (val <= 60)
            return 1 + val % 10;

        val = (val - 60) * 7 + rand7(); // get 1-21
        if (val <= 20)
            return 1 + val % 10;
    }
}
