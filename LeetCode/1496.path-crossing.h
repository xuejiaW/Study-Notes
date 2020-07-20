// 判断路径是否相交

// 难度：简单

// Tags:

// hash-table | string

// 给你一个字符串 path，其中 path[i] 的值可以是 'N'、'S'、'E' 或者 'W'，分别表示向北、向南、向东、向西移动一个单位。

// 机器人从二维平面上的原点 (0, 0) 处开始出发，按 path 所指示的路径行走。

// 如果路径在任何位置上出现相交的情况，也就是走到之前已经走过的位置，请返回 True ；否则，返回 False 。

// 示例 1：
// 输入：path = "NES"
// 输出：false 
// 解释：该路径没有在任何位置相交。

// 示例 2：
// 输入：path = "NESWW"
// 输出：true
// 解释：该路径经过原点两次。

#include "parser.h"
#include "debug.h"
#include <unordered_set>

bool isPathCrossing(string path);

void TestPathCrossing()
{
    cout << isPathCrossing("NNSWW");
}

bool isPathCrossing(string path)
{
    int upTimes = 0, rightTimes = 0;
    unordered_set<string> visited;
    visited.insert("0,0");
    for (int i = 0; i != path.size(); ++i)
    {
        if (path[i] == 'N')
            ++upTimes;
        else if (path[i] == 'S')
            --upTimes;
        else if (path[i] == 'E')
            ++rightTimes;
        else if (path[i] == 'W')
            --rightTimes;

        string coordinate = to_string(upTimes) + "," + to_string(rightTimes);

        if (visited.find(coordinate) != visited.end())
            return true;
        visited.insert(coordinate);
    }

    return false;
}