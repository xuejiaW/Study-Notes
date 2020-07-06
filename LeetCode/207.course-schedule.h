// 课程表

// 难度：中等

// Tags
// depth-first-search | breadth-first-search | graph | topological-sort

// 你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。

// 在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]

// 给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？

// 示例 1:
// 输入: 2, [[1,0]] 
// 输出: true
// 解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。

// 示例 2:
// 输入: 2, [[1,0],[0,1]]
// 输出: false
// 解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。

#include "parser.h"
#include "debug.h"

bool canFinish(int numCourses, vector<vector<int>> &prerequisites);

void TestCanFinish()
{
    int numCourses = 2;
    vector<vector<int>> prerequisites{{1, 0}};
    bool result = canFinish(numCourses, prerequisites);
    cout << result << endl;
}

// // Version: BFS
// bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
// {
//     vector<int> reliesNum(numCourses); // reliesNum[0] -> course 0 relyes how many courses
//     vector<vector<int>> graphics(numCourses, vector<int>());
//     queue<int> nonRelyCourses;

//     for (vector<int> &requisite : prerequisites)
//     {
//         reliesNum[requisite[0]]++;
//         graphics[requisite[1]].push_back(requisite[0]);
//     }

//     for (int i = 0; i != numCourses; ++i)
//     {
//         if (reliesNum[i] == 0)
//             nonRelyCourses.push(i);
//     }

//     while (!nonRelyCourses.empty())
//     {
//         numCourses--;
//         int course = nonRelyCourses.front();
//         nonRelyCourses.pop();
//         vector<int> &reliedCourses = graphics[course];
//         for (const int &course : reliedCourses)
//         {
//             if (--reliesNum[course] == 0)
//                 nonRelyCourses.push(course);
//         }
//     }

//     return numCourses == 0;
// }

// Version: DFS
// TODO
// bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
// {
// }
