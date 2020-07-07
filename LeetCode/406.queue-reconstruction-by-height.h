// 根据身高重建队列

// 难度：中等

// Tags
// greedy

// 假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身高，k是排在这个人前面且身高大于或等于h的人数。 编写一个算法来重建这个队列。

// 注意：
// 总人数少于1100人。

// 示例

// 输入:
// [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

// 输出:
// [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

#include "parser.h"
#include "debug.h"
#include <map>
#include <set>

vector<vector<int>> reconstructQueue(vector<vector<int>> &people);
void TestReconstructQueue()
{
    vector<vector<int>> people = parser2VectorArray_int("[[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]");
    DebugVectorArray(people);
    cout << endl;
    vector<vector<int>> result = reconstructQueue(people);
    DebugVectorArray(result);
}

// Version: greedy
vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
{
    vector<vector<int>> result;

    sort(people.begin(), people.end(), [](const vector<int> &a, const vector<int> &b) {
        if (a[0] > b[0])
            return true;
        if (a[0] == b[0] && a[1] < b[1])
            return true;
        return false;
    });

    for (const vector<int> &person : people)
        result.insert(result.begin() + person[1], person);

    return result;
}
