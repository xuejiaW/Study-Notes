// 复原IP地址

// 难度：中等

// Tags:

// string | back tracking

// 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

// 有效的 IP 地址正好由四个整数（每个整数位于 0 到 255 之间组成），整数之间用 '.' 分隔。


// 示例:

// 输入: "25525511135"
// 输出: ["255.255.11.135", "255.255.111.35"]

#include <string>
#include <vector>
#include <unordered_set>
#include "debug.h"

using namespace std;

vector<string> restoreIpAddresses(string s);
void TestRestoreIpAddress()
{
    // vector<string> result = restoreIpAddresses("25525511135");
    vector<string> result = restoreIpAddresses("0000");
    // vector<string> result = restoreIpAddresses("010010");

    DebugVector(result);
}

// Version: back Tracking
void backTracking(vector<string> &result, string solution, string s, int part);
vector<string> restoreIpAddresses(string s)
{
    vector<string> result;
    backTracking(result, "", s, 0);
    return result;
}

void backTracking(vector<string> &result, string solution, string s, int part)
{
    int sSize = s.size();
    if (part == 4 || sSize == 0)
    {
        if (sSize == 0 && part == 4)
            result.push_back(solution);
        return;
    }

    int curr = 0;
    string temp = part == 0 ? "" : (solution + ".");
    backTracking(result, temp + s.substr(0, 1), s.substr(1), part + 1);

    if (s[0] == '0')
        return;

    if (sSize >= 2)
        backTracking(result, temp + s.substr(0, 2), s.substr(2), part + 1);

    if (sSize >= 3 && (curr = stoi(s.substr(0, 3))) <= 255)
        backTracking(result, temp + s.substr(0, 3), s.substr(3), part + 1);
}
